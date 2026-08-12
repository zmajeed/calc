// parser/calc1_parser.cpp

/*
MIT License

Copyright (c) 2024-2026 Zartaj Majeed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "lexer/calc1_lexer.h"
#include "calc1_parser.bison.h"

#include <stdlib.h>
#include <getopt.h>

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <istream>
#include <fstream>
#include <print>
#include <chrono>
#include <variant>
#include <utility>
#include <ranges>
#include <algorithm>
#include <map>

using namespace std;
using namespace chrono;

using namespace calc1;

void usage() {
  println("Usage: calc1 [-h | --help] [--debug] [--stats] [-e expr] [file]");
  println("Simple arithmetic expressions parser");
  println("Prints nothing if parse succeeds, otherwise prints an error message with line number");
  println("");
  println("Options:");
  println("-e: arithmetic expression, only one of -e or file argument is allowed");
  println("--debug: turns on Bison parser and Flex lexer debug traces, off by default");
  println("--stats: print timing stats on successful parse");
  println("--symbols: print symbol table");
  println("--help | -h: prints usage help");
}

int main(int argc, char* argv[])
{
  int debug = 0;
  int printStats = 0;
  int printSymbols = 0;
  string evalStr;
  

// need filename pointer to stick around for bison error messages that print filename and position
  auto inputName = make_unique<string>("stdin");

  option opts[] = {
    {"debug", no_argument, &debug, 1},
    {"stats", no_argument, &printStats, 1},
    {"symbols", no_argument, &printSymbols, 1},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
  };

  for(int i, optLetter; (optLetter = getopt_long(argc, argv, "e:h", opts, &i)) != -1;) {
    switch(optLetter) {
    case 0:
      break;
    case 'e':
      evalStr = optarg;
      break;
    case 'h':
      usage();
      return 0;
    case '?':
      usage();
      return 1;
    default:
      break;
    }
  }

  if(optind > argc || optind + 1 < argc) {
    usage();
    exit(1);
  }

  Calc1Lexer lexer;

// input stream must remain valid for lifetime of lexer
  variant<monostate, istringstream, ifstream> instrm;

// input can be string or exactly one file or keep default stdin
  if(!evalStr.empty()) {

    if(optind < argc) {
      usage();
      exit(1);
    }

    instrm.emplace<istringstream>(evalStr);
    lexer.switch_streams(get_if<istringstream>(&instrm));
    *inputName = "string";

  } else if(optind + 1 == argc) {

    const char* filename = argv[optind];
    ifstream filestrm;
    if(filename != "-"sv) {
      if(filestrm.open(filename); !filestrm) {
        println(stderr, "error opening file \"{}\"", filename);
        exit(1);
      }
      instrm = move(filestrm);
      lexer.switch_streams(get_if<ifstream>(&instrm));
      *inputName = filename;
    }
  }

  BisonParam bisonParam;
  LexParam lexParam{.loc = location(inputName.get())};

  duration<double> lexSec{};

  Calc1Parser parser(
    [&lexer, &lexSec](LexParam& lexParam) -> Calc1Parser::symbol_type {
      time_point<steady_clock> start = steady_clock::now();
      auto token = lexer.yylex(lexParam);
      time_point<steady_clock> end = steady_clock::now();
      lexSec += end - start;
      return token;
    },
    bisonParam,
    lexParam
  );

  lexer.set_debug(debug);
  parser.set_debug_level(debug);

  time_point<steady_clock> parseStart = steady_clock::now();
  auto ev = parser();
  time_point<steady_clock> parseEnd = steady_clock::now();

  if(ev != 0) {
    println(stderr, "parse failed");
    return ev;
  }

  println("{}", bisonParam.expr);

  if(printStats == 1) {
    duration<double> parseSec = parseEnd - parseStart;
    println("parse time: {:.9f} sec", parseSec.count());
    println("lex time {:.9f} sec", lexSec.count());
  }

  if(printSymbols == 1) {
    println("symbols:");
    auto syms = map(bisonParam.symtab.begin(), bisonParam.symtab.end());
    for(const auto& [sym, val]: syms) {
      println("{}: {}", sym, val);
    }
  }

  return 0;
}

