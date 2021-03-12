#include "Qualdruple.h"

using namespace std;

void beforeLeave(hash_map<string, Symbol>* table, bool isTemp) {
	string type = "";
	hash_map<string, Symbol>::iterator iter = table->begin();
	for (; iter != table->end(); iter++){
		switch (iter->second.style)
		{
		case TYPE_INT:
			type = "int";
			break;
		case TYPE_CHAR:
			type = "char";
			break;
		case TYPE_DOUBLE:
			type = "double";
			break;
		case TYPE_FLOAT:
			type = "float";
			break;
		default:
			if (IS_POINTER(iter->second.style)) {
				switch (TYPE_OF_POINTER(iter->second.style)) 
				{
				case TYPE_INT:
					type = "int";
					break;
				case TYPE_CHAR:
					type = "char";
					break;
				case TYPE_DOUBLE:
					type = "double";
					break;
				case TYPE_FLOAT:
					type = "float";
					break;
				}
				for (int i = 0; i < LEVEL_OF_POINTER(iter->second.style); i++)
				{
					type += "*";
				}
			}
			break;
		}
		if (isTemp)
			dataInit.addTempData(type, iter->first, iter->second.style);
		else {
			dataInit.addSymbolData(type, iter->first, sigTable.getScopeId(iter->first));
		}
	}
}

int typeOfArg(string arg) {
	if (arg == "") {
		return ARG_EMPTY;
	}
	else if (arg[0] == '&') {
		return ARG_TEMP;
	}
	else if ((arg[0] <= '9' && arg[0] >= '0') || arg[0] == '.' || arg[0] == '-' || arg[0] == '+') {
		return ARG_CONST;
	}
	else {
		return ARG_SYMBOL;
	}
}

int typeByOperate(string op, string arg1, string arg2) {
	int type = -1;
	int type1 = -1;
	int type2 = -1;
	switch (typeOfArg(arg1))
	{
	case ARG_EMPTY:
		return type;
	case ARG_CONST:
		if (isStrNumInt(arg1)) type1 = TYPE_INT;
		else type1 = TYPE_DOUBLE;
		break;
	case ARG_TEMP:
		type1 = tempTable.get(arg1).style;
		break;
	case ARG_SYMBOL:
		type1 = sigTable.get(arg1).style;
		break;
	}
	switch (typeOfArg(arg2))
	{
	case ARG_EMPTY:
		if (op == "_&") return MAKE_TYPE_BY_AND(type1);
		if (op == "_*") return MAKE_TYPE_BY_STAR(type1);
		if (op == "!") return TYPE_CHAR;
		//强制类行转换
		if (firstIsNum(op)) return stringToNum<int>(op);
		return type1;
	case ARG_CONST:
		if (isStrNumInt(arg2)) type2 = TYPE_INT;
		else type2 = TYPE_DOUBLE;
		break;
	case ARG_TEMP:
		type2 = tempTable.get(arg2).style;
		break;
	case ARG_SYMBOL:
		type2 = sigTable.get(arg2).style;
		break;
	}
	if (op == "+" || op == "-") type = MAKE_TYPE_BY_ADD_OR_PLUS(type1, type2);
	else if (op == "*" || op == "/") type = MAKE_TYPE_BY_MUL_OR_DEV(type1, type2);
	else if (op == "%" || op == "|" || op == "^" || op == "&" || op == "<<" || op == ">>") type = MAKE_TYPE_BY_MOD_OR_BIT(type1, type2);
	else if (op == ",") type = MAKE_TYPE_BY_COMMA(type1, type2);
	else if (op == "&&" || op == "||" || op == "==" || op == "!=" || op == ">=" || op == "<=" || op == ">" || op == "<") type = MAKE_TYPE_BY_LOGIC(type1, type2);
	return type;
}



