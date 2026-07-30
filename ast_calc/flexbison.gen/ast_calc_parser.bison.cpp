// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 193 "./ast_calc/grammar/ast_calc_parser.bison.y"

// % code top
// appears as topmost code block in generated .cpp file just below gnu license
// your license for .cpp file

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


#line 70 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"


// First part of user prologue.
#line 224 "./ast_calc/grammar/ast_calc_parser.bison.y"

// %{ unnamed codeblock
// goes at top of .cpp file after %code top, before namespace and parser class


#line 80 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"


#include "ast_calc_parser.bison.h"


// Unqualified %code blocks.
#line 230 "./ast_calc/grammar/ast_calc_parser.bison.y"

// %code
// appears in generated .cpp file after #include of generated .h file and before parser namespace and class

#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <chrono>
#include <print>
#include <ranges>
#include <sstream>

#ifdef _MSC_VER
// disable vc++ warning C4065, switch statement contains default but no other case labels when there are no semantic actions
#pragma warning(push)
#pragma warning(disable: 4065)

// disable vc++ warning C4244, return conversion from const short to findqparser::FindqParser::state_type, possible loss of data 
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

using namespace std;
using views::as_rvalue;

namespace {
  const auto defaultInputName = "inputstream"s;
}

void astcalc::AstCalcParser::error(const location& loc, const string& msg) {
  println("error at {}: {}", loc, msg);
}


#line 125 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 147 "./ast_calc/grammar/ast_calc_parser.bison.y"
namespace astcalc {
#line 218 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"

