#ifndef CALC1_LEXER_H
#define CALC1_LEXER_H
// lexer.h

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

#include "calc1_parser.bison.h"

#include "calc1_lexer_guard.h"

namespace calc1 {
using namespace std;

class Calc1Lexer: public Calc1FlexLexer {
public:

// can only declare here since flex generates the implementation
  Calc1Parser::symbol_type yylex(LexParam&);

  Calc1Lexer() = default;

  explicit Calc1Lexer(istream* yyin_arg): Calc1FlexLexer(yyin_arg) {}
  explicit Calc1Lexer(istream& yyin_arg): Calc1FlexLexer(&yyin_arg) {}

private:

// fix gcc warning -Woverloaded-virtual that virtual int Calc1ParserFlexLexer::yylex() was hidden
  using Calc1FlexLexer::yylex;
  
};

}

#endif

