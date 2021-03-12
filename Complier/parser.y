%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines 
%define api.namespace {CP}
%define parser_class_name {Parser}

%code requires {
    namespace CP {
        class Driver;
        class Scanner;
    }

    // The following definitions is missing when %locations isn't used
    #ifndef YY_NULLPTR
    #define YY_NULLPTR nullptr
    #endif
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code{
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
}

%code requires
{
	#include "AST.h"
	struct myType
	{
		AST tree;
		string str;
		int wnext;
	};
}

%define api.value.type {struct myType}
%define parse.assert

%token				END    0     "end of file"
%token <str> IDENTIFIER INT_CONST DOUBLE_CONST CHAR_CONST STR_CONST
%token <str> VOID CHAR INT FLOAT DOUBLE
%token <str> IF ELSE FOR
%token <wnext> WHILE
%token <str> CONTINUE BREAK RETURN
%token <str> OR_OP AND_OP EQ_OP NE_OP LE_OP GE_OP LEFT_OP RIGHT_OP INC_OP DEC_OP SIZEOF PTR_OP
%token <str> MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token <str> LBRACE RBRACE LCURVE RCURVE LSQUARE RSQUARE COMMA SQM
%token <str> STAR ADD SUB DIV MOD ASSIGN QUESTION COLON
%token <str> INCLUSIVE_OR EXCLUSIVE_OR AND LESS GREATER DOT WAVE SIGH
%token <str> READ WRITE GOTO
%token <str> TYPEDEF EXTERN STATIC AUTO REGISTER ELLIPSIS
%token <str> STRUCT UNION ENUM CONST VOLATILE CASE DEFAULT
%type <tree> program 
%type <tree> external_declaration declaration parameter_declaration
%type <tree> function_definition
%type <tree> type_specifier storage_class_specifier struct_or_union_specifier type_qualifier type_qualifier_list
%type <tree> declarator direct_declarator init_declarator init_declarator_tail init_declarator_body
%type <tree> statement compound_statement expression_statement selection_statement iteration_statement jump_statement
%type <tree> read_statement write_statement labeled_statement
%type <tree> pointer
%type <tree> expression constant_expression conditional_expression assignment_expression unary_expression 
%type <tree> logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression
%type <tree> and_expression relational_expression shift_expression additive_expression equality_expression
%type <tree> multiplicative_expression cast_expression postfix_expression primary_expression
%type <tree> parameter_list statement_list declaration_list initializer_list parameter_type_list
%type <tree> argument_expression_list
%type <tree> initializer
%type <tree> assignment_operator unary_operator
%type <tree> struct_or_union struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list struct_declarator
%type <tree> enum_specifier enumerator_list enumerator abstract_declarator direct_abstract_declarator

%locations

%%
code					: END 
						| program END		{
												AST::setTopLevel($1.rootNode()->level);
												//$1.outputTreeReverse();
											}
						;

program					: external_declaration		{
														int nowlevel=$1.rootNode()->level;
														$$.rootNode()->type="PROGRAM";
														$$.rootNode()->value="PROGRAM";
														$$.rootNode()->level=nowlevel+1;
														$1.addFather($$);
														$$=$1;
													}
						| program external_declaration		{
																int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
																$1.changeLevel(maxLevel);
																$2.changeLevel(maxLevel);
																$1.addBrother($2);
																int nowlevel=$1.rootNode()->level;
																$$.rootNode()->type="PROGRAM";
																$$.rootNode()->value="PROGRAM";
																$$.rootNode()->level=nowlevel+1;
																$1.addFather($$);
																$$=$1;
															}
						;
 
external_declaration	: function_definition		{
														int nowlevel=$1.rootNode()->level;
														$$.rootNode()->type="DECLARATION";
														$$.rootNode()->value="EXTERNAL_DECL";
														$$.rootNode()->level=nowlevel+1;
														$1.addFather($$);
														$$=$1;
													}
						| declaration		{
												int nowlevel=$1.rootNode()->level;
												$$.rootNode()->type="DECLARATION";
												$$.rootNode()->value="EXTERNAL_DECL";
												$$.rootNode()->level=nowlevel+1;
												$1.addFather($$);
												$$=$1;
											}
						;
     
function_definition		: type_specifier declarator compound_statement
							{
								int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level,$3.rootNode()->level});
								$1.changeLevel(maxLevel);
								$2.changeLevel(maxLevel);
								$3.changeLevel(maxLevel);
								$2.addBrother($3);
								$1.addBrother($2);
								int nowlevel=$1.rootNode()->level;
								$$.rootNode()->style=TYPE_REXPR;
								$$.rootNode()->type="DEFINITION";
								$$.rootNode()->value="FUNCTION_DEFI";
								$$.rootNode()->level=nowlevel+1;
								$1.addFather($$);
								$$=$1;
							}
						;
 
type_specifier			: VOID		{
										currentType = TYPE_VOID;
										$$.rootNode()->style = currentType;
										$$.rootNode()->type="TYPE_SPECIFIER";
										$$.rootNode()->value="VOID";
										$$.rootNode()->level=0;
									}
						| CHAR		{
										currentType = TYPE_CHAR;
										$$.rootNode()->style = currentType;
										$$.rootNode()->type="TYPE_SPECIFIER";
										$$.rootNode()->value="CHAR";
										$$.rootNode()->level=0;
									}
						| INT
									{
										currentType = TYPE_INT;
										$$.rootNode()->style = currentType;
										$$.rootNode()->type="TYPE_SPECIFIER";
										$$.rootNode()->value="INT";
										$$.rootNode()->level=0;
									}
						| FLOAT
									{
										currentType = TYPE_FLOAT;
										$$.rootNode()->style = currentType;
										$$.rootNode()->type="TYPE_SPECIFIER";
										$$.rootNode()->value="FLOAT";
										$$.rootNode()->level=0;
									}
						| DOUBLE	{
										currentType = TYPE_DOUBLE;
										$$.rootNode()->style = currentType;
										$$.rootNode()->type="TYPE_SPECIFIER";
										$$.rootNode()->value="DOUBLE";
										$$.rootNode()->level=0;
									}
						;

 
