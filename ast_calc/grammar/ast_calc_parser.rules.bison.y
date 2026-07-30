// ast_calc_parser.rules.bison.y

// calc grammar without clutter of semantic actions
// bison -Wall -Wdangling-alias -Werror --color=always -Wcounterexamples --report counterexamples,lookaheads,solved --report-file bisonreport.txt ast_calc_parser.rules.bison.y

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



