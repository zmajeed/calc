/* calc2_lexer.flex.l */

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

/* flex -Cfe -o calc2_lexer.flex.cpp calc2_lexer.flex.l */
/* g++ -O0 -Wall -Wextra -Werror -std=c++2b -o calc2_lexer calc2_lexer.flex.cpp */

 // flex directives

 // turn on warnings
%option warn

 // always generate 8bit lexer
%option 8bit

 // C++ lexer class
%option c++

 // custom C++ lexer classname
%option yyclass="Calc2Lexer"

 // custom prefix to turn yyFlexLexer into Calc2FlexLexer
%option prefix="Calc2"

%option debug

 // disable default rule that echoes unmatched input, gives flex scanner jammed error for any unmatched input
%option nodefault

 // noninteractive lexer has better performance, use with -Cfe
%option never-interactive

%option yylineno

%option noyywrap
 // disable various options for interactive lexer
%option nounput noinput batch

 // flex start conditions ie states
 // INITIAL 0 is default start condition
 // start conditions appear as macros defined inside ylex()

%top{
// top of generated .cpp file

// fix flex bug vc++ warning C4005, INT8_MIN macro redefinition
#include <stdint.h>
#ifdef _WIN32
#  undef INT8_MIN
#endif

#include <string>
#include <print>

#ifdef _MSC_VER
#pragma warning(push)
// disable vc++ warning C4244, return conversion from streamsize to int possible loss of data, in yyFlexLexer::LexerInput() in .cpp file
#pragma warning(disable: 4244)
#endif

}

%{
// bison generated header with C++ namespace and token definitions
#include "calc2_parser.bison.h"
#include "lexer/calc2_lexer.h"

#undef YY_DECL
#define YY_DECL calc2::Calc2Parser::symbol_type calc2::Calc2Lexer::yylex(LexParam& param)

// fix flex error could not convert 0 from int to symbol_type for #define YY_NULL 0
// caused by turning on bison %locations because symbol_type no longer has single int constructor for implicit conversion
#define yyterminate() return symbol_type(YY_NULL, loc)

using namespace std;

using namespace calc2;

// needed for custom yyterminate
using symbol_type = Calc2Parser::symbol_type;

// flex start conditions appear as macros in .cpp file here

%}

%%

 // code appears inside generated yylex function at start

 // position in input stream
  auto& loc = param.loc;
 // update current position to previous line and column numbers
  loc.step();

 // flex rules section
 /* only c-style comments starting at second column allowed inside rules section */
 /* first flex rule starts at beginning of line */

[+-]?[0-9]+ {
  loc.columns(yyleng);
  int64_t val;
// flex doesn't understand preprocessor #ifdef, move brace for if-block out of #ifdef to avoid unbalanced braces and prevent flex error eof encountered inside action
#if __cpp_lib_to_chars >= 202306L
  if(auto res = from_chars(yytext, &yytext[yyleng], val); !res)
#else
  if(auto res = from_chars(yytext, &yytext[yyleng], val); res.ec != errc{})
#endif
  {
    println("malformed number {}", yytext);
    return Calc2Parser::make_YYUNDEF(loc);
  }
  return Calc2Parser::make_INT(val, loc);
}

 /* assumes typical identifier syntax */
[A-Za-z_][A-Za-z0-9_]* {
  loc.columns(yyleng);
  return Calc2Parser::make_IDENT(yytext, loc);
}

"/" {
  loc.columns(yyleng);
  return Calc2Parser::make_DIV(loc);
}

= {
  loc.columns(yyleng);
  return Calc2Parser::make_EQUAL(loc);
}

"(" {
  loc.columns(yyleng);
  return Calc2Parser::make_LEFT_PAREN(loc);
}

- {
  loc.columns(yyleng);
  return Calc2Parser::make_MINUS(loc);
}

"+" {
  loc.columns(yyleng);
  return Calc2Parser::make_PLUS(loc);
}

")" {
  loc.columns(yyleng);
  return Calc2Parser::make_RIGHT_PAREN(loc);
}

; {
  loc.columns(yyleng);
  return Calc2Parser::make_SEMICOLON(loc);
}

"*" {
  loc.columns(yyleng);
  return Calc2Parser::make_TIMES(loc);
}

 /* match newlines separately to correctly update line numbers */
\n {
  loc.lines(yyleng);
}

 /* whitespace except newline, same as [ \t\v\f\r] but easier to understand */
([[:space:]]{-}[\n])+ {
  loc.columns(yyleng);
}

 /* all input must be consumed in every state */
. {
  loc.columns(yyleng);
  return Calc2Parser::make_YYUNDEF(loc);
}

%%

#ifdef _MSC_VER
#pragma warning(pop)
#endif

