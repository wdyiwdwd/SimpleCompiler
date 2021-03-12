#include "signary.h"

using namespace std;

Signary::Signary(){
	this->index = 0;
	this->currentTable = this;
}

Signary::~Signary(){
	//需要递归析构 还得改一下
	this->deleteTable(this);
}

void Signary::deleteTable(Signary *signary) {
	list<hash_map<string, Symbol>>::iterator iter = signary->table.begin();
	for (; iter != signary->table.end(); iter++){
		hash_map<string, Symbol>::iterator iter_ = iter->begin();
		for (; iter_ != iter->end(); iter_++) {
			if (iter_->second.subSignary != NULL) {
				deleteTable(iter_->second.subSignary);
				delete iter_->second.subSignary;
			}
		}
	}
}

void Signary::enterScope() {
	indexes.push_back(++index);
	hash_map<string, Symbol> tmp;
	this->currentTable->table.push_front(tmp);
	this->historyTable.push(this->currentTable);
}

int Signary::enterScope(string id) {
	Symbol newScope;
	if (this->put(id, newScope)) {
		indexes.push_back(++index);
		Symbol* temp = this->get_symbol_adress(id);
		temp->subSignary = new Signary();
		hash_map<string, Symbol> tmp;
		temp->subSignary->table.push_front(tmp);
		this->historyTable.push(this->currentTable);
		this->currentTable = temp->subSignary;
		return 1;
	}
	else {
		return 0;
	}
}

void Signary::leaveScope() {
	this->indexes.pop_back();
	if (this->historyTable.top() == this->currentTable) {
		//这儿释放空间
		this->currentTable->table.front();
		hash_map<string, Symbol>::iterator iter = this->currentTable->table.front().begin();
		for (; iter != this->currentTable->table.front().end(); iter++) {
			if (iter->second.subSignary != NULL) {
				this->deleteTable(iter->second.subSignary);
			}
		}
		this->currentTable->table.pop_front();
	}
	this->currentTable = this->historyTable.top();
	this->historyTable.pop();
}

bool Signary::isRepeatInScope(string id) {
	if (this->currentTable->table.front().find(id) != this->currentTable->table.front().end()) {
		return true;
	}
	else {
		return false;
	}
}

int Signary::put(string id, Symbol symbol) {
	if (this->isRepeatInScope(id)){
		this->currentTable->table.front().find(id)->second = symbol;
		return 0;
	}
	else {
		this->currentTable->table.front().insert(make_pair(id, symbol));
		return 1;
	}
}

Symbol* Signary::get_symbol_adress(string id) {
	list<hash_map<string, Symbol>>::iterator iter;
	Symbol* result = NULL;
	for (iter = this->table.begin(); iter != this->table.end(); iter++){
		hash_map<string, Symbol>::iterator tmp = iter->find(id);
		if (tmp != iter->end()) {
			result = &(tmp->second);
			break;
		}
	}
	return result;
}

Symbol* Signary::get_extern_symbol_adress(stack<Signary*> stack, string id) {
	Symbol* tmp = this->get_symbol_adress(id);
	if (tmp != NULL){
		return tmp;
	}
	while (!stack.empty()){
		Symbol* tmp = stack.top()->get_symbol_adress(id);
		if (tmp != NULL) {
			return tmp;
		}
		else {
			stack.pop();
		}
	}
	return NULL;
}

Symbol Signary::get(string id) {
	Symbol result;
	Symbol* tmp = this->currentTable->get_symbol_adress(id);
	if (tmp != NULL){
		result = *tmp;
	}
	return result;
}

Symbol Signary::getInExtern(string id) {
	stack<Signary*> temp(this->historyTable);
	Symbol result;
	Symbol* tmp = this->currentTable->get_extern_symbol_adress(temp, id);
	if (tmp != NULL){
		result = *tmp;
	}
	return result;
}

Symbol Signary::getInScope(string id) {
	Symbol result;
	if (isRepeatInScope(id)) {
		return this->currentTable->table.front().find(id)->second;
	}
	return result;
}

bool Signary::isRepeatInExtern(string id) {
	stack<Signary*> temp(this->historyTable);
	if (this->currentTable->get_extern_symbol_adress(temp, id) == NULL){
		return false;
	}
	else {
		return true;
	}
}

bool Signary::isRepeat(string id) {
	if (this->currentTable->get_symbol_adress(id) == NULL){
		return false;
	}
	else {
		return true;
	}
}

bool Signary::modify(string id, Symbol symbol) {
	stack<Signary*> temp(this->historyTable);
	Symbol* tmp = this->currentTable->get_extern_symbol_adress(temp, id);
	if (tmp != NULL){
		*tmp = symbol;
		return true;
	}
	else {
		return false;
	}
}

//得到当前Scope的标号（最外层是1） 不算带名字的Scope
int Signary::getScope(string id) {
	int level = this->table.size();
	list<hash_map<string, Symbol>>::iterator iter;
	Symbol* result = NULL;
	for (iter = this->table.begin(); iter != this->table.end(); iter++){
		hash_map<string, Symbol>::iterator tmp = iter->find(id);
		if (tmp == iter->end()) {
			level--;
		}
		else {
			break;
		}
	}
	return level;
}

int Signary::getScopeId(string id) {
	return this->indexes[this->getScope(id) - 1];
}