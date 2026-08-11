#ifndef CALC3_API_H
#define CALC3_API_H
// calc3_api.h

#include <stdint.h>

#include <string>
#include <expected>
#include <variant>
#include <chrono>
#include <ranges>
#include <flat_map>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>

#include "lexer/calc3_lexer.h"
#include "calc3_parser.bison.h"

#include "parser/calc3_bison_types.h"

namespace calc3 {
using namespace std;
using namespace chrono;

struct ParseConfig {
  bool debug = false;
  string filename{};
};

struct Stats {
  duration<double> parseSec;
  duration<double> lexSec;
  time_point<steady_clock> parseStart;
  time_point<steady_clock> parseEnd;
};

struct EvalContext {
  Symtab symtab;
};

struct Calc3 {

  Expr expr;
  Symtab symtab;
  int errCode;
  Error errInfo;
  Stats stats{};

  static Calc3 parse(istream& in, const ParseConfig& config) {

    string filename = config.filename;
    if(filename.empty()) {
      filename = "stream";
    }
    auto inputName = make_unique<string>(filename);

    Calc3Lexer lexer{in};

    BisonDriver driver;
    BisonParam bisonParam{driver};
    LexParam lexParam{.loc = location(inputName.get())};

    duration<double> lexSec{};

    Calc3Parser parser(
      [&lexer, &lexSec](LexParam& lexParam) -> Calc3Parser::symbol_type {
        time_point<steady_clock> start = steady_clock::now();
        auto token = lexer.yylex(lexParam);
        time_point<steady_clock> end = steady_clock::now();
        lexSec += end - start;
        return token;
      },
      bisonParam,
      lexParam
    );

    lexer.set_debug(config.debug);
    parser.set_debug_level(config.debug);

    time_point<steady_clock> parseStart = steady_clock::now();
    int ev = parser();
    time_point<steady_clock> parseEnd = steady_clock::now();

    return Calc3{
      .expr = move(driver.expr),
      .symtab = move(driver.symtab),
      .errCode = ev,
      .errInfo = move(driver.error),
      .stats = {
        parseEnd - parseStart,
        lexSec,
        parseStart,
        parseEnd,
      }
    };
  }

  static Calc3 parse(istream& in = cin, const ParseConfig&& config = { .filename = "stdin" }) {
    return parse(in, config);
  }

  static Calc3 parseString(const string& str, const ParseConfig&& config = { .filename = "string" }) {
    istringstream in{str};
    return parse(in, config);
  }

  static Calc3 parseFile(const string& file, ParseConfig&& config = {}) {
    if(config.filename.empty()) {
      config.filename = file;
    }

    if(file == "-") {
      return parse(cin, config);
    }
    ifstream filestrm;
    if(filestrm.open(file); !filestrm) {
      return Calc3{
        .expr = {},
        .symtab = {},
        .errCode = 1,
        .errInfo = {
          "cannot open file",
          0,
          0,
          file,
        },
        .stats = {}
      };
    }
    return parse(filestrm, config);
  }

  expected<int64_t, int> eval(EvalContext& ctx);

  expected<int64_t, int> eval(EvalContext&& ctx = {}) {
    return eval(ctx);
  }

  bool hasError() {
    return errCode != 0;
  }

  int errorCode() {
    return errCode;
  }

  Error errorInfo() {
    return errInfo;
  }

  string errorStr() {
    const auto& [msg, line, col, file] = errInfo;
    return format("{}:{}.{}: {}", file, line, col, msg);
  }

private:

#if WIN32
  template<class... Ts> struct __declspec(empty_bases) overload: Ts... { using Ts::operator()...; };
#else
  template<class... Ts> struct overload: Ts... { using Ts::operator()...; };
#endif
  template<class... Ts> overload(Ts...) -> overload<Ts...>;

};

inline
expected<int64_t, int> Calc3::eval(EvalContext& ctx) {

  if(errCode != 0) {
    return unexpected{errCode};
  }

  ctx.symtab.insert(symtab.begin(), symtab.end());

  auto result = visit(overload{

    [](this auto&& self, const Expr& e) -> int64_t {
      int64_t result = 0;
      for(int i = 0; i < ssize(e.assigns); ++i) {
        auto& ass = e.assigns[i];
        result = self(ass);
      }
      return result;
    },

    [](this auto&& self, const Group& g) -> int64_t {
      int64_t result = 0;
      for(int i = 0; i < ssize(g.assigns); ++i) {
        auto& ass = g.assigns[i];
        result = self(ass);
      }
      return result;
    },

    [](this auto&& self, const AssignExpr& a) -> int64_t {
#if __cpp_lib_variant >= 202306L
      auto result = a.visit(self);
#else
      auto result = visit(self, a);
#endif
      return result;
    },

    [&ctx](this auto&& self, const Assignment& a) -> int64_t {
      auto& [ident, rhs] = a;
      if(!ctx.symtab.contains(ident)) {
        ctx.symtab[ident] = 0;
      }
      auto rhsVal = self(*rhs);
      ctx.symtab[ident] = rhsVal;
      auto result = ctx.symtab[ident];
      return result;
    },

    [](this auto&& self, const AddExpr& a) -> int64_t {
      int64_t result = 0;
      for(int i = 0; i < ssize(a.terms); ++i) {
        auto& term = a.terms[i];
        if(i == 0 || a.ops[i - 1] == AddExpr::op::plus) {
          result += self(term);
          continue;
        }
        result -= self(term);
      }
      return result;
    },

    [](this auto&& self, const Term& t) -> int64_t {
      int64_t result = 1;
      for(int i = 0; i < ssize(t.factors); ++i) {
        auto& factor = t.factors[i];
        if(i == 0 || t.ops[i - 1] == Term::op::times) {
          result *= self(factor);
          continue;
        }
        result /= self(factor);
      }
      return result;
    },

    [](this auto&& self, const Factor& f) -> int64_t {
      auto result = self(f.atom);
      return result;
    },

    [](this auto&& self, const Atom& a) -> int64_t {
#if __cpp_lib_variant >= 202306L
      auto result = a.visit(self);
#else
      auto result = visit(self, a);
#endif
      return result;
    },

    [&ctx](this auto&&, const Ident& i) -> int64_t {
      if(!ctx.symtab.contains(i)) {
        ctx.symtab[i] = 0;
      }
      auto result = ctx.symtab[i];
      return result;
    },

    [](this auto&&, const Int i) -> int64_t {
      return i;
    },

// default match

    [](this const auto&&, const auto&) -> int64_t {
      println("printAst.constrvalref: unexpected default match");
      return 0;
    },

  }, variant<Expr>{expr});

  return result;

}


}

#endif
