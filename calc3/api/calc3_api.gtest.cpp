// calc3_api/calc3_api.gtest.cpp

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

#include "calc3_api.h"

#include <sstream>
#include <string>
#include <iostream>
#include <print>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

using namespace ::testing;

// print struct on test failure
namespace calc3 {

void PrintTo(const Error& e, ostream* os) {
  *os << format("{{\"{}\", {}, {}, \"{}\"}}", e.msg, e.line, e.col, e.file);
}

}

namespace calc3::testing {

TEST(Calc3Api, test_000) {

  stringstream s("2 + 3");
  auto calc = Calc3::parse(s);

  EXPECT_FALSE(calc.hasError());
  EXPECT_EQ(calc.eval().value_or(0), 5);
}

TEST(Calc3Api, test_001) {

  string s = "2 + 3";
  auto calc = Calc3::parseString(s);

  EXPECT_FALSE(calc.hasError());
  EXPECT_EQ(calc.eval().value_or(0), 5);
}

TEST(Calc3Api, test_002) {

  string s = "2 + ";
  auto calc = Calc3::parseString(s);

  EXPECT_TRUE(calc.hasError());
  EXPECT_FALSE(calc.eval());
  EXPECT_THAT(calc.errorInfo(), FieldsAre(StartsWith("syntax error"), 1, 4, "string"));

}

}



