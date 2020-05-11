#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template<typename T>
class LinkedList {
private:
	Node<T>* head;
	int NodesinList;

public:
	LinkedList();
	~LinkedList();

	void AddNode(Node<T>*);

	void PrintList();

	int GetNodesInList() { return NodesinList; }
};
#endif // !LINKEDLIST_H

