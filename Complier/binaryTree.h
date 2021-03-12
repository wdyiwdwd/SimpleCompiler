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
	//����ӿ� ����һ������ҲΪ�ȺŲ���������������
	void copy(const binaryTree<T>& tree);
	//����ӿ� �ж϶������Ƿ�Ϊ��
	bool isEmpty(){
		return root == NULL;
	}
	//����ӿ� �Ѹ��ڵ��ֵ����x
	bool Root(T& x) const;
	//����ӿ� ���ظ��ڵ�ĵ�ַ(root)
	binaryTreeNode<T>* getRoot();
	//����ӿ� ����������ĸ��ڵ�
	void makeTree(const T& element, binaryTree<T>& left, binaryTree<T>& right);
	void makeTree(const T& element, binaryTree<T>& tree, bool isLeft);
	void makeTree(const T& element);
	//�����ұߵĽڵ�������һ����
	void makeRightMostTree(binaryTree<T>& right);
	//������ߵĽڵ�������һ����
	void makeLeftMostTree(binaryTree<T>& right);
	//����ӿ� �ƻ����ĸ��ڵ㣬���Ѹ��ڵ�����Ҷ��ӵ�����Ϊ�µĶ�����
	void breakTree(T& element, binaryTree<T>& left, binaryTree<T>& right);
	//����ӿ� ��break���ֻ�������ƻ���
	void getTrees(T& element, binaryTree<T>* left, binaryTree<T>* right) const;
	//����ӿ� ����һ�Ŷ�����
	void input(){
		input(root);
	}
	//����ӿ� ǰ����� ��һ�������Ǻ���ָ�� ����Ҫǰ������Ĳ���
	void preOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		preOrder(visit, root);
	}
	//����ӿ� �������
	void inOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		inOrder(visit, root);
	}
	//����ӿ� �������
	void postOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		postOrder(visit, root);
	}
	//����ӿ� ������� �Դ� �Ǳ�׼����
	void rightOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		rightOrder(visit, root);
	}
	//����ӿ� ��ȱ��� ����.......
	void levelOrder(void(*visit)(binaryTreeNode<T> *u)) const
	{
		levelOrder(visit, root);
	}
	//����ӿ� ɾ��һ�Ŷ�����
	void distory() {
		postOrder(Free, root);
		root = 0;
	}
	//����ӿ� �������ĸ߶�
	int height() const {
		return height(root);
	}
	//����ӿ� �����׺���ʽ
	void infix() const {
		infix(root);
	}
	//����ӿ� �������
	void preOutput() const{
		preOrder(Visit);
	}
	//����ӿ� �������
	void inOutput() const{
		inOrder(Visit);
	}
	//����ӿ� �������
	void postOutput() const{
		postOrder(Visit);
	}
	//����ӿ� ������� �Դ� �Ǳ�׼����
	void rightOutput() const{
		rightOrder(Visit);
	}
	//����ӿ� ������
	void levelOutput() const{
		levelOrder(Visit);
	}
	//����ӿ� ���ؽڵ���
	int size() const{
		return size(root);
	}
	//����ӿ� ����Ҷ����
	int numOfLeaves() const{
		return numOfLeaves(root);
	}
	//����ӿ� ������������
	void exchangeBothSide(){
		preOrder(ExchangeBothSide, root);  //����������ߺ��� ���򲻻���Ч�� ������ֽ�ϻ�
		//postOrder(ExchangeBothSide, root);
	}
	//����ӿ� ���ض������Ŀ��
	int width() const;

	/*************************************************************************************************************************/
	//����ӿ� �������
	void rightTreeOrder(void(*visit)(binaryTreeNode<T> *u, int degree), binaryTreeNode<T> *t, int degree) const;
	void rightTreeOutput(){
		rightTreeOrder(TreeOutput, root, 0);
	}
	/*************************************************************************************************************************/

protected:
	binaryTreeNode<T> *root;
	//�ڲ����� ���������
	void input(binaryTreeNode<T> *t);
	//�ڲ����� ǰ�����
	void preOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//�ڲ����� �������
	void inOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//�ڲ����� �������
	void postOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//�Դ� �Ǳ�׼���� ������� �ȱ����ұ� ˳��Ϊ��->��->��
	void rightOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//�ڲ����� ������
	void levelOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const;
	//�ڲ����� �������ĸ߶�
	int height(binaryTreeNode<T> *t) const;
	//�ڲ����� �����׺���ʽ
	void infix(binaryTreeNode<T> *t) const;
	//�ڲ����� ����һ�Ŷ������Ľڵ���
	int size(binaryTreeNode<T> *t) const;
	//�ڲ����� ����һ�Ŷ�������Ҷ����
	int numOfLeaves(binaryTreeNode<T> *t) const;
	//�ڲ����� ������������
	static void ExchangeBothSide(binaryTreeNode<T> *t){
		binaryTreeNode<T> *temp = t->leftNode;
		t->leftNode = t->rightNode;
		t->rightNode = temp;
	}
	//��̬���� ɾ��һ�����Ľڵ�
	static void Free(binaryTreeNode<T> *t) {
		delete t;
	}
	//��̬���� ���ʲ����һ���ڵ�
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
	//��������m��������
	binaryTree<T>* leftTree = new binaryTree<T>();
	//m��������
	binaryTree<T>* rightTree = new binaryTree<T>();
	//���m�Ľڵ�Ԫ��
	T theElement;
	//��m��
	m.getTrees(theElement, leftTree, rightTree);
	//�µ������������ݹ�
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
	//�����µ������ݹ�õ�
	makeTree(theElement, *newLeftTree, *newRightTree);
}

