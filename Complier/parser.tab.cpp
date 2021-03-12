// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


// First part of user declarations.

#line 37 "parser.tab.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.h"

// User implementation prologue.

#line 51 "parser.tab.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 23 "parser.y" // lalr1.cc:413

	#include <iostream>
	#include <cstdlib>
	#include <fstream>

	#include "signary.h"
	#include "tempTable.h"
	#include "Type.h"
	#include <iostream>
	#include <string>
	#include <cstdio>
	#include <algorithm>
	#include "Qualdruple.h"

	#include "driver.h"
	#include "tools.h"

	#undef yylex
	#define yylex scanner.yylex

	#include "parser_before.h"
	using namespace std;
	TempTable tempTable;
	Qualdruples qualdruples;
	Signary sigTable;
	int index=1;
	bool isIdType(ASTNode s){ return (s.type == "IDENTIFIER") ? 1 : 0; }
	int currentType;
	int leftLevel = 0;
	int rightLevel = 0;

#line 85 "parser.tab.cpp" // lalr1.cc:413


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.y" // lalr1.cc:479
namespace CP {
#line 171 "parser.tab.cpp" // lalr1.cc:479

  /// Build a parser object.
  Parser::Parser (Scanner  &scanner_yyarg, Driver  &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 106 "parser.y" // lalr1.cc:859
    {
												AST::setTopLevel((yystack_[1].value.tree).rootNode()->level);
												//$1.outputTreeReverse();
											}
#line 617 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 4:
#line 112 "parser.y" // lalr1.cc:859
    {
														int nowlevel=(yystack_[0].value.tree).rootNode()->level;
														(yylhs.value.tree).rootNode()->type="PROGRAM";
														(yylhs.value.tree).rootNode()->value="PROGRAM";
														(yylhs.value.tree).rootNode()->level=nowlevel+1;
														(yystack_[0].value.tree).addFather((yylhs.value.tree));
														(yylhs.value.tree)=(yystack_[0].value.tree);
													}
#line 630 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 5:
#line 120 "parser.y" // lalr1.cc:859
    {
																int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																(yystack_[1].value.tree).changeLevel(maxLevel);
																(yystack_[0].value.tree).changeLevel(maxLevel);
																(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																(yylhs.value.tree).rootNode()->type="PROGRAM";
																(yylhs.value.tree).rootNode()->value="PROGRAM";
																(yylhs.value.tree).rootNode()->level=nowlevel+1;
																(yystack_[1].value.tree).addFather((yylhs.value.tree));
																(yylhs.value.tree)=(yystack_[1].value.tree);
															}
#line 647 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 6:
#line 134 "parser.y" // lalr1.cc:859
    {
														int nowlevel=(yystack_[0].value.tree).rootNode()->level;
														(yylhs.value.tree).rootNode()->type="DECLARATION";
														(yylhs.value.tree).rootNode()->value="EXTERNAL_DECL";
														(yylhs.value.tree).rootNode()->level=nowlevel+1;
														(yystack_[0].value.tree).addFather((yylhs.value.tree));
														(yylhs.value.tree)=(yystack_[0].value.tree);
													}
#line 660 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 7:
#line 142 "parser.y" // lalr1.cc:859
    {
												int nowlevel=(yystack_[0].value.tree).rootNode()->level;
												(yylhs.value.tree).rootNode()->type="DECLARATION";
												(yylhs.value.tree).rootNode()->value="EXTERNAL_DECL";
												(yylhs.value.tree).rootNode()->level=nowlevel+1;
												(yystack_[0].value.tree).addFather((yylhs.value.tree));
												(yylhs.value.tree)=(yystack_[0].value.tree);
											}
#line 673 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 8:
#line 153 "parser.y" // lalr1.cc:859
    {
								int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
								(yystack_[2].value.tree).changeLevel(maxLevel);
								(yystack_[1].value.tree).changeLevel(maxLevel);
								(yystack_[0].value.tree).changeLevel(maxLevel);
								(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
								(yystack_[2].value.tree).addBrother((yystack_[1].value.tree));
								int nowlevel=(yystack_[2].value.tree).rootNode()->level;
								(yylhs.value.tree).rootNode()->style=TYPE_REXPR;
								(yylhs.value.tree).rootNode()->type="DEFINITION";
								(yylhs.value.tree).rootNode()->value="FUNCTION_DEFI";
								(yylhs.value.tree).rootNode()->level=nowlevel+1;
								(yystack_[2].value.tree).addFather((yylhs.value.tree));
								(yylhs.value.tree)=(yystack_[2].value.tree);
							}
#line 693 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 9:
#line 170 "parser.y" // lalr1.cc:859
    {
										currentType = TYPE_VOID;
										(yylhs.value.tree).rootNode()->style = currentType;
										(yylhs.value.tree).rootNode()->type="TYPE_SPECIFIER";
										(yylhs.value.tree).rootNode()->value="VOID";
										(yylhs.value.tree).rootNode()->level=0;
									}
#line 705 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 10:
#line 177 "parser.y" // lalr1.cc:859
    {
										currentType = TYPE_CHAR;
										(yylhs.value.tree).rootNode()->style = currentType;
										(yylhs.value.tree).rootNode()->type="TYPE_SPECIFIER";
										(yylhs.value.tree).rootNode()->value="CHAR";
										(yylhs.value.tree).rootNode()->level=0;
									}
#line 717 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 11:
#line 185 "parser.y" // lalr1.cc:859
    {
										currentType = TYPE_INT;
										(yylhs.value.tree).rootNode()->style = currentType;
										(yylhs.value.tree).rootNode()->type="TYPE_SPECIFIER";
										(yylhs.value.tree).rootNode()->value="INT";
										(yylhs.value.tree).rootNode()->level=0;
									}
#line 729 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 12:
#line 193 "parser.y" // lalr1.cc:859
    {
										currentType = TYPE_FLOAT;
										(yylhs.value.tree).rootNode()->style = currentType;
										(yylhs.value.tree).rootNode()->type="TYPE_SPECIFIER";
										(yylhs.value.tree).rootNode()->value="FLOAT";
										(yylhs.value.tree).rootNode()->level=0;
									}
#line 741 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 13:
#line 200 "parser.y" // lalr1.cc:859
    {
										currentType = TYPE_DOUBLE;
										(yylhs.value.tree).rootNode()->style = currentType;
										(yylhs.value.tree).rootNode()->type="TYPE_SPECIFIER";
										(yylhs.value.tree).rootNode()->value="DOUBLE";
										(yylhs.value.tree).rootNode()->level=0;
									}
#line 753 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 14:
#line 210 "parser.y" // lalr1.cc:859
    {
															int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
															(yystack_[1].value.tree).changeLevel(maxLevel);
															(yystack_[0].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
															int nowlevel=(yystack_[1].value.tree).rootNode()->level;
															(yylhs.value.tree).rootNode()->type="DECLARATOR";
															(yylhs.value.tree).rootNode()->value="DECLARATOR";
															(yylhs.value.tree).rootNode()->level=nowlevel+1;
															(yylhs.value.tree).rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[1].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[0].value.tree).rootNode()->style));
															(yystack_[1].value.tree).addFather((yylhs.value.tree));
															(yylhs.value.tree)=(yystack_[1].value.tree);
															list<ASTNode> l;
															(yylhs.value.tree).getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[1].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[0].value.tree).rootNode()->style));
																putSymbol.type = index;
																if (!sigTable.isRepeatInScope(l.front().value))
																{
																	sigTable.put(l.front().value, putSymbol);
																	index++;
																}
																else {
																	CP::Parser::error(location_type(), "Replication declaration!");
																	system("pause");
																}
																l.pop_front();
															}
														}
#line 789 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 15:
#line 242 "parser.y" // lalr1.cc:859
    {
															int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=maxLevel;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=maxLevel;
															(yystack_[2].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).addBrother(temp2);
															(yystack_[2].value.tree).addBrother((yystack_[1].value.tree));
															temp1.addBrother((yystack_[2].value.tree));
															int nowlevel=temp1.rootNode()->level;
															(yylhs.value.tree).rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[2].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[1].value.tree).rootNode()->style));
															(yylhs.value.tree).rootNode()->type="DECLARATOR";
															(yylhs.value.tree).rootNode()->value="DECLARATOR";
															(yylhs.value.tree).rootNode()->level=nowlevel+1;
															temp1.addFather((yylhs.value.tree));
															(yylhs.value.tree)=temp1;
															list<ASTNode> l;
															(yylhs.value.tree).getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[2].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[1].value.tree).rootNode()->style));
																putSymbol.type = index;
																if (!sigTable.isRepeatInScope(l.front().value))
																{
																	sigTable.put(l.front().value, putSymbol);
																	index++;
																}
																else {
																	CP::Parser::error(location_type(), "Replication declaration!");
																	system("pause");
																}
																l.pop_front();
															}
														}
#line 835 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 16:
#line 284 "parser.y" // lalr1.cc:859
    {
															int maxLevel=max({(yystack_[3].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=maxLevel;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=maxLevel;
															(yystack_[3].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).addBrother(temp2);
															temp1.addBrother((yystack_[1].value.tree));
															(yystack_[3].value.tree).addBrother(temp1);
															int nowlevel=(yystack_[3].value.tree).rootNode()->level;
															(yylhs.value.tree).rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[3].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[1].value.tree).rootNode()->style));
															(yylhs.value.tree).rootNode()->type="DECLARATOR";
															(yylhs.value.tree).rootNode()->value="DECLARATOR";
															(yylhs.value.tree).rootNode()->level=nowlevel+1;
															(yystack_[3].value.tree).addFather((yylhs.value.tree));
															(yylhs.value.tree)=(yystack_[3].value.tree);
															list<ASTNode> l;
															(yylhs.value.tree).getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[3].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[1].value.tree).rootNode()->style));
																putSymbol.type = index;
																if (!sigTable.isRepeatInScope(l.front().value))
																{
																	sigTable.put(l.front().value, putSymbol);
																	index++;
																}
																else {
																	CP::Parser::error(location_type(), "Replication declaration!");
																	system("pause");
																}
																l.pop_front();
															}
														}
#line 881 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 17:
#line 326 "parser.y" // lalr1.cc:859
    {
															int maxLevel=max({(yystack_[4].value.tree).rootNode()->level,(yystack_[2].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=maxLevel;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=maxLevel;
															(yystack_[4].value.tree).changeLevel(maxLevel);
															(yystack_[2].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).changeLevel(maxLevel);
															(yystack_[1].value.tree).addBrother(temp2);
															(yystack_[2].value.tree).addBrother((yystack_[1].value.tree));
															temp1.addBrother((yystack_[2].value.tree));
															(yystack_[4].value.tree).addBrother(temp1);
															int nowlevel=(yystack_[4].value.tree).rootNode()->level;
															(yylhs.value.tree).rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[4].value.tree).rootNode()->style)+LEVEL_OF_POINTER((yystack_[2].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[1].value.tree).rootNode()->style));
															(yylhs.value.tree).rootNode()->type="DECLARATOR";
															(yylhs.value.tree).rootNode()->value="DECLARATOR";
															(yylhs.value.tree).rootNode()->level=nowlevel+1;
															(yystack_[4].value.tree).addFather((yylhs.value.tree));
															(yylhs.value.tree)=(yystack_[4].value.tree);
															list<ASTNode> l;
															(yylhs.value.tree).getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER((yystack_[4].value.tree).rootNode()->style)+LEVEL_OF_POINTER((yystack_[2].value.tree).rootNode()->style)+LEVEL_OF_ARRAY((yystack_[1].value.tree).rootNode()->style));
																putSymbol.type = index;
																if (!sigTable.isRepeatInScope(l.front().value))
																{
																	sigTable.put(l.front().value, putSymbol);
																	index++;
																}
																else {
																	CP::Parser::error(location_type(), "Replication declaration!");
																	system("pause");
																}
																l.pop_front();
															}
														}
