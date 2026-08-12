#ifndef CALC3_AST_H
#define CALC3_AST_H
// ast/calc3_ast.h

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
#include <variant>
#include <utility>
#include <algorithm>
#include <memory>
#include <functional>
#include <print>

#if _WIN32 || __clang__
#include "indirect.h"
#endif

namespace calc3 {
using namespace std;

#if _WIN32 || __clang__
using xyz::indirect;
#endif

// ast node types

struct AddExpr;
struct AssignExpr;
struct Atom;
struct Expr;
struct Factor;
struct Group;
struct Term;


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
  enum class op {
    none,
    plus,
    minus
  };

  Atom atom;
  vector<op> ops;
};

struct Term {
  enum class op {
    times,
    div
  };

  vector<Factor> factors;
  vector<op> ops;
};

struct AddExpr {
  enum class op {
    plus,
    minus
  };

  vector<Term> terms;
  vector<op> ops;
};

struct Assignment {
  Ident ident;
  indirect<AssignExpr> rhs;
};

struct AssignExpr: variant<monostate, Assignment, AddExpr> {
  using variant::variant;
};


}

#endif

