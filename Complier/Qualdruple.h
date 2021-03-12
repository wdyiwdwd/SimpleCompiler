
#ifndef _QUALDRUPLE_H_
#define _QUALDRUPLE_H_
#include "type.h"
#include "tempTable.h"
#include "signary.h"
#include "dataInit.h"
#include <vector>
#include <string>

#define ARG_TEMP 1
#define ARG_SYMBOL 2
#define ARG_CONST 3
#define ARG_EMPTY 4

#define RESULT_KEY 1
#define RESULT_SYMBOL 2
#define RESULT_TEMP 3
#define RESULT_ERROR 0

extern TempTable tempTable;
extern Signary sigTable;
extern DataInit dataInit;

using namespace std;

int typeByOperate(string op, string arg1, string arg2);
int typeOfArg(string arg);
void beforeLeave(hash_map<string, Symbol>* table, bool isTemp);


class Result {
	friend ostream& operator << (ostream& out, Result& r) {
		if (r.isKey()) out << r.key+1;
		if (r.isSymbol()) out << *(r.symbol);
		if (r.isTemp()) out << *(r.temp);
		return out;
	}
public:
	string* temp;
	string* symbol;
	int key;
	~Result() {
		if (temp != NULL) delete temp;
		if (symbol != NULL) delete symbol;
	}
	Result() {
		temp = NULL;
		symbol = NULL;
		int key = 0;
	}
	Result(int key) {
		this->key = key;
		temp = NULL;
		symbol = NULL;
	}
	Result(string text, bool isTemp) {
		this->temp = NULL;
		this->symbol = NULL;
		if (isTemp) this->temp = new string(text);
		else this->symbol = new string(text);
	}
	Result(const Result& result) {
		this->key = result.key;
		temp = NULL;
		symbol = NULL;
		if (result.symbol != NULL) this->symbol = new string(*result.symbol);
		if (result.temp != NULL) this->temp = new string(*result.temp);
	}
	Result& operator = (const Result& result) {
		if (temp != NULL) delete temp;
		if (symbol != NULL) delete symbol;
		this->key = result.key;
		if (result.symbol != NULL) this->symbol = new string(*result.symbol);
		if (result.temp != NULL) this->temp = new string(*result.temp);
	}
	bool isTemp() {
		if (this->temp != NULL) {
			return true;
		}
		return false;
	}
	bool isSymbol() {
		if (this->symbol != NULL) {
			return true;
		}
		return false;
	}
	bool isKey() {
		if (this->symbol == NULL && this->temp == NULL) {
			return true;
		}
		return false;
	}
	int typeOfResult() {
		if (isKey()) return RESULT_KEY;
		else if (isSymbol()) return RESULT_SYMBOL;
		else if (isTemp()) return RESULT_TEMP;
		return RESULT_ERROR;
	}
};

class Qualdruple{
	friend ostream& operator << (ostream& out, Qualdruple& q) {
		int maxTab = 20;
		int tabSize = 1;
		int opTab = maxTab - (int)q.op.size() / tabSize;
		out << q.op;
		for (int i = 0; i < opTab; i++) {
			out << " ";
		}
		int arg1Tab = maxTab - (int)q.arg1.size() / tabSize;
		out << q.arg1;
		for (int i = 0; i < arg1Tab; i++) {
			out << " ";
		}
		int arg2Tab = maxTab - (int)q.arg2.size() / tabSize;
		out << q.arg2;
		for (int i = 0; i < arg2Tab; i++) {
			out << " ";
		}
		out << *(q.result);
		return out;
	}
public:
	string op;
	string arg1;
	string arg2;
	Result* result;
	vector<string> code;
	bool flag;
	Qualdruple() {
		op = "";
		arg1 = "";
		arg2 = "";
		result = NULL;
		flag = false;
	};
	~Qualdruple() {
		if (result != NULL) delete result;
	}
	Qualdruple(string op, string arg1, string arg2, Result result, bool flag) {
		this->op = op;
		this->arg1 = arg1;
		this->arg2 = arg2;
		this->result = new Result(result);
		this->flag = flag;
	}
	Qualdruple(string op, string arg1, string arg2, int result, bool flag) {
		this->op = op;
		this->arg1 = arg1;
		this->arg2 = arg2;
		this->result = new Result(result);
		this->flag = flag;
	}
	Qualdruple(string op, string arg1, string arg2, string result, bool isTemp, bool flag) {
		this->op = op;
		this->arg1 = arg1;
		this->arg2 = arg2;
		this->result = new Result(result, isTemp);
		this->flag = flag;
	}
	Qualdruple(Qualdruple& q) {
		this->op = q.op;
		this->arg1 = q.arg1;
		this->arg2 = q.arg2;
		if (q.result != NULL) this->result = new Result(*q.result);
		this->flag = q.flag;
		this->code = q.code;
	}
	Qualdruple& operator = (const Qualdruple& q) {
		if (result != NULL) delete result;
		this->op = q.op;
		this->arg1 = q.arg1;
		this->arg2 = q.arg2;
		if (q.result != NULL) this->result = new Result(*q.result);
		this->flag = q.flag;
		this->code = q.code;
		return *this;
	}
	bool isTemp() {
		if (result != NULL){
			return result->isKey();
		}
		return false;
	}
	bool isSymbol() {
		if (result != NULL){
			return result->isSymbol();
		}
		return false;
	}
	bool isKey() {
		if (result != NULL){
			return result->isKey();
		}
		return false;
	}
	int typeOfQualdruple() {
		if (result != NULL){
			if (isKey()) return RESULT_KEY;
			else if (isSymbol()) return RESULT_SYMBOL;
			else if (isTemp()) return RESULT_TEMP;
		}
		return RESULT_ERROR;
	}

