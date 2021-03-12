#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if !defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif

#include "parser.tab.h"
#include "location.hh"

namespace CP{

	class Scanner : public yyFlexLexer{
	public:
		Scanner(std::istream *in) : yyFlexLexer(in) {};
		virtual ~Scanner() {};
		virtual int yylex(CP::Parser::semantic_type * const lval,
			CP::Parser::location_type *location);
		// YY_DECL defined in lexer.l
		// Method body created by flex in lexer.yy.cc
	private:
		CP::Parser::semantic_type *yylval = nullptr;  /* yyval ptr */
	};

} /* end namespace CP */

#endif /* END __SCANNER_HPP__ */
