//
// Created by wjc on 17-10-14.
//

#ifndef FLEX_BISON_CMAKE_PARSER_AFTER_HPP
#define FLEX_BISON_CMAKE_PARSER_AFTER_HPP

#include "parser_before.h"


void CP::Parser::error(const location_type &l, const std::string &err_message)
{
	std::cerr << "Error: " << err_message << " at " << l << " \nline: " <<myline <<"  text: "<<mytext<< "\n";
}


#endif //FLEX_BISON_CMAKE_PARSER_AFTER_HPP
