#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include "binaryTreeNode.h"
#include "linkedQueue.h"
using namespace std;

template <class T>
class binaryTree
{
public:
	binaryTree(){
		root = NULL;
	}
	binaryTree(binaryTree<T>&);
	binaryTree<T>& operator = (const binaryTree<T>& tree);
	~binaryTree(){
		this->postOrder(Free);
	}
	//对外接口 复制一棵树，也为等号操作符重载做贡献
	void copy(const binaryTree<T>& tree);
	//对外接口 判断二叉树是否为空
	bool isEmpty(){
		return root == NULL;
	}
	//对外接口 把根节点的值赋给x
	bool Root(T& x) const;
	//对外接口 返回根节点的地址(root)
	binaryTreeNode<T>* getRoot();
	//对外接口 制造二叉树的根节点
	void makeTree(const T& element, binaryTree<T>& left, binaryTree<T>& right);
	void makeTree(const T& element, binaryTree<T>& tree, bool isLeft);
	void makeTree(const T& element);
	//在最右边的节点中增加一棵树
	void makeRightMostTree(binaryTree<T>& right);
	//在最左边的节点中增加一棵树
	void makeLeftMostTree(binaryTree<T>& right);
	//对外接口 破坏树的根节点，并把根节点的左右儿子单独成为新的二叉树
	void breakTree(T& element, binaryTree<T>& left, binaryTree<T>& right);
	//对外接口 和break差不多只不过不破坏树
	void getTrees(T& element, binaryTree<T>* left, binaryTree<T>* right) const;
	//对外接口 输入一颗二叉树
	void input(){
		input(root);
	}
	//对外接口 前序遍历 第一个参数是函数指针 传入要前序遍历的操作
	void preOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		preOrder(visit, root);
	}
	//对外接口 中序遍历
	void inOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		inOrder(visit, root);
	}
	//对外接口 后序遍历
	void postOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		postOrder(visit, root);
	}
	//对外接口 右序遍历 自创 非标准遍历
	void rightOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		rightOrder(visit, root);
	}
	//对外接口 宽度遍历 待续.......
	void levelOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		levelOrder(visit, root);
	}
	//对外接口 删除一颗二叉树
	void distory() {
		postOrder(Free, root);
		root = 0;
	}
	//对外接口 返回树的高度
	int height() const {
		return height(root);
	}
	//对外接口 输出中缀表达式
	void infix() const {
		infix(root);
	}
	//对外接口 先序输出
	void preOutput() const{
		preOrder(Visit);
	}
	//对外接口 中序输出
	void inOutput() const{
		inOrder(Visit);
	}
	//对外接口 后序输出
	void postOutput() const{
		postOrder(Visit);
	}
	//对外接口 右序输出 自创 非标准遍历
	void rightOutput() const{
		rightOrder(Visit);
	}
	//对外接口 逐层输出
	void levelOutput() const{
		levelOrder(Visit);
	}
	//对外接口 返回节点数
	int size() const{
		return size(root);
	}
	//对外接口 返回叶子数
	int numOfLeaves() const{
		return numOfLeaves(root);
	}
	//对外接口 交换左右子树
	void exchangeBothSide(){
		preOrder(ExchangeBothSide, root);  //必须先序或者后序 中序不会达成效果 不信在纸上画
		//postOrder(ExchangeBothSide, root);
	}
	//对外接口 返回二叉树的宽度
	int width() const;

	/*************************************************************************************************************************/
	//对外接口 树形输出
	void rightTreeOrder(void(*visit)(binaryTreeNode<T> *u, int degree), binaryTreeNode<T> *t, int degree) const;
	void rightTreeOutput(){
		rightTreeOrder(TreeOutput, root, 0);
	}
	/*************************************************************************************************************************/

