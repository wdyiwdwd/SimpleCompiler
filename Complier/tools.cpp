#include "tools.h"

bool isStrNumInt(string num) {
	if (num.find(".") != std::string::npos) return false;
	if (num.find("E") != std::string::npos) return false;
	if (num.find("e") != std::string::npos) return false;
	double a = stringToNum<double>(num);
	return ((int)a) == a;
}

int Operate(int num1, string operate, int num2){
	if (operate == "<<")
		return num1 << num2;
	else if (operate == ">>")
		return num1 >> num2;
	else if (operate == "<")
		return num1 < num2;
	else if (operate == ">")
		return num1 > num2;
	else if (operate == "<=")
		return num1 <= num2;
	else if (operate == ">=")
		return num1 >= num2;
	else if (operate == "==")
		return num1 == num2;
	else if (operate == "!=")
		return num1 != num2;
	else if (operate == "&")
		return num1 & num2;
	else if (operate == "&&")
		return num1 && num2;
	else if (operate == "|")
		return num1 | num2;
	else if (operate == "||")
		return num1 || num2;
	else if (operate == "^")
		return num1^num2;
	else if (operate == "!")
		return !num2;
	else if (operate == "-")
		return -num2;
	else
		return -99;
}


string getStars(int num){
	string stars = "";
	for (int i = 0; i < num; i++)
		stars += "*";
	return stars;
}


bool firstIsNum(string str){
	char c = str[0];
	if ((str[0] <= '9' && str[0] >= '0'))
		return true;
	return false;
}

int deleteStar(string& arg) {
	int num = 0;
	while (arg[0] == '*') {
		arg = arg.substr(1, arg.size());
		num++;
	}
	return num;
}

string addStar(string arg, int num){
	return getStars(num) + arg;
}