Qualdruple* Qualdruples::makeCode(string op, string arg1, string arg2, Result result, bool flag) {
	Qualdruple* q = new Qualdruple(op, arg1, arg2, result, flag);
	//v就是那个vector 想怎么用就怎么用
	vector<string>& v = q->code;
	//有几个操作数
	int numOfargs = 2;
	//去星星
	int startNum1 = 0;
	int startNum2 = 0;
	if (arg1[0] == '*'){
		startNum1 = deleteStar(arg1);
	}
	if (arg2[0] == '*'){
		startNum2 = deleteStar(arg2);
	}
	//取arg1的信息
	int arg1Num = 0;
	int arg1Type = 0;
	string arg1Name = "";
	switch (typeOfArg(arg1))
	{
	case ARG_EMPTY:
		numOfargs--;
		break;
	case ARG_SYMBOL:
		arg1Num = sigTable.getScopeId(arg1);
		arg1Type = sigTable.get(arg1).style;
		arg1Name = DataInit::makeSymbolData(arg1, arg1Num);
		break;
	case ARG_TEMP:
		arg1Type = tempTable.get(arg1).style;
		arg1Name = DataInit::makeTempData(arg1, arg1Type);
		break;
	case ARG_CONST:
		if (isStrNumInt(arg1)) arg1Type = TYPE_INT;
		else arg1Type = TYPE_DOUBLE;
		arg1Name = arg1;
		break;
	}
	//取arg2的信息
	int arg2Num = 0;
	int arg2Type = 0;
	string arg2Name = "";
	switch (typeOfArg(arg2))
	{
	case ARG_EMPTY:
		numOfargs--;
		break;
	case ARG_SYMBOL:
		arg2Num = sigTable.getScopeId(arg2);
		arg2Type = sigTable.get(arg2).style;
		arg2Name = DataInit::makeSymbolData(arg2, arg2Num);
		break;
	case ARG_TEMP:
		arg2Type = tempTable.get(arg2).style;
		arg2Name = DataInit::makeTempData(arg2, arg2Type);
		break;
	case ARG_CONST:
		if (isStrNumInt(arg2)) arg2Type = TYPE_INT;
		else arg2Type = TYPE_DOUBLE;
		arg2Name = arg2;
		break;
	}
	//取result的信息
	int resultType = 0;
	string resultName = "";
	if (!result.isKey()) {
		if (result.isTemp()) {
			//是临时变量
			if ((*(result.temp))[0] == '*'){
				int num = deleteStar(*(result.temp));
				resultType = tempTable.get(*(result.temp)).style;
				resultName = DataInit::makeTempData(*(result.temp), resultType);
				resultName = addStar(resultName, num);
			}
			else{
				resultType = tempTable.get(*(result.temp)).style;
				resultName = DataInit::makeTempData(*(result.temp), resultType);
			}
		}
		else {
			//不是临时变量
			if (*(result.symbol) != ""){
				if ((*(result.symbol))[0] == '*'){
					int num = deleteStar(*(result.symbol));
					int resultNum = sigTable.getScopeId(*(result.symbol));
					resultType = sigTable.get(*(result.symbol)).style;
					resultName = DataInit::makeSymbolData(*(result.symbol), resultNum);
					resultName = addStar(resultName, num);
				}
				else{
					int resultNum = sigTable.getScopeId(*(result.symbol));
					resultType = sigTable.get(*(result.symbol)).style;
					resultName = DataInit::makeSymbolData(*(result.symbol), resultNum);
				}
			}
		}
	}
	//把星星家回来
	arg1Name = addStar(arg1Name, startNum1);
	arg2Name = addStar(arg2Name, startNum2);

	// 需要名字就用xxxName 需要Type就用xxxType 如 arg1Name arg1Type 类型为(stirng int)

	switch (result.typeOfResult())
	{
	case RESULT_KEY:
		//跳转语句
		//You code here
		if ((op == "IF") || (op == "WHILE") || (op == "FOR"))
		{
			v.push_back("if(!" + arg1Name + ")");
			v.push_back("goto LABEL");
			v.push_back("666");
		}
		else if (op == "GOTO")
		{
			v.push_back("goto LABEL");
			v.push_back("666");
		}
		break;
	case RESULT_SYMBOL:
	case RESULT_TEMP:
		//结果赋值给临时变量表中的变量的
		//You code here
		//结果赋值给符号表中的变量的
		if (op == "=" || op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=" || op == "&=" || op == "|=" || op == "^=" || op == "<<=" || op == ">>="){
			string cmd = resultName + op + arg1Name + ";";
			v.push_back(cmd);
		}
		if (op == "READ") {
			v.push_back("cin>>" + arg1Name + ";");
		}
		else if (op == "WRITE") {
			v.push_back("cout<<" + arg1Name + "<<endl;");
		}
		else if (op == "==" || op == "!=" || op == "<=" || op == "<" || op == ">=" || op == ">" || op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>"){
			string cmd = resultName + " = " + arg1Name + op + arg2Name + ";";
			v.push_back(cmd);
		}
		else if (op == "!"){
			string cmd = resultName + " = " + op + arg1Name + ";";
			v.push_back(cmd);
		}
		else if (op == "_&"){
			string cmd = resultName + " = &" + arg1Name + ";";
			v.push_back(cmd);
		}
		else if (op == "_*"){
			string cmd = resultName + " = *" + arg1Name + ";";
			v.push_back(cmd);
		}
		else if (op == "++a" || op == "--a"){
			op = op.substr(0, 2);
			string cmd = resultName + " = " + op + arg1Name + ";";
			v.push_back(cmd);
		}
		else if (op == "a++" || op == "a--"){
			op = op.substr(1, 3);
			string cmd = resultName + " = " + arg1Name + op + ";";
			v.push_back(cmd);
		}
		else if (op == "&&" || op == "||"){
			string cmd = resultName + " = " + arg1Name + op + arg2Name + ";";
			v.push_back(cmd);
		}
		else if (op == "array"){
			string cmd = resultName + " = " + arg1Name + "[" + arg2Name + "];";
			v.push_back(cmd);
		}
		else if (op == "SIZEOF"){
			string cmd = resultName + "=sizeof(" + arg1Name + ");";
			v.push_back(cmd);
		}
		else if (firstIsNum(op)){
			//强制类型转换
			//普通强制类型转换
			if (op == numToString<int>(TYPE_INT)){
				string cmd = resultName + " =(int)" + arg1Name + ";";
				v.push_back(cmd);
			}
			else if (op == numToString<int>(TYPE_DOUBLE)){
				string cmd = resultName + " =(double)" + arg1Name + ";";
				v.push_back(cmd);
			}
			else if (op == numToString<int>(TYPE_FLOAT)){
				string cmd = resultName + " =(float)" + arg1Name + ";";
				v.push_back(cmd);
			}
			else if (op == numToString<int>(TYPE_CHAR)){
				string cmd = resultName + " =(char)" + arg1Name + ";";
				v.push_back(cmd);
			}
			else{
				//指针强制类型转换
				int num = stringToNum<int>(op);
				if (IS_POINTER(num)){
					int type = TYPE_OF_POINTER(num);
					int level = LEVEL_OF_POINTER(num);
					if (type == TYPE_INT){
						string Type = "(int" + getStars(level) + ")";
						string cmd = resultName + " = " + Type + arg1Name + ";";
						v.push_back(cmd);
					}
					else if (type == TYPE_DOUBLE){
						string Type = "(double" + getStars(level) + ")";
						string cmd = resultName + " = " + Type + arg1Name + ";";
						v.push_back(cmd);
					}
					else if (type == TYPE_FLOAT){
						string Type = "(float" + getStars(level) + ")";
						string cmd = resultName + " = " + Type + arg1Name + ";";
						v.push_back(cmd);
					}
					else if (type == TYPE_CHAR){
						string Type = "(char" + getStars(level) + ")";
						string cmd = resultName + " = " + Type + arg1Name + ";";
						v.push_back(cmd);
					}
				}

			}

		}

		break;
	case RESULT_ERROR:
		//某种未知错误
		break;
	}
	//cout << arg1Name << " " << arg2Name << " " << resultName << endl;
	return q;
}






void Qualdruples::outputCode() {
	for (int i = 0; i < this->qualdruples.size(); i++){
		cout << "LABEL" + to_string(i) + ":" << endl;
		for (int j = 0; j < qualdruples[i]->code.size(); j++) {
			if (qualdruples[i]->isKey() && qualdruples[i]->code[j + 1] == "666") {
				qualdruples[i]->code[j] += numToString<int>(qualdruples[i]->result->key) + ";";
				cout << qualdruples[i]->code[j] << endl;
				j++;
			}
			else {
				cout << qualdruples[i]->code[j] << endl;
			}
		}
	}
	cout << "LABEL" + to_string(this->qualdruples.size()) + ": ;" << endl;
}