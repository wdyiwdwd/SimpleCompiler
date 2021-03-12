#pragma once
#include <iostream>
#include <stdexcept>
#include "chainNode.h"
using namespace std;

template <class T>
class linkedQueue
{
public:
	linkedQueue(){
		queueFront = NULL;
		queueBack = NULL;
		queueSize = 0;
	}
	//linkedQueue(const linkedQueue<T>&);
	~linkedQueue();
	bool empty() const{
		return queueFront == NULL;
	}
	int size() const{
		return queueSize;
	}
	T& front() const{
		if (queueFront == NULL){
			throw invalid_argument("front error");
		}
		return queueFront->element;
	}
	T& back() const{
		if (queueBack == NULL){
			throw invalid_argument("back error");
		}
		return queueBack->element;
	}
	void pop();
	void push(const T& theElement);
private:
	chainNode<T>* queueFront;
	chainNode<T>* queueBack;
	chainNode<T>* queue;
	int queueSize;
};

/*template <class T>
linkedQueue<T>::linkedQueue(const linkedQueue<T>& m)
{
if (m.queueFront == NULL){
queueFront = NULL;
queueBack = NULL;
queueSzie = 0;
}
else{
chainNode<T> p = m.queueFront->next;
chainNode<T> theQueue = queueFront->next;
while (p != NULL){
chainNode<T>* theNode = new chainNode<T>(p->element);
theQueue = theNode;
theQueue = theQueue->next;
p = p->next;
}
}
}*/

template <class T>
linkedQueue<T>::~linkedQueue()
{
	if (queueFront != NULL){
		chainNode<T> *p = queueFront;
		chainNode <T> *tp = p->next;
		while (p != NULL){
			delete p;
			p = tp;
			tp = p->next;
		}
	}
}

template <class T>
void linkedQueue<T>::pop()
{
	//删除首元素
	if (queueFront == NULL){
		throw invalid_argument("pop error");
	}

	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}

template <class T>
void linkedQueue<T>::push(const T& theElement)
{
	//把元素排到队尾
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	//把新节点放到队尾
	if (queueSize == 0){
		queueFront = newNode;
	}
	else{
		queueBack->next = newNode;
	}
	queueBack = newNode;
	queueSize++;
}