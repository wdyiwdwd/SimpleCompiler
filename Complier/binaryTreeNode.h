#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T> *leftNode;
	binaryTreeNode<T> *rightNode;

	binaryTreeNode(){
		leftNode = NULL;
		rightNode = NULL;
	}
	//�������캯��
	binaryTreeNode(const binaryTreeNode<T>& m){
		element = m.element;
		leftNode = NULL; 
		rightNode = NULL;
	}
	binaryTreeNode(const T& theElement){
		element = theElement;
		leftNode = NULL;
		rightNode = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild){  //ע���˰���������
		element = theElement;
		leftNode = theLeftChild;
		rightNode = theRightChild;
	}
};
