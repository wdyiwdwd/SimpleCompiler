#ifndef    ASTNODE
#define    ASTNODE
#include <string>
using namespace std;

class ASTNode {
	friend ostream & operator<<(ostream &out, ASTNode &node) {
		out << node.type << " " << node.value;
		return out;
	}
public:
	int style;
	string type;
	string value;
	string explain;
	int level;
	int line;
	int next;
	ASTNode() {
		this->type = "";
		this->value = "";
		this->level = 0;
		this->style = 0;
		this->next = 0;
	}
	ASTNode(const ASTNode& node) {
		this->value = node.value;
		this->level = node.level;
		this->type = node.type;
		this->explain = node.explain;
		this->style = node.style;
		this->next = node.next;
	}
	ASTNode(string value, int level) {
		this->value = value;
		this->level = level;
	}
	ASTNode(string value, int level, int style) {
		this->value = value;
		this->level = level;
		this->style = style;
	}
	ASTNode(int next, string value, int style) {
		this->value = value;
		this->next = next;
		this->style = style;
	}
	ASTNode& operator = (const ASTNode &node) {
		this->value = node.value;
		this->level = node.level;
		this->type = node.type;
		this->explain = node.explain;
		this->style = node.style;
		this->next = node.next;
		return *this;
	}
};
#endif