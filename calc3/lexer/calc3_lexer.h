#ifndef CALC3_LEXER_H
#define CALC3_LEXER_H
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

#include "calc3_parser.bison.h"

#include "calc3_lexer_guard.h"

namespace calc3 {
using namespace std;

class Calc3Lexer: public Calc3FlexLexer {
public:

// can only declare here since flex generates the implementation
  Calc3Parser::symbol_type yylex(LexParam&);

  Calc3Lexer() = default;

  explicit Calc3Lexer(istream* yyin_arg): Calc3FlexLexer(yyin_arg) {}
  explicit Calc3Lexer(istream& yyin_arg): Calc3FlexLexer(&yyin_arg) {}

private:

// fix gcc warning -Woverloaded-virtual that virtual int Calc3ParserFlexLexer::yylex() was hidden
  using Calc3FlexLexer::yylex;
  
};

}

#endif

