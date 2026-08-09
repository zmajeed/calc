#ifndef CALC2_LEXER_H
#define CALC2_LEXER_H
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

#include "calc2_parser.bison.h"

#include "calc2_lexer_guard.h"

namespace calc2 {
using namespace std;

class Calc2Lexer: public Calc2FlexLexer {
public:

// can only declare here since flex generates the implementation
  Calc2Parser::symbol_type yylex(LexParam&);

  Calc2Lexer() = default;

  explicit Calc2Lexer(istream* yyin_arg): Calc2FlexLexer(yyin_arg) {}
  explicit Calc2Lexer(istream& yyin_arg): Calc2FlexLexer(&yyin_arg) {}

private:

// fix gcc warning -Woverloaded-virtual that virtual int Calc2ParserFlexLexer::yylex() was hidden
  using Calc2FlexLexer::yylex;
  
};

}

#endif

