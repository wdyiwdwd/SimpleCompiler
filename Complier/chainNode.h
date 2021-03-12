#ifndef _CHAINNODE_H_
#define _CHAINNODE_H_
template <class T>
struct chainNode
{
	//成员
	T element;
	chainNode<T>* next;
	//方法
	chainNode(){
		this->next = NULL;
	}
	chainNode(const T& element){
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next){
		this->element = element;
		this->next = next;
	}
};
#endif