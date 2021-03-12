#pragma once
#ifndef _SIGNARY_H_
#define _SIGNARY_H_
#include <iostream>
#include <string>
#include <hash_map>
#include <list>
#include <stack>
#include <vector>
#include "symbol.h"

using namespace std;

class Symbol;

class Signary
{
private:
	//用于唯一标识作用域
	int index;
	vector<int> indexes;
	list<hash_map<string, Symbol> >  table;
	Signary* currentTable;
	void deleteTable(Signary* signary);
	stack<Signary*> historyTable;
	Symbol* get_symbol_adress(string id);
	Symbol* get_extern_symbol_adress(stack<Signary*> stack, string id);
public:
	Signary();
	~Signary();
	// when we enter a new Scope we will create a new hashmap
	void enterScope();
	//when we leave ths scope we will delete the hashmap
	void leaveScope();
	// find out whether id repeat in the scope we are in
	bool isRepeatInScope(string id);
	// find out whether id repeat in the extern we are in
	bool isRepeatInExtern(string id);
	// find out whether id repeat
	bool isRepeat(string id);
	//add a item in the haspmap in top
	int put(string id, Symbol symbol);
	//get the symbol by id
	Symbol get(string id);
	//get the symbol by id in a scope
	Symbol getInScope(string id);
	//get the symbol by id in extern
	Symbol getInExtern(string id);
	//modify the symbol if failed return false
	bool modify(string id, Symbol symbol);
	//enter scope for struct
	int enterScope(string id);
	//get which scope the id is in 第几层
	int getScope(string id);
	//get scope id which the id is in 哪一个作用域
	int getScopeId(string id);

	//此次作业专用
	hash_map<string, Symbol>* returnMap() {
		return &this->table.front();
	}
};
#endif