	//增加代码 返回数组长度
	int appendCode(string code) {
		this->code.push_back(code);
		return this->code.size();
	}
};


class Qualdruples {
	friend ostream& operator << (ostream& out, Qualdruples& q) {
		vector<Qualdruple*>::iterator iter = q.qualdruples.begin();
		for (; iter != q.qualdruples.end(); iter++) {
			if ((*iter) != NULL) {
				out << **iter << endl;
			}
		}
		return out;
	}
private:
	vector<Qualdruple*> qualdruples;
public:
	Qualdruples(){};
	~Qualdruples(){
		vector<Qualdruple*>::iterator iter = qualdruples.begin();
		for (; iter != qualdruples.end(); iter++) {
			if ((*iter) != NULL) {
				delete *iter;
			}
		}
	};
	void append(Qualdruple* q) {
		qualdruples.push_back(q);
	}
	//加结果是临时变量的四元式
	string append(string op, string arg1, string arg2, bool flag = false) {
		Symbol tempSymbol;
		tempSymbol.style = typeByOperate(op, arg1, arg2);
		string order = tempTable.putTemp(tempSymbol);
		this->append(makeCode(op, arg1, arg2, Result(order, true), flag));
		return order;
	}
	//加结果是变量的四元式
	string append(string op, string arg1, string arg2, string symbol, bool flag = false) {
		int starNum = deleteStar(symbol);
		if (symbol.size() > 0 && symbol[0] == '&'){
			symbol = addStar(symbol, starNum);
			this->append(makeCode(op, arg1, arg2, Result(symbol, true), flag));
		}
		else {
			symbol = addStar(symbol, starNum);
			this->append(makeCode(op, arg1, arg2, Result(symbol, false), flag));
		}
		return symbol;
	}
	//加结果是跳转的四元式
	int append(string op, string arg1, string arg2, int key, bool flag = false) {
		this->append(makeCode(op, arg1, arg2, Result(key), flag));
		return key;
	}
	//插入结果是跳转的四元式
	int insert(int position, string op, string arg1, string arg2, int key, bool flag = false) {
		vector<Qualdruple*>::iterator iter = qualdruples.begin();
		for (; iter != qualdruples.end(); iter++) {
			if ((*iter) != NULL) {
				if ((*iter)->flag == true){
					if ((*iter)->isKey() && (*iter)->result->key >= position) (*iter)->result->key++;
				}
				else{
					if ((*iter)->isKey() && (*iter)->result->key > position) (*iter)->result->key++;
				}
					
			}
		}
		Qualdruple* temp = makeCode(op, arg1, arg2, Result(key), flag);
		qualdruples.insert(qualdruples.begin() + position, temp);
		return key;
	}
	//修改一个为key的四元式
	bool modifyKey(int number, int i) {
		if (number >= qualdruples.size()) return false;
		if (!qualdruples[number]->isKey()) return false;
		qualdruples[number]->result->key +=i;
		return true;
	}

	//为了部落！
	bool modifyKey(int number) {
		if (number + 1 >= qualdruples.size()) return false;
		vector<Qualdruple*>::iterator iter = qualdruples.begin() + number + 1;
		for (; iter != qualdruples.end(); iter++) {
			if (((*iter)->op == "FOR" || (*iter)->op == "WHILE") && (*iter)->isKey()) {
				(*iter)->result->key--;
				break;
			}
		}
		return true;
	}

	//返回下一个插入的编号
	int nextKey() {
		return qualdruples.size();
	}

	void outputCode();

	//生成汇编代码的函数 返回一个自带汇编代码的四元式指针
	Qualdruple* makeCode(string op, string arg1, string arg2, Result result, bool flag);
};

#endif