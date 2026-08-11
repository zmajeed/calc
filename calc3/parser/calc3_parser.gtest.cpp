// calc3_parser.gtest.cpp

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

#include "calc3_bison_types.h"

#include "lexer/calc3_lexer.h"
#include "calc3_parser.bison.h"

#include <sstream>
#include <string>
#include <queue>

#include <gtest/gtest.h>

using namespace std;

using namespace ::testing;

namespace calc3::testing {

TEST(Calc3_BisonNoFlex, test_00) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// 3
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_INT(3, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_BisonNoFlex, test_01) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// 3 * 5
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_INT(3, location{}),
    Calc3Parser::make_TIMES(location{}),
    Calc3Parser::make_INT(5, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_BisonNoFlex, test_02) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// 3 + 5 * 7
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_INT(3, location{}),
    Calc3Parser::make_PLUS(location{}),
    Calc3Parser::make_INT(5, location{}),
    Calc3Parser::make_TIMES(location{}),
    Calc3Parser::make_INT(7, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_BisonNoFlex, test_03) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// 3 + x * 7
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_INT(3, location{}),
    Calc3Parser::make_PLUS(location{}),
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_TIMES(location{}),
    Calc3Parser::make_INT(7, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_BisonNoFlex, test_04) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// x = 7
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_INT(7, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_BisonNoFlex, test_05) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// x = 3 + 5
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_INT(3, location{}),
    Calc3Parser::make_PLUS(location{}),
    Calc3Parser::make_INT(5, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 1);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("x"));
}

TEST(Calc3_BisonNoFlex, test_06) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// x = y = 7
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_IDENT("y", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_INT(7, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 2);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("x"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("y"));
}

TEST(Calc3_BisonNoFlex, test_07) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// x = 7; y = x + 5
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_INT(7, location{}),
    Calc3Parser::make_SEMICOLON(location{}),
    Calc3Parser::make_IDENT("y", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_PLUS(location{}),
    Calc3Parser::make_INT(5, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 2);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 2);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("x"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("y"));
}

TEST(Calc3_BisonNoFlex, test_08) {

  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

// (x = (3 + 5) * 2) + 9 -> 25, x == 16
  queue<Calc3Parser::symbol_type> tokens{{
    Calc3Parser::make_LEFT_PAREN(location{}),
    Calc3Parser::make_IDENT("x", location{}),
    Calc3Parser::make_EQUAL(location{}),
    Calc3Parser::make_LEFT_PAREN(location{}),
    Calc3Parser::make_INT(3, location{}),
    Calc3Parser::make_PLUS(location{}),
    Calc3Parser::make_INT(5, location{}),
    Calc3Parser::make_RIGHT_PAREN(location{}),
    Calc3Parser::make_TIMES(location{}),
    Calc3Parser::make_INT(2, location{}),
    Calc3Parser::make_RIGHT_PAREN(location{}),
    Calc3Parser::make_PLUS(location{}),
    Calc3Parser::make_INT(9, location{}),
  }};

  Calc3Parser parser([&tokens](LexParam&) -> Calc3Parser::symbol_type {
    if(tokens.empty()) {
      return Calc3Parser::make_YYEOF(location{});
    }
    auto tok = tokens.front();
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 1);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("x"));
}

TEST(Calc3_Bison, test_00) {

  stringstream s("2 + 3");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_Bison, test_01) {

  stringstream s("2 - 7");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_Bison, test_02) {

  stringstream s("-2 + -7");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_Bison, test_03) {

  stringstream s("a = b = c = 10");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 3);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("a"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("b"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("c"));
}

TEST(Calc3_Bison, test_04) {

  stringstream s(R"%(
a = 3; b = 5;
c=7;
x = a + b * c;
)%");

  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 4);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 4);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("x"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("a"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("b"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("c"));
}

TEST(Calc3_Bison, test_05) {

  stringstream s(R"%(
a = 1; b = 2; c = 9; d = 4; e = 2; f = 3;
((a + b) * (c - d)) / (e + f)
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 7);
}

TEST(Calc3_Bison, test_06) {

  stringstream s(R"%(
100 / 10 / 2
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 1);
}

TEST(Calc3_Bison, test_07) {

  stringstream s(R"%(
(a) = 5;
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc3_Bison, test_08) {

  stringstream s(R"%(
a = b * / c
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc3_Bison, test_09) {

  stringstream s(R"%(
a + b = c
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Calc3_Bison, test_10) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a + (b = c)
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 4);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 3);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("b"));
}

TEST(Calc3_Bison, test_11) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a = -b * -c
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 4);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 3);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("a"));
}

TEST(Calc3_Bison, test_12) {

  stringstream s(R"%(
c = 3;
a = (b = c + 5) * 2
)%");
  Calc3Lexer lexer(s);
  BisonDriver driver;
  BisonParam bisonParam{driver};
  LexParam lexParam;

  Calc3Parser parser([&lexer](LexParam& lexParam) -> Calc3Parser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.driver.expr.assigns.size(), 2);
  EXPECT_EQ(bisonParam.driver.symtab.size(), 3);
  EXPECT_TRUE(bisonParam.driver.symtab.contains("a"));
  EXPECT_TRUE(bisonParam.driver.symtab.contains("b"));
}

}

