#ifndef    ASTTREE
#define    ASTTREE
#include "binaryTree.h"
#include "ASTNode.h"
#include <list>

using namespace std;

class AST {
protected:
	binaryTree<ASTNode> ast;
	void static output(binaryTreeNode<ASTNode> *t);
	void static outputReverse(binaryTreeNode<ASTNode> *t);
	void static addNodeLevel(binaryTreeNode<ASTNode> *t);
	void static subNodeLevel(binaryTreeNode<ASTNode> *t);
	void static addNodeNext(binaryTreeNode<ASTNode> *t);
	void getNodesWanted(bool(*condition)(ASTNode), list<ASTNode>& l, binaryTree<ASTNode>* root);
	static int topLevel;
public:
	AST() {
		this->ast.makeTree(ASTNode());
	}
	AST(AST& tree) {
		this->ast = tree.ast;
	}
	~AST() {
	}
	AST(ASTNode node);
	AST& operator = (const AST& tree);
	ASTNode* rootNode();
	void makeTree(ASTNode node);
	void addBrother(ASTNode node);
	void addBrother(AST tree);
	void addFather(ASTNode node);
	void addFather(AST tree);
	void outputTree();
	void outputTreeReverse();
	void changeLevel(int topLevel);
	void static setTopLevel(int level);
	void getNodesWanted(bool(*condition)(ASTNode), list<ASTNode>& l);
	void addNext();
};
#endif