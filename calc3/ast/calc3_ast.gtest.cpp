// calc3_ast.gtest.cpp

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

#include "calc3_ast.h"

#include <sstream>
#include <string>
#include <utility>

#include <gtest/gtest.h>

using namespace std;

namespace calc3::testing {

TEST(Calc3_Ast, test_00) {

// x = 5
  Factor factor{Atom{5}};
  Term term = { { factor }, {} };
  AddExpr addExpr = { { term }, {} };
  AssignExpr axp1 = addExpr;
  Assignment ass2{"x", indirect<AssignExpr>{move(axp1)}};
  AssignExpr axp3 = move(ass2);
  Expr expr;
  expr.assigns.push_back(move(axp3));
}


}