protected:
	binaryTreeNode<T> *root;
	//内部函数 输入二叉树
	void input(binaryTreeNode<T> *t);
	//内部函数 前序遍历
	void preOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//内部函数 中序遍历
	void inOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//内部函数 后序遍历
	void postOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//自创 非标准遍历 右序遍历 先遍历右边 顺序为右->中->左
	void rightOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//内部函数 逐层遍历
	void levelOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//内部函数 返回树的高度
	int height(binaryTreeNode<T> *t) const;
	//内部函数 输出中缀表达式
	void infix(binaryTreeNode<T> *t) const;
	//内部函数 返回一颗二叉树的节点数
	int size(binaryTreeNode<T> *t) const;
	//内部函数 返回一颗二叉树的叶子数
	int numOfLeaves(binaryTreeNode<T> *t) const;
	//内部函数 交换左右子树
	static void ExchangeBothSide(binaryTreeNode<T> *t){
		binaryTreeNode<T> *temp = t->leftNode;
		t->leftNode = t->rightNode;
		t->rightNode = temp;
	}
	//静态函数 删除一个树的节点
	static void Free(binaryTreeNode<T> *t) {
		delete t;
	}
	//静态函数 访问并输出一个节点
	static void Visit(binaryTreeNode<T> *t){
		cout << t->element << " ";
	}

	/************************************************************************************************************************/
	static void TreeOutput(binaryTreeNode<T> *t, int degree){
		string str = "";
		for (int i = 0; i < degree; i++){
			str += "\t";
		}
		cout << str;
		cout << t->element << endl;
	}
	/************************************************************************************************************************/
};

template <class T>
binaryTree<T>::binaryTree(binaryTree<T>& m)
{
	//这棵树存放m的左子树
	binaryTree<T>* leftTree = new binaryTree<T>();
	//m的右子树
	binaryTree<T>* rightTree = new binaryTree<T>();
	//存放m的节点元素
	T theElement;
	//把m拆开
	m.getTrees(theElement, leftTree, rightTree);
	//新的左右树用做递归
	binaryTree<T> *newLeftTree = NULL;
	binaryTree<T> *newRightTree = NULL;
	if (leftTree->root != NULL){
		newLeftTree = new binaryTree<T>(*leftTree);
	}
	else{
		newLeftTree = new binaryTree<T>();
	}
	if (rightTree->root != NULL){
		newRightTree = new binaryTree<T>(*rightTree);
	}
	else{
		newRightTree = new binaryTree<T>();
	}
	//复制新的树，递归得到
	makeTree(theElement, *newLeftTree, *newRightTree);
}

template <class T>
void binaryTree<T>::copy(const binaryTree<T>& m) {
	this->postOrder(Free);
	//这棵树存放m的左子树
	binaryTree<T>* leftTree = new binaryTree<T>();
	//m的右子树
	binaryTree<T>* rightTree = new binaryTree<T>();
	//存放m的节点元素
	T theElement;
	//把m拆开
	m.getTrees(theElement, leftTree, rightTree);
	//新的左右树用做递归
	binaryTree<T> *newLeftTree = NULL;
	binaryTree<T> *newRightTree = NULL;
	if (leftTree->root != NULL){
		newLeftTree = new binaryTree<T>(*leftTree);
	}
	else{
		newLeftTree = new binaryTree<T>();
	}
	if (rightTree->root != NULL){
		newRightTree = new binaryTree<T>(*rightTree);
	}
	else{
		newRightTree = new binaryTree<T>();
	}
	//复制新的树，递归得到
	makeTree(theElement, *newLeftTree, *newRightTree);
}

template <class T>
binaryTree<T>& binaryTree<T>::operator = (const binaryTree<T>& m)
{
	this->copy(m);
	return *this;
}

//把根节点的值赋给x
template <class T>
bool binaryTree<T>::Root(T& x) const
{
	if (root){
		x = root->element;
		return true;
	}
	return false;
}

//返回root
template <class T>
binaryTreeNode<T>* binaryTree<T>::getRoot()
{
	return this->root;
}

//制造二叉树
template<class T>
void binaryTree<T>::makeTree(const T& element, binaryTree<T>& left, binaryTree<T>& right)
{	// Combine left, right, and element to make new tree.
	// left, right, and this must be different trees.
	// create combined tree
	root = new binaryTreeNode<T>(element, left.root, right.root);
	// deny access from trees left and right
	 left.root = right.root = 0;
}