  /// Build a parser object.
  AstCalcParser::AstCalcParser (function<AstCalcParser::symbol_type(LexParam&)> yylex_yyarg, BisonParam& bisonParam_yyarg, LexParam& lexParam_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yylex (yylex_yyarg),
      bisonParam (bisonParam_yyarg),
      lexParam (lexParam_yyarg)
  {}

  AstCalcParser::~AstCalcParser ()
  {}

  AstCalcParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  AstCalcParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  AstCalcParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  AstCalcParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  AstCalcParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  AstCalcParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  AstCalcParser::symbol_kind_type
  AstCalcParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  AstCalcParser::stack_symbol_type::stack_symbol_type ()
  {}

  AstCalcParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_add_expr: // add_expr
        value.YY_MOVE_OR_COPY< AddExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_expr: // assign_expr
        value.YY_MOVE_OR_COPY< AssignExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_atom: // atom
        value.YY_MOVE_OR_COPY< Atom > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< Expr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< Factor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_term: // term
        value.YY_MOVE_OR_COPY< Term > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // IDENT
        value.YY_MOVE_OR_COPY< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_exprs: // assign_exprs
        value.YY_MOVE_OR_COPY< vector<AssignExpr> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  AstCalcParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_add_expr: // add_expr
        value.move< AddExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_expr: // assign_expr
        value.move< AssignExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_atom: // atom
        value.move< Atom > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< Expr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_factor: // factor
        value.move< Factor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_term: // term
        value.move< Term > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // IDENT
        value.move< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_exprs: // assign_exprs
        value.move< vector<AssignExpr> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  AstCalcParser::stack_symbol_type&
  AstCalcParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_add_expr: // add_expr
        value.copy< AddExpr > (that.value);
        break;

      case symbol_kind::S_assign_expr: // assign_expr
        value.copy< AssignExpr > (that.value);
        break;

      case symbol_kind::S_atom: // atom
        value.copy< Atom > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< Expr > (that.value);
        break;

      case symbol_kind::S_factor: // factor
        value.copy< Factor > (that.value);
        break;

      case symbol_kind::S_term: // term
        value.copy< Term > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< int64_t > (that.value);
        break;

      case symbol_kind::S_IDENT: // IDENT
        value.copy< string > (that.value);
        break;

      case symbol_kind::S_assign_exprs: // assign_exprs
        value.copy< vector<AssignExpr> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  AstCalcParser::stack_symbol_type&
  AstCalcParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_add_expr: // add_expr
        value.move< AddExpr > (that.value);
        break;

      case symbol_kind::S_assign_expr: // assign_expr
        value.move< AssignExpr > (that.value);
        break;

      case symbol_kind::S_atom: // atom
        value.move< Atom > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< Expr > (that.value);
        break;

      case symbol_kind::S_factor: // factor
        value.move< Factor > (that.value);
        break;

      case symbol_kind::S_term: // term
        value.move< Term > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< int64_t > (that.value);
        break;

      case symbol_kind::S_IDENT: // IDENT
        value.move< string > (that.value);
        break;

      case symbol_kind::S_assign_exprs: // assign_exprs
        value.move< vector<AssignExpr> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  AstCalcParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  AstCalcParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  AstCalcParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  AstCalcParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  AstCalcParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  AstCalcParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  AstCalcParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  AstCalcParser::debug_level_type
  AstCalcParser::debug_level () const
  {
    return yydebug_;
  }

  void
  AstCalcParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  AstCalcParser::state_type
  AstCalcParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  AstCalcParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  AstCalcParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  AstCalcParser::operator() ()
  {
    return parse ();
  }

  int
  AstCalcParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 268 "./ast_calc/grammar/ast_calc_parser.bison.y"
{
// %initial-action codeblock
// goes inside parse() function in .cpp, it's a separate brace-scoped block, anything declared here is local to this block and cannot be used anywhere else in parse()

// suppress unused variable warning till fix in release after version 3.8.2, https://github.com/akimd/bison/commit/a166d5450e3f47587b98f6005f9f5627dbe21a5b
// yynerrs_ is local to generated parse function
  (void)yynerrs_;

  bisonParam.stats.parseStartTime = steady_clock::now();

  auto& loc = lexParam.loc;

  if(loc.begin.filename == nullptr) {
    loc.initialize(&defaultInputName);
  }
}

#line 642 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (lexParam));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_add_expr: // add_expr
        yylhs.value.emplace< AddExpr > ();
        break;

      case symbol_kind::S_assign_expr: // assign_expr
        yylhs.value.emplace< AssignExpr > ();
        break;

      case symbol_kind::S_atom: // atom
        yylhs.value.emplace< Atom > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< Expr > ();
        break;

      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< Factor > ();
        break;

      case symbol_kind::S_term: // term
        yylhs.value.emplace< Term > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< int64_t > ();
        break;

      case symbol_kind::S_IDENT: // IDENT
        yylhs.value.emplace< string > ();
        break;

      case symbol_kind::S_assign_exprs: // assign_exprs
        yylhs.value.emplace< vector<AssignExpr> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // expr: assign_exprs postprocess
#line 313 "./ast_calc/grammar/ast_calc_parser.bison.y"
                           {

  println("bison.expr.1:");
  yylhs.value.as < Expr > ().assigns = move(yystack_[1].value.as < vector<AssignExpr> > ());
  bisonParam.ast = yylhs.value.as < Expr > ();
}
#line 821 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 3: // expr: assign_exprs ";" postprocess
#line 320 "./ast_calc/grammar/ast_calc_parser.bison.y"
                               {

  println("bison.expr.2:");
  yylhs.value.as < Expr > ().assigns = move(yystack_[2].value.as < vector<AssignExpr> > ());
  bisonParam.ast = yylhs.value.as < Expr > ();
}
#line 832 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 4: // assign_exprs: assign_expr
#line 330 "./ast_calc/grammar/ast_calc_parser.bison.y"
              {

  println("bison.assign_exprs.1:");
  yylhs.value.as < vector<AssignExpr> > ().push_back(move(yystack_[0].value.as < AssignExpr > ()));
}
#line 842 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 5: // assign_exprs: assign_exprs ";" assign_expr
#line 336 "./ast_calc/grammar/ast_calc_parser.bison.y"
                               {

  println("bison.assign_exprs.2:");
  yylhs.value.as < vector<AssignExpr> > () = move(yystack_[2].value.as < vector<AssignExpr> > ());
  yylhs.value.as < vector<AssignExpr> > ().push_back(move(yystack_[0].value.as < AssignExpr > ()));
}
#line 853 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 6: // assign_expr: IDENT "=" assign_expr
#line 345 "./ast_calc/grammar/ast_calc_parser.bison.y"
                             {

  println("bison.assign_expr.1:");
  if(!bisonParam.symtab.contains(yystack_[2].value.as < string > ())) {
    bisonParam.symtab[yystack_[2].value.as < string > ()] = 0;
  }
  yylhs.value.as < AssignExpr > () = Assignment{yystack_[2].value.as < string > (), indirect<AssignExpr>{move(yystack_[0].value.as < AssignExpr > ())}};
}
#line 866 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 7: // assign_expr: add_expr
#line 354 "./ast_calc/grammar/ast_calc_parser.bison.y"
           {

  println("bison.assign_expr.2:");
  yylhs.value.as < AssignExpr > () = move(yystack_[0].value.as < AddExpr > ());
}
#line 876 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 8: // add_expr: term
#line 362 "./ast_calc/grammar/ast_calc_parser.bison.y"
       {

  println("bison.add_expr.1:");
  yylhs.value.as < AddExpr > ().terms.push_back(move(yystack_[0].value.as < Term > ()));
}
#line 886 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 9: // add_expr: add_expr "+" term
#line 368 "./ast_calc/grammar/ast_calc_parser.bison.y"
                    {

  println("bison.add_expr.2:");
  yylhs.value.as < AddExpr > () = move(yystack_[2].value.as < AddExpr > ());
  yylhs.value.as < AddExpr > ().terms.push_back(move(yystack_[0].value.as < Term > ()));
  yylhs.value.as < AddExpr > ().ops.push_back(AddExpr::op::plus);
}
#line 898 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 10: // add_expr: add_expr "-" term
#line 376 "./ast_calc/grammar/ast_calc_parser.bison.y"
                    {

  println("bison.add_expr.3:");
  yylhs.value.as < AddExpr > () = move(yystack_[2].value.as < AddExpr > ());
  yylhs.value.as < AddExpr > ().terms.push_back(move(yystack_[0].value.as < Term > ()));
  yylhs.value.as < AddExpr > ().ops.push_back(AddExpr::op::minus);
}
#line 910 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 11: // term: factor
#line 386 "./ast_calc/grammar/ast_calc_parser.bison.y"
         {

  println("bison.term.1:");
  yylhs.value.as < Term > ().factors.push_back(move(yystack_[0].value.as < Factor > ()));
}
#line 920 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 12: // term: term "*" factor
#line 392 "./ast_calc/grammar/ast_calc_parser.bison.y"
                  {

  println("bison.term.2:");
  yylhs.value.as < Term > () = move(yystack_[2].value.as < Term > ());
  yylhs.value.as < Term > ().factors.push_back(move(yystack_[0].value.as < Factor > ()));
  yylhs.value.as < Term > ().ops.push_back(Term::op::times);
}
#line 932 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 13: // term: term "/" factor
#line 400 "./ast_calc/grammar/ast_calc_parser.bison.y"
                  {

  println("bison.term.3:");
  yylhs.value.as < Term > () = move(yystack_[2].value.as < Term > ());
  yylhs.value.as < Term > ().factors.push_back(move(yystack_[0].value.as < Factor > ()));
  yylhs.value.as < Term > ().ops.push_back(Term::op::div);
}
#line 944 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 14: // factor: atom
#line 410 "./ast_calc/grammar/ast_calc_parser.bison.y"
       {

  println("bison.factor.1:");
  yylhs.value.as < Factor > () = {yystack_[0].value.as < Atom > (), Factor::op::none};
}
#line 954 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 15: // factor: "+" atom
#line 416 "./ast_calc/grammar/ast_calc_parser.bison.y"
           {

  println("bison.factor.2:");
  yylhs.value.as < Factor > () = {yystack_[0].value.as < Atom > (), Factor::op::plus};
}
#line 964 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 16: // factor: "-" atom
#line 422 "./ast_calc/grammar/ast_calc_parser.bison.y"
           {

  println("bison.factor.3:");
  yylhs.value.as < Factor > () = {yystack_[0].value.as < Atom > (), Factor::op::minus};
}
#line 974 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 17: // atom: INT
#line 430 "./ast_calc/grammar/ast_calc_parser.bison.y"
      {
  println("bison.atom.1:");
  yylhs.value.as < Atom > () = yystack_[0].value.as < int64_t > ();
}
#line 983 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 18: // atom: IDENT
#line 435 "./ast_calc/grammar/ast_calc_parser.bison.y"
        {

  println("bison.atom.2:");
  if(!bisonParam.symtab.contains(yystack_[0].value.as < string > ())) {
    bisonParam.symtab[yystack_[0].value.as < string > ()] = 0;
  }
  yylhs.value.as < Atom > () = move(yystack_[0].value.as < string > ());
}
#line 996 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 19: // atom: "(" expr ")"
#line 444 "./ast_calc/grammar/ast_calc_parser.bison.y"
               {

  println("bison.atom.3:");
  yylhs.value.as < Atom > () = Group{yystack_[1].value.as < Expr > ()};
}
#line 1006 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;

  case 20: // postprocess: %empty
#line 451 "./ast_calc/grammar/ast_calc_parser.bison.y"
                    {
  auto& [start, end, elapsed] = bisonParam.stats;
  end = steady_clock::now();
  elapsed = end - start;
}
#line 1016 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"
    break;


#line 1020 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  AstCalcParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  AstCalcParser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "/", "=", "(", "-", "+", ")",
  ";", "*", "IDENT", "INT", "$accept", "expr", "assign_exprs",
  "assign_expr", "add_expr", "term", "factor", "atom", "postprocess", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // AstCalcParser::context.
  AstCalcParser::context::context (const AstCalcParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  AstCalcParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  AstCalcParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  AstCalcParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char AstCalcParser::yypact_ninf_ = -6;

  const signed char AstCalcParser::yytable_ninf_ = -1;

  const signed char
  AstCalcParser::yypact_[] =
  {
      -5,    -5,     3,     3,    12,    -6,    26,    18,    -6,     6,
       8,    -6,    -6,    21,    -6,    -6,    -6,    -5,    -6,    -5,
      -6,    -2,    -2,    -2,    -2,    -6,    -6,    -6,    -6,     8,
       8,    -6,    -6
  };

  const signed char
  AstCalcParser::yydefact_[] =
  {
       0,     0,     0,     0,    18,    17,     0,    20,     4,     7,
       8,    11,    14,     0,    18,    16,    15,     0,     1,    20,
       2,     0,     0,     0,     0,    19,     6,     5,     3,    10,
       9,    13,    12
  };

  const signed char
  AstCalcParser::yypgoto_[] =
  {
      -6,    27,    -6,     0,    -6,    -1,     1,    20,    11
  };

  const signed char
  AstCalcParser::yydefgoto_[] =
  {
       0,     6,     7,     8,     9,    10,    11,    12,    20
  };

  const signed char
  AstCalcParser::yytable_[] =
  {
       1,     2,     3,     1,     2,     3,     4,     5,     1,    14,
       5,    23,    21,    22,    14,     5,    17,    26,    24,    27,
      29,    30,    15,    16,    31,    32,    18,    19,    13,    25,
      28
  };

  const signed char
  AstCalcParser::yycheck_[] =
  {
       5,     6,     7,     5,     6,     7,    11,    12,     5,    11,
      12,     3,     6,     7,    11,    12,     4,    17,    10,    19,
      21,    22,     2,     3,    23,    24,     0,     9,     1,     8,
      19
  };

  const signed char
  AstCalcParser::yystos_[] =
  {
       0,     5,     6,     7,    11,    12,    14,    15,    16,    17,
      18,    19,    20,    14,    11,    20,    20,     4,     0,     9,
      21,     6,     7,     3,    10,     8,    16,    16,    21,    18,
      18,    19,    19
  };

  const signed char
  AstCalcParser::yyr1_[] =
  {
       0,    13,    14,    14,    15,    15,    16,    16,    17,    17,
      17,    18,    18,    18,    19,    19,    19,    20,    20,    20,
      21
  };

  const signed char
  AstCalcParser::yyr2_[] =
  {
       0,     2,     2,     3,     1,     3,     3,     1,     1,     3,
       3,     1,     3,     3,     1,     2,     2,     1,     1,     3,
       0
  };




#if YYDEBUG
  const short
  AstCalcParser::yyrline_[] =
  {
       0,   313,   313,   320,   330,   336,   345,   354,   362,   368,
     376,   386,   392,   400,   410,   416,   422,   430,   435,   444,
     451
  };

  void
  AstCalcParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  AstCalcParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 147 "./ast_calc/grammar/ast_calc_parser.bison.y"
} // astcalc
#line 1457 "./ast_calc/flexbison.gen/ast_calc_parser.bison.cpp"

#line 457 "./ast_calc/grammar/ast_calc_parser.bison.y"

// %code epilog block
// goes at bottom of generated .cpp file after namespace and parser implementation


#ifdef _MSC_VER
#pragma warning(pop)
#pragma warning(pop)
#endif