#line 929 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 18:
#line 369 "parser.y" // lalr1.cc:859
    {
															int nowlevel=(yystack_[0].value.tree).rootNode()->level;
															(yylhs.value.tree).rootNode()->style=MAKE_TYPE_BY_UNKNOWN(currentType, (yystack_[0].value.tree).rootNode()->style);
															(yylhs.value.tree).rootNode()->type="DECLARATOR";
															(yylhs.value.tree).rootNode()->value="DECLARATOR";
															(yylhs.value.tree).rootNode()->level=nowlevel+1;
															(yystack_[0].value.tree).addFather((yylhs.value.tree));
															(yylhs.value.tree)=(yystack_[0].value.tree);
															list<ASTNode> l;
															(yylhs.value.tree).getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = MAKE_TYPE_BY_UNKNOWN(currentType, (yystack_[0].value.tree).rootNode()->style);
																putSymbol.type = index;
																if (!sigTable.isRepeatInScope(l.front().value))
																{
																	sigTable.put(l.front().value, putSymbol);
																	index++;
																}
																else {
																	CP::Parser::error(location_type(), "Replication declaration!");
																	system("pause");
																}
																l.pop_front();
															}
														}
#line 961 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 19:
#line 397 "parser.y" // lalr1.cc:859
    {
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
															(yystack_[1].value.tree).addBrother(temp2);
															temp1.addBrother((yystack_[1].value.tree));
															int nowlevel=temp1.rootNode()->level;
															(yylhs.value.tree).rootNode()->style= MAKE_TYPE_BY_UNKNOWN(currentType, (yystack_[1].value.tree).rootNode()->style);
															(yylhs.value.tree).rootNode()->type="DECLARATOR";
															(yylhs.value.tree).rootNode()->value="DECLARATOR";
															(yylhs.value.tree).rootNode()->level=nowlevel+1;
															temp1.addFather((yylhs.value.tree));
															(yylhs.value.tree)=temp1;
															list<ASTNode> l;
															(yylhs.value.tree).getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = MAKE_TYPE_BY_UNKNOWN(currentType, (yystack_[1].value.tree).rootNode()->style);
																putSymbol.type = index;
																if (!sigTable.isRepeatInScope(l.front().value))
																{
																	sigTable.put(l.front().value, putSymbol);
																	index++;
																}
																else {
																	CP::Parser::error(location_type(), "Replication declaration!");
																	system("pause");
																}
																l.pop_front();
															}
														}
#line 1003 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 20:
#line 436 "parser.y" // lalr1.cc:859
    {
											(yylhs.value.tree).rootNode()->style=TYPE_POINTER(TYPE_UNKNOWN, 1);
											(yylhs.value.tree).rootNode()->type="POINTER";
											(yylhs.value.tree).rootNode()->value="*";
											(yylhs.value.tree).rootNode()->level=0;
										}
#line 1014 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 21:
#line 442 "parser.y" // lalr1.cc:859
    {
											AST ptr;
											ptr.rootNode()->style=TYPE_UNKNOWN;
											ptr.rootNode()->type="POINTER";
											ptr.rootNode()->value="*";
											ptr.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
											(yystack_[1].value.tree).addBrother(ptr);
											int nowlevel=(yystack_[1].value.tree).rootNode()->level;
											(yylhs.value.tree).rootNode()->type="POINTER";
											(yylhs.value.tree).rootNode()->value="POINTER";
											(yylhs.value.tree).rootNode()->level=nowlevel+1;
											(yylhs.value.tree).rootNode()->style=TYPE_POINTER(TYPE_OF_POINTER((yystack_[1].value.tree).rootNode()->style),LEVEL_OF_POINTER((yystack_[1].value.tree).rootNode()->style)+1);
											(yystack_[1].value.tree).addFather((yylhs.value.tree));
											(yylhs.value.tree)=(yystack_[1].value.tree);
										}
#line 1034 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 22:
#line 459 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=(yystack_[0].value.str);
																				temp1.rootNode()->level=0;
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="DIRECT_DECL";
																				(yylhs.value.tree).rootNode()->level=1;
																				(yylhs.value.tree).rootNode()->style=temp1.rootNode()->style;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1052 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 23:
#line 472 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="LSQUARE";
																				temp1.rootNode()->value="[";
																				temp1.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="RSQUARE";
																				temp2.rootNode()->value="]";
																				temp2.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				temp1.addBrother(temp2);
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=TYPE_ARRAY(TYPE_OF_ARRAY((yystack_[2].value.tree).rootNode()->style),LEVEL_OF_ARRAY((yystack_[2].value.tree).rootNode()->style)+1);
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="DIRECT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);	
																				leftLevel = 999;
																			}
#line 1077 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 24:
#line 493 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[3].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LSQUARE";
																				temp1.rootNode()->value="[";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RSQUARE";
																				temp2.rootNode()->value="]";
																				temp2.rootNode()->level=maxLevel;
																				(yystack_[3].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[1].value.tree));
																				(yystack_[3].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[3].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=TYPE_ARRAY(TYPE_OF_ARRAY((yystack_[3].value.tree).rootNode()->style),LEVEL_OF_ARRAY((yystack_[3].value.tree).rootNode()->style)+1);
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="DIRECT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[3].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[3].value.tree);	
																				if(!isStrNumInt((yystack_[1].value.tree).rootNode()->explain)){
																					CP::Parser::error(location_type(), "Must be int!");
																					system("pause");
																				}
																				leftLevel = stringToNum<int>((yystack_[1].value.tree).rootNode()->explain);
																			}
#line 1110 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 25:
#line 521 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=(yystack_[3].value.str);
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp3);
																				temp2.addBrother((yystack_[1].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=(yystack_[1].value.tree).rootNode()->style;
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="DIRECT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;	
																			}
#line 1140 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 26:
#line 546 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=(yystack_[2].value.str);
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=0;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=0;
																				temp2.addBrother(temp3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=temp1.rootNode()->style;
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="DIRECT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;	
																			}
#line 1169 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 27:
#line 628 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="CONSTANT_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->explain=(yystack_[0].value.tree).rootNode()->value;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1183 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 28:
#line 639 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="PARAMETER_LIST";
																				(yylhs.value.tree).rootNode()->value="PARAMETER_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1196 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 29:
#line 647 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp1.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="PARAMETER_LIST";
																				(yylhs.value.tree).rootNode()->value="PARAMETER_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 1218 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 30:
#line 666 "parser.y" // lalr1.cc:859
    {
																				if(!sigTable.isRepeatInScope((yystack_[0].value.str)))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put((yystack_[0].value.str), putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get((yystack_[0].value.str));
																				AST temp1;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=(yystack_[0].value.str);
																				temp1.rootNode()->explain=to_string(outSymbol.type);
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="PARAMETER_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);
																			}
#line 1245 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 31:
#line 690 "parser.y" // lalr1.cc:859
    {
																				beforeLeave(sigTable.returnMap(), false);
																				beforeLeave(tempTable.returnMap(), true);
																				sigTable.leaveScope();
																				tempTable.leaveScope();
																				AST temp1;
																				temp1.rootNode()->type="LBRACE";
																				temp1.rootNode()->value="{";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="RBRACE";
																				temp2.rootNode()->value="}";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="COMPOUND_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();	
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1271 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 32:
#line 711 "parser.y" // lalr1.cc:859
    {
																				beforeLeave(sigTable.returnMap(), false);
																				beforeLeave(tempTable.returnMap(), true);
																				sigTable.leaveScope();
																				tempTable.leaveScope();
																				if((yystack_[1].value.tree).rootNode()->value=="STATEMENT_LIST")
																				{
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																					(yystack_[1].value.tree).addBrother(temp2);
																					temp1.addBrother((yystack_[1].value.tree));
																					int nowlevel=temp1.rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="STATEMENT";
																					(yylhs.value.tree).rootNode()->value="COMPOUND_STAT";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->next=(yystack_[1].value.tree).rootNode()->next;
																					temp1.addFather((yylhs.value.tree));
																					(yylhs.value.tree)=temp1;
																				}
																				else
																				{
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=0;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=0;
																					temp1.addBrother(temp2);
																					(yylhs.value.tree).rootNode()->type="STATEMENT";
																					(yylhs.value.tree).rootNode()->value="COMPOUND_STAT";
																					(yylhs.value.tree).rootNode()->level=1;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					temp1.addFather((yylhs.value.tree));
																					(yylhs.value.tree)=temp1;
																				}
																			}
#line 1320 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 33:
#line 755 "parser.y" // lalr1.cc:859
    {
																				beforeLeave(sigTable.returnMap(), false);
																				beforeLeave(tempTable.returnMap(), true);
																				sigTable.leaveScope();
																				tempTable.leaveScope();
																				if((yystack_[1].value.tree).rootNode()->value=="STATEMENT_LIST")
																				{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=maxLevel;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[1].value.tree).changeLevel(maxLevel);
																					(yystack_[1].value.tree).addBrother(temp2);
																					(yystack_[2].value.tree).addBrother((yystack_[1].value.tree));
																					temp1.addBrother((yystack_[2].value.tree));
																					int nowlevel=temp1.rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="STATEMENT";
																					(yylhs.value.tree).rootNode()->value="COMPOUND_STAT";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->next=(yystack_[1].value.tree).rootNode()->next;
																					temp1.addFather((yylhs.value.tree));
																					(yylhs.value.tree)=temp1;
																				}
																				else
																				{
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																					(yystack_[2].value.tree).addBrother(temp2);
																					temp1.addBrother((yystack_[2].value.tree));
																					int nowlevel=temp1.rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="STATEMENT";
																					(yylhs.value.tree).rootNode()->value="COMPOUND_STAT";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->next=(yystack_[2].value.tree).rootNode()->next;
																					temp1.addFather((yylhs.value.tree));
																					(yylhs.value.tree)=temp1;
																				}
																			}
#line 1375 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 34:
#line 807 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION_LIST";
																				(yylhs.value.tree).rootNode()->value="DECLARATION_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1389 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 35:
#line 816 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION_LIST";
																				(yylhs.value.tree).rootNode()->value="DECLARATION_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);
																			}
#line 1407 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 36:
#line 831 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="DECLARATION";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[1].value.tree).rootNode()->next;
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);
																			}
#line 1426 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 37:
#line 845 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother(temp1);
																				(yystack_[2].value.tree).addBrother((yystack_[1].value.tree));
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="DECLARATION";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[1].value.tree).rootNode()->next;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 1449 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 38:
#line 865 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp1.addBrother((yystack_[0].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL_TAIL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1468 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 39:
#line 879 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp1.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;

																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL_TAIL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 1492 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 40:
