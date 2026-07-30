// ast_calc_parser.gtest.cpp

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

#include "lexer/ast_calc_lexer.h"
#include "ast_calc_parser.bison.h"

#include <sstream>
#include <string>
#include <queue>

#include <gtest/gtest.h>

using namespace std;

using namespace ::testing;

namespace astcalc::testing {

TEST(AstCalc_BisonNoFlex, test_0000) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_INT(3, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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

#if 0
  lexer.set_debug(1);
  parser.set_debug_level(1);
#endif

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 3);
}

TEST(AstCalc_BisonNoFlex, test_0001) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 * 5
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_INT(3, location{}),
    AstCalcParser::make_TIMES(location{}),
    AstCalcParser::make_INT(5, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 15);
}

TEST(AstCalc_BisonNoFlex, test_0002) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + 5 * 7
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_INT(3, location{}),
    AstCalcParser::make_PLUS(location{}),
    AstCalcParser::make_INT(5, location{}),
    AstCalcParser::make_TIMES(location{}),
    AstCalcParser::make_INT(7, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 38);
}

TEST(AstCalc_BisonNoFlex, test_0003) {

  BisonParam bisonParam;
  LexParam lexParam;

// 3 + x * 7
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_INT(3, location{}),
    AstCalcParser::make_PLUS(location{}),
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_TIMES(location{}),
    AstCalcParser::make_INT(7, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 3);
}

TEST(AstCalc_BisonNoFlex, test_0004) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_INT(7, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 7);
}

TEST(AstCalc_BisonNoFlex, test_0005) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 3 + 5
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_INT(3, location{}),
    AstCalcParser::make_PLUS(location{}),
    AstCalcParser::make_INT(5, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 8);
  EXPECT_EQ(bisonParam.ast.symtab["x"], 8);
}

TEST(AstCalc_BisonNoFlex, test_0006) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = y = 7
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_IDENT("y", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_INT(7, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 7);
  EXPECT_EQ(bisonParam.ast.symtab["x"], 7);
  EXPECT_EQ(bisonParam.ast.symtab["y"], 7);
}

TEST(AstCalc_BisonNoFlex, test_0007) {

  BisonParam bisonParam;
  LexParam lexParam;

// x = 7; y = x + 5
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_INT(7, location{}),
    AstCalcParser::make_SEMICOLON(location{}),
    AstCalcParser::make_IDENT("y", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_PLUS(location{}),
    AstCalcParser::make_INT(5, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 12);
  EXPECT_EQ(bisonParam.ast.symtab["x"], 7);
  EXPECT_EQ(bisonParam.ast.symtab["y"], 12);
}

TEST(AstCalc_BisonNoFlex, test_0008) {

  BisonParam bisonParam;
  LexParam lexParam;

// (x = (3 + 5) * 2) + 9 -> 25, x == 16
  queue<AstCalcParser::symbol_type> tokens{{
    AstCalcParser::make_LEFT_PAREN(location{}),
    AstCalcParser::make_IDENT("x", location{}),
    AstCalcParser::make_EQUAL(location{}),
    AstCalcParser::make_LEFT_PAREN(location{}),
    AstCalcParser::make_INT(3, location{}),
    AstCalcParser::make_PLUS(location{}),
    AstCalcParser::make_INT(5, location{}),
    AstCalcParser::make_RIGHT_PAREN(location{}),
    AstCalcParser::make_TIMES(location{}),
    AstCalcParser::make_INT(2, location{}),
    AstCalcParser::make_RIGHT_PAREN(location{}),
    AstCalcParser::make_PLUS(location{}),
    AstCalcParser::make_INT(9, location{}),
  }};

  AstCalcParser parser([&tokens](LexParam&) -> AstCalcParser::symbol_type {
    if(tokens.empty()) {
      return AstCalcParser::make_YYEOF(location{});
    }
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
  EXPECT_EQ(bisonParam.ast.eval(), 25);
  EXPECT_EQ(bisonParam.ast.symtab["x"], 16);
}

TEST(AstCalc_Bison, test_0000) {

  stringstream s("2 + 3");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 5);
}

TEST(AstCalc_Bison, test_0001) {

  stringstream s("2 - 7");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), -5);
}

TEST(AstCalc_Bison, test_0002) {

  stringstream s("-2 + -7");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), -9);
}

TEST(AstCalc_Bison, test_0003) {

  stringstream s("a = b = c = 10");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 10);
  EXPECT_EQ(bisonParam.ast.symtab["a"], 10);
  EXPECT_EQ(bisonParam.ast.symtab["b"], 10);
  EXPECT_EQ(bisonParam.ast.symtab["c"], 10);
}

TEST(AstCalc_Bison, test_0004) {

  stringstream s(R"%(
a = 3; b = 5;
c=7;
x = a + b * c;
)%");

  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 38);
  EXPECT_EQ(bisonParam.ast.symtab["x"], 38);
  EXPECT_EQ(bisonParam.ast.symtab["a"], 3);
  EXPECT_EQ(bisonParam.ast.symtab["b"], 5);
  EXPECT_EQ(bisonParam.ast.symtab["c"], 7);
}

TEST(AstCalc_Bison, test_0005) {

  stringstream s(R"%(
a = 1; b = 2; c = 9; d = 4; e = 2; f = 3;
((a + b) * (c - d)) / (e + f)
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 3);
}

TEST(AstCalc_Bison, test_0006) {

  stringstream s(R"%(
100 / 10 / 2
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 5);
}

TEST(AstCalc_Bison, test_0007) {

  stringstream s(R"%(
(a) = 5;
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(AstCalc_Bison, test_0008) {

  stringstream s(R"%(
a = b * / c
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(AstCalc_Bison, test_0009) {

  stringstream s(R"%(
a + b = c
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_NE(parser(), 0);
}

TEST(AstCalc_Bison, test_0010) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a + (b = c)
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 2);
  EXPECT_EQ(bisonParam.ast.symtab["b"], -5);

}

TEST(AstCalc_Bison, test_0011) {

  stringstream s(R"%(
a = 7; b = 3; c = -5;
a = -b * -c
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), -15);
  EXPECT_EQ(bisonParam.ast.symtab["a"], -15);
}

TEST(AstCalc_Bison, test_0012) {

  stringstream s(R"%(
c = 3;
a = (b = c + 5) * 2
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  AstCalcParser parser([&lexer](LexParam& lexParam) -> AstCalcParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  EXPECT_EQ(parser(), 0);
  EXPECT_EQ(bisonParam.ast.eval(), 16);
  EXPECT_EQ(bisonParam.ast.symtab["a"], 16);
  EXPECT_EQ(bisonParam.ast.symtab["b"], 8);
}

}