//制造二叉树
template<class T>
void binaryTree<T>::makeTree(const T& element, binaryTree<T>& tree, bool isLeft) {
	binaryTree<T> tmp;
	if(isLeft) {
		this->makeTree(element, tree, tmp);
	}
	else {
		this->makeTree(element, tmp, tree);
	}
}

//制造二叉树
template<class T>
void binaryTree<T>::makeTree(const T& element) {
	binaryTree<T> tmpLeft;
	binaryTree<T> tmpRight;
	this->makeTree(element, tmpLeft, tmpRight);
}

//在最右边的节点上连接一棵二叉树
template<class T>
void binaryTree<T>::makeRightMostTree(binaryTree<T>& right) {
	binaryTreeNode<T>* p = this->root;
	while (p->rightNode != NULL) {
		p = p->rightNode;
	}
	p->rightNode = right.root;
}

//在最左边的节点上连接一棵二叉树
template<class T>
void binaryTree<T>::makeLeftMostTree(binaryTree<T>& left) {
	binaryTreeNode<T>* p = this->root;
	while (p->leftNode != NULL) {
		p = p->leftNode;
	}
	p->leftNode = left.root;
}

//破坏二叉树
template<class T>
void binaryTree<T>::breakTree(T& element, binaryTree<T>& left, binaryTree<T>& right)
{// left, right, and this must be different trees.
	// check if empty
	if (!root){
		throw invalid_argument("break error"); // tree empty
	}
	// break the tree
	element = root->element;
	left.root = root->leftNode;
	right.root = root->rightNode;

	delete root;
	root = 0;
}

//得到二叉树的信息
template<class T>
void binaryTree<T>::getTrees(T& element, binaryTree<T>* left, binaryTree<T>* right) const
{// left, right, and this must be different trees.
	// check if empty
	if (!root){
		throw invalid_argument("break error"); // tree empty
	}
	// break the tree
	element = root->element;
	left->root = root->leftNode;
	right->root = root->rightNode;
}

//外部 输入
template <class T>
void binaryTree<T>::input(binaryTreeNode<T> *t)
{
	if (t == NULL){
		root = new binaryTreeNode<T>();
		t = root;
	}
	T theElement;
	bool left;
	bool right;
	cout << "这个节点的值为：" << endl;
	cin >> theElement;
	t->element = theElement;

	cout << "他左边有儿子吗：（1代表有，0代表没有，随便瞎输估计程序就崩溃了）" << endl;
	cin >> left;
	if (left == true){
		binaryTreeNode<T> *newLeft = new binaryTreeNode<T>();
		t->leftNode = newLeft;
		input(newLeft);
	}
	else{
		t->leftNode = NULL;
	}

	cout << "他右边有儿子吗：（1代表有，0代表没有，随便瞎输估计程序就崩溃了）" << endl;
	cin >> right;
	if (right == true){
		binaryTreeNode<T> *newRight = new binaryTreeNode<T>();
		t->rightNode = newRight;
		input(newRight);
	}
	else{
		t->rightNode = NULL;
	}
}

//内部前序
template <class T>
void binaryTree<T>::preOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Preorder traversal of *t.
	if (t) {
		visit(t);                 // visit tree root
		preOrder(visit, t->leftNode);   // do left subtree
		preOrder(visit, t->rightNode);  // do right subtree
	}
}

//内部中序
template <class T>
void binaryTree<T>::inOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Inorder traversal of *t.
	if (t) {
		inOrder(visit, t->leftNode);   // do left subtree
		visit(t);                // visit tree root
		inOrder(visit, t->rightNode);  // do right subtree
	}
}

//内部后序
template <class T>
void binaryTree<T>::postOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// postOrder traversal of *t.
	if (t) {
		postOrder(visit, t->leftNode);   // do left subtree
		postOrder(visit, t->rightNode);  // do right subtree
		visit(t);                // visit tree root
	}
}