#line 900 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				if (IS_POINTER((yystack_[0].value.tree).rootNode()->style)){
																					(yylhs.value.tree).rootNode()->style=TYPE_POINTER((yystack_[1].value.tree).rootNode()->style, LEVEL_OF_POINTER((yystack_[0].value.tree).rootNode()->style));
																				}
																				else if (IS_ARRAY((yystack_[0].value.tree).rootNode()->style)){
																					(yylhs.value.tree).rootNode()->style=TYPE_ARRAY((yystack_[1].value.tree).rootNode()->style, LEVEL_OF_ARRAY((yystack_[0].value.tree).rootNode()->style));
																				}
																				else {
																					(yylhs.value.tree).rootNode()->style=(yystack_[1].value.tree).rootNode()->style;
																				}
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);
																			}
#line 1519 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 41:
#line 922 "parser.y" // lalr1.cc:859
    {
																				
																				int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="AUTO";
																				temp1.rootNode()->value=(yystack_[2].value.str);
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																				temp1.addBrother((yystack_[1].value.tree));
																				if (IS_POINTER((yystack_[0].value.tree).rootNode()->style)){
																					(yylhs.value.tree).rootNode()->style=TYPE_POINTER((yystack_[1].value.tree).rootNode()->style, LEVEL_OF_POINTER((yystack_[0].value.tree).rootNode()->style));
																				}
																				else if (IS_ARRAY((yystack_[0].value.tree).rootNode()->style)){
																					(yylhs.value.tree).rootNode()->style=TYPE_ARRAY((yystack_[1].value.tree).rootNode()->style, LEVEL_OF_ARRAY((yystack_[0].value.tree).rootNode()->style));
																				}
																				else {
																					(yylhs.value.tree).rootNode()->style=(yystack_[1].value.tree).rootNode()->style;
																				}
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1552 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 42:
#line 950 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->explain=="no")
																				{
																					 CP::Parser::error(location_type(), "bad!");
																					 system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="AUTO";
																				temp1.rootNode()->value=(yystack_[1].value.str);
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp1.addBrother((yystack_[0].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=TYPE_INT;
																				(yylhs.value.tree).rootNode()->type="DECLARATION";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1577 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 43:
#line 972 "parser.y" // lalr1.cc:859
    {
																
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL_BODY";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->explain="no";

																				(yylhs.value.tree).rootNode()->value = (yystack_[0].value.tree).rootNode()->value;
																				(yylhs.value.tree).rootNode()->next = qualdruples.nextKey();
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1596 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 44:
#line 986 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="ASSIGN";
																				temp1.rootNode()->value="=";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp1.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				//printf("LEFT: %d\n", $1.rootNode()->style);
																				//printf("RIGHT: %d\n", $3.rootNode()->style);
																				if(!CAN_ASSIGH(MAKE_LEXPR_BY_TYPE((yystack_[2].value.tree).rootNode()->style), (yystack_[0].value.tree).rootNode()->style)){
																					CP::Parser::error(location_type(), "Initial fail!");
																					system("pause");
																				}
																				if(leftLevel < rightLevel){
																					CP::Parser::error(location_type(), "List is too large!");
																					system("pause");
																				}
																				(yylhs.value.tree).rootNode()->type="DECLARATOR";
																				(yylhs.value.tree).rootNode()->value="INIT_DECL_BODY";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;

																				list<ASTNode> l;
																				(yystack_[2].value.tree).getNodesWanted(isIdType, l);
																				qualdruples.append("=", (yystack_[0].value.tree).rootNode()->value, "", l.front().value);
																				(yylhs.value.tree).rootNode()->next = qualdruples.nextKey();

																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																				
																			}
#line 1635 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 45:
#line 1022 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					(yylhs.value.tree).rootNode()->type="INITIALIZER";
																					(yylhs.value.tree).rootNode()->value="INITIALIZER";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;


																					(yylhs.value.tree).rootNode()->value = (yystack_[0].value.tree).rootNode()->value;
																					(yylhs.value.tree).rootNode()->next = qualdruples.nextKey();
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}

																			}
#line 1659 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 46:
#line 1041 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="LBRACE";
																				temp1.rootNode()->value="{";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="RBRACE";
																				temp2.rootNode()->value="}";
																				temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[1].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_ARRAY(TYPE_OF_EXPR((yystack_[1].value.tree).rootNode()->style), 1);
																				(yylhs.value.tree).rootNode()->type="INITIALIZER";
																				(yylhs.value.tree).rootNode()->value="INITIALIZER";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1683 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 47:
#line 1060 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="LBRACE";
																				temp1.rootNode()->value="{";
																				temp1.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="COMMA";
																				temp2.rootNode()->value=",";
																				temp2.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				AST temp3;
																				temp3.rootNode()->type="RBRACE";
																				temp3.rootNode()->value="}";
																				temp3.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				temp2.addBrother(temp3);
																				(yystack_[2].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[2].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=(yylhs.value.tree).rootNode()->style=TYPE_REXPR_ARRAY(TYPE_OF_EXPR((yystack_[2].value.tree).rootNode()->style), 1);
																				(yylhs.value.tree).rootNode()->type="INITIALIZER";
																				(yylhs.value.tree).rootNode()->value="INITIALIZER";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1712 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 48:
#line 1086 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																				(yylhs.value.tree).rootNode()->type="INITIALIZER_LIST";
																				(yylhs.value.tree).rootNode()->value="INITIALIZER_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																				rightLevel = 1;
																			}
#line 1727 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 49:
#line 1096 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp1.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				int style = FIND_MAX_TYPE((yystack_[2].value.tree).rootNode()->style, (yystack_[0].value.tree).rootNode()->style);
																				if(style > 0){
																					(yylhs.value.tree).rootNode()->style=FIND_MAX_TYPE((yystack_[2].value.tree).rootNode()->style, (yystack_[0].value.tree).rootNode()->style);
																				}
																				else {
																					CP::Parser::error(location_type(), "list item is not same");
																					system("pause");
																				}
																				(yylhs.value.tree).rootNode()->type="INITIALIZER_LIST";
																				(yylhs.value.tree).rootNode()->value="INITIALIZER_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																				rightLevel += 1;
																			}
#line 1758 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 50:
#line 1124 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT_LIST";
																				(yylhs.value.tree).rootNode()->value="STATEMENT_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1772 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 51:
#line 1133 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT_LIST";
																				(yylhs.value.tree).rootNode()->value="STATEMENT_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);
																			}
#line 1790 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 53:
#line 1149 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1804 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 54:
#line 1158 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1818 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 55:
#line 1167 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1832 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 56:
#line 1176 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1846 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 57:
#line 1185 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1859 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 58:
#line 1193 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1873 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 59:
#line 1202 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1887 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 60:
#line 1211 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="STATEMENT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 1900 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 61:
#line 1221 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="READ";
																				temp1.rootNode()->value="READ";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=0;
																				AST temp4;
																				temp4.rootNode()->type="RCURVE";
																				temp4.rootNode()->value=")";
																				temp4.rootNode()->level=0;
																				AST temp5;
																				temp5.rootNode()->type="SQM";
																				temp5.rootNode()->value=";";
																				temp5.rootNode()->level=0;
																				temp4.addBrother(temp5);
																				(yystack_[2].value.tree).addBrother(temp4);
																				temp2.addBrother((yystack_[2].value.tree));
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="READ_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				qualdruples.append("READ",(yystack_[2].value.tree).rootNode()->value,"","", false);
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1934 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 62:
#line 1252 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="WRITE";
																				temp1.rootNode()->value="WRITE";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=0;
																				AST temp4;
																				temp4.rootNode()->type="RCURVE";
																				temp4.rootNode()->value=")";
																				temp4.rootNode()->level=0;
																				AST temp5;
																				temp5.rootNode()->type="SQM";
																				temp5.rootNode()->value=";";
																				temp5.rootNode()->level=0;
																				temp4.addBrother(temp5);
																				(yystack_[2].value.tree).addBrother(temp4);
																				temp2.addBrother((yystack_[2].value.tree));
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="WRITE_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				qualdruples.append("WRITE",(yystack_[2].value.tree).rootNode()->value,"","", false);
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1968 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 63:
#line 1283 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=0;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="EXPRESSION_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 1985 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 64:
#line 1295 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="EXPRESSION_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->next=(yystack_[1].value.tree).rootNode()->next;
																				(yylhs.value.tree).rootNode()->value=(yystack_[1].value.tree).rootNode()->value;
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);
																			}
