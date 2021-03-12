#pragma once
#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include "signary.h"
#include <hash_map>

using namespace std;

class Signary;

class Symbol
{
public:
	int style;
	void* address;
	int type;
	Signary* subSignary;
	Symbol(){
		this->style = 0;
		this->address = NULL;
		this->type = 0;
		this->subSignary = NULL;
	}
	Symbol(void* address, int type){
		this->address = address;
		this->type = type;
		this->subSignary = NULL;
		this->style = 0;
	}
	Symbol(void* address, int type, int style){
		this->style = style;
		this->address = address;
		this->type = type;
		this->subSignary = NULL;
	}
	Symbol(const Symbol& symbol) {
		this->address = symbol.address;
		this->type = symbol.type;
		this->subSignary = symbol.subSignary;
		this->style = symbol.style;
	}
	Symbol& operator = (Symbol& symbol) {
		this->address = symbol.address;
		this->type = symbol.type;
		this->subSignary = symbol.subSignary;
		this->style = symbol.style;
		return *this;
	}
	bool operator == (const Symbol& symbol) {
		return (this->address == symbol.address &&
			this->type == symbol.type &&
			this->subSignary == symbol.subSignary &&
			this->style == symbol.style);
	}
};

#endif