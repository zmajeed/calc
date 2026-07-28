// simple_calc_parser.gtest.cpp

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

#include "lexer/simple_calc_lexer.h"
#include "simple_calc_parser.bison.h"

#include <sstream>
#include <string>
#include <queue>

#include <gtest/gtest.h>

using namespace std;

using namespace ::testing;

namespace simplecalc::testing {

TEST(BisonNoFlex, test_0000) {

  BisonParam bisonParam;
  LexParam lexParam;

  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_INT(3, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() != "end of file"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(BisonNoFlex, test_0001) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 * 5
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_INT(3, location{}),
    SimpleCalcParser::make_TIMES(location{}),
    SimpleCalcParser::make_INT(5, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 15);
}

TEST(BisonNoFlex, test_0002) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + 5 * 7
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_INT(3, location{}),
    SimpleCalcParser::make_PLUS(location{}),
    SimpleCalcParser::make_INT(5, location{}),
    SimpleCalcParser::make_TIMES(location{}),
    SimpleCalcParser::make_INT(7, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 38);
}

TEST(BisonNoFlex, test_0003) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + x * 7
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_INT(3, location{}),
    SimpleCalcParser::make_PLUS(location{}),
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_TIMES(location{}),
    SimpleCalcParser::make_INT(7, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(BisonNoFlex, test_0004) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_INT(7, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 7);
}

TEST(BisonNoFlex, test_0005) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 3 + 5
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_INT(3, location{}),
    SimpleCalcParser::make_PLUS(location{}),
    SimpleCalcParser::make_INT(5, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 8);
  EXPECT_EQ(bisonParam.symtab["x"], 8);
}

TEST(BisonNoFlex, test_0006) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = y = 7
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_IDENT("y", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_INT(7, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
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

TEST(BisonNoFlex, test_0007) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7; y = x + 5
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_INT(7, location{}),
    SimpleCalcParser::make_SEMICOLON(location{}),
    SimpleCalcParser::make_IDENT("y", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_PLUS(location{}),
    SimpleCalcParser::make_INT(5, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
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

TEST(BisonNoFlex, test_0008) {

  BisonParam bisonParam;
  LexParam lexParam;

// (x = (3 + 5) * 2) + 9 -> 25, x == 16
  queue<SimpleCalcParser::symbol_type> tokens{{
    SimpleCalcParser::make_LEFT_PAREN(location{}),
    SimpleCalcParser::make_IDENT("x", location{}),
    SimpleCalcParser::make_EQUAL(location{}),
    SimpleCalcParser::make_LEFT_PAREN(location{}),
    SimpleCalcParser::make_INT(3, location{}),
    SimpleCalcParser::make_PLUS(location{}),
    SimpleCalcParser::make_INT(5, location{}),
    SimpleCalcParser::make_RIGHT_PAREN(location{}),
    SimpleCalcParser::make_TIMES(location{}),
    SimpleCalcParser::make_INT(2, location{}),
    SimpleCalcParser::make_RIGHT_PAREN(location{}),
    SimpleCalcParser::make_PLUS(location{}),
    SimpleCalcParser::make_INT(9, location{}),
    SimpleCalcParser::make_YYEOF(location{})
  }};

  SimpleCalcParser parser([&tokens](LexParam&) -> SimpleCalcParser::symbol_type {
    auto tok = tokens.front();
    if(tok.name() == "INT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<int64_t>());
      } else if(tok.name() == "IDENT"s) {
      println("yylex.lambda: return token {} {}", tok.name(), tok.value.as<string>());
    } else {
      println("yylex.lambda: return token {}", tok.name());
    }
    tokens.pop();
    return tok;
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 25);
  EXPECT_EQ(bisonParam.symtab["x"], 16);
}

TEST(Bison, test_0000) {

  stringstream s("2 + 3");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 5);
}

TEST(Bison, test_0001) {

  stringstream s("2 - 7");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -5);
}

TEST(Bison, test_0002) {

  stringstream s("-2 + -7");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -9);
}

TEST(Bison, test_0003) {

  stringstream s("a = b = c = 10");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
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

TEST(Bison, test_0004) {

  stringstream s(R"%(
a = 3; b = 5;
c=7;
x = a + b * c;
)%");

  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
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

TEST(Bison, test_0005) {

  stringstream s(R"%(
a = 1; b = 2; c = 9; d = 4; e = 2; f = 3;
((a + b) * (c - d)) / (e + f)
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 3);
}

TEST(Bison, test_0006) {

  stringstream s(R"%(
100 / 10 / 2
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, 5);
}

TEST(Bison, test_0007) {

  stringstream s(R"%(
(a) = 5;
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Bison, test_0008) {

  stringstream s(R"%(
a = b * / c
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(Bison, test_0009) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a = -b * -c
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.expr, -15);
  EXPECT_EQ(bisonParam.symtab["a"], -15);
}

TEST(Bison, test_0010) {

  stringstream s(R"%(
c = 3;
a = (b = c + 5) * 2
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  SimpleCalcParser parser([&lexer](LexParam& lexParam) -> SimpleCalcParser::symbol_type {
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

