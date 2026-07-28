// simple_calc_parser.rules.bison.y

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

// calc grammar without clutter of semantic actions
// bison -Wall -Wdangling-alias -Werror --color=always -Wcounterexamples --report=counterexamples,lookaheads,solved --report-file=bisonreport.txt simple_calc_parser.rules.bison.y

%token DIV                  "/"
%token EQUAL                "="
%token LEFT_PAREN           "("
%token MINUS                "-"
%token PLUS                 "+"
%token RIGHT_PAREN          ")"
%token SEMICOLON            ";"
%token TIMES                "*"

%token                      INT
%token                      IDENT

%start expr

%%

expr: assign_exprs | assign_exprs ";"

assign_exprs: assign_expr | assign_exprs ";" assign_expr

assign_expr: IDENT "=" assign_expr | add_expr

add_expr: term | add_expr "+" term | add_expr "-" term

term: factor | term "*" factor | term "/" factor

factor: atom | "+" factor | "-" factor

atom: INT | IDENT | "(" expr ")"
