//
// Created by wjc on 17-10-14.
//

#ifndef FLEX_BISON_CMAKE_PARSER_BEFORE_HPP_HPP
#define FLEX_BISON_CMAKE_PARSER_BEFORE_HPP_HPP

// FIXME: We need attention to not put any implementation into this header, Since we have include this file multitimes in parser.yy
// FIXME: It maybe possible to put this file multiple times due to HEADER INCLUDE PROTECTION

namespace CP {
	class Driver;
	class Scanner;
}

// The following definitions is missing when %locations isn't used

#ifndef YY_NULLPTR
#define YY_NULLPTR nullptr
#endif

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "driver.h"
#include "parser.tab.h"
#include "scanner.h"

#undef yylex
#define yylex scanner.yylex
#define myline scanner.lineno()
#define mytext scanner.YYText()
#endif //FLEX_BISON_CMAKE_PARSER_BEFORE_HPP_HPP