#line 2005 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 65:
#line 1312 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="IF";
																				temp1.rootNode()->value="IF";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=maxLevel;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp3.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp3);
																				temp2.addBrother((yystack_[2].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="SELECTION_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[2].value.tree).rootNode()->next,"IF",(yystack_[2].value.tree).rootNode()->value,"",(yystack_[0].value.tree).rootNode()->next);
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2040 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 66:
#line 1342 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[4].value.tree).rootNode()->level,(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="IF";
																				temp1.rootNode()->value="IF";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=maxLevel;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=maxLevel;
																				AST temp4;
																				temp4.rootNode()->type="ELSE";
																				temp4.rootNode()->value="ELSE";
																				temp4.rootNode()->level=maxLevel;
																				(yystack_[4].value.tree).changeLevel(maxLevel);
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp4.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp4);
																				temp3.addBrother((yystack_[2].value.tree));
																				(yystack_[4].value.tree).addBrother(temp3);
																				temp2.addBrother((yystack_[4].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="SELECTION_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[2].value.tree).addNext();
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[4].value.tree).rootNode()->next,"IF",(yystack_[4].value.tree).rootNode()->value,"",(yystack_[2].value.tree).rootNode()->next);
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[2].value.tree).rootNode()->next,"GOTO","","",(yystack_[0].value.tree).rootNode()->next);
																				if(!qualdruples.modifyKey((yystack_[4].value.tree).rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail!");
																					system("pause");
																				}
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2090 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 67:
#line 1389 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="WHILE";
																				temp1.rootNode()->value="WHILE";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=maxLevel;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp3.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp3);
																				temp2.addBrother((yystack_[2].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="ITERATION_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[2].value.tree).rootNode()->next,"WHILE",(yystack_[2].value.tree).rootNode()->value,"",(yystack_[0].value.tree).rootNode()->next);
																				qualdruples.insert((yystack_[0].value.tree).rootNode()->next,"GOTO","","",(yystack_[4].value.wnext),true);
																				if(!qualdruples.modifyKey((yystack_[2].value.tree).rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail!");
																					system("pause");
																				}
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2131 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 68:
#line 1426 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[3].value.tree).rootNode()->level,(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="FOR";
																				temp1.rootNode()->value="FOR";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=maxLevel;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=maxLevel;
																				(yystack_[3].value.tree).changeLevel(maxLevel);
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp3.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp3);
																				(yystack_[3].value.tree).addBrother((yystack_[2].value.tree));
																				temp2.addBrother((yystack_[3].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="ITERATION_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[2].value.tree).rootNode()->next,"FOR",(yystack_[2].value.tree).rootNode()->value,"",(yystack_[0].value.tree).rootNode()->next);
																				qualdruples.insert((yystack_[0].value.tree).rootNode()->next,"GOTO","","",(yystack_[3].value.tree).rootNode()->next,true);
																				if(!qualdruples.modifyKey((yystack_[2].value.tree).rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail!");
																					system("pause");
																				}
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2174 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 69:
#line 1465 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[4].value.tree).rootNode()->level,(yystack_[3].value.tree).rootNode()->level,(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="FOR";
																				temp1.rootNode()->value="FOR";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=maxLevel;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=maxLevel;
																				(yystack_[4].value.tree).changeLevel(maxLevel);
																				(yystack_[3].value.tree).changeLevel(maxLevel);
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp3.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp3);
																				(yystack_[3].value.tree).addBrother((yystack_[2].value.tree));
																				(yystack_[4].value.tree).addBrother((yystack_[3].value.tree));
																				temp2.addBrother((yystack_[4].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="ITERATION_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[2].value.tree).addNext();
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[3].value.tree).rootNode()->next,"FOR",(yystack_[3].value.tree).rootNode()->value,"",(yystack_[0].value.tree).rootNode()->next);
																				(yystack_[2].value.tree).addNext();
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[3].value.tree).rootNode()->next+1,"GOTO","","",(yystack_[2].value.tree).rootNode()->next);
																				qualdruples.insert((yystack_[0].value.tree).rootNode()->next,"GOTO","","",(yystack_[3].value.tree).rootNode()->next+2,true);
																				if(!qualdruples.modifyKey((yystack_[3].value.tree).rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail11!");
																					system("pause");
																				}
																				(yystack_[0].value.tree).addNext();
																				qualdruples.insert((yystack_[2].value.tree).rootNode()->next,"GOTO","","",(yystack_[4].value.tree).rootNode()->next,true);
																				if(!qualdruples.modifyKey((yystack_[3].value.tree).rootNode()->next+1,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail22!");
																					system("pause");
																				}
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2230 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 70:
#line 1518 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="CONTINUE";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="JUMP_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2251 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 71:
#line 1534 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="BREAK";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="JUMP_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2272 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 72:
#line 1550 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="RETURN";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="JUMP_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2293 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 73:
#line 1566 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="RETURN";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[1].value.tree));
																				int nowLevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="JUMP_STAT";
																				(yylhs.value.tree).rootNode()->level=nowLevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2316 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 74:
#line 1584 "parser.y" // lalr1.cc:859
    {
																				Symbol outSymbol=sigTable.get((yystack_[1].value.str));
																				if(outSymbol.type==0)
																				{
																					CP::Parser::error(location_type(), "Undefined");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="GOTO";
																				temp1.rootNode()->value=(yystack_[2].value.str);
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=(yystack_[1].value.str);
																				temp2.rootNode()->explain=to_string(outSymbol.type);
																				temp2.rootNode()->level=0;
																				AST temp3;
																				temp3.rootNode()->type="SQM";
																				temp3.rootNode()->value=";";
																				temp3.rootNode()->level=0;
																				temp2.addBrother(temp3);
																				temp1.addBrother(temp2);
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="JUMP_STAT";
																				(yylhs.value.tree).rootNode()->level=1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 2349 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 75:
#line 1614 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="EXPRESSION";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2372 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 76:
#line 1632 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp1.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="EXPRESSION";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																				///
																				(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																				(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																				///
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 2399 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 77:
#line 1656 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="ASSIGNMENT_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2422 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 78:
#line 1675 "parser.y" // lalr1.cc:859
    {
																				if(!CAN_ASSIGH((yystack_[2].value.tree).rootNode()->style,(yystack_[0].value.tree).rootNode()->style))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother((yystack_[1].value.tree));
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="ASSIGNMENT_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																				////
																				if(!((yystack_[2].value.tree).rootNode()->value==(yystack_[0].value.tree).rootNode()->value)){
																					string t=qualdruples.append((yystack_[1].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value,"",(yystack_[2].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				////
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);

																			}
#line 2454 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 79:
#line 1704 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="CONDITIONAL_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2477 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 80:
#line 1723 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[4].value.tree).rootNode()->level,(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="QUESTION";
																				temp1.rootNode()->value="?";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=maxLevel;
																				(yystack_[4].value.tree).changeLevel(maxLevel);
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp2.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp2);
																				temp2.addBrother((yystack_[2].value.tree));
																				(yystack_[4].value.tree).addBrother(temp2);
																				int nowlevel=(yystack_[4].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="CONDITIONAL_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR;
																				(yystack_[4].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[4].value.tree);
																			}
#line 2507 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 81:
#line 1750 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="LOGICAL_OR_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2530 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 82:
#line 1769 "parser.y" // lalr1.cc:859
    {
																				if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"||",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="OR_OP";
																					temp1.rootNode()->value="||";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="LOGICAL_OR_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);

																					///
																					string t=qualdruples.append("||",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																			}
#line 2573 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 83:
#line 1809 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="LOGICAL_AND_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///

																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2597 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 84:
#line 1829 "parser.y" // lalr1.cc:859
    {
																				if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"&&",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="AND_OP";
																					temp1.rootNode()->value="&&";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="LOGICAL_AND_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("&&",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);

																				}
																			}
#line 2641 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 85:
#line 1870 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="INCLUSIVE_OR_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2664 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 86:
#line 1889 "parser.y" // lalr1.cc:859
    {
																				if(!(CAN_BIT((yystack_[2].value.tree).rootNode()->style)&&CAN_BIT((yystack_[0].value.tree).rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"|",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="INCLUSIVE_OR";
																					temp1.rootNode()->value="|";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="INCLUSIVE_OR_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					////
																					string t=qualdruples.append("|",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																					
																				}
																			}
#line 2713 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1935 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="EXCLUSIVE_OR_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2736 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1953 "parser.y" // lalr1.cc:859
    {
																				if(!(CAN_BIT((yystack_[2].value.tree).rootNode()->style)&&CAN_BIT((yystack_[0].value.tree).rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"^",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="EXCLUSIVE_OR";
																					temp1.rootNode()->value="^";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="EXCLUSIVE_OR_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					////
																					string t=qualdruples.append("^",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																					
																				}
																			}
#line 2785 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1999 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="AND_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																					
																				}
																			}
#line 2809 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 90:
#line 2018 "parser.y" // lalr1.cc:859
    {
																				if(!(CAN_BIT((yystack_[2].value.tree).rootNode()->style)&&CAN_BIT((yystack_[0].value.tree).rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"&",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="AND";
																					temp1.rootNode()->value="&";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="AND_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					////
																					string t=qualdruples.append("&",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																					
																				}
																			}
#line 2858 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 91:
#line 2064 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="EQUALITY_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2881 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 92:
#line 2082 "parser.y" // lalr1.cc:859
    {
																				if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"==",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="EQ_OP";
																					temp1.rootNode()->value="==";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="EQUALITY_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("==",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																				}
																			}
#line 2924 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 93:
#line 2120 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"!=",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="NE_OP";
																					temp1.rootNode()->value="!=";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="EQUALITY_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("!=",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																				}
																			}
#line 2969 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 94:
#line 2162 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="RELATIONAL_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 2992 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 95:
#line 2180 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"<",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LESS";
																					temp1.rootNode()->value="<";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="RELATIONAL_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("<",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);

																				}

																			}
#line 3039 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 96:
#line 2222 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,">",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="GREATER";
																					temp1.rootNode()->value=">";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="RELATIONAL_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append(">",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);

																				}
																			}
#line 3085 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 97:
#line 2263 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"<=",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LE_OP";
																					temp1.rootNode()->value="<=";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="RELATIONAL_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("<=",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																				}
																			}
#line 3130 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 98:
#line 2303 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,">=",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="GE_OP";
																					temp1.rootNode()->value=">=";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="RELATIONAL_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append(">=",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																					
																				}
																			}
#line 3176 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 99:
#line 2346 "parser.y" // lalr1.cc:859
    {
																				string type=(yystack_[0].value.tree).rootNode()->type;
																				if(type=="INT_CONST"||type=="DOUBLE_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="SHIFT_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 3200 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 100:
#line 2365 "parser.y" // lalr1.cc:859
    {
																				if(!(CAN_BIT((yystack_[2].value.tree).rootNode()->style)&&CAN_BIT((yystack_[0].value.tree).rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"<<",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LEFT_OP";
																					temp1.rootNode()->value="<<";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="SHIFT_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					////
																					string t=qualdruples.append("<<",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																					
																				}

																			}
#line 3252 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 101:
#line 2412 "parser.y" // lalr1.cc:859
    {
																				if(!(CAN_BIT((yystack_[2].value.tree).rootNode()->style)&&CAN_BIT((yystack_[0].value.tree).rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,">>",val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					
																				}
																				else{
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="RIGHT_OP";
																					temp1.rootNode()->value=">>";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="SHIFT_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					////
																					string t=qualdruples.append(">>",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																					
																				}

																			}
#line 3305 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 102:
#line 2462 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="ADDITIVE_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 3328 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 103:
#line 2480 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;

																					string result="";
																					if(type1=="CHAR_CONST"){
																						char val1=value1[1];
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1+val2);
																					}
																					else if(type2=="CHAR_CONST"){
																						char val2=value2[1];
																						double val1=stringToNum<double>(value1);
																						result=numToString<double>(val1+val2);
																					}
																					else{
																						double val1=stringToNum<double>(value1);
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1+val2);
																					}

																					//如果两个变量不都是整形
																					if(!((type1=="INT_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="CHAR_CONST"))){
																						if(isStrNumInt(result)){
																							result+=".0";
																						}
																					}
																					
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="CHAR_CONST")&&(yystack_[2].value.tree).rootNode()->value=="0"){
																						(yylhs.value.tree)=(yystack_[0].value.tree);
																					}
																					else if(((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST")&&(yystack_[0].value.tree).rootNode()->value=="0"){
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																					else{
																						int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="ADD";
																						temp1.rootNode()->value="+";
																						temp1.rootNode()->level=maxLevel;
																						(yystack_[2].value.tree).changeLevel(maxLevel);
																						(yystack_[0].value.tree).changeLevel(maxLevel);
																						temp1.addBrother((yystack_[0].value.tree));
																						(yystack_[2].value.tree).addBrother(temp1);
																						int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																						(yylhs.value.tree).rootNode()->type="EXPRESSION";
																						(yylhs.value.tree).rootNode()->value="ADDITIVE_EXPR1";
																						(yylhs.value.tree).rootNode()->level=nowlevel+1;
																						(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																						///
																						string t=qualdruples.append("+",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																						(yylhs.value.tree).rootNode()->value=t;
																						(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																						///
																						(yystack_[2].value.tree).addFather((yylhs.value.tree));
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																				}

																			}
#line 3405 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 104:
#line 2552 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;

																					string result="";
																					if(type1=="CHAR_CONST"){
																						char val1=value1[1];
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1-val2);
																					}
																					else if(type2=="CHAR_CONST"){
																						char val2=value2[1];
																						double val1=stringToNum<double>(value1);
																						result=numToString<double>(val1-val2);
																					}
																					else{
																						double val1=stringToNum<double>(value1);
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1-val2);
																					}
																					//如果两个变量不都是整形
																					if(!((type1=="INT_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="CHAR_CONST"))){
																						if(isStrNumInt(result)){
																							result+=".0";
																						}
																					}
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST")&&(yystack_[0].value.tree).rootNode()->value=="0"){
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																					else{
																						int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="SUB";
																						temp1.rootNode()->value="-";
																						temp1.rootNode()->level=maxLevel;
																						(yystack_[2].value.tree).changeLevel(maxLevel);
																						(yystack_[0].value.tree).changeLevel(maxLevel);
																						temp1.addBrother((yystack_[0].value.tree));
																						(yystack_[2].value.tree).addBrother(temp1);
																						int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																						(yylhs.value.tree).rootNode()->type="EXPRESSION";
																						(yylhs.value.tree).rootNode()->value="ADDITIVE_EXPR";
																						(yylhs.value.tree).rootNode()->level=nowlevel+1;
																						(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																						////
																						string t=qualdruples.append("-",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																						(yylhs.value.tree).rootNode()->value=t;
																						(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																						////
																						(yystack_[2].value.tree).addFather((yylhs.value.tree));
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																				}

																			}
#line 3476 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 105:
#line 2620 "parser.y" // lalr1.cc:859
    {
                                                                                if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="MULTIPLICATIVE_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}

																			}
#line 3500 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 106:
#line 2639 "parser.y" // lalr1.cc:859
    {
							                                                    string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;

																					string result="";
																					if(type1=="CHAR_CONST"){
																						char val1=value1[1];
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1*val2);
																					}
																					else if(type2=="CHAR_CONST"){
																						char val2=value2[1];
																						double val1=stringToNum<double>(value1);
																						result=numToString<double>(val1*val2);
																					}
																					else{
																						double val1=stringToNum<double>(value1);
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1*val2);
																					}
																					//如果两个变量不都是整形
																					if(!((type1=="INT_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="CHAR_CONST"))){
																						if(isStrNumInt(result)){
																							result+=".0";
																						}
																					}
																					
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(((yystack_[2].value.tree).rootNode()->type=="INT_CONST"||(yystack_[2].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[2].value.tree).rootNode()->type=="CHAR_CONST")&&(yystack_[2].value.tree).rootNode()->value=="1"){
																						(yylhs.value.tree)=(yystack_[0].value.tree);
																					}
																					else if(((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST")&&(yystack_[0].value.tree).rootNode()->value=="1"){
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																					else{
																						int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="MULTI";
																						temp1.rootNode()->value="*";
																						temp1.rootNode()->level=maxLevel;
																						(yystack_[2].value.tree).changeLevel(maxLevel);
																						(yystack_[0].value.tree).changeLevel(maxLevel);
																						temp1.addBrother((yystack_[0].value.tree));
																						(yystack_[2].value.tree).addBrother(temp1);
																						int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																						(yylhs.value.tree).rootNode()->type="EXPRESSION";
																						(yylhs.value.tree).rootNode()->value="MULTIPLICATIVE_EXPR";
																						(yylhs.value.tree).rootNode()->level=nowlevel+1;
																						(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																						////
																						string t=qualdruples.append("*",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																						(yylhs.value.tree).rootNode()->value=t;
																						(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																						////
																						(yystack_[2].value.tree).addFather((yylhs.value.tree));
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																				}
																				
																			}
#line 3575 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 107:
#line 2709 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;

																					string result="";
																					if(type1=="CHAR_CONST"){
																						char val1=value1[1];
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1/val2);
																					}
																					else if(type2=="CHAR_CONST"){
																						char val2=value2[1];
																						double val1=stringToNum<double>(value1);
																						result=numToString<double>(val1/val2);
																					}
																					else{
																						double val1=stringToNum<double>(value1);
																						double val2=stringToNum<double>(value2);
																						result=numToString<double>(val1/val2);
																					}
																					//如果两个变量不都是整形
																					if(!((type1=="INT_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="CHAR_CONST"))){
																						if(isStrNumInt(result)){
																							result+=".0";
																						}
																					}
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST")&&(yystack_[0].value.tree).rootNode()->value=="1"){
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																					else{
																						int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="DIV";
																						temp1.rootNode()->value="/";
																						temp1.rootNode()->level=maxLevel;
																						(yystack_[2].value.tree).changeLevel(maxLevel);
																						(yystack_[0].value.tree).changeLevel(maxLevel);
																						temp1.addBrother((yystack_[0].value.tree));
																						(yystack_[2].value.tree).addBrother(temp1);
																						int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																						(yylhs.value.tree).rootNode()->type="EXPRESSION";
																						(yylhs.value.tree).rootNode()->value="MULTIPLICATIVE_EXPR";
																						(yylhs.value.tree).rootNode()->level=nowlevel+1;
																						(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																						////
																						string t=qualdruples.append("/",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																						(yylhs.value.tree).rootNode()->value=t;
																						(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																						////
																						(yystack_[2].value.tree).addFather((yylhs.value.tree));
																						(yylhs.value.tree)=(yystack_[2].value.tree);
																					}
																				}

																			}
#line 3646 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 108:
#line 2775 "parser.y" // lalr1.cc:859
    {
																				string type1=(yystack_[2].value.tree).rootNode()->type;
																				string type2=(yystack_[0].value.tree).rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=(yystack_[2].value.tree).rootNode()->value;
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<double>(val1%val2);
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					
																				}
																				else{																				
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="MOD";
																					temp1.rootNode()->value="%";
																					temp1.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp1.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp1);
																					int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="MULTIPLICATIVE_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[2].value.tree).rootNode()->style);
																					////
																					string t=qualdruples.append("%",(yystack_[2].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value);
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[2].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[2].value.tree);
																				}
																			}
#line 3692 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 109:
#line 2818 "parser.y" // lalr1.cc:859
    {
                                                                                if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="CAST_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 3715 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 110:
#line 2836 "parser.y" // lalr1.cc:859
    {
																				if(((yystack_[2].value.tree).rootNode()->type=="TYPE_SPECIFIER"&&(yystack_[2].value.tree).rootNode()->value!="VOID")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST")){
																					string type=(yystack_[2].value.tree).rootNode()->value;
																					string value=(yystack_[0].value.tree).rootNode()->value;
																					string result="";
																					if(type=="INT")
																						result=numToString<int>(stringToNum<int>(value));
																					else if(type=="FLOAT"){
																						result=numToString<float>(stringToNum<float>(value));
																						type="DOUBLE";
																					}
																					else if(type=="DOUBLE")
																						result=numToString<double>(stringToNum<double>(value));
																					else if(type=="CHAR")
																						result=numToString<char>(stringToNum<char>(value));
																					else{
																						//error
																					}
																					(yylhs.value.tree).rootNode()->type=type+"_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[0].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																				
																					int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LCURVE";
																					temp1.rootNode()->value="(";
																					temp1.rootNode()->level=maxLevel;
																					AST temp2;
																					temp2.rootNode()->type="RCURVE";
																					temp2.rootNode()->value=")";
																					temp2.rootNode()->level=maxLevel;
																					(yystack_[2].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					temp2.addBrother((yystack_[0].value.tree));
																					(yystack_[2].value.tree).addBrother(temp2);
																					temp1.addBrother((yystack_[2].value.tree));
																					int nowlevel=temp1.rootNode()->level;
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR_BY_TYPE((yystack_[2].value.tree).rootNode()->style);
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="CAST_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					////
																					string t=qualdruples.append(numToString<int>((yystack_[2].value.tree).rootNode()->style),(yystack_[0].value.tree).rootNode()->value,"");
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					temp1.addFather((yylhs.value.tree));
																					(yylhs.value.tree)=temp1;
																				}

																			}
#line 3776 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 111:
#line 2892 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[3].value.tree).rootNode()->level,(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LCURVE";
																				temp1.rootNode()->value="(";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RCURVE";
																				temp2.rootNode()->value=")";
																				temp2.rootNode()->level=maxLevel;
																				(yystack_[3].value.tree).changeLevel(maxLevel);
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp2.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp2);
																				(yystack_[3].value.tree).addBrother((yystack_[2].value.tree));
																				temp1.addBrother((yystack_[3].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->style=MAKE_REXPR_BY_TYPE(TYPE_POINTER((yystack_[3].value.tree).rootNode()->style,LEVEL_OF_POINTER((yystack_[2].value.tree).rootNode()->style)));
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="CAST_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				////
																				string t=qualdruples.append(numToString<int>(TYPE_POINTER((yystack_[3].value.tree).rootNode()->style,LEVEL_OF_POINTER((yystack_[2].value.tree).rootNode()->style))),(yystack_[0].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;	

																			}
#line 3812 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 112:
#line 2925 "parser.y" // lalr1.cc:859
    {
                                                                                
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="UNARY_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 3836 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 113:
#line 2944 "parser.y" // lalr1.cc:859
    {
																				if(CAN_ASSIGN_TO((yystack_[0].value.tree).rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="INC_OP";
																				temp1.rootNode()->value="++";
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp1.addBrother((yystack_[0].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="UNARY_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																				////
																				string t=qualdruples.append("++a",(yystack_[0].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;

																			}
#line 3866 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 114:
#line 2969 "parser.y" // lalr1.cc:859
    {
																				if(CAN_ASSIGN_TO((yystack_[0].value.tree).rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="DEC_OP";
																				temp1.rootNode()->value="--";
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp1.addBrother((yystack_[0].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="UNARY_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																				////
																				string t=qualdruples.append("--a",(yystack_[0].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;

																			}
#line 3896 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 115:
#line 2994 "parser.y" // lalr1.cc:859
    {
																				if(((yystack_[1].value.tree).rootNode()->value=="!"||(yystack_[1].value.tree).rootNode()->value=="-"||(yystack_[1].value.tree).rootNode()->value=="+")&&((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST")){
																					string value2=(yystack_[0].value.tree).rootNode()->value;
																					double val2=stringToNum<double>(value2);
																					string result=numToString<int>(Operate(0,(yystack_[1].value.tree).rootNode()->value,val2));
																					(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																					(yylhs.value.tree).rootNode()->value=result;
																					(yylhs.value.tree).rootNode()->level=max((yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level);
																					(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[0].value.tree).rootNode()->style);
																					///
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({(yystack_[1].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																					(yystack_[1].value.tree).changeLevel(maxLevel);
																					(yystack_[0].value.tree).changeLevel(maxLevel);
																					(yystack_[1].value.tree).addBrother((yystack_[0].value.tree));
																					int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="UNARY_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					if((yystack_[1].value.tree).rootNode()->value=="*"&&IS_POINTER(TYPE_OF_EXPR((yystack_[0].value.tree).rootNode()->style))){
																						(yylhs.value.tree).rootNode()->style=SUB_LEVEL_OF_POINTER_EXPR((yystack_[0].value.tree).rootNode()->style);
																					}
																					else if((yystack_[1].value.tree).rootNode()->value=="&")
																					{
																						if(LEVEL_OF_BASIC_TYPE(TYPE_OF_EXPR((yystack_[0].value.tree).rootNode()->style)) == 0){
																							(yylhs.value.tree).rootNode()->style=TYPE_REXPR_POINTER(TYPE_OF_EXPR((yystack_[0].value.tree).rootNode()->style), 1);
																						}
																						else if(IS_POINTER(TYPE_OF_EXPR((yystack_[0].value.tree).rootNode()->style))){
																							(yylhs.value.tree).rootNode()->style=TYPE_REXPR_POINTER(TYPE_OF_POINTER(TYPE_OF_EXPR((yystack_[0].value.tree).rootNode()->style)), LEVEL_OF_POINTER_EXPR((yystack_[0].value.tree).rootNode()->style) + 1);
																						}
																					}
																					else
																						(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[0].value.tree).rootNode()->style);

																					////
																					string t="";
																					if((yystack_[1].value.tree).rootNode()->value=="&"){
																						t=qualdruples.append("_&",(yystack_[0].value.tree).rootNode()->value,"");
																					}
																					else if((yystack_[1].value.tree).rootNode()->value=="*"){
																						string result="*"+(yystack_[0].value.tree).rootNode()->value;
																						t=qualdruples.append("_*",(yystack_[0].value.tree).rootNode()->value,"",result);
																					}
																					else{
																						t=qualdruples.append((yystack_[1].value.tree).rootNode()->value,(yystack_[0].value.tree).rootNode()->value,"");
																					}
																					(yylhs.value.tree).rootNode()->value=t;
																					(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																					////
																					(yystack_[1].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[1].value.tree);
																				}

																			}
#line 3957 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 116:
#line 3050 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="SIZEOF";
																				temp1.rootNode()->value="SIZEOF";
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp1.addBrother((yystack_[0].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="UNARY_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																				////
																				string t=qualdruples.append("SIZEOF",(yystack_[0].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;

																			}
#line 3982 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 117:
#line 3070 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="SIZEOF";
																				temp1.rootNode()->value="SIZEOF";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp3);
																				temp2.addBrother((yystack_[1].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="UNARY_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																				////
																				string t=qualdruples.append("SIZEOF",(yystack_[1].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;

																			}
#line 4017 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 118:
#line 3102 "parser.y" // lalr1.cc:859
    {
																				
																				if((yystack_[0].value.tree).rootNode()->type=="INT_CONST"||(yystack_[0].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[0].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																				else{
																					int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[0].value.tree).rootNode()->style;
																					///
																					(yylhs.value.tree).rootNode()->next=(yystack_[0].value.tree).rootNode()->next;
																					(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																					///
																					(yystack_[0].value.tree).addFather((yylhs.value.tree));
																					(yylhs.value.tree)=(yystack_[0].value.tree);
																				}
																			}
#line 4041 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 119:
#line 3121 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[3].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LSQUARE";
																				temp1.rootNode()->value="[";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RSQUARE";
																				temp2.rootNode()->value="]";
																				temp2.rootNode()->level=maxLevel;
																				(yystack_[3].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[1].value.tree));
																				(yystack_[3].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[3].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=SUB_LEVEL_OF_ARRAY_EXPR((yystack_[3].value.tree).rootNode()->style);
																				////
																				string t=qualdruples.append("array",(yystack_[3].value.tree).rootNode()->value,(yystack_[1].value.tree).rootNode()->value);
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				(yystack_[3].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[3].value.tree);	


																			}
#line 4076 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 120:
#line 3151 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="LCURVE";
																				temp1.rootNode()->value="(";
																				temp1.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="RCURVE";
																				temp2.rootNode()->value=")";
																				temp2.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				temp1.addBrother(temp2);
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 4100 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 121:
#line 3171 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[3].value.tree).rootNode()->level,(yystack_[1].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LCURVE";
																				temp1.rootNode()->value="(";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RCURVE";
																				temp2.rootNode()->value=")";
																				temp2.rootNode()->level=maxLevel;
																				(yystack_[3].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).changeLevel(maxLevel);
																				(yystack_[1].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[1].value.tree));
																				(yystack_[3].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[3].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR;
																				(yystack_[3].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[3].value.tree);
																			}
#line 4128 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 122:
#line 3194 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="DOT";
																				temp1.rootNode()->value=".";
																				temp1.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				if(!sigTable.isRepeatInScope((yystack_[0].value.str)))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put((yystack_[0].value.str), putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get((yystack_[0].value.str));
																				AST temp2;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=(yystack_[0].value.str);
																				temp2.rootNode()->explain=to_string(outSymbol.type);
																				temp2.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				temp1.addBrother(temp2);
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_LEXPR;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 4161 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 123:
#line 3222 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="PTR_OP";
																				temp1.rootNode()->value="->";
																				temp1.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				if(!sigTable.isRepeatInScope((yystack_[0].value.str)))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put((yystack_[0].value.str), putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get((yystack_[0].value.str));
																				AST temp2;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=(yystack_[0].value.str);
																				temp2.rootNode()->explain=to_string(outSymbol.type);
																				temp2.rootNode()->level=(yystack_[2].value.tree).rootNode()->level;
																				temp1.addBrother(temp2);
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=TYPE_LEXPR;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 4194 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 124:
#line 3250 "parser.y" // lalr1.cc:859
    {
																				if(CAN_ASSIGN_TO((yystack_[1].value.tree).rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="INC_OP";
																				temp1.rootNode()->value="++";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[1].value.tree).rootNode()->style);
																				
																				////
																				string t=qualdruples.append("a++",(yystack_[1].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);

																			}
#line 4225 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 125:
#line 3276 "parser.y" // lalr1.cc:859
    {
																				if(CAN_ASSIGN_TO((yystack_[1].value.tree).rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="DEC_OP";
																				temp1.rootNode()->value="--";
																				temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																				(yystack_[1].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[1].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value="POSTFIX_EXPR";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yylhs.value.tree).rootNode()->style=MAKE_REXPR((yystack_[1].value.tree).rootNode()->style);
																				////
																				string t=qualdruples.append("a--",(yystack_[1].value.tree).rootNode()->value,"");
																				(yylhs.value.tree).rootNode()->value=t;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				////
																				(yystack_[1].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[1].value.tree);

																			}
#line 4255 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 126:
#line 3303 "parser.y" // lalr1.cc:859
    {
																				Symbol outSymbol=sigTable.get((yystack_[0].value.str));
																				if(outSymbol.type==0)
																				{
																					CP::Parser::error(location_type(), "Undefined");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=(yystack_[0].value.str);
																				temp1.rootNode()->explain=to_string(outSymbol.type);
																				temp1.rootNode()->level=0;
																				temp1.rootNode()->style=outSymbol.style;
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value=temp1.rootNode()->value;
																				(yylhs.value.tree).rootNode()->level=1;
																				(yylhs.value.tree).rootNode()->style=MAKE_LEXPR_BY_TYPE(outSymbol.style);
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 4280 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 127:
#line 3323 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="INT_CONST";
																				(yylhs.value.tree).rootNode()->value=(yystack_[0].value.str);
																				(yylhs.value.tree).rootNode()->level=0;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_INT;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																			}
#line 4292 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 128:
#line 3330 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="DOUBLE_CONST";
																				(yylhs.value.tree).rootNode()->value=(yystack_[0].value.str);
																				(yylhs.value.tree).rootNode()->level=0;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_DOUBLE;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																			}
#line 4304 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 129:
#line 3337 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="CHAR_CONST";
																				(yylhs.value.tree).rootNode()->value=(yystack_[0].value.str);
																				(yylhs.value.tree).rootNode()->level=0;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_CHAR;
																				(yylhs.value.tree).rootNode()->next=qualdruples.nextKey();
																				/*
																				AST temp1;
																				temp1.rootNode()->type="CHAR_CONST";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=0;
																				temp1.rootNode()->style=TYPE_REXPR_CHAR;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="PRIMARY_EXPRESSION";
																				$$.rootNode()->level=1;
																				$$.rootNode()->style=TYPE_REXPR_CHAR;
																				temp1.addFather($$);
																				$$=temp1;
																				*/
																			}
#line 4329 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 130:
#line 3357 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="STR_CONST";
																				temp1.rootNode()->value=(yystack_[0].value.str);
																				temp1.rootNode()->level=0;
																				temp1.rootNode()->style=TYPE_REXPR_POINTER(TYPE_CHAR,1);
																				(yylhs.value.tree).rootNode()->type="EXPRESSION";
																				(yylhs.value.tree).rootNode()->value=temp1.rootNode()->value;
																				(yylhs.value.tree).rootNode()->level=1;
																				(yylhs.value.tree).rootNode()->style=TYPE_REXPR_POINTER(TYPE_CHAR,1);
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 4347 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 131:
#line 3370 "parser.y" // lalr1.cc:859
    {
																				if((yystack_[1].value.tree).rootNode()->type=="INT_CONST"||(yystack_[1].value.tree).rootNode()->type=="DOUBLE_CONST"||(yystack_[1].value.tree).rootNode()->type=="CHAR_CONST"){
																					(yylhs.value.tree)=(yystack_[1].value.tree);
																				}
																				else{
																					AST temp1;
																					temp1.rootNode()->type="LCURVE";
																					temp1.rootNode()->value="(";
																					temp1.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																					AST temp2;
																					temp2.rootNode()->type="RCURVE";
																					temp2.rootNode()->value=")";
																					temp2.rootNode()->level=(yystack_[1].value.tree).rootNode()->level;
																					(yystack_[1].value.tree).addBrother(temp2);
																					temp1.addBrother((yystack_[1].value.tree));
																					int nowlevel=temp1.rootNode()->level;
																					(yylhs.value.tree).rootNode()->type="EXPRESSION";
																					(yylhs.value.tree).rootNode()->value=(yystack_[1].value.tree).rootNode()->value;
																					(yylhs.value.tree).rootNode()->level=nowlevel+1;
																					(yylhs.value.tree).rootNode()->style=(yystack_[1].value.tree).rootNode()->style;
																					temp1.addFather((yylhs.value.tree));
																					(yylhs.value.tree)=temp1;	
																				}
																			}
#line 4376 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 132:
#line 3396 "parser.y" // lalr1.cc:859
    {
																				int nowlevel=(yystack_[0].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="ARGUMENT_EXPRESSION_LIST";
																				(yylhs.value.tree).rootNode()->value="ARGUMENT_EXPRESSION_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				///
																				(yylhs.value.tree).rootNode()->value=(yystack_[0].value.tree).rootNode()->value;
																				///
																				(yystack_[0].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[0].value.tree);
																			}
#line 4392 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 133:
#line 3408 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp1.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp1);
																				int nowlevel=(yystack_[2].value.tree).rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="ARGUMENT_EXPRESSION_LIST";
																				(yylhs.value.tree).rootNode()->value="ARGUMENT_EXPRESSION_LIST";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				(yystack_[2].value.tree).addFather((yylhs.value.tree));
																				(yylhs.value.tree)=(yystack_[2].value.tree);
																			}
#line 4414 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 134:
#line 3427 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="UNARY_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="&";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4424 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 135:
#line 3432 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="UNARY_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="*";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4434 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 136:
#line 3437 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="UNARY_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="+";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4444 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 137:
#line 3442 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="UNARY_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="-";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4454 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 138:
#line 3447 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="UNARY_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="~";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4464 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 139:
#line 3452 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="UNARY_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="!";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4474 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 140:
#line 3459 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4484 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 141:
#line 3464 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="*=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4494 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 142:
#line 3469 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="/=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4504 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 143:
#line 3474 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="%=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4514 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 144:
#line 3479 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="+=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4524 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 145:
#line 3484 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="-=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4534 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 146:
#line 3489 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="<<=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4544 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 147:
#line 3494 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value=">>=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4554 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 148:
#line 3499 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="&=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4564 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 149:
#line 3504 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="^=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4574 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 150:
#line 3509 "parser.y" // lalr1.cc:859
    {
																				(yylhs.value.tree).rootNode()->type="ASSIGNMENT_OPRATOR";
																				(yylhs.value.tree).rootNode()->value="|=";
																				(yylhs.value.tree).rootNode()->level=0;
																			}
#line 4584 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 151:
#line 3516 "parser.y" // lalr1.cc:859
    {
																				if(!sigTable.isRepeatInScope((yystack_[2].value.str)))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put((yystack_[2].value.str), putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get((yystack_[2].value.str));
																				AST temp1;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=(yystack_[2].value.str);
																				temp1.rootNode()->explain=to_string(outSymbol.type);
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp2.addBrother((yystack_[0].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="LABELED_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 4616 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 152:
#line 3543 "parser.y" // lalr1.cc:859
    {
																				int maxLevel=max({(yystack_[2].value.tree).rootNode()->level,(yystack_[0].value.tree).rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="CASE";
																				temp1.rootNode()->value=(yystack_[3].value.str);
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=maxLevel;
																				(yystack_[2].value.tree).changeLevel(maxLevel);
																				(yystack_[0].value.tree).changeLevel(maxLevel);
																				temp2.addBrother((yystack_[0].value.tree));
																				(yystack_[2].value.tree).addBrother(temp2);
																				temp1.addBrother((yystack_[2].value.tree));
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="LABELED_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 4643 "parser.tab.cpp" // lalr1.cc:859
    break;

  case 153:
#line 3565 "parser.y" // lalr1.cc:859
    {
																				AST temp1;
																				temp1.rootNode()->type="DEFAULT";
																				temp1.rootNode()->value=(yystack_[2].value.str);
																				temp1.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=(yystack_[0].value.tree).rootNode()->level;
																				temp2.addBrother((yystack_[0].value.tree));
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				(yylhs.value.tree).rootNode()->type="STATEMENT";
																				(yylhs.value.tree).rootNode()->value="LABELED_STAT";
																				(yylhs.value.tree).rootNode()->level=nowlevel+1;
																				temp1.addFather((yylhs.value.tree));
																				(yylhs.value.tree)=temp1;
																			}
#line 4666 "parser.tab.cpp" // lalr1.cc:859
    break;


#line 4670 "parser.tab.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const short int Parser::yypact_ninf_ = -170;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      21,  -170,  -170,  -170,  -170,  -170,  -170,    76,    10,    47,
    -170,  -170,    91,  -170,    88,   -30,    12,  -170,    91,   -21,
     115,   -10,  -170,  -170,  -170,  -170,   -33,  -170,    91,  -170,
     161,    29,    13,   172,  -170,   576,    12,  -170,   -10,   595,
     171,  -170,  -170,    91,  -170,  -170,    39,   101,  -170,   188,
    -170,  -170,  -170,  -170,  -170,  -170,   728,   728,   745,   576,
     524,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
      -3,    24,    -6,    -5,    18,   226,   -12,   245,   223,    14,
    -170,   249,   201,  -170,   778,    13,   231,  -170,    36,  -170,
    -170,    33,    48,    51,    53,    66,    73,   628,  -170,  -170,
      95,   110,   129,   778,    99,    91,  -170,   250,  -170,   320,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,   247,  -170,  -170,
    -170,  -170,  -170,   216,  -170,   778,  -170,  -170,   524,  -170,
    -170,   -20,    -2,   102,   778,   778,   778,   778,   778,   778,
     778,   778,   778,   778,   778,   778,   778,   778,   778,   778,
     778,   778,   778,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   778,  -170,  -170,   149,   645,   778,
     155,  -170,   252,  -170,  -170,   458,   778,   678,   778,  -170,
    -170,  -170,   257,   778,   778,   122,   116,   458,  -170,   389,
    -170,  -170,   778,  -170,  -170,   140,  -170,   543,   778,    31,
    -170,    24,   -22,    -6,    -5,    18,   226,   -12,   -12,   245,
     245,   245,   245,   223,   223,    14,    14,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   119,   260,  -170,  -170,  -170,   124,
     678,   146,  -170,   147,   196,  -170,   458,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   778,   778,  -170,   778,  -170,   458,
     695,   458,   162,   167,  -170,  -170,  -170,  -170,   182,   458,
     225,  -170,  -170,  -170,   458,  -170,   458,  -170,  -170
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     2,     9,    10,    11,    12,    13,     0,     0,     0,
       4,     6,     0,     7,     0,    22,     0,    20,     0,    43,
       0,    18,    42,     1,     3,     5,    43,    40,     0,    36,
       0,     0,     0,     0,    41,     0,     0,    21,    14,     0,
       0,     8,    38,     0,    37,    26,     0,     0,    28,     0,
      19,   126,   127,   128,   129,   130,     0,     0,     0,     0,
       0,   135,   136,   137,   134,   138,   139,    44,    45,    77,
      79,    81,    83,    85,    87,    89,    91,    94,    99,   102,
     105,   109,   112,   118,     0,     0,     0,    23,     0,    27,
     109,   126,     0,     0,     0,     0,     0,     0,    31,    63,
       0,     0,     0,     0,     0,     0,    53,    52,    34,     0,
      50,    58,    59,    54,    55,    56,    57,     0,    75,    60,
      39,    30,    25,     0,    15,     0,   113,   114,     0,   116,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   140,     0,   124,   125,     0,     0,     0,
       0,   115,     0,    16,    24,     0,     0,     0,     0,    70,
      71,    72,     0,     0,     0,     0,     0,     0,    35,     0,
      32,    51,     0,    64,    29,     0,    46,     0,     0,     0,
     131,    82,     0,    84,    86,    88,    90,    92,    93,    97,
      98,    95,    96,   100,   101,   103,   104,   106,   107,   108,
      78,   123,   120,   132,     0,     0,   122,    17,   151,     0,
       0,     0,    73,     0,     0,    74,     0,   153,    33,    76,
     117,    47,    49,   110,     0,     0,   121,     0,   119,     0,
       0,     0,     0,     0,   152,   111,    80,   133,    65,     0,
       0,    67,    61,    62,     0,    68,     0,    66,    69
  };

  const short int
  Parser::yypgoto_[] =
  {
    -170,  -170,  -170,   189,  -170,    20,   207,   -11,   108,   137,
    -170,   123,   224,  -170,   -34,  -170,  -170,   127,   -55,  -170,
     135,   -98,  -170,  -170,  -169,  -170,  -170,  -170,   -53,   -35,
     -37,  -170,   157,   173,   156,   175,   164,   179,    60,   165,
     180,   -81,   -38,  -170,  -170,  -170,  -170,  -170,  -170
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     8,     9,    10,    11,    12,    19,    20,    21,    88,
      47,    48,   106,   107,    13,    30,    14,    27,    67,   131,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,   224,    84,   164,   119
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      68,    90,    89,   171,   130,    32,   108,   133,   230,    40,
      23,   191,   142,   143,    31,    15,    15,   134,   126,   127,
     129,     1,    35,   196,    68,    85,   192,    18,   197,     2,
       3,     4,     5,     6,    35,   245,    39,     2,     3,     4,
       5,     6,   121,   198,   182,   136,    90,    24,    17,   144,
     145,    46,   137,   135,   138,     2,     3,     4,     5,     6,
     105,   250,    17,    37,   150,    90,    89,   151,   152,   217,
     218,   219,   133,   188,    45,   133,   244,   228,   139,    15,
     132,    37,   202,   174,     2,     3,     4,     5,     6,   237,
     175,   191,   176,     7,    15,   177,    90,   178,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,   179,   225,   243,    15,     7,
      16,   199,   180,   229,    33,   231,    17,   105,    38,   220,
     233,   234,   185,   223,    22,    16,    28,    29,   254,   183,
      49,    17,   242,    46,    86,    34,   122,   200,   195,   123,
     192,   258,   221,   261,   184,    42,   187,   239,   226,    36,
      90,   265,    68,   255,   246,    37,   267,   247,   268,   249,
     120,   235,   192,   236,    91,    52,    53,    54,    55,     2,
       3,     4,     5,     6,    92,   240,    93,    94,    95,    96,
      97,   251,   252,   172,   192,   192,   264,   260,    25,    56,
      57,    58,   209,   210,   211,   212,    90,    90,   256,    43,
      44,   262,   257,    40,    98,    60,   263,    50,    39,    26,
      99,    61,    62,    63,     2,     3,     4,     5,     6,   165,
     166,    64,   167,   124,    39,    65,    66,   100,   101,   102,
     186,   253,   189,     7,   192,   168,   194,   169,   140,   141,
      41,   103,   104,    91,    52,    53,    54,    55,     2,     3,
       4,     5,     6,    92,   170,    93,    94,    95,    96,    97,
     266,   146,   147,   192,   148,   149,   173,    39,    56,    57,
      58,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   201,    40,   204,    60,   192,   193,   227,    39,    99,
      61,    62,    63,   206,   163,   192,   232,   248,   192,   203,
      64,   213,   214,   205,    65,    66,   100,   101,   102,   207,
     208,     0,     7,    91,    52,    53,    54,    55,   215,   216,
     103,   104,     0,    92,     0,    93,    94,    95,    96,    97,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,   190,    60,     0,     0,     0,     0,    99,
      61,    62,    63,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,    65,    66,   100,   101,   102,     0,
       0,     0,    91,    52,    53,    54,    55,     0,     0,     0,
     103,   104,    92,     0,    93,    94,    95,    96,    97,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    40,   238,    60,     0,     0,     0,     0,    99,    61,
      62,    63,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,    65,    66,   100,   101,   102,     0,     0,
       0,    91,    52,    53,    54,    55,     0,     0,     0,   103,
     104,    92,     0,    93,    94,    95,    96,    97,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,     0,    60,     0,     0,     0,     0,    99,    61,    62,
      63,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,    65,    66,   100,   101,   102,    51,    52,    53,
      54,    55,     2,     3,     4,     5,     6,     0,   103,   104,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
      55,     0,    56,    57,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
       0,    56,    57,    58,    61,    62,    63,     0,     0,    51,
      52,    53,    54,    55,    64,    59,   241,    60,    65,    66,
       0,     0,     0,    61,    62,    63,     0,     0,    51,    52,
      53,    54,    55,    64,    56,    57,    58,    65,    66,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      60,     0,     0,    56,    57,    58,    61,    62,    63,     0,
       0,    51,    52,    53,    54,    55,    64,     0,     0,    60,
      65,    66,    87,     0,     0,    61,    62,    63,    51,    52,
      53,    54,    55,     0,     0,    64,    56,    57,    58,    65,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,    56,    57,    58,     0,   181,    61,    62,
      63,    51,    52,    53,    54,    55,     0,     0,    64,    60,
     222,     0,    65,    66,     0,    61,    62,    63,    51,    52,
      53,    54,    55,     0,     0,    64,    56,    57,    58,    65,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,    56,    57,    58,     0,    99,    61,    62,
      63,    51,    52,    53,    54,    55,     0,     0,    64,    60,
     259,     0,    65,    66,     0,    61,    62,    63,    51,    52,
      53,    54,    55,     0,     0,    64,    56,    57,    58,    65,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,    56,    57,    58,     0,     0,    61,    62,
      63,    51,    52,    53,    54,    55,     0,     0,    64,   128,
       0,     0,    65,    66,     0,    61,    62,    63,     0,     0,
       0,     0,     0,     0,     0,    64,    56,    57,    58,    65,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,     0,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,    65,    66
  };

  const short int
  Parser::yycheck_[] =
  {
      35,    39,    39,    84,    59,    16,    40,    60,   177,    42,
       0,   109,    24,    25,    44,     3,     3,    20,    56,    57,
      58,     0,    55,    43,    59,    36,    48,     7,    48,     8,
       9,    10,    11,    12,    55,    57,    46,     8,     9,    10,
      11,    12,     3,    45,    97,    21,    84,     0,    50,    61,
      62,    31,    58,    56,    59,     8,     9,    10,    11,    12,
      40,   230,    50,    50,    50,   103,   103,    53,    54,   150,
     151,   152,   125,   107,    45,   128,    45,   175,    60,     3,
      60,    50,   135,    47,     8,     9,    10,    11,    12,   187,
      57,   189,    44,    72,     3,    44,   134,    44,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,    49,   169,   198,     3,    72,
      44,   132,    49,   176,    16,   178,    50,   107,    20,   164,
     183,   184,     3,   168,     7,    44,    48,    49,   236,    44,
      32,    50,   197,   123,    36,    18,    45,    45,   128,    48,
      48,   249,     3,   251,    44,    28,    57,   192,     3,    44,
     198,   259,   197,   244,    45,    50,   264,    48,   266,    45,
      43,    49,    48,    57,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    45,    15,    16,    17,    18,
      19,    45,    45,    85,    48,    48,    14,   250,     9,    28,
      29,    30,   142,   143,   144,   145,   244,   245,   245,    48,
      49,    49,   247,    42,    43,    44,    49,    45,    46,    12,
      49,    50,    51,    52,     8,     9,    10,    11,    12,    28,
      29,    60,    31,    45,    46,    64,    65,    66,    67,    68,
     103,    45,   107,    72,    48,    44,   123,    46,    22,    23,
      26,    80,    81,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    63,    15,    16,    17,    18,    19,
      45,    26,    27,    48,    51,    52,    45,    46,    28,    29,
      30,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,   134,    42,   137,    44,    48,    49,    45,    46,    49,
      50,    51,    52,   139,    55,    48,    49,    47,    48,   136,
      60,   146,   147,   138,    64,    65,    66,    67,    68,   140,
     141,    -1,    72,     3,     4,     5,     6,     7,   148,   149,
      80,    81,    -1,    13,    -1,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      80,    81,    13,    -1,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    80,
      81,    13,    -1,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    64,    65,    66,    67,    68,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    28,    29,    30,    50,    51,    52,    -1,    -1,     3,
       4,     5,     6,     7,    60,    42,    43,    44,    64,    65,
      -1,    -1,    -1,    50,    51,    52,    -1,    -1,     3,     4,
       5,     6,     7,    60,    28,    29,    30,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      44,    -1,    -1,    28,    29,    30,    50,    51,    52,    -1,
      -1,     3,     4,     5,     6,     7,    60,    -1,    -1,    44,
      64,    65,    47,    -1,    -1,    50,    51,    52,     3,     4,
       5,     6,     7,    -1,    -1,    60,    28,    29,    30,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    28,    29,    30,    -1,    49,    50,    51,
      52,     3,     4,     5,     6,     7,    -1,    -1,    60,    44,
      45,    -1,    64,    65,    -1,    50,    51,    52,     3,     4,
       5,     6,     7,    -1,    -1,    60,    28,    29,    30,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    28,    29,    30,    -1,    49,    50,    51,
      52,     3,     4,     5,     6,     7,    -1,    -1,    60,    44,
      45,    -1,    64,    65,    -1,    50,    51,    52,     3,     4,
       5,     6,     7,    -1,    -1,    60,    28,    29,    30,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    28,    29,    30,    -1,    -1,    50,    51,
      52,     3,     4,     5,     6,     7,    -1,    -1,    60,    44,
      -1,    -1,    64,    65,    -1,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    28,    29,    30,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     0,     8,     9,    10,    11,    12,    72,    83,    84,
      85,    86,    87,    96,    98,     3,    44,    50,    87,    88,
      89,    90,    99,     0,     0,    85,    88,    99,    48,    49,
      97,    44,    89,    90,    99,    55,    44,    50,    90,    46,
      42,    94,    99,    48,    49,    45,    87,    92,    93,    90,
      45,     3,     4,     5,     6,     7,    28,    29,    30,    42,
      44,    50,    51,    52,    60,    64,    65,   100,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   128,    89,    90,    47,    91,   112,
     124,     3,    13,    15,    16,    17,    18,    19,    43,    49,
      66,    67,    68,    80,    81,    87,    94,    95,    96,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   130,
      99,     3,    45,    48,    45,    44,   124,   124,    44,   124,
     100,   101,    87,   110,    20,    56,    21,    58,    59,    60,
      22,    23,    24,    25,    61,    62,    26,    27,    51,    52,
      50,    53,    54,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    55,   129,    28,    29,    31,    44,    46,
      63,   123,    90,    45,    47,    57,    44,    44,    44,    49,
      49,    49,   110,    44,    44,     3,    91,    57,    96,   102,
      43,   103,    48,    49,    93,    87,    43,    48,    45,    89,
      45,   114,   110,   115,   116,   117,   118,   119,   119,   120,
     120,   120,   120,   121,   121,   122,   122,   123,   123,   123,
     111,     3,    45,   111,   127,   110,     3,    45,   103,   110,
     106,   110,    49,   110,   110,    49,    57,   103,    43,   111,
      45,    43,   100,   123,    45,    57,    45,    48,    47,    45,
     106,    45,    45,    45,   103,   123,   112,   111,   103,    45,
     110,   103,    49,    49,    14,   103,    45,   103,   103
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    83,    84,    84,    85,    85,    86,    87,
      87,    87,    87,    87,    88,    88,    88,    88,    88,    88,
      89,    89,    90,    90,    90,    90,    90,    91,    92,    92,
      93,    94,    94,    94,    95,    95,    96,    96,    97,    97,
      98,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     102,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   105,   106,   106,   107,   107,   108,   108,   108,
     109,   109,   109,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   118,   119,   119,   119,   119,   119,   120,
     120,   120,   121,   121,   121,   122,   122,   122,   122,   123,
     123,   123,   124,   124,   124,   124,   124,   124,   125,   125,
     125,   125,   125,   125,   125,   125,   126,   126,   126,   126,
     126,   126,   127,   127,   128,   128,   128,   128,   128,   128,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   130,   130,   130
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     1,     1,     3,     1,
       1,     1,     1,     1,     2,     4,     4,     5,     1,     3,
       1,     2,     1,     3,     4,     4,     3,     1,     1,     3,
       2,     2,     3,     4,     1,     2,     2,     3,     2,     3,
       2,     3,     2,     1,     3,     1,     3,     4,     1,     3,
       1,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     1,     2,     5,     7,     5,     6,     7,
       2,     2,     2,     3,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       4,     5,     1,     2,     2,     2,     2,     4,     1,     4,
       3,     4,     3,     3,     2,     2,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "IDENTIFIER", "INT_CONST",
  "DOUBLE_CONST", "CHAR_CONST", "STR_CONST", "VOID", "CHAR", "INT",
  "FLOAT", "DOUBLE", "IF", "ELSE", "FOR", "WHILE", "CONTINUE", "BREAK",
  "RETURN", "OR_OP", "AND_OP", "EQ_OP", "NE_OP", "LE_OP", "GE_OP",
  "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "SIZEOF", "PTR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "LBRACE", "RBRACE", "LCURVE", "RCURVE", "LSQUARE", "RSQUARE", "COMMA",
  "SQM", "STAR", "ADD", "SUB", "DIV", "MOD", "ASSIGN", "QUESTION", "COLON",
  "INCLUSIVE_OR", "EXCLUSIVE_OR", "AND", "LESS", "GREATER", "DOT", "WAVE",
  "SIGH", "READ", "WRITE", "GOTO", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "ELLIPSIS", "STRUCT", "UNION", "ENUM", "CONST", "VOLATILE",
  "CASE", "DEFAULT", "$accept", "code", "program", "external_declaration",
  "function_definition", "type_specifier", "declarator", "pointer",
  "direct_declarator", "constant_expression", "parameter_list",
  "parameter_declaration", "compound_statement", "declaration_list",
  "declaration", "init_declarator_tail", "init_declarator",
  "init_declarator_body", "initializer", "initializer_list",
  "statement_list", "statement", "read_statement", "write_statement",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "expression", "assignment_expression",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "postfix_expression", "primary_expression", "argument_expression_list",
  "unary_operator", "assignment_operator", "labeled_statement", YY_NULLPTR
  };


  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   105,   105,   106,   112,   120,   134,   142,   152,   170,
     177,   184,   192,   200,   210,   241,   283,   325,   369,   396,
     436,   442,   459,   472,   492,   521,   546,   628,   639,   647,
     666,   690,   711,   755,   807,   816,   831,   845,   865,   879,
     900,   922,   950,   972,   986,  1022,  1041,  1060,  1086,  1096,
    1124,  1133,  1146,  1149,  1158,  1167,  1176,  1185,  1193,  1202,
    1211,  1221,  1252,  1283,  1295,  1312,  1342,  1389,  1425,  1464,
    1518,  1534,  1550,  1566,  1584,  1614,  1632,  1656,  1674,  1704,
    1722,  1750,  1768,  1809,  1828,  1870,  1888,  1935,  1953,  1999,
    2018,  2064,  2082,  2120,  2162,  2180,  2222,  2263,  2303,  2346,
    2365,  2412,  2462,  2480,  2552,  2620,  2639,  2709,  2775,  2818,
    2836,  2892,  2925,  2944,  2969,  2994,  3050,  3070,  3102,  3121,
    3151,  3170,  3194,  3222,  3250,  3276,  3303,  3323,  3330,  3337,
    3357,  3370,  3396,  3407,  3427,  3432,  3437,  3442,  3447,  3452,
    3459,  3464,  3469,  3474,  3479,  3484,  3489,  3494,  3499,  3504,
    3509,  3516,  3543,  3565
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81
    };
    const unsigned int user_token_number_max_ = 336;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 5 "parser.y" // lalr1.cc:1167
} // CP
#line 5323 "parser.tab.cpp" // lalr1.cc:1167
#line 3584 "parser.y" // lalr1.cc:1168


#include "parser_after.h"
