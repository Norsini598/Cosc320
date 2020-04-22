#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template<typename T>
class LinkedList
{
	template<typename J>
	friend class HashTable;
private:
	Node<T>* head;
	int NodesinList;

public:
	LinkedList();
	~LinkedList();

	void AddNode(Node<T>);

	void PrintList();

	void EmptyList(); //basically the deconstructor.

	int GetNodesInList() { return NodesinList; }

	bool IsEmpty() { return (head) ? false : true; } //return true if head is NULL, i.e empty

	bool InList(T); //return true if that T is in the list, false otherwise
};
#endif // !LINKEDLIST_H

