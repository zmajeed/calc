// parser/calc3_parser.cpp

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

#include "api/calc3_api.h"

#include <stdlib.h>
#include <getopt.h>

#include <string>
#include <memory>
#include <iostream>
#include <istream>
#include <fstream>
#include <print>
#include <chrono>
#include <variant>
#include <utility>

#include "isocline.h"

using namespace std;
using namespace chrono;

using namespace calc3;

void usage() {
  println("Usage: calc3 [-h | --help] [--debug] [--stats] [-e expr] [file]");
  println("Simple arithmetic expressions parser");
  println("Prints nothing if parse succeeds, otherwise prints an error message with line number");
  println("");
  println("Options:");
  println("-e: arithmetic expression, only one of -e or file argument is allowed");
  println("--debug: turns on Bison parser and Flex lexer debug traces, off by default");
  println("-i | --interactive: launch interactive REPL");
  println("--stats: print timing stats on successful parse");
  println("--symbols: print symbol table");
  println("--help | -h: prints usage help");
}


void runInteractive() {

  ic_set_history("calc3_history.txt", -1);

  EvalContext ctx;

  char* input = nullptr;
  while((input = ic_readline("calc3")) != nullptr) {
    string line(input);
    ic_free(input);

    if(line.empty()) {
      continue;
    }
    if(line == "exit" || line == "quit") {
      break;
    }

    Calc3 calc = Calc3::parseString(line);

    auto result = calc.eval(ctx);

    if(!result) {
      println("{}", calc.errorStr());
      continue;
    }

    println("{}", result.value());

    ic_history_add(line.c_str());
  }

}

int main(int argc, char* argv[])
{
  int debug = 0;
  int printStats = 0;
  int printSymbols = 0;
  int interactive = 0;
  string evalStr;
  

// need filename pointer to stick around for bison error messages that print filename and position
  auto inputName = make_unique<string>("stdin");

  option opts[] = {
    {"debug", no_argument, &debug, 1},
    {"interactive", no_argument, &interactive, 1},
    {"stats", no_argument, &printStats, 1},
    {"symbols", no_argument, &printSymbols, 1},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
  };

  for(int i, optLetter; (optLetter = getopt_long(argc, argv, "e:hi", opts, &i)) != -1;) {
    switch(optLetter) {
    case 0:
      break;
    case 'e':
      evalStr = optarg;
      break;
    case 'i':
      interactive = 1;
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

  if(interactive) {
    runInteractive();
    return 0;
  }

  Calc3 calc;

// input can be string or exactly one file or keep default stdin
  if(!evalStr.empty()) {

    if(optind < argc) {
      usage();
      exit(1);
    }

    calc = Calc3::parseString(evalStr, { .debug = debug != 0 });

  } else if(optind + 1 == argc) {

    calc = Calc3::parseFile(argv[optind], { .debug = debug != 0 });
  }

  if(calc.hasError()) {
    println(stderr, "parse failed");
    return calc.errorCode();
  }

  EvalContext ctx;
  println("{}", calc.eval(ctx).value_or(0));

  if(printStats) {
    auto [parseSec, lexSec, _, __] = calc.stats;
    println("parse time: {:.9f} sec", parseSec.count());
    println("lex time {:.9f} sec", lexSec.count());
  }

  if(printSymbols == 1) {
    println("symbols:");
    for(const auto& [sym, val]: ctx.symtab) {
      println("{}: {}", sym, val);
    }
  }

  return 0;
}

