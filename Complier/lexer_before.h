//
// Created by wjc on 17-10-14.
//

#ifndef FLEX_BISON_CMAKE_LEXER_HPP
#define FLEX_BISON_CMAKE_LEXER_HPP

// FIXME: We need attention to not put any implementation into this header, Since we have include this file multitimes in parser.yy
// FIXME: It maybe possible to put this file multiple times due to HEADER INCLUDE PROTECTION

/* C++ string header, for string ops below */
#include <string>
#define YY_NO_UNISTD_H

/* Implementation of yyFlexScanner */
#include "scanner.h"

#undef  YY_DECL
#define YY_DECL int CP::Scanner::yylex( CP::Parser::semantic_type * const lval, CP::Parser::location_type *loc )

/*	typedef to make the returns for the tokens shorter */
using token = CP::Parser::token;

/*	define yyterminate as this instead of NULL */
#define yyterminate() do { return token::END; } while(0)

/*	update location on matching
	Since it actually just use this macro as statement rather than expression */
#define YY_USER_ACTION do { loc->step(); loc->columns(yyleng); } while(0);

#endif //FLEX_BISON_CMAKE_LEXER_HPP