template <class T>
void binaryTree<T>::copy(const binaryTree<T>& m) {
	this->postOrder(Free);
	//��������m��������
	binaryTree<T>* leftTree = new binaryTree<T>();
	//m��������
	binaryTree<T>* rightTree = new binaryTree<T>();
	//���m�Ľڵ�Ԫ��
	T theElement;
	//��m��
	m.getTrees(theElement, leftTree, rightTree);
	//�µ������������ݹ�
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
	//�����µ������ݹ�õ�
	makeTree(theElement, *newLeftTree, *newRightTree);
}

template <class T>
binaryTree<T>& binaryTree<T>::operator = (const binaryTree<T>& m)
{
	this->copy(m);
	return *this;
}

//�Ѹ��ڵ��ֵ����x
template <class T>
bool binaryTree<T>::Root(T& x) const
{
	if (root){
		x = root->element;
		return true;
	}
	return false;
}

//����root
template <class T>
binaryTreeNode<T>* binaryTree<T>::getRoot()
{
	return this->root;
}

//���������
template<class T>
void binaryTree<T>::makeTree(const T& element, binaryTree<T>& left, binaryTree<T>& right)
{	// Combine left, right, and element to make new tree.
	// left, right, and this must be different trees.
	// create combined tree
	root = new binaryTreeNode<T>(element, left.root, right.root);
	// deny access from trees left and right
	 left.root = right.root = 0;
}

//���������
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

//���������
template<class T>
void binaryTree<T>::makeTree(const T& element) {
	binaryTree<T> tmpLeft;
	binaryTree<T> tmpRight;
	this->makeTree(element, tmpLeft, tmpRight);
}

//�����ұߵĽڵ�������һ�ö�����
template<class T>
void binaryTree<T>::makeRightMostTree(binaryTree<T>& right) {
	binaryTreeNode<T>* p = this->root;
	while (p->rightNode != NULL) {
		p = p->rightNode;
	}
	p->rightNode = right.root;
}

//������ߵĽڵ�������һ�ö�����
template<class T>
void binaryTree<T>::makeLeftMostTree(binaryTree<T>& left) {
	binaryTreeNode<T>* p = this->root;
	while (p->leftNode != NULL) {
		p = p->leftNode;
	}
	p->leftNode = left.root;
}

//�ƻ�������
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

//�õ�����������Ϣ
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

//�ⲿ ����
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
	cout << "����ڵ��ֵΪ��" << endl;
	cin >> theElement;
	t->element = theElement;

	cout << "������ж����𣺣�1�����У�0����û�У����Ϲ����Ƴ���ͱ����ˣ�" << endl;
	cin >> left;
	if (left == true){
		binaryTreeNode<T> *newLeft = new binaryTreeNode<T>();
		t->leftNode = newLeft;
		input(newLeft);
	}
	else{
		t->leftNode = NULL;
	}

	cout << "���ұ��ж����𣺣�1�����У�0����û�У����Ϲ����Ƴ���ͱ����ˣ�" << endl;
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

//�ڲ�ǰ��
template <class T>
void binaryTree<T>::preOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Preorder traversal of *t.
	if (t) {
		visit(t);                 // visit tree root
		preOrder(visit, t->leftNode);   // do left subtree
		preOrder(visit, t->rightNode);  // do right subtree
	}
}

//�ڲ�����
template <class T>
void binaryTree<T>::inOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Inorder traversal of *t.
	if (t) {
		inOrder(visit, t->leftNode);   // do left subtree
		visit(t);                // visit tree root
		inOrder(visit, t->rightNode);  // do right subtree
	}
}

//�ڲ�����
template <class T>
void binaryTree<T>::postOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// postOrder traversal of *t.
	if (t) {
		postOrder(visit, t->leftNode);   // do left subtree
		postOrder(visit, t->rightNode);  // do right subtree
		visit(t);                // visit tree root
	}
}

//�ڲ����� �Ǳ�׼����
template <class T>
void binaryTree<T>::rightOrder(void(*visit)(binaryTreeNode<T> *u), binaryTreeNode<T> *t) const
{	// Preorder traversal of *t.
	if (t) {
		rightOrder(visit, t->rightNode);  // do right subtree
		visit(t);                 // visit tree root
		rightOrder(visit, t->leftNode);   // do left subtree
	}
}

//�ڲ����
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
		//ɾ�������е�ǰ���
		Q.pop();
		try{
			t = Q.front();
		}
		catch (invalid_argument){
			return;
		}
	}
}


//�ڲ� �߶�
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

//�ڲ� ��׺
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

//�ڲ� �ڵ���
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

//�ڲ� Ҷ����
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
	int numThisLevel = 1;  //���ڵ�ĸ���
	int orderThisLevel = 0;  //��ǰ����ڵ��ǵڼ���
	int numNextLevel = 0;  //��һ��ڵ�ĸ���
	int theWidth = 1;  //���
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
//�������α���
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