declarator				: pointer direct_declarator		{
															int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
															$1.changeLevel(maxLevel);
															$2.changeLevel(maxLevel);
															$1.addBrother($2);
															int nowlevel=$1.rootNode()->level;
															$$.rootNode()->type="DECLARATOR";
															$$.rootNode()->value="DECLARATOR";
															$$.rootNode()->level=nowlevel+1;
															$$.rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER($1.rootNode()->style)+LEVEL_OF_ARRAY($2.rootNode()->style));
															$1.addFather($$);
															$$=$1;
															list<ASTNode> l;
															$$.getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER($1.rootNode()->style)+LEVEL_OF_ARRAY($2.rootNode()->style));
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
						| LCURVE pointer direct_declarator RCURVE
														{
															int maxLevel=max({$2.rootNode()->level,$3.rootNode()->level});
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=maxLevel;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=maxLevel;
															$2.changeLevel(maxLevel);
															$3.changeLevel(maxLevel);
															$3.addBrother(temp2);
															$2.addBrother($3);
															temp1.addBrother($2);
															int nowlevel=temp1.rootNode()->level;
															$$.rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER($2.rootNode()->style)+LEVEL_OF_ARRAY($3.rootNode()->style));
															$$.rootNode()->type="DECLARATOR";
															$$.rootNode()->value="DECLARATOR";
															$$.rootNode()->level=nowlevel+1;
															temp1.addFather($$);
															$$=temp1;
															list<ASTNode> l;
															$$.getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER($2.rootNode()->style)+LEVEL_OF_ARRAY($3.rootNode()->style));
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
						| pointer LCURVE direct_declarator RCURVE
														{
															int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=maxLevel;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=maxLevel;
															$1.changeLevel(maxLevel);
															$3.changeLevel(maxLevel);
															$3.addBrother(temp2);
															temp1.addBrother($3);
															$1.addBrother(temp1);
															int nowlevel=$1.rootNode()->level;
															$$.rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER($1.rootNode()->style)+LEVEL_OF_ARRAY($3.rootNode()->style));
															$$.rootNode()->type="DECLARATOR";
															$$.rootNode()->value="DECLARATOR";
															$$.rootNode()->level=nowlevel+1;
															$1.addFather($$);
															$$=$1;
															list<ASTNode> l;
															$$.getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER($1.rootNode()->style)+LEVEL_OF_ARRAY($3.rootNode()->style));
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
						| pointer LCURVE pointer direct_declarator RCURVE
														{
															int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level,$4.rootNode()->level});
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=maxLevel;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=maxLevel;
															$1.changeLevel(maxLevel);
															$3.changeLevel(maxLevel);
															$4.changeLevel(maxLevel);
															$4.addBrother(temp2);
															$3.addBrother($4);
															temp1.addBrother($3);
															$1.addBrother(temp1);
															int nowlevel=$1.rootNode()->level;
															$$.rootNode()->style=TYPE_POINTER(currentType,LEVEL_OF_POINTER($1.rootNode()->style)+LEVEL_OF_POINTER($3.rootNode()->style)+LEVEL_OF_ARRAY($4.rootNode()->style));
															$$.rootNode()->type="DECLARATOR";
															$$.rootNode()->value="DECLARATOR";
															$$.rootNode()->level=nowlevel+1;
															$1.addFather($$);
															$$=$1;
															list<ASTNode> l;
															$$.getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = TYPE_POINTER(currentType,LEVEL_OF_POINTER($1.rootNode()->style)+LEVEL_OF_POINTER($3.rootNode()->style)+LEVEL_OF_ARRAY($4.rootNode()->style));
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
						| direct_declarator				{
															int nowlevel=$1.rootNode()->level;
															$$.rootNode()->style=MAKE_TYPE_BY_UNKNOWN(currentType, $1.rootNode()->style);
															$$.rootNode()->type="DECLARATOR";
															$$.rootNode()->value="DECLARATOR";
															$$.rootNode()->level=nowlevel+1;
															$1.addFather($$);
															$$=$1;
															list<ASTNode> l;
															$$.getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = MAKE_TYPE_BY_UNKNOWN(currentType, $1.rootNode()->style);
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
						| LCURVE direct_declarator RCURVE
														{
															AST temp1;
															temp1.rootNode()->type="LCURVE";
															temp1.rootNode()->value="(";
															temp1.rootNode()->level=$2.rootNode()->level;
															AST temp2;
															temp2.rootNode()->type="RCURVE";
															temp2.rootNode()->value=")";
															temp2.rootNode()->level=$2.rootNode()->level;
															$2.addBrother(temp2);
															temp1.addBrother($2);
															int nowlevel=temp1.rootNode()->level;
															$$.rootNode()->style= MAKE_TYPE_BY_UNKNOWN(currentType, $2.rootNode()->style);
															$$.rootNode()->type="DECLARATOR";
															$$.rootNode()->value="DECLARATOR";
															$$.rootNode()->level=nowlevel+1;
															temp1.addFather($$);
															$$=temp1;
															list<ASTNode> l;
															$$.getNodesWanted(isIdType, l);
															while (!(l.empty())){
																//cout << l.front().value << " ";
																Symbol putSymbol;
																putSymbol.style = MAKE_TYPE_BY_UNKNOWN(currentType, $2.rootNode()->style);
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
						;
 
pointer					: STAR			{
											$$.rootNode()->style=TYPE_POINTER(TYPE_UNKNOWN, 1);
											$$.rootNode()->type="POINTER";
											$$.rootNode()->value="*";
											$$.rootNode()->level=0;
										}
						| pointer STAR	{
											AST ptr;
											ptr.rootNode()->style=TYPE_UNKNOWN;
											ptr.rootNode()->type="POINTER";
											ptr.rootNode()->value="*";
											ptr.rootNode()->level=$1.rootNode()->level;
											$1.addBrother(ptr);
											int nowlevel=$1.rootNode()->level;
											$$.rootNode()->type="POINTER";
											$$.rootNode()->value="POINTER";
											$$.rootNode()->level=nowlevel+1;
											$$.rootNode()->style=TYPE_POINTER(TYPE_OF_POINTER($1.rootNode()->style),LEVEL_OF_POINTER($1.rootNode()->style)+1);
											$1.addFather($$);
											$$=$1;
										}
						;
 
direct_declarator		: IDENTIFIER										{
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=0;
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="DIRECT_DECL";
																				$$.rootNode()->level=1;
																				$$.rootNode()->style=temp1.rootNode()->style;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| direct_declarator LSQUARE RSQUARE							{
																				AST temp1;
																				temp1.rootNode()->type="LSQUARE";
																				temp1.rootNode()->value="[";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="RSQUARE";
																				temp2.rootNode()->value="]";
																				temp2.rootNode()->level=$1.rootNode()->level;
																				temp1.addBrother(temp2);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->style=TYPE_ARRAY(TYPE_OF_ARRAY($1.rootNode()->style),LEVEL_OF_ARRAY($1.rootNode()->style)+1);
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="DIRECT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;	
																				leftLevel = 999;
																			}
						| direct_declarator LSQUARE constant_expression RSQUARE		
																			{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LSQUARE";
																				temp1.rootNode()->value="[";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RSQUARE";
																				temp2.rootNode()->value="]";
																				temp2.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$3.addBrother(temp2);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->style=TYPE_ARRAY(TYPE_OF_ARRAY($1.rootNode()->style),LEVEL_OF_ARRAY($1.rootNode()->style)+1);
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="DIRECT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;	
																				if(!isStrNumInt($3.rootNode()->explain)){
																					CP::Parser::error(location_type(), "Must be int!");
																					system("pause");
																				}
																				leftLevel = stringToNum<int>($3.rootNode()->explain);
																			}
						| IDENTIFIER LCURVE parameter_list RCURVE					{
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=$3.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=$3.rootNode()->level;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=$3.rootNode()->level;
																				$3.addBrother(temp3);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->style=$3.rootNode()->style;
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="DIRECT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;	
																			}
						| IDENTIFIER LCURVE RCURVE								{
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$1;
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
																				$$.rootNode()->style=temp1.rootNode()->style;
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="DIRECT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;	
																			}
						;
						/*| direct_declarator COMMA identifier_list				{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->style=$1.rootNode()->style;
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="DIRECT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
identifier_list			: IDENTIFIER										{
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=0;
																				$$.rootNode()->type="IDENTIFIER_LIST";
																				$$.rootNode()->style=temp1.rootNode()->style;
																				$$.rootNode()->value="IDENTIFIER_LIST";
																				$$.rootNode()->level=1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| identifier_list COMMA IDENTIFIER					{
																				AST temp1;
																				temp1.rootNode()->style=TYPE_UNKNOWN;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->style=TYPE_UNKNOWN;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=$3;
																				temp2.rootNode()->level=$1.rootNode()->level;
																				temp1.addBrother(temp2);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->style=$1.rootNode()->style;
																				$$.rootNode()->type="IDENTIFIER_LIST";
																				$$.rootNode()->value="IDENTIFIER_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 */
constant_expression		: conditional_expression							{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="CONSTANT_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->explain=$1.rootNode()->value;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
parameter_list			: parameter_declaration								{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="PARAMETER_LIST";
																				$$.rootNode()->value="PARAMETER_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						| parameter_list COMMA parameter_declaration			{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="PARAMETER_LIST";
																				$$.rootNode()->value="PARAMETER_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						;

parameter_declaration	: type_specifier  IDENTIFIER				{
																				if(!sigTable.isRepeatInScope($2))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put($2, putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get($2);
																				AST temp1;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$2;
																				temp1.rootNode()->explain=to_string(outSymbol.type);
																				temp1.rootNode()->level=$1.rootNode()->level;
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="PARAMETER_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
compound_statement		: LBRACE RBRACE											{
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
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="COMPOUND_STAT";
																				$$.rootNode()->level=1;
																				$$.rootNode()->next=qualdruples.nextKey();	
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| LBRACE statement_list RBRACE						{
																				beforeLeave(sigTable.returnMap(), false);
																				beforeLeave(tempTable.returnMap(), true);
																				sigTable.leaveScope();
																				tempTable.leaveScope();
																				if($2.rootNode()->value=="STATEMENT_LIST")
																				{
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=$2.rootNode()->level;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=$2.rootNode()->level;
																					$2.addBrother(temp2);
																					temp1.addBrother($2);
																					int nowlevel=temp1.rootNode()->level;
																					$$.rootNode()->type="STATEMENT";
																					$$.rootNode()->value="COMPOUND_STAT";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->next=$2.rootNode()->next;
																					temp1.addFather($$);
																					$$=temp1;
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
																					$$.rootNode()->type="STATEMENT";
																					$$.rootNode()->value="COMPOUND_STAT";
																					$$.rootNode()->level=1;
																					$$.rootNode()->next=qualdruples.nextKey();
																					temp1.addFather($$);
																					$$=temp1;
																				}
																			}
						| LBRACE declaration_list statement_list RBRACE		{
																				beforeLeave(sigTable.returnMap(), false);
																				beforeLeave(tempTable.returnMap(), true);
																				sigTable.leaveScope();
																				tempTable.leaveScope();
																				if($3.rootNode()->value=="STATEMENT_LIST")
																				{
																					int maxLevel=max({$2.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=maxLevel;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=maxLevel;
																					$2.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					$3.addBrother(temp2);
																					$2.addBrother($3);
																					temp1.addBrother($2);
																					int nowlevel=temp1.rootNode()->level;
																					$$.rootNode()->type="STATEMENT";
																					$$.rootNode()->value="COMPOUND_STAT";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->next=$3.rootNode()->next;
																					temp1.addFather($$);
																					$$=temp1;
																				}
																				else
																				{
																					AST temp1;
																					temp1.rootNode()->type="LBRACE";
																					temp1.rootNode()->value="{";
																					temp1.rootNode()->level=$2.rootNode()->level;
																					AST temp2;
																					temp2.rootNode()->type="RBRACE";
																					temp2.rootNode()->value="}";
																					temp2.rootNode()->level=$2.rootNode()->level;
																					$2.addBrother(temp2);
																					temp1.addBrother($2);
																					int nowlevel=temp1.rootNode()->level;
																					$$.rootNode()->type="STATEMENT";
																					$$.rootNode()->value="COMPOUND_STAT";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->next=$2.rootNode()->next;
																					temp1.addFather($$);
																					$$=temp1;
																				}
																			}
						;
 
declaration_list		: declaration										{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION_LIST";
																				$$.rootNode()->value="DECLARATION_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| declaration_list declaration						{
																				int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
																				$1.changeLevel(maxLevel);
																				$2.changeLevel(maxLevel);
																				$1.addBrother($2);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION_LIST";
																				$$.rootNode()->value="DECLARATION_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$2.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
declaration				: init_declarator SQM								{
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="DECLARATION";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| init_declarator init_declarator_tail SQM			{
																				int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$2.changeLevel(maxLevel);
																				$2.addBrother(temp1);
																				$1.addBrother($2);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="DECLARATION";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$2.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						;

init_declarator_tail	: COMMA init_declarator_body								{
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="INIT_DECL_TAIL";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$2.rootNode()->next;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| init_declarator_tail COMMA init_declarator_body		{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;

																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="INIT_DECL_TAIL";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$3.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						;

init_declarator			: type_specifier init_declarator_body				{
																				int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
																				$1.changeLevel(maxLevel);
																				$2.changeLevel(maxLevel);
																				$1.addBrother($2);
																				int nowlevel=$1.rootNode()->level;
																				if (IS_POINTER($2.rootNode()->style)){
																					$$.rootNode()->style=TYPE_POINTER($1.rootNode()->style, LEVEL_OF_POINTER($2.rootNode()->style));
																				}
																				else if (IS_ARRAY($2.rootNode()->style)){
																					$$.rootNode()->style=TYPE_ARRAY($1.rootNode()->style, LEVEL_OF_ARRAY($2.rootNode()->style));
																				}
																				else {
																					$$.rootNode()->style=$1.rootNode()->style;
																				}
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="INIT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$2.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| AUTO type_specifier init_declarator_body			{
																				
																				int maxLevel=max({$2.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="AUTO";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=maxLevel;
																				$2.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$2.addBrother($3);
																				temp1.addBrother($2);
																				if (IS_POINTER($3.rootNode()->style)){
																					$$.rootNode()->style=TYPE_POINTER($2.rootNode()->style, LEVEL_OF_POINTER($3.rootNode()->style));
																				}
																				else if (IS_ARRAY($3.rootNode()->style)){
																					$$.rootNode()->style=TYPE_ARRAY($2.rootNode()->style, LEVEL_OF_ARRAY($3.rootNode()->style));
																				}
																				else {
																					$$.rootNode()->style=$2.rootNode()->style;
																				}
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="INIT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$3.rootNode()->next;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| AUTO init_declarator_body							{
																				if($2.rootNode()->explain=="no")
																				{
																					 CP::Parser::error(location_type(), "bad!");
																					 system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="AUTO";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=$2.rootNode()->level;
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->style=TYPE_INT;
																				$$.rootNode()->type="DECLARATION";
																				$$.rootNode()->value="INIT_DECL";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$2.rootNode()->next;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;
 
init_declarator_body	: declarator										{
																
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->style=$1.rootNode()->style;
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="INIT_DECL_BODY";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->explain="no";

																				$$.rootNode()->value = $1.rootNode()->value;
																				$$.rootNode()->next = qualdruples.nextKey();
																				$1.addFather($$);
																				$$=$1;
																			}
						| declarator ASSIGN initializer						{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="ASSIGN";
																				temp1.rootNode()->value="=";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				//printf("LEFT: %d\n", $1.rootNode()->style);
																				//printf("RIGHT: %d\n", $3.rootNode()->style);
																				if(!CAN_ASSIGH(MAKE_LEXPR_BY_TYPE($1.rootNode()->style), $3.rootNode()->style)){
																					CP::Parser::error(location_type(), "Initial fail!");
																					system("pause");
																				}
																				if(leftLevel < rightLevel){
																					CP::Parser::error(location_type(), "List is too large!");
																					system("pause");
																				}
																				$$.rootNode()->type="DECLARATOR";
																				$$.rootNode()->value="INIT_DECL_BODY";
																				$$.rootNode()->level=nowlevel+1;

																				list<ASTNode> l;
																				$1.getNodesWanted(isIdType, l);
																				qualdruples.append("=", $3.rootNode()->value, "", l.front().value);
																				$$.rootNode()->next = qualdruples.nextKey();

																				$1.addFather($$);
																				$$=$1;
																				
																			}
						;
 
initializer				: assignment_expression								{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->style=$1.rootNode()->style;
																					$$.rootNode()->type="INITIALIZER";
																					$$.rootNode()->value="INITIALIZER";
																					$$.rootNode()->level=nowlevel+1;


																					$$.rootNode()->value = $1.rootNode()->value;
																					$$.rootNode()->next = qualdruples.nextKey();
																					$1.addFather($$);
																					$$=$1;
																				}

																			}
						| LBRACE initializer_list RBRACE							{
																				AST temp1;
																				temp1.rootNode()->type="LBRACE";
																				temp1.rootNode()->value="{";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="RBRACE";
																				temp2.rootNode()->value="}";
																				temp2.rootNode()->level=$2.rootNode()->level;
																				$2.addBrother(temp2);
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->style=TYPE_REXPR_ARRAY(TYPE_OF_EXPR($2.rootNode()->style), 1);
																				$$.rootNode()->type="INITIALIZER";
																				$$.rootNode()->value="INITIALIZER";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| LBRACE initializer_list COMMA RBRACE						{
																				AST temp1;
																				temp1.rootNode()->type="LBRACE";
																				temp1.rootNode()->value="{";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="COMMA";
																				temp2.rootNode()->value=",";
																				temp2.rootNode()->level=$2.rootNode()->level;
																				AST temp3;
																				temp3.rootNode()->type="RBRACE";
																				temp3.rootNode()->value="}";
																				temp3.rootNode()->level=$2.rootNode()->level;
																				temp2.addBrother(temp3);
																				$2.addBrother(temp2);
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->style=$$.rootNode()->style=TYPE_REXPR_ARRAY(TYPE_OF_EXPR($2.rootNode()->style), 1);
																				$$.rootNode()->type="INITIALIZER";
																				$$.rootNode()->value="INITIALIZER";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;
 
initializer_list		: initializer										{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->style=$1.rootNode()->style;
																				$$.rootNode()->type="INITIALIZER_LIST";
																				$$.rootNode()->value="INITIALIZER_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																				rightLevel = 1;
																			}
						| initializer_list COMMA initializer					{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				int style = FIND_MAX_TYPE($1.rootNode()->style, $3.rootNode()->style);
																				if(style > 0){
																					$$.rootNode()->style=FIND_MAX_TYPE($1.rootNode()->style, $3.rootNode()->style);
																				}
																				else {
																					CP::Parser::error(location_type(), "list item is not same");
																					system("pause");
																				}
																				$$.rootNode()->type="INITIALIZER_LIST";
																				$$.rootNode()->value="INITIALIZER_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																				rightLevel += 1;
																			}
						;
 
statement_list			: statement											{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT_LIST";
																				$$.rootNode()->value="STATEMENT_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| statement_list statement							{
																				int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
																				$1.changeLevel(maxLevel);
																				$2.changeLevel(maxLevel);
																				$1.addBrother($2);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT_LIST";
																				$$.rootNode()->value="STATEMENT_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$2.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						|
						;
 
statement				: compound_statement								{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| expression_statement								{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| selection_statement								{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| iteration_statement								{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| jump_statement									{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						| read_statement									{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| write_statement									{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$1.addFather($$);
																				$$=$1;
																			}
						| labeled_statement									{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="STATEMENT";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
 read_statement			: READ LCURVE expression RCURVE SQM					{
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
																				$3.addBrother(temp4);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="READ_STAT";
																				$$.rootNode()->level=1;
																				qualdruples.append("READ",$3.rootNode()->value,"","", false);
																				$$.rootNode()->next=qualdruples.nextKey();
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;

write_statement			: WRITE LCURVE expression RCURVE SQM					{
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
																				$3.addBrother(temp4);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="WRITE_STAT";
																				$$.rootNode()->level=1;
																				qualdruples.append("WRITE",$3.rootNode()->value,"","", false);
																				$$.rootNode()->next=qualdruples.nextKey();
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;

expression_statement	: SQM												{
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=0;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="EXPRESSION_STAT";
																				$$.rootNode()->level=1;
																				$$.rootNode()->next=qualdruples.nextKey();
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| expression SQM									{
																				AST temp1;
																				temp1.rootNode()->type="SQM";
																				temp1.rootNode()->value=";";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="EXPRESSION_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->next=$1.rootNode()->next;
																				$$.rootNode()->value=$1.rootNode()->value;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
selection_statement		: IF LCURVE expression RCURVE statement					{
																				int maxLevel=max({$3.rootNode()->level,$5.rootNode()->level});
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
																				$3.changeLevel(maxLevel);
																				$5.changeLevel(maxLevel);
																				temp3.addBrother($5);
																				$3.addBrother(temp3);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="SELECTION_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				$5.addNext();
																				qualdruples.insert($3.rootNode()->next,"IF",$3.rootNode()->value,"",$5.rootNode()->next);
																				$$.rootNode()->next=$5.rootNode()->next;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| IF LCURVE expression RCURVE statement ELSE statement	{
																				int maxLevel=max({$3.rootNode()->level,$5.rootNode()->level,$7.rootNode()->level});
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
																				$3.changeLevel(maxLevel);
																				$5.changeLevel(maxLevel);
																				$7.changeLevel(maxLevel);
																				temp4.addBrother($7);
																				$5.addBrother(temp4);
																				temp3.addBrother($5);
																				$3.addBrother(temp3);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="SELECTION_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				$5.addNext();
																				$7.addNext();
																				qualdruples.insert($3.rootNode()->next,"IF",$3.rootNode()->value,"",$5.rootNode()->next);
																				$7.addNext();
																				qualdruples.insert($5.rootNode()->next,"GOTO","","",$7.rootNode()->next);
																				if(!qualdruples.modifyKey($3.rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail!");
																					system("pause");
																				}
																				$$.rootNode()->next=$7.rootNode()->next;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;
 
iteration_statement		: WHILE LCURVE expression RCURVE statement				{
																				int maxLevel=max({$3.rootNode()->level,$5.rootNode()->level});
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
																				$3.changeLevel(maxLevel);
																				$5.changeLevel(maxLevel);
																				temp3.addBrother($5);
																				$3.addBrother(temp3);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="ITERATION_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				$5.addNext();
																				qualdruples.insert($3.rootNode()->next,"WHILE",$3.rootNode()->value,"",$5.rootNode()->next);
																				qualdruples.insert($5.rootNode()->next,"GOTO","","",$1,true);
																				if(!qualdruples.modifyKey($3.rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail!");
																					system("pause");
																				}
																				$$.rootNode()->next=$5.rootNode()->next+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| FOR LCURVE expression_statement expression_statement RCURVE statement
																			{
																				int maxLevel=max({$3.rootNode()->level,$4.rootNode()->level,$6.rootNode()->level});
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
																				$3.changeLevel(maxLevel);
																				$4.changeLevel(maxLevel);
																				$6.changeLevel(maxLevel);
																				temp3.addBrother($6);
																				$4.addBrother(temp3);
																				$3.addBrother($4);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="ITERATION_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				$6.addNext();
																				qualdruples.insert($4.rootNode()->next,"FOR",$4.rootNode()->value,"",$6.rootNode()->next);
																				qualdruples.insert($6.rootNode()->next,"GOTO","","",$3.rootNode()->next,true);
																				if(!qualdruples.modifyKey($4.rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail!");
																					system("pause");
																				}
																				$$.rootNode()->next=$6.rootNode()->next+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| FOR LCURVE expression_statement expression_statement expression RCURVE statement
																			{
																				int maxLevel=max({$3.rootNode()->level,$4.rootNode()->level,$5.rootNode()->level,$7.rootNode()->level});
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
																				$3.changeLevel(maxLevel);
																				$4.changeLevel(maxLevel);
																				$5.changeLevel(maxLevel);
																				$7.changeLevel(maxLevel);
																				temp3.addBrother($7);
																				$5.addBrother(temp3);
																				$4.addBrother($5);
																				$3.addBrother($4);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="ITERATION_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				$5.addNext();
																				$7.addNext();
																				qualdruples.insert($4.rootNode()->next,"FOR",$4.rootNode()->value,"",$7.rootNode()->next);
																				$5.addNext();
																				$7.addNext();
																				qualdruples.insert($4.rootNode()->next+1,"GOTO","","",$5.rootNode()->next);
																				qualdruples.insert($7.rootNode()->next,"GOTO","","",$4.rootNode()->next+2,true);
																				if(!qualdruples.modifyKey($4.rootNode()->next,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail11!");
																					system("pause");
																				}
																				$7.addNext();
																				qualdruples.insert($5.rootNode()->next,"GOTO","","",$3.rootNode()->next,true);
																				if(!qualdruples.modifyKey($4.rootNode()->next+1,1))
																				{
																					CP::Parser::error(location_type(), "Modify key fail22!");
																					system("pause");
																				}
																				$$.rootNode()->next=$7.rootNode()->next+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;
 
jump_statement			: CONTINUE SQM										{
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="CONTINUE";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="JUMP_STAT";
																				$$.rootNode()->level=1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| BREAK SQM											{
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="BREAK";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="JUMP_STAT";
																				$$.rootNode()->level=1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| RETURN SQM										{
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="RETURN";
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=0;
																				temp1.addBrother(temp2);
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="JUMP_STAT";
																				$$.rootNode()->level=1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| RETURN expression SQM								{
																				AST temp1;
																				temp1.rootNode()->type="JUMP";
																				temp1.rootNode()->value="RETURN";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="SQM";
																				temp2.rootNode()->value=";";
																				temp2.rootNode()->level=$2.rootNode()->level;
																				$2.addBrother(temp2);
																				temp1.addBrother($2);
																				int nowLevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="JUMP_STAT";
																				$$.rootNode()->level=nowLevel+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						| GOTO IDENTIFIER SQM								{
																				Symbol outSymbol=sigTable.get($2);
																				if(outSymbol.type==0)
																				{
																					CP::Parser::error(location_type(), "Undefined");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="GOTO";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=0;
																				AST temp2;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=$2;
																				temp2.rootNode()->explain=to_string(outSymbol.type);
																				temp2.rootNode()->level=0;
																				AST temp3;
																				temp3.rootNode()->type="SQM";
																				temp3.rootNode()->value=";";
																				temp3.rootNode()->level=0;
																				temp2.addBrother(temp3);
																				temp1.addBrother(temp2);
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="JUMP_STAT";
																				$$.rootNode()->level=1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
						;
	
expression				: assignment_expression								{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="EXPRESSION";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| expression COMMA assignment_expression				{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="EXPRESSION";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=$3.rootNode()->style;
																				///
																				$$.rootNode()->next=$3.rootNode()->next;
																				$$.rootNode()->value=$3.rootNode()->value;
																				///
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
assignment_expression	: conditional_expression							{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="ASSIGNMENT_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| unary_expression assignment_operator assignment_expression
																			{
																				if(!CAN_ASSIGH($1.rootNode()->style,$3.rootNode()->style))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level,$3.rootNode()->level});
																				$1.changeLevel(maxLevel);
																				$2.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$2.addBrother($3);
																				$1.addBrother($2);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="ASSIGNMENT_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=$3.rootNode()->style;
																				////
																				if(!($1.rootNode()->value==$3.rootNode()->value)){
																					string t=qualdruples.append($2.rootNode()->value,$3.rootNode()->value,"",$1.rootNode()->value);
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				////
																				$1.addFather($$);
																				$$=$1;

																			}
						;
 
conditional_expression	: logical_or_expression								{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="CONDITIONAL_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| logical_or_expression QUESTION expression COLON conditional_expression
																			{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level,$5.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="QUESTION";
																				temp1.rootNode()->value="?";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$5.changeLevel(maxLevel);
																				temp2.addBrother($5);
																				$3.addBrother(temp2);
																				temp2.addBrother($3);
																				$1.addBrother(temp2);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="CONDITIONAL_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_REXPR;
																				$1.addFather($$);
																				$$=$1;
																			}
						;
 
logical_or_expression	: logical_and_expression							{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="LOGICAL_OR_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| logical_or_expression OR_OP logical_and_expression
																			{
																				if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST")&&($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"||",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="OR_OP";
																					temp1.rootNode()->value="||";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="LOGICAL_OR_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					$1.addFather($$);
																					$$=$1;

																					///
																					string t=qualdruples.append("||",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																			}
						;
 
logical_and_expression	: inclusive_or_expression							{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="LOGICAL_AND_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///

																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| logical_and_expression AND_OP inclusive_or_expression
																			{
																				if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST")&&($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"&&",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="AND_OP";
																					temp1.rootNode()->value="&&";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="LOGICAL_AND_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("&&",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;

																				}
																			}
						;
 
inclusive_or_expression	: exclusive_or_expression							{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="INCLUSIVE_OR_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| inclusive_or_expression INCLUSIVE_OR exclusive_or_expression
																			{
																				if(!(CAN_BIT($1.rootNode()->style)&&CAN_BIT($3.rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST")&&($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"|",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="INCLUSIVE_OR";
																					temp1.rootNode()->value="|";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="INCLUSIVE_OR_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					////
																					string t=qualdruples.append("|",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																					
																				}
																			}
						;
 
exclusive_or_expression	: and_expression									{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="EXCLUSIVE_OR_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| exclusive_or_expression EXCLUSIVE_OR and_expression {
																				if(!(CAN_BIT($1.rootNode()->style)&&CAN_BIT($3.rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST")&&($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"^",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="EXCLUSIVE_OR";
																					temp1.rootNode()->value="^";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="EXCLUSIVE_OR_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					////
																					string t=qualdruples.append("^",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																					
																				}
																			}
						;
 
and_expression			: equality_expression								{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="AND_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->value=$1.rootNode()->value;
																					$$.rootNode()->next=qualdruples.nextKey();
																					///
																					$1.addFather($$);
																					$$=$1;
																					
																				}
																			}
						| and_expression AND equality_expression			{
																				if(!(CAN_BIT($1.rootNode()->style)&&CAN_BIT($3.rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST")&&($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"&",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="AND";
																					temp1.rootNode()->value="&";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="AND_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					////
																					string t=qualdruples.append("&",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																					
																				}
																			}
						;
 
equality_expression		: relational_expression								{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="EQUALITY_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| equality_expression EQ_OP relational_expression	{
																				if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST")&&($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"==",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="EQ_OP";
																					temp1.rootNode()->value="==";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="EQUALITY_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("==",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| equality_expression NE_OP relational_expression	{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"!=",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="NE_OP";
																					temp1.rootNode()->value="!=";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="EQUALITY_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("!=",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						;
 
relational_expression	: shift_expression									{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="RELATIONAL_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| relational_expression LESS shift_expression		{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"<",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LESS";
																					temp1.rootNode()->value="<";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="RELATIONAL_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("<",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;

																				}

																			}
						| relational_expression GREATER shift_expression	{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,">",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="GREATER";
																					temp1.rootNode()->value=">";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="RELATIONAL_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append(">",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;

																				}
																			}
						| relational_expression LE_OP shift_expression		{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"<=",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LE_OP";
																					temp1.rootNode()->value="<=";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="RELATIONAL_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append("<=",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| relational_expression GE_OP shift_expression		{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,">=",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="GE_OP";
																					temp1.rootNode()->value=">=";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="RELATIONAL_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=TYPE_REXPR_INT;
																					////
																					string t=qualdruples.append(">=",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																					
																				}
																			}
						;
 
shift_expression		: additive_expression								{
																				string type=$1.rootNode()->type;
																				if(type=="INT_CONST"||type=="DOUBLE_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="SHIFT_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| shift_expression LEFT_OP additive_expression		{
																				if(!(CAN_BIT($1.rootNode()->style)&&CAN_BIT($3.rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,"<<",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LEFT_OP";
																					temp1.rootNode()->value="<<";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="SHIFT_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					////
																					string t=qualdruples.append("<<",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																					
																				}

																			}
						| shift_expression RIGHT_OP additive_expression		{
																				if(!(CAN_BIT($1.rootNode()->style)&&CAN_BIT($3.rootNode()->style)))
																				{
																					CP::Parser::error(location_type(), "Type error!");
																					system("pause");
																				}
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<int>(Operate(val1,">>",val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																					
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="RIGHT_OP";
																					temp1.rootNode()->value=">>";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="SHIFT_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					////
																					string t=qualdruples.append(">>",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																					
																				}

																			}
						;
 
additive_expression		: multiplicative_expression							{
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="ADDITIVE_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
						| additive_expression ADD multiplicative_expression	{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;

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
																					
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="CHAR_CONST")&&$1.rootNode()->value=="0"){
																						$$=$3;
																					}
																					else if(($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="CHAR_CONST")&&$3.rootNode()->value=="0"){
																						$$=$1;
																					}
																					else{
																						int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="ADD";
																						temp1.rootNode()->value="+";
																						temp1.rootNode()->level=maxLevel;
																						$1.changeLevel(maxLevel);
																						$3.changeLevel(maxLevel);
																						temp1.addBrother($3);
																						$1.addBrother(temp1);
																						int nowlevel=$1.rootNode()->level;
																						$$.rootNode()->type="EXPRESSION";
																						$$.rootNode()->value="ADDITIVE_EXPR1";
																						$$.rootNode()->level=nowlevel+1;
																						$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																						///
																						string t=qualdruples.append("+",$1.rootNode()->value,$3.rootNode()->value);
																						$$.rootNode()->value=t;
																						$$.rootNode()->next=qualdruples.nextKey();
																						///
																						$1.addFather($$);
																						$$=$1;
																					}
																				}

																			}
						| additive_expression SUB multiplicative_expression	{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;

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
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST"||$3.rootNode()->type=="CHAR_CONST")&&$3.rootNode()->value=="0"){
																						$$=$1;
																					}
																					else{
																						int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="SUB";
																						temp1.rootNode()->value="-";
																						temp1.rootNode()->level=maxLevel;
																						$1.changeLevel(maxLevel);
																						$3.changeLevel(maxLevel);
																						temp1.addBrother($3);
																						$1.addBrother(temp1);
																						int nowlevel=$1.rootNode()->level;
																						$$.rootNode()->type="EXPRESSION";
																						$$.rootNode()->value="ADDITIVE_EXPR";
																						$$.rootNode()->level=nowlevel+1;
																						$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																						////
																						string t=qualdruples.append("-",$1.rootNode()->value,$3.rootNode()->value);
																						$$.rootNode()->value=t;
																						$$.rootNode()->next=qualdruples.nextKey();
																						////
																						$1.addFather($$);
																						$$=$1;
																					}
																				}

																			}
						;
 
multiplicative_expression	: cast_expression								{
                                                                                if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="MULTIPLICATIVE_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}

																			}
							| multiplicative_expression STAR cast_expression	{
							                                                    string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;

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
																					
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST")&&$1.rootNode()->value=="1"){
																						$$=$3;
																					}
																					else if(($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST"||$3.rootNode()->type=="CHAR_CONST")&&$3.rootNode()->value=="1"){
																						$$=$1;
																					}
																					else{
																						int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="MULTI";
																						temp1.rootNode()->value="*";
																						temp1.rootNode()->level=maxLevel;
																						$1.changeLevel(maxLevel);
																						$3.changeLevel(maxLevel);
																						temp1.addBrother($3);
																						$1.addBrother(temp1);
																						int nowlevel=$1.rootNode()->level;
																						$$.rootNode()->type="EXPRESSION";
																						$$.rootNode()->value="MULTIPLICATIVE_EXPR";
																						$$.rootNode()->level=nowlevel+1;
																						$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																						////
																						string t=qualdruples.append("*",$1.rootNode()->value,$3.rootNode()->value);
																						$$.rootNode()->value=t;
																						$$.rootNode()->next=qualdruples.nextKey();
																						////
																						$1.addFather($$);
																						$$=$1;
																					}
																				}
																				
																			}
							| multiplicative_expression DIV cast_expression	{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST"||type1=="CHAR_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST"||type2=="CHAR_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;

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
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					if(($3.rootNode()->type=="INT_CONST"||$3.rootNode()->type=="DOUBLE_CONST"||$3.rootNode()->type=="CHAR_CONST")&&$3.rootNode()->value=="1"){
																						$$=$1;
																					}
																					else{
																						int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																						AST temp1;
																						temp1.rootNode()->type="DIV";
																						temp1.rootNode()->value="/";
																						temp1.rootNode()->level=maxLevel;
																						$1.changeLevel(maxLevel);
																						$3.changeLevel(maxLevel);
																						temp1.addBrother($3);
																						$1.addBrother(temp1);
																						int nowlevel=$1.rootNode()->level;
																						$$.rootNode()->type="EXPRESSION";
																						$$.rootNode()->value="MULTIPLICATIVE_EXPR";
																						$$.rootNode()->level=nowlevel+1;
																						$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																						////
																						string t=qualdruples.append("/",$1.rootNode()->value,$3.rootNode()->value);
																						$$.rootNode()->value=t;
																						$$.rootNode()->next=qualdruples.nextKey();
																						////
																						$1.addFather($$);
																						$$=$1;
																					}
																				}

																			}
							| multiplicative_expression MOD cast_expression	{
																				string type1=$1.rootNode()->type;
																				string type2=$3.rootNode()->type;
																				if((type1=="INT_CONST"||type1=="DOUBLE_CONST")&&(type2=="INT_CONST"||type2=="DOUBLE_CONST")){
																					string value1=$1.rootNode()->value;
																					string value2=$3.rootNode()->value;
																					int val1=stringToNum<int>(value1);
																					int val2=stringToNum<int>(value2);
																					string result=numToString<double>(val1%val2);
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$3.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																					
																				}
																				else{																				
																					int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="MOD";
																					temp1.rootNode()->value="%";
																					temp1.rootNode()->level=maxLevel;
																					$1.changeLevel(maxLevel);
																					$3.changeLevel(maxLevel);
																					temp1.addBrother($3);
																					$1.addBrother(temp1);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="MULTIPLICATIVE_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																					////
																					string t=qualdruples.append("%",$1.rootNode()->value,$3.rootNode()->value);
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
							;
 
cast_expression				: unary_expression								{
                                                                                if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="CAST_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
							| LCURVE type_specifier RCURVE cast_expression		{
																				if(($2.rootNode()->type=="TYPE_SPECIFIER"&&$2.rootNode()->value!="VOID")&&($4.rootNode()->type=="INT_CONST"||$4.rootNode()->type=="DOUBLE_CONST"||$4.rootNode()->type=="CHAR_CONST")){
																					string type=$2.rootNode()->value;
																					string value=$4.rootNode()->value;
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
																					$$.rootNode()->type=type+"_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($2.rootNode()->level,$4.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($4.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																				
																					int maxLevel=max({$2.rootNode()->level,$4.rootNode()->level});
																					AST temp1;
																					temp1.rootNode()->type="LCURVE";
																					temp1.rootNode()->value="(";
																					temp1.rootNode()->level=maxLevel;
																					AST temp2;
																					temp2.rootNode()->type="RCURVE";
																					temp2.rootNode()->value=")";
																					temp2.rootNode()->level=maxLevel;
																					$2.changeLevel(maxLevel);
																					$4.changeLevel(maxLevel);
																					temp2.addBrother($4);
																					$2.addBrother(temp2);
																					temp1.addBrother($2);
																					int nowlevel=temp1.rootNode()->level;
																					$$.rootNode()->style=MAKE_REXPR_BY_TYPE($2.rootNode()->style);
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="CAST_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					////
																					string t=qualdruples.append(numToString<int>($2.rootNode()->style),$4.rootNode()->value,"");
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					temp1.addFather($$);
																					$$=temp1;
																				}

																			}
							| LCURVE type_specifier pointer RCURVE cast_expression		{
																				int maxLevel=max({$2.rootNode()->level,$3.rootNode()->level,$5.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LCURVE";
																				temp1.rootNode()->value="(";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RCURVE";
																				temp2.rootNode()->value=")";
																				temp2.rootNode()->level=maxLevel;
																				$2.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$5.changeLevel(maxLevel);
																				temp2.addBrother($5);
																				$3.addBrother(temp2);
																				$2.addBrother($3);
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->style=MAKE_REXPR_BY_TYPE(TYPE_POINTER($2.rootNode()->style,LEVEL_OF_POINTER($3.rootNode()->style)));
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="CAST_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				////
																				string t=qualdruples.append(numToString<int>(TYPE_POINTER($2.rootNode()->style,LEVEL_OF_POINTER($3.rootNode()->style))),$5.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather($$);
																				$$=temp1;	

																			}
							;
 
unary_expression			: postfix_expression							{
                                                                                
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="UNARY_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
							| INC_OP unary_expression						{
																				if(CAN_ASSIGN_TO($2.rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="INC_OP";
																				temp1.rootNode()->value="++";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="UNARY_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=$2.rootNode()->style;
																				////
																				string t=qualdruples.append("++a",$2.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather($$);
																				$$=temp1;

																			}
							| DEC_OP unary_expression						{
																				if(CAN_ASSIGN_TO($2.rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="DEC_OP";
																				temp1.rootNode()->value="--";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="UNARY_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=$2.rootNode()->style;
																				////
																				string t=qualdruples.append("--a",$2.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather($$);
																				$$=temp1;

																			}
							| unary_operator cast_expression				{
																				if(($1.rootNode()->value=="!"||$1.rootNode()->value=="-"||$1.rootNode()->value=="+")&&($2.rootNode()->type=="INT_CONST"||$2.rootNode()->type=="DOUBLE_CONST")){
																					string value2=$2.rootNode()->value;
																					double val2=stringToNum<double>(value2);
																					string result=numToString<int>(Operate(0,$1.rootNode()->value,val2));
																					$$.rootNode()->type="DOUBLE_CONST";
																					$$.rootNode()->value=result;
																					$$.rootNode()->level=max($1.rootNode()->level,$2.rootNode()->level);
																					$$.rootNode()->style=MAKE_REXPR($2.rootNode()->style);
																					///
																					$$.rootNode()->next=qualdruples.nextKey();
																				}
																				else{
																					int maxLevel=max({$1.rootNode()->level,$2.rootNode()->level});
																					$1.changeLevel(maxLevel);
																					$2.changeLevel(maxLevel);
																					$1.addBrother($2);
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="UNARY_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					if($1.rootNode()->value=="*"&&IS_POINTER(TYPE_OF_EXPR($2.rootNode()->style))){
																						$$.rootNode()->style=SUB_LEVEL_OF_POINTER_EXPR($2.rootNode()->style);
																					}
																					else if($1.rootNode()->value=="&")
																					{
																						if(LEVEL_OF_BASIC_TYPE(TYPE_OF_EXPR($2.rootNode()->style)) == 0){
																							$$.rootNode()->style=TYPE_REXPR_POINTER(TYPE_OF_EXPR($2.rootNode()->style), 1);
																						}
																						else if(IS_POINTER(TYPE_OF_EXPR($2.rootNode()->style))){
																							$$.rootNode()->style=TYPE_REXPR_POINTER(TYPE_OF_POINTER(TYPE_OF_EXPR($2.rootNode()->style)), LEVEL_OF_POINTER_EXPR($2.rootNode()->style) + 1);
																						}
																					}
																					else
																						$$.rootNode()->style=MAKE_REXPR($2.rootNode()->style);

																					////
																					string t="";
																					if($1.rootNode()->value=="&"){
																						t=qualdruples.append("_&",$2.rootNode()->value,"");
																					}
																					else if($1.rootNode()->value=="*"){
																						string result="*"+$2.rootNode()->value;
																						t=qualdruples.append("_*",$2.rootNode()->value,"",result);
																					}
																					else{
																						t=qualdruples.append($1.rootNode()->value,$2.rootNode()->value,"");
																					}
																					$$.rootNode()->value=t;
																					$$.rootNode()->next=qualdruples.nextKey();
																					////
																					$1.addFather($$);
																					$$=$1;
																				}

																			}
							| SIZEOF unary_expression						{
																				AST temp1;
																				temp1.rootNode()->type="SIZEOF";
																				temp1.rootNode()->value="SIZEOF";
																				temp1.rootNode()->level=$2.rootNode()->level;
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="UNARY_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_REXPR_INT;
																				////
																				string t=qualdruples.append("SIZEOF",$2.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather($$);
																				$$=temp1;

																			}
							| SIZEOF LCURVE type_specifier RCURVE				{
																				AST temp1;
																				temp1.rootNode()->type="SIZEOF";
																				temp1.rootNode()->value="SIZEOF";
																				temp1.rootNode()->level=$3.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="LCURVE";
																				temp2.rootNode()->value="(";
																				temp2.rootNode()->level=$3.rootNode()->level;
																				AST temp3;
																				temp3.rootNode()->type="RCURVE";
																				temp3.rootNode()->value=")";
																				temp3.rootNode()->level=$3.rootNode()->level;
																				$3.addBrother(temp3);
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="UNARY_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_REXPR_INT;
																				////
																				string t=qualdruples.append("SIZEOF",$3.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				temp1.addFather($$);
																				$$=temp1;

																			}
							;
 
postfix_expression			: primary_expression							{
																				
																				if($1.rootNode()->type=="INT_CONST"||$1.rootNode()->type=="DOUBLE_CONST"||$1.rootNode()->type=="CHAR_CONST"){
																					$$=$1;
																				}
																				else{
																					int nowlevel=$1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value="POSTFIX_EXPR";
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$1.rootNode()->style;
																					///
																					$$.rootNode()->next=$1.rootNode()->next;
																					$$.rootNode()->value=$1.rootNode()->value;
																					///
																					$1.addFather($$);
																					$$=$1;
																				}
																			}
							| postfix_expression LSQUARE expression RSQUARE	{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LSQUARE";
																				temp1.rootNode()->value="[";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RSQUARE";
																				temp2.rootNode()->value="]";
																				temp2.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$3.addBrother(temp2);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=SUB_LEVEL_OF_ARRAY_EXPR($1.rootNode()->style);
																				////
																				string t=qualdruples.append("array",$1.rootNode()->value,$3.rootNode()->value);
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				$1.addFather($$);
																				$$=$1;	


																			}
							| postfix_expression LCURVE RCURVE					{
																				AST temp1;
																				temp1.rootNode()->type="LCURVE";
																				temp1.rootNode()->value="(";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="RCURVE";
																				temp2.rootNode()->value=")";
																				temp2.rootNode()->level=$1.rootNode()->level;
																				temp1.addBrother(temp2);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_REXPR;
																				$1.addFather($$);
																				$$=$1;
																			}
							| postfix_expression LCURVE argument_expression_list RCURVE
																			{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="LCURVE";
																				temp1.rootNode()->value="(";
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="RCURVE";
																				temp2.rootNode()->value=")";
																				temp2.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				$3.addBrother(temp2);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_REXPR;
																				$1.addFather($$);
																				$$=$1;
																			}
							| postfix_expression DOT IDENTIFIER				{
																				AST temp1;
																				temp1.rootNode()->type="DOT";
																				temp1.rootNode()->value=".";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				if(!sigTable.isRepeatInScope($3))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put($3, putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get($3);
																				AST temp2;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=$3;
																				temp2.rootNode()->explain=to_string(outSymbol.type);
																				temp2.rootNode()->level=$1.rootNode()->level;
																				temp1.addBrother(temp2);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_LEXPR;
																				$1.addFather($$);
																				$$=$1;
																			}
							| postfix_expression PTR_OP IDENTIFIER			{
																				AST temp1;
																				temp1.rootNode()->type="PTR_OP";
																				temp1.rootNode()->value="->";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				if(!sigTable.isRepeatInScope($3))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put($3, putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get($3);
																				AST temp2;
																				temp2.rootNode()->type="IDENTIFIER";
																				temp2.rootNode()->value=$3;
																				temp2.rootNode()->explain=to_string(outSymbol.type);
																				temp2.rootNode()->level=$1.rootNode()->level;
																				temp1.addBrother(temp2);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=TYPE_LEXPR;
																				$1.addFather($$);
																				$$=$1;
																			}
							| postfix_expression INC_OP						{
																				if(CAN_ASSIGN_TO($1.rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="INC_OP";
																				temp1.rootNode()->value="++";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																				
																				////
																				string t=qualdruples.append("a++",$1.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				$1.addFather($$);
																				$$=$1;

																			}
							| postfix_expression DEC_OP						{
																				if(CAN_ASSIGN_TO($1.rootNode()->style)==0)
																				{
																					CP::Parser::error(location_type(), "Need left!");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="DEC_OP";
																				temp1.rootNode()->value="--";
																				temp1.rootNode()->level=$1.rootNode()->level;
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value="POSTFIX_EXPR";
																				$$.rootNode()->level=nowlevel+1;
																				$$.rootNode()->style=MAKE_REXPR($1.rootNode()->style);
																				////
																				string t=qualdruples.append("a--",$1.rootNode()->value,"");
																				$$.rootNode()->value=t;
																				$$.rootNode()->next=qualdruples.nextKey();
																				////
																				$1.addFather($$);
																				$$=$1;

																			}
							;
 
primary_expression			: IDENTIFIER									{
																				Symbol outSymbol=sigTable.get($1);
																				if(outSymbol.type==0)
																				{
																					CP::Parser::error(location_type(), "Undefined");
																					system("pause");
																				}
																				AST temp1;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->explain=to_string(outSymbol.type);
																				temp1.rootNode()->level=0;
																				temp1.rootNode()->style=outSymbol.style;
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value=temp1.rootNode()->value;
																				$$.rootNode()->level=1;
																				$$.rootNode()->style=MAKE_LEXPR_BY_TYPE(outSymbol.style);
																				temp1.addFather($$);
																				$$=temp1;
																			}
							| INT_CONST										{
																				$$.rootNode()->type="INT_CONST";
																				$$.rootNode()->value=$1;
																				$$.rootNode()->level=0;
																				$$.rootNode()->style=TYPE_REXPR_INT;
																				$$.rootNode()->next=qualdruples.nextKey();
																			}
							| DOUBLE_CONST									{
																				$$.rootNode()->type="DOUBLE_CONST";
																				$$.rootNode()->value=$1;
																				$$.rootNode()->level=0;
																				$$.rootNode()->style=TYPE_REXPR_DOUBLE;
																				$$.rootNode()->next=qualdruples.nextKey();
																			}
							| CHAR_CONST										{
																				$$.rootNode()->type="CHAR_CONST";
																				$$.rootNode()->value=$1;
																				$$.rootNode()->level=0;
																				$$.rootNode()->style=TYPE_REXPR_CHAR;
																				$$.rootNode()->next=qualdruples.nextKey();
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
							| STR_CONST										{
																				AST temp1;
																				temp1.rootNode()->type="STR_CONST";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=0;
																				temp1.rootNode()->style=TYPE_REXPR_POINTER(TYPE_CHAR,1);
																				$$.rootNode()->type="EXPRESSION";
																				$$.rootNode()->value=temp1.rootNode()->value;
																				$$.rootNode()->level=1;
																				$$.rootNode()->style=TYPE_REXPR_POINTER(TYPE_CHAR,1);
																				temp1.addFather($$);
																				$$=temp1;
																			}
							| LCURVE expression RCURVE						{
																				if($2.rootNode()->type=="INT_CONST"||$2.rootNode()->type=="DOUBLE_CONST"||$2.rootNode()->type=="CHAR_CONST"){
																					$$=$2;
																				}
																				else{
																					AST temp1;
																					temp1.rootNode()->type="LCURVE";
																					temp1.rootNode()->value="(";
																					temp1.rootNode()->level=$2.rootNode()->level;
																					AST temp2;
																					temp2.rootNode()->type="RCURVE";
																					temp2.rootNode()->value=")";
																					temp2.rootNode()->level=$2.rootNode()->level;
																					$2.addBrother(temp2);
																					temp1.addBrother($2);
																					int nowlevel=temp1.rootNode()->level;
																					$$.rootNode()->type="EXPRESSION";
																					$$.rootNode()->value=$2.rootNode()->value;
																					$$.rootNode()->level=nowlevel+1;
																					$$.rootNode()->style=$2.rootNode()->style;
																					temp1.addFather($$);
																					$$=temp1;	
																				}
																			}
							;
 
argument_expression_list	: assignment_expression							{
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="ARGUMENT_EXPRESSION_LIST";
																				$$.rootNode()->value="ARGUMENT_EXPRESSION_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				///
																				$$.rootNode()->value=$1.rootNode()->value;
																				///
																				$1.addFather($$);
																				$$=$1;
																			}
							| argument_expression_list COMMA assignment_expression
																			{
																				int maxLevel=max({$1.rootNode()->level,$3.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="COMMA";
																				temp1.rootNode()->value=",";
																				temp1.rootNode()->level=maxLevel;
																				$1.changeLevel(maxLevel);
																				$3.changeLevel(maxLevel);
																				temp1.addBrother($3);
																				$1.addBrother(temp1);
																				int nowlevel=$1.rootNode()->level;
																				$$.rootNode()->type="ARGUMENT_EXPRESSION_LIST";
																				$$.rootNode()->value="ARGUMENT_EXPRESSION_LIST";
																				$$.rootNode()->level=nowlevel+1;
																				$1.addFather($$);
																				$$=$1;
																			}
							;
 
unary_operator				: AND											{
																				$$.rootNode()->type="UNARY_OPRATOR";
																				$$.rootNode()->value="&";
																				$$.rootNode()->level=0;
																			}
							| STAR											{
																				$$.rootNode()->type="UNARY_OPRATOR";
																				$$.rootNode()->value="*";
																				$$.rootNode()->level=0;
																			}
							| ADD											{
																				$$.rootNode()->type="UNARY_OPRATOR";
																				$$.rootNode()->value="+";
																				$$.rootNode()->level=0;
																			}
							| SUB											{
																				$$.rootNode()->type="UNARY_OPRATOR";
																				$$.rootNode()->value="-";
																				$$.rootNode()->level=0;
																			}
							| WAVE											{
																				$$.rootNode()->type="UNARY_OPRATOR";
																				$$.rootNode()->value="~";
																				$$.rootNode()->level=0;
																			}
							| SIGH											{
																				$$.rootNode()->type="UNARY_OPRATOR";
																				$$.rootNode()->value="!";
																				$$.rootNode()->level=0;
																			}
							;
 
assignment_operator			: ASSIGN											{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="=";
																				$$.rootNode()->level=0;
																			}
							| MUL_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="*=";
																				$$.rootNode()->level=0;
																			}
							| DIV_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="/=";
																				$$.rootNode()->level=0;
																			}
							| MOD_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="%=";
																				$$.rootNode()->level=0;
																			}
							| ADD_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="+=";
																				$$.rootNode()->level=0;
																			}
							| SUB_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="-=";
																				$$.rootNode()->level=0;
																			}
							| LEFT_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="<<=";
																				$$.rootNode()->level=0;
																			}
							| RIGHT_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value=">>=";
																				$$.rootNode()->level=0;
																			}
							| AND_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="&=";
																				$$.rootNode()->level=0;
																			}
							| XOR_ASSIGN									{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="^=";
																				$$.rootNode()->level=0;
																			}
							| OR_ASSIGN										{
																				$$.rootNode()->type="ASSIGNMENT_OPRATOR";
																				$$.rootNode()->value="|=";
																				$$.rootNode()->level=0;
																			}
							;
     
labeled_statement			: IDENTIFIER COLON statement					{
																				if(!sigTable.isRepeatInScope($1))
																				{
																					Symbol putSymbol;
																					putSymbol.type=index;
																					sigTable.put($1, putSymbol);
																					index++;
																				}
																				Symbol outSymbol=sigTable.get($1);
																				AST temp1;
																				temp1.rootNode()->type="IDENTIFIER";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->explain=to_string(outSymbol.type);
																				temp1.rootNode()->level=$3.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=$3.rootNode()->level;
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="LABELED_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
							| CASE constant_expression COLON statement		{
																				int maxLevel=max({$2.rootNode()->level,$4.rootNode()->level});
																				AST temp1;
																				temp1.rootNode()->type="CASE";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=maxLevel;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=maxLevel;
																				$2.changeLevel(maxLevel);
																				$4.changeLevel(maxLevel);
																				temp2.addBrother($4);
																				$2.addBrother(temp2);
																				temp1.addBrother($2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="LABELED_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
							| DEFAULT COLON statement						{
																				AST temp1;
																				temp1.rootNode()->type="DEFAULT";
																				temp1.rootNode()->value=$1;
																				temp1.rootNode()->level=$3.rootNode()->level;
																				AST temp2;
																				temp2.rootNode()->type="COLON";
																				temp2.rootNode()->value=":";
																				temp2.rootNode()->level=$3.rootNode()->level;
																				temp2.addBrother($3);
																				temp1.addBrother(temp2);
																				int nowlevel=temp1.rootNode()->level;
																				$$.rootNode()->type="STATEMENT";
																				$$.rootNode()->value="LABELED_STAT";
																				$$.rootNode()->level=nowlevel+1;
																				temp1.addFather($$);
																				$$=temp1;
																			}
							;
%%

#include "parser_after.h"
