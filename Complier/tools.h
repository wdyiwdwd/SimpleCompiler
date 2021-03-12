#pragma once
#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <iostream>  
#include <sstream>

using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

template <class Type>
string numToString(const Type& num)
{
	ostringstream oss;
	oss << num;
	return oss.str();
}

bool isStrNumInt(string num);

int Operate(int num1, string operate, int num2);

bool firstIsNum(string str);

string getStars(int num);

int deleteStar(string& arg);

string addStar(string arg, int num);

#endif;