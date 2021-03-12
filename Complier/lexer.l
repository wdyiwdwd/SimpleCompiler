%{
#include "lexer_before.h"

#include "symbol.h"
#include "signary.h"
#include "tempTable.h"
#include "ASTNode.h"
#include "Qualdruple.h"
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
extern Signary sigTable;
extern TempTable tempTable;
extern Qualdruples qualdruples;
%}

%option debug
%option nodefault
%option yyclass="CP::Scanner"
%option noyywrap
%option yylineno
%option c++

delim   [ \t\r\n]
ws      {delim}+
letter_ [A-Za-z_]
digit   [0-9]
id      {letter_}({letter_}|{digit})*
int_const 0|([1-9][0-9]*)
double_const {digit}*(\.{digit}*)?([eE][+-]?{digit}+)?
literal (\"(\\.|[^"\\])*\")
sigle_literal (\'(\\.|[^'\\])*\')
note	("/*"[^*]*[*]+([^*/][^*]*[*]+)*[*]*"/")|("//".*)

%%
%{          /** Code executed at the beginning of yylex **/
	yylval = lval;
%}
{ws}        {/* nothing */}
{note}		{
			}
void		{
				yylval->str=yytext;
                return token::VOID;
			}
char		{
				yylval->str=yytext;
                return token::CHAR;
			}
int			{
				yylval->str=yytext;
                return token::INT;
			}
float		{
				yylval->str=yytext;
                return token::FLOAT;
			}
double		{
				yylval->str=yytext;
                return token::DOUBLE;
			}
if			{
				yylval->str=yytext;
                return token::IF;
			}
else		{
				yylval->str=yytext;
                return token::ELSE;
			}
while 		{
				yylval->wnext=qualdruples.nextKey();
                return token::WHILE;
			}
for	 		{
				yylval->str=yytext;
                return token::FOR;
			}
continue	{
				yylval->str=yytext;
                return token::CONTINUE;
			}
break		{
				yylval->str=yytext;
                return token::BREAK;
			}
return		{
				yylval->str=yytext;
                return token::RETURN;
			}
read		{
				yylval->str=yytext;
                return token::READ;
			}
write		{
				yylval->str=yytext;
                return token::WRITE;
			}
goto		{
				yylval->str=yytext;
                return token::GOTO;
			}
typedef		{
				yylval->str=yytext;
                return token::TYPEDEF;
			}
extern		{
				yylval->str=yytext;
                return token::EXTERN;
			}
static		{
				yylval->str=yytext;
                return token::STATIC;
			}
auto		{
				yylval->str=yytext;
                return token::AUTO;
			}
struct		{
				yylval->str=yytext;
                return token::STRUCT;
			}
union		{
				yylval->str=yytext;
                return token::UNION;
			}
enum		{
				yylval->str=yytext;
                return token::ENUM;
			}
const		{
				yylval->str=yytext;
                return token::CONST;
			}
volatile	{
				yylval->str=yytext;
                return token::VOLATILE;
			}
register	{
				yylval->str=yytext;
                return token::REGISTER;
			}
case		{
				yylval->str=yytext;
                return token::CASE;
			}
default		{
				yylval->str=yytext;
                return token::DEFAULT;
			}
"..."		{
				yylval->str=yytext;
                return token::ELLIPSIS;
			}
"||"		{
				yylval->str=yytext;
                return token::OR_OP;
			}
"&&"		{
				yylval->str=yytext;
                return token::AND_OP;
			}
"=="			{
				yylval->str=yytext;
                return token::EQ_OP;
			}
"!="		{
				yylval->str=yytext;
                return token::NE_OP;
			}
"<="		{
				yylval->str=yytext;
                return token::LE_OP;
			}
">="		{
				yylval->str=yytext;
                return token::GE_OP;
			}
"<<"		{
				yylval->str=yytext;
                return token::LEFT_OP;
			}
">>"		{
				yylval->str=yytext;
                return token::RIGHT_OP;
			}
"++"		{
				yylval->str=yytext;
                return token::INC_OP;
			}
"--"		{
				yylval->str=yytext;
                return token::DEC_OP;
			}
sizeof		{
				yylval->str=yytext;
                return token::SIZEOF;
			}
"->"		{
				yylval->str=yytext;
                return token::PTR_OP;
			}
{sigle_literal}	{
				yylval->str=yytext;
                return token::CHAR_CONST;
			}
{literal}	{
				yylval->str=yytext;
                return token::STR_CONST;
			}
"*="		{
				yylval->str=yytext;
                return token::MUL_ASSIGN;
			}
"/="		{
				yylval->str=yytext;
                return token::DIV_ASSIGN;
			}
"%="		{
				yylval->str=yytext;
                return token::MOD_ASSIGN;
			}
"+="		{
				yylval->str=yytext;
                return token::ADD_ASSIGN;
			}
"-="		{
				yylval->str=yytext;
                return token::SUB_ASSIGN;
			}
"<<="		{
				yylval->str=yytext;
                return token::LEFT_ASSIGN;
			}
">>="		{
				yylval->str=yytext;
                return token::RIGHT_ASSIGN;
			}
"&="		{
				yylval->str=yytext;
                return token::AND_ASSIGN;
			}
"^="		{
				yylval->str=yytext;
                return token::XOR_ASSIGN;
			}
"|="		{
				yylval->str=yytext;
                return token::OR_ASSIGN;
			}
"{"         {
                sigTable.enterScope();
				tempTable.enterScope();
                yylval->str=yytext;
                return token::LBRACE;
            }
"}"         {
                
                yylval->str=yytext;
                return token::RBRACE;
            }
"("         {
				yylval->str=yytext;
                return token::LCURVE;
			}
")"         {
				yylval->str=yytext;
                return token::RCURVE;
			}
","         {
				yylval->str=yytext;
                return token::COMMA;
			}
";"         {
				yylval->str=yytext;
                return token::SQM;
			}
":"         {
				yylval->str=yytext;
                return token::COLON;
			}
"?"         {
				yylval->str=yytext;
                return token::QUESTION;
			}
"*"         {
				yylval->str=yytext;
                return token::STAR;
			}
"+"         {
				yylval->str=yytext;
                return token::ADD;
			}
"-"         {
				yylval->str=yytext;
                return token::SUB;
			}
"/"         {
				yylval->str=yytext;
                return token::DIV;
			}
"%"         {
				yylval->str=yytext;
                return token::MOD;
			}
"="         {
				yylval->str=yytext;
                return token::ASSIGN;
			}
"["         {
				yylval->str=yytext;
                return token::LSQUARE;
			}
"]"         {
				yylval->str=yytext;
                return token::RSQUARE;
			}
"|"         {
				yylval->str=yytext;
                return token::INCLUSIVE_OR;
			}
"^"         {
				yylval->str=yytext;
                return token::EXCLUSIVE_OR;
			}
"&"         {
				yylval->str=yytext;
                return token::AND;
			}
"<"         {
				yylval->str=yytext;
                return token::LESS;
			}
">"         {
				yylval->str=yytext;
                return token::GREATER;
			}
"."         {
				yylval->str=yytext;
                return token::DOT;
			}
"~"         {
				yylval->str=yytext;
                return token::WAVE;
			}
"!"         {
				yylval->str=yytext;
                return token::SIGH;
			}
{id}        {
                yylval->str=yytext;
                return token::IDENTIFIER;
            }
{int_const}	{
				yylval->str=yytext;
                return token::INT_CONST;
			}

{double_const}	{
				yylval->str=yytext;
                return token::DOUBLE_CONST;
			}

%%

#include "lexer_after.h"
