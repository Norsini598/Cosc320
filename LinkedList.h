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

	bool InList(T*); //return true if input value is in the list already


	void AddNode(Node<T>*);
	void AddNode(T*);
	void AddNode(T);

	void EmptyList(); //psuedo deconstructor

	void PrintList();

	int GetNodesInList();

	T* GetHead(); //return the head point and remove it form the list
	//return pointers OR copies? to but does not remove from the list
	
	void RemoveItem(T*); //given a value find it in the list and remove it from the list 

	T* GetClosestItem(T*);
	T* GetSecondClosestItem(T*);
	T* GetThirdClosestItem(T*);

};
#endif // !LINKEDLIST_H

