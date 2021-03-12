#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "parser.tab.h"
#include "scanner.h"

namespace CP{
	
	class Parser;
	class Scanner;

	class Driver
	{
	public:
		Driver() = default;
		virtual ~Driver();
		void parse(std::istream &iss);

	private:
		CP::Parser  *parser = nullptr;
		CP::Scanner *scanner = nullptr;
	};

} /* end namespace CP */
#endif /* END __DRIVER_HPP__ */
