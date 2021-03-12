#include "AST.h"

using namespace std;

int AST::topLevel = 0;

AST::AST(ASTNode node) {
	this->ast.makeTree(node);
}

ASTNode* AST::rootNode() {
	return &((this->ast.getRoot())->element);
}

AST& AST::operator = (const AST& tree) {
	this->ast = tree.ast;
	return *this;
}

void AST::makeTree(ASTNode node) {
	this->ast.makeTree(node);
}

void AST::addBrother(ASTNode node) {
	ASTNode temp;
	binaryTree<ASTNode> left;
	binaryTree<ASTNode> right;
	this->ast.breakTree(temp, left, right);
	this->ast.makeTree(node, right, false);
	binaryTree<ASTNode> tempRight(this->ast);
	this->ast.makeTree(temp, left, tempRight);
}

void AST::addBrother(AST tree) {
	AST* t = new AST(tree);
	this->ast.makeRightMostTree(t->ast);
}

void AST::addFather(ASTNode node){
	binaryTree<ASTNode>* temp = new binaryTree<ASTNode>(this->ast);
	this->ast.makeTree(node, *temp, true);
}

void AST::addFather(AST tree){
	ASTNode node; 
	tree.ast.Root(node);
	this->addFather(node);
}

void AST::outputTree() {
	this->ast.preOrder(AST::output);
}

void AST::outputTreeReverse() {
	this->ast.preOrder(AST::outputReverse);
}

void AST::output(binaryTreeNode<ASTNode> *t) {
	int tabnum = t->element.level;
	for (int i = 0; i < tabnum; i++){
		cout << " ";
	}
	cout << t->element << endl;
}

void AST::outputReverse(binaryTreeNode<ASTNode> *t) {
	int tabnum = AST::topLevel - t->element.level;
	for (int i = 0; i < tabnum; i++){
		cout << " ";
	}
	cout << t->element << endl;
}

void AST::setTopLevel(int level) {
	AST::topLevel = level;
}


void AST::addNodeLevel(binaryTreeNode<ASTNode> *t) {
	t->element.level++;
}

void AST::subNodeLevel(binaryTreeNode<ASTNode> *t) {
	t->element.level--;
}

void AST::addNodeNext(binaryTreeNode<ASTNode> *t) {
	t->element.next++;
}

void AST::addNext() {
	this->ast.preOrder(addNodeNext);
}

void AST::changeLevel(int topLevel) {
	int nowLevel = this->rootNode()->level;
	if (topLevel > nowLevel) {
		for (int i = 0; i < topLevel - nowLevel; i++){
			this->ast.preOrder(addNodeLevel);
		}
	}
	else {
		for (int i = 0; i < nowLevel - topLevel; i++){
			this->ast.preOrder(subNodeLevel);
		}
	}
}

void AST::getNodesWanted(bool(*condition)(ASTNode), list<ASTNode>& l, binaryTree<ASTNode>* root){
	ASTNode temp;
	binaryTree<ASTNode>* leftNode = new binaryTree<ASTNode>();
	binaryTree<ASTNode>* rightNode = new binaryTree<ASTNode>();
	root->getTrees(temp, leftNode, rightNode);
	if (condition(temp)) {
		l.push_back(temp);
	}
	if (leftNode->getRoot() != NULL){
		getNodesWanted(condition, l, leftNode);
	}
	if (rightNode->getRoot() != NULL){
		getNodesWanted(condition, l, rightNode);
	}
}

void AST::getNodesWanted(bool(*condition)(ASTNode), list<ASTNode>& l){
	this->getNodesWanted(condition, l, &(this->ast));
}