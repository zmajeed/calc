#ifndef AST_CALC_AST_H
#define AST_CALC_AST_H
// ast/ast_calc_ast.h

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

#include <stdint.h>

#include <string>
#include <vector>
#include <set>
#include <flat_set>
#include <initializer_list>
#include <map>
#include <variant>
#include <compare>
#include <utility>
#include <algorithm>
#include <memory>
#include <functional>
#include <print>

#if _WIN32 || __clang__
#include "indirect.h"
#endif

namespace astcalc {
using namespace std;

#if _WIN32 || __clang__
using xyz::indirect;
#endif

// main ast node types

struct AssignExpr;
struct Expr;
struct AddExpr;
struct Term;
struct Factor;
struct Group;
struct Atom;


using Int = int64_t;
using Ident = string;

struct Expr {
  vector<AssignExpr> assigns;
};

struct Group: Expr {
};

struct Atom: variant<Int, Ident, Group> {
  using variant::variant;
};

struct Factor {
  Atom atom;
  enum class op {
    none,
    plus,
    minus
  } op = op::none;
};

struct Term {
  vector<Factor> factors;

  enum class op {
    times,
    div
  };

  vector<op> ops;
};

struct AddExpr {
  vector<Term> terms;

  enum class op {
    plus,
    minus
  };

  vector<op> ops;
};

struct Assignment {
  Ident ident;
  indirect<AssignExpr> rhs;
};

struct AssignExpr: variant<monostate, Assignment, AddExpr> {
  using variant::variant;
};


struct CalcAstNode: variant<monostate, Expr, Group, Atom, Factor, Term, AddExpr, Assignment, AssignExpr> {
  using variant::variant;

  unordered_map<string, int64_t> symtab;

  int64_t eval();

private:

#if WIN32
  template<class... Ts> struct __declspec(empty_bases) overload: Ts... { using Ts::operator()...; };
#else
  template<class... Ts> struct overload: Ts... { using Ts::operator()...; };
#endif
  template<class... Ts> overload(Ts...) -> overload<Ts...>;

};

inline
int64_t CalcAstNode::eval() {

  //unordered_map<string, int64_t> symtab;

  return visit(overload{

    [](this auto&& self, const Expr& e) -> int64_t {
      println("expr:");
      int64_t result;
      for(int i = 0; i < ssize(e.assigns); ++i) {
        auto& ass = e.assigns[i];
        result = self(ass);
      }
      println("expr: return {}", result);
      return result;
    },

    [](this auto&& self, const Group& g) -> int64_t {
      println("group:");
      int64_t result;
      for(int i = 0; i < ssize(g.assigns); ++i) {
        auto& ass = g.assigns[i];
        result = self(ass);
      }
      println("group: return {}", result);
      return result;
    },

    [](this auto&& self, const AssignExpr& a) -> int64_t {
      println("assign_expr:");
#if __cpp_lib_variant >= 202306L
      auto result = a.visit(self);
#else
      auto result = visit(self, a);
#endif
      println("assign_expr: return {}", result);
      return result;
    },

    //[&symtab](this auto&& self, const Assignment& a) -> int64_t {
    [this](this auto&& self, const Assignment& a) -> int64_t {
      println("assignment:");
      auto& [ident, rhs] = a;
      println("ident \"{}\"", ident);
      if(!symtab.contains(ident)) {
        symtab[ident] = 0;
      }
      auto rhsVal = self(*rhs);
      symtab[ident] = rhsVal;
      auto result = symtab[ident];
      println("assignment: return {}", result);
      return result;
    },

    [](this auto&& self, const AddExpr& a) -> int64_t {
      println("add_expr:");
      int64_t result = 0;
      for(int i = 0; i < ssize(a.terms); ++i) {
        auto& term = a.terms[i];
        if(i == 0 || a.ops[i - 1] == AddExpr::op::plus) {
          result += self(term);
          continue;
        }
        result -= self(term);
      }
      println("add_expr: return {}", result);
      return result;
    },

    [](this auto&& self, const Term& t) -> int64_t {
      println("term: factors size {}", t.factors.size());
      int64_t result = 1;
      for(int i = 0; i < ssize(t.factors); ++i) {
        auto& factor = t.factors[i];
        if(i == 0 || t.ops[i - 1] == Term::op::times) {
          result *= self(factor);
          continue;
        }
        result /= self(factor);
      }
      println("term: return {}", result);
      return result;
    },

    [](this auto&& self, const Factor& f) -> int64_t {
      println("factor:");
      auto result = self(f.atom);
      println("factor: return {}", result);
      return result;
    },

    [](this auto&& self, const Atom& a) -> int64_t {
      println("atom:");
#if __cpp_lib_variant >= 202306L
      auto result = a.visit(self);
#else
      auto result = visit(self, a);
#endif
      println("atom: return {}", result);
      return result;
    },

    //[&symtab](this auto&&, const Ident& i) -> int64_t {
    [this](this auto&&, const Ident& i) -> int64_t {
      println("ident \"{}\"", i);
      if(!symtab.contains(i)) {
        symtab[i] = 0;
      }
      auto result = symtab[i];
      println("ident: return {}", result);
      return result;
    },

    [](this auto&&, const Int i) -> int64_t {
      println("int \"{}\"", i);
      println("int: return {}", i);
      return i;
    },

    [](this auto&&, monostate) -> int64_t {
      println("monostate:");
      return 0;
    },

// default match

    [](this const auto&&, const auto&) -> int64_t {
      println("printAst.constrvalref: unexpected default match");
      return 0;
    },

// new c++26 variant visit member function, takes 1 parameter
// old variant visit global function, takes 2 parameters
#if __cpp_lib_variant >= 202306L
  });
#else
  }, *this);
#endif

}

}

#endif

