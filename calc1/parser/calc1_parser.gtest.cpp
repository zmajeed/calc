// calc1_parser.gtest.cpp

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

#include <sstream>
#include <string>
#include <queue>

#include <gtest/gtest.h>

using namespace std;

using namespace ::testing;

namespace calc1::testing {

TEST(Calc1_BisonNoFlex, test_00) {

  BisonParam bisonParam;
  LexParam lexParam;

  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_INT(3, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(Calc1_BisonNoFlex, test_01) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 * 5
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_INT(3, location{}),
    Calc1Parser::make_TIMES(location{}),
    Calc1Parser::make_INT(5, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 15);
}

TEST(Calc1_BisonNoFlex, test_02) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + 5 * 7
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_INT(3, location{}),
    Calc1Parser::make_PLUS(location{}),
    Calc1Parser::make_INT(5, location{}),
    Calc1Parser::make_TIMES(location{}),
    Calc1Parser::make_INT(7, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 38);
}

TEST(Calc1_BisonNoFlex, test_03) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + x * 7
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_INT(3, location{}),
    Calc1Parser::make_PLUS(location{}),
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_TIMES(location{}),
    Calc1Parser::make_INT(7, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(Calc1_BisonNoFlex, test_04) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_INT(7, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 7);
}

TEST(Calc1_BisonNoFlex, test_05) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 3 + 5
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_INT(3, location{}),
    Calc1Parser::make_PLUS(location{}),
    Calc1Parser::make_INT(5, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 8);
  EXPECT_EQ(bisonParam.symtab["x"], 8);
}

TEST(Calc1_BisonNoFlex, test_06) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = y = 7
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_IDENT("y", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_INT(7, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 7);
  EXPECT_EQ(bisonParam.symtab["x"], 7);
  EXPECT_EQ(bisonParam.symtab["y"], 7);
}

TEST(Calc1_BisonNoFlex, test_07) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7; y = x + 5
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_INT(7, location{}),
    Calc1Parser::make_SEMICOLON(location{}),
    Calc1Parser::make_IDENT("y", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_PLUS(location{}),
    Calc1Parser::make_INT(5, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 12);
  EXPECT_EQ(bisonParam.symtab["x"], 7);
  EXPECT_EQ(bisonParam.symtab["y"], 12);
}

TEST(Calc1_BisonNoFlex, test_08) {

  BisonParam bisonParam;
  LexParam lexParam;

// (x = (3 + 5) * 2) + 9 -> 25, x == 16
  queue<Calc1Parser::symbol_type> tokens{{
    Calc1Parser::make_LEFT_PAREN(location{}),
    Calc1Parser::make_IDENT("x", location{}),
    Calc1Parser::make_EQUAL(location{}),
    Calc1Parser::make_LEFT_PAREN(location{}),
    Calc1Parser::make_INT(3, location{}),
    Calc1Parser::make_PLUS(location{}),
    Calc1Parser::make_INT(5, location{}),
    Calc1Parser::make_RIGHT_PAREN(location{}),
    Calc1Parser::make_TIMES(location{}),
    Calc1Parser::make_INT(2, location{}),
    Calc1Parser::make_RIGHT_PAREN(location{}),
    Calc1Parser::make_PLUS(location{}),
    Calc1Parser::make_INT(9, location{}),
  }};

  Calc1Parser parser([&tokens](LexParam&) -> Calc1Parser::symbol_type {
    if(tokens.empty()) {
      return Calc1Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 25);
  EXPECT_EQ(bisonParam.symtab["x"], 16);
}

TEST(Calc1_Bison, test_00) {

  stringstream s("2 + 3");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 5);
}

TEST(Calc1_Bison, test_01) {

  stringstream s("2 - 7");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -5);
}

TEST(Calc1_Bison, test_02) {

  stringstream s("-2 + -7");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -9);
}

TEST(Calc1_Bison, test_03) {

  stringstream s("a = b = c = 10");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 10);
  EXPECT_EQ(bisonParam.symtab["a"], 10);
  EXPECT_EQ(bisonParam.symtab["b"], 10);
  EXPECT_EQ(bisonParam.symtab["c"], 10);
}

TEST(Calc1_Bison, test_04) {

  stringstream s(R"%(
a = 3; b = 5;
c=7;
x = a + b * c;
)%");

  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 38);
  EXPECT_EQ(bisonParam.symtab["x"], 38);
  EXPECT_EQ(bisonParam.symtab["a"], 3);
  EXPECT_EQ(bisonParam.symtab["b"], 5);
  EXPECT_EQ(bisonParam.symtab["c"], 7);
}

TEST(Calc1_Bison, test_05) {

  stringstream s(R"%(
a = 1; b = 2; c = 9; d = 4; e = 2; f = 3;
((a + b) * (c - d)) / (e + f)
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(Calc1_Bison, test_06) {

  stringstream s(R"%(
100 / 10 / 2
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 5);
}

TEST(Calc1_Bison, test_07) {

  stringstream s(R"%(
(a) = 5;
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc1_Bison, test_08) {

  stringstream s(R"%(
a = b * / c
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc1_Bison, test_09) {

  stringstream s(R"%(
a + b = c
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc1_Bison, test_10) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a + (b = c)
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 2);
  EXPECT_EQ(bisonParam.symtab["b"], -5);
}

TEST(Calc1_Bison, test_11) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a = -b * -c
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -15);
  EXPECT_EQ(bisonParam.symtab["a"], -15);
}

TEST(Calc1_Bison, test_12) {

  stringstream s(R"%(
c = 3;
a = (b = c + 5) * 2
)%");
  Calc1Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc1Parser parser([&lexer](LexParam& lexParam) -> Calc1Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 16);
  EXPECT_EQ(bisonParam.symtab["a"], 16);
  EXPECT_EQ(bisonParam.symtab["b"], 8);
}

}

