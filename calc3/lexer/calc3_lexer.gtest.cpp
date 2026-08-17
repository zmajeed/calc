// calc3_lexer.gtest.cpp

/*
MIT License

Copyright (c) 2024.-2026 Zartaj Majeed

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

#include "calc3_lexer.h"
#include "calc3_parser.bison.h"

#include <sstream>
#include <string>
#include <utility>

#include <gtest/gtest.h>

using namespace std;
using namespace ::testing;

namespace calc3::testing {

TEST(Calc3_Lexer, test_00) {

  stringstream s("5");
  Calc3Lexer lexer(s);
  LexParam lexParam{};

  auto token = lexer.yylex(lexParam);

  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 5);
}

TEST(Calc3_Lexer, test_01) {

  stringstream s("x");
  Calc3Lexer lexer(s);
  LexParam lexParam{};

  auto token = lexer.yylex(lexParam);

  ASSERT_STREQ(token.name(), "ident");
  EXPECT_EQ(token.value.as<string>(), "x");
}

TEST(Calc3_Lexer, test_02) {

  stringstream s("2 + 3");
  Calc3Lexer lexer(s);
  LexParam lexParam{};

  auto token = lexer.yylex(lexParam);

  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 2);

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  EXPECT_STREQ(token.name(), "+");

  destroy_at(&token);
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 3);

}

TEST(Calc3_Lexer, test_03) {

  stringstream s("2 + -3");
  Calc3Lexer lexer(s);
  LexParam lexParam{};

  auto token = lexer.yylex(lexParam);

  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 2);

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  EXPECT_STREQ(token.name(), "+");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "-");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 3);

}

TEST(Calc3_Lexer, test_04) {

  stringstream s("3-5");
  Calc3Lexer lexer(s);
  LexParam lexParam{};

  auto token = lexer.yylex(lexParam);

  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 3);

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  EXPECT_STREQ(token.name(), "-");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 5);

}

TEST(Calc3_Lexer, test_05) {

  stringstream s("val1 = 2; val2 = -val1+val3");
  Calc3Lexer lexer(s);
  LexParam lexParam{};

  auto token = lexer.yylex(lexParam);

  ASSERT_STREQ(token.name(), "ident");
  EXPECT_EQ(token.value.as<string>(), "val1");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "=");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "int");
  EXPECT_EQ(token.value.as<int64_t>(), 2);

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), ";");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "ident");
  EXPECT_EQ(token.value.as<string>(), "val2");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "=");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "-");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "ident");
  EXPECT_EQ(token.value.as<string>(), "val1");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "+");

  token.clear();
  construct_at(&token, lexer.yylex(lexParam));
  ASSERT_STREQ(token.name(), "ident");
  EXPECT_EQ(token.value.as<string>(), "val3");

}

}