//内部右序 非标准遍历
template <class T>
void binaryTree<T>::rightOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Preorder traversal of *t.
	if (t) {
		rightOrder(visit, t->rightNode);  // do right subtree
		visit(t);                 // visit tree root
		rightOrder(visit, t->leftNode);   // do left subtree
	}
}

//内部逐层
template <class T>
void binaryTree<T>::levelOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Level-order traversal of *t.
	linkedQueue<binaryTreeNode<T>*> Q;
	Q.push(t);
	while (!Q.empty()) {
		visit(t);  // visit t
		// put t's children on queue
		if (t->leftNode != NULL){
			Q.push(t->leftNode);
		}
		if (t->rightNode != NULL){
			Q.push(t->rightNode);
		}
		// get next node to visit
		//删除队列中当前结点
		Q.pop();
		try{
			t = Q.front();
		}
		catch (invalid_argument){
			return;
		}
	}
}


//内部 高度
template <class T>
int binaryTree<T>::height(binaryTreeNode<T> *t) const
{// Return height of tree *t.
	if (!t) return 0;               // empty tree
	int hl = height(t->leftNode);  // height of left
	int hr = height(t->rightNode); // height of right
	if (hl > hr){
		return ++hl;
	}
	else{
		return ++hr;
	}
}

//内部 中缀
template <class T>
void binaryTree<T>::infix(binaryTreeNode<T> *t) const
{	// Output infix form of expression.
	if (t) {
		cout << '(';
		infix(t->leftNode);  // left operand
		cout << t->element;      // operator
		infix(t->rightNode); // right operand
		cout << ')';
	}
}

//内部 节点数
template <class T>
int binaryTree<T>::size(binaryTreeNode<T> *t) const
{
	if (!t){
		return 0;
	}
	else {
		return size(t->leftNode) + size(t->rightNode) + 1;
	}
}

//内部 叶子数
template <class T>
int binaryTree<T>::numOfLeaves(binaryTreeNode<T> *t) const
{
	if (!t){
		return 0;
	}
	else if (t->leftNode == NULL && t->rightNode == NULL){
		return numOfLeaves(t->leftNode) + numOfLeaves(t->rightNode) + 1;
	}
	else{
		return numOfLeaves(t->leftNode) + numOfLeaves(t->rightNode);
	}
}

template <class T>
int binaryTree<T>::width() const
{
	linkedQueue<binaryTreeNode<T>*> Q;
	binaryTreeNode<T> *t;
	int numThisLevel = 1;  //这层节点的个数
	int orderThisLevel = 0;  //当前这个节点是第几个
	int numNextLevel = 0;  //下一层节点的个数
	int theWidth = 1;  //宽度
	t = root;
	Q.push(t);
	while (!Q.empty()) {
		// put t's children on queue
		if (t->leftNode != NULL){
			Q.push(t->leftNode);
			numNextLevel++;
		}
		if (t->rightNode != NULL){
			Q.push(t->rightNode);
			numNextLevel++;
		}

		orderThisLevel++;
		if (orderThisLevel == numThisLevel){
			orderThisLevel = 0;
			numThisLevel = numNextLevel;
			numNextLevel = 0;
			if (numThisLevel > theWidth){
				theWidth = numThisLevel;
			}
		}
		// get next node to visit
		Q.pop();
		try{
			t = Q.front();
		}
		catch (invalid_argument){
			return theWidth;
		}
	}
	return theWidth;
}

/**************************************************************************************************************************************/
//右序树形遍历
template <class T>
void binaryTree<T>::rightTreeOrder(void(*visit)(binaryTreeNode<T> *u, int degree), binaryTreeNode<T> *t, int degree) const
{	// Preorder traversal of *t.
	if (t) {
		rightTreeOrder(visit, t->rightNode, degree + 1);  // do right subtree
		visit(t, degree);                 // visit tree root
		rightTreeOrder(visit, t->leftNode, degree + 1);   // do left subtree
	}
}
/****************************************************************************************************************************************/