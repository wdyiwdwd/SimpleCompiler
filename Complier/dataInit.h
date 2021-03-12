#pragma once

#include <sstream>
#include <vector>
#include <hash_map>
#include "tools.h"

using namespace std;

class DataInit {
public:
	static string makeTempData(string name, int type){
		return "TEMP" + name.substr(1, name.size()) + "_" + numToString<int>(type);
	}
	static string makeSymbolData(string name, int index) {
		return "_" + numToString<int>(index) +name;
	}
	static int lengthOfType(int type) {
		//
		return 2;
	}
	friend ostream& operator << (ostream& out, DataInit r) {
		for (int i = 0; i < r.data.size(); i++){
			out << r.data[i] << endl;
		}
		return out;
	}
	vector<string> data;
	hash_map<string, int> datamap;
	DataInit() {
		data.push_back("#include <iostream>");
		data.push_back("#include <string>");
		data.push_back("using namespace std;");
		data.push_back("int main() {");
	}
	int addData(string data) {
		this->data.push_back(data);
		return this->data.size();
	}
	int addSymbolData(string type, string name, int index) {
		string trueName = makeSymbolData(name, index);
		if (datamap.find(trueName) == datamap.end()) {
			datamap.insert(make_pair(trueName, 1));
			//¸Ä
			data.push_back(type + " " + trueName + ";");
		}
		return this->data.size();
	}
	int addTempData(string type, string name, int index) {
		string trueName = makeTempData(name, index);
		if (datamap.find(trueName) == datamap.end()) {
			datamap.insert(make_pair(trueName, 1));
			//¸Ä
			data.push_back(type + " " + trueName + ";");
		}
		return this->data.size();
	}
};

