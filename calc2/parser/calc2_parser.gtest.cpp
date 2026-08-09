// calc2_parser.gtest.cpp

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

#include "lexer/calc2_lexer.h"
#include "calc2_parser.bison.h"

#include <sstream>
#include <string>
#include <queue>

#include <gtest/gtest.h>

using namespace std;

using namespace ::testing;

namespace calc2::testing {

TEST(Calc2_BisonNoFlex, test_0000) {

  BisonParam bisonParam;
  LexParam lexParam;

  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_INT(3, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0001) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 * 5
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_INT(3, location{}),
    Calc2Parser::make_TIMES(location{}),
    Calc2Parser::make_INT(5, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0002) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + 5 * 7
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_INT(3, location{}),
    Calc2Parser::make_PLUS(location{}),
    Calc2Parser::make_INT(5, location{}),
    Calc2Parser::make_TIMES(location{}),
    Calc2Parser::make_INT(7, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0003) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + x * 7
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_INT(3, location{}),
    Calc2Parser::make_PLUS(location{}),
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_TIMES(location{}),
    Calc2Parser::make_INT(7, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0004) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_INT(7, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0005) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 3 + 5
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_INT(3, location{}),
    Calc2Parser::make_PLUS(location{}),
    Calc2Parser::make_INT(5, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0006) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = y = 7
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_IDENT("y", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_INT(7, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0007) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7; y = x + 5
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_INT(7, location{}),
    Calc2Parser::make_SEMICOLON(location{}),
    Calc2Parser::make_IDENT("y", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_PLUS(location{}),
    Calc2Parser::make_INT(5, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_BisonNoFlex, test_0008) {

  BisonParam bisonParam;
  LexParam lexParam;

// (x = (3 + 5) * 2) + 9 -> 25, x == 16
  queue<Calc2Parser::symbol_type> tokens{{
    Calc2Parser::make_LEFT_PAREN(location{}),
    Calc2Parser::make_IDENT("x", location{}),
    Calc2Parser::make_EQUAL(location{}),
    Calc2Parser::make_LEFT_PAREN(location{}),
    Calc2Parser::make_INT(3, location{}),
    Calc2Parser::make_PLUS(location{}),
    Calc2Parser::make_INT(5, location{}),
    Calc2Parser::make_RIGHT_PAREN(location{}),
    Calc2Parser::make_TIMES(location{}),
    Calc2Parser::make_INT(2, location{}),
    Calc2Parser::make_RIGHT_PAREN(location{}),
    Calc2Parser::make_PLUS(location{}),
    Calc2Parser::make_INT(9, location{}),
  }};

  Calc2Parser parser([&tokens](LexParam&) -> Calc2Parser::symbol_type {
    if(tokens.empty()) {
      return Calc2Parser::make_YYEOF(location{});
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

TEST(Calc2_Bison, test_0000) {

  stringstream s("2 + 3");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 5);
}

TEST(Calc2_Bison, test_0001) {

  stringstream s("2 - 7");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -5);
}

TEST(Calc2_Bison, test_0002) {

  stringstream s("-2 + -7");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -9);
}

TEST(Calc2_Bison, test_0003) {

  stringstream s("a = b = c = 10");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
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

TEST(Calc2_Bison, test_0004) {

  stringstream s(R"%(
a = 3; b = 5;
c=7;
x = a + b * c;
)%");

  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
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

TEST(Calc2_Bison, test_0005) {

  stringstream s(R"%(
a = 1; b = 2; c = 9; d = 4; e = 2; f = 3;
((a + b) * (c - d)) / (e + f)
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(Calc2_Bison, test_0006) {

  stringstream s(R"%(
100 / 10 / 2
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 5);
}

TEST(Calc2_Bison, test_0007) {

  stringstream s(R"%(
(a) = 5;
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc2_Bison, test_0008) {

  stringstream s(R"%(
a = b * / c
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc2_Bison, test_0009) {

  stringstream s(R"%(
a + b = c
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc2_Bison, test_0010) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a + (b = c)
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 2);
  EXPECT_EQ(bisonParam.symtab["b"], -5);
}

TEST(Calc2_Bison, test_0011) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a = -b * -c
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -15);
  EXPECT_EQ(bisonParam.symtab["a"], -15);
}

TEST(Calc2_Bison, test_0012) {

  stringstream s(R"%(
c = 3;
a = (b = c + 5) * 2
)%");
  Calc2Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  Calc2Parser parser([&lexer](LexParam& lexParam) -> Calc2Parser::symbol_type {
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

