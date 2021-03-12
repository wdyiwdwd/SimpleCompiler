#ifndef _CHAINNODE_H_
#define _CHAINNODE_H_
template <class T>
struct chainNode
{
	//��Ա
	T element;
	chainNode<T>* next;
	//����
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