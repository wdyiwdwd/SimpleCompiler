#include <cctype>
#include <fstream>
#include <cassert>

#include "driver.h"

using namespace std;
using namespace CP;

Driver::~Driver()
{
	delete scanner;
	scanner = nullptr;
	delete parser;
	parser = nullptr;
}


void Driver::parse(istream &stream)
{
	if (stream.good() || !stream.eof())
	{
		//Originally scanner and parser are nullptr
		delete scanner;
		delete parser;

		try {
			scanner = new Scanner(&stream);
			parser = new Parser((*scanner), (*this));
		}
		catch (bad_alloc &ba) {
			cerr << "Failed to allocate scanner: (" << ba.what() << "), exiting!!\n";
			exit(EXIT_FAILURE);
		}

		static const int accept = 0;
		if (parser->parse() != accept) {
			cerr << "Parse failed!!\n";
		}
	}
}


