#pragma once
#ifndef _TEMP_H_
#define _TEMP_H_
#include "signary.h"
#include "tools.h"

using namespace std;

class TempTable:public Signary
{
public:
	int max;
	TempTable(){
		max = 0;
	};
	~TempTable(){};
	string putTemp(Symbol symbol) {
		int i = 0;
		while (true) {
			if (!this->isRepeatInExtern("&"+numToString<int>(i))){
				break;
			}
			i++;
		}
		this->put("&" + numToString<int>(i), symbol);
		if (i > max) max = i;
		return "&" + numToString<int>(i);
	}
	int getMax() {
		return max;
	}
private:

};

#endif