#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Edge.h"
#include <iostream>
/*
In this project T is a vertex type
*/
template<typename T>
class LinkedList {
	template<typename J>
	friend class Vertex; //vertex can access me just fine
private:
	Edge<T>* head; //shoot should have done Node<Edge<T>>*. no no, but then you'd have to implement with Node<T<C>> right?- since node
	//would take a template but as does edge who would be T is the comment above ?? IDK
	int NodesinList;

public:
	LinkedList();
	~LinkedList();

	void AddNode(T, int = 1); //pass in a vertex and the distance to that vertex. default of 1- arguments create an edge
	void AddNode(Edge<T>*); //pass in an edge

	void operator+(const Edge<T>*);

	void RemoveNode(T); //remove this now, if in the list from the list
	void RemoveNode(Edge<T>*); //Remove an edge in the linked list

	int GetNodesInList() { return NodesinList; }

	bool InList(T); //can use this to test if one vertex is connected to another
	bool operator==(T);

	void EmptyList();

	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& obj) {
		Edge<T>* temp = obj.head;
		if (temp) {
			os << temp->vert;
			if (temp->next)
				os << ", ";
			while (temp->next) {
				temp = temp->next;
				os << temp->vert;
				if(temp->next)
					os << ", ";
			}
		}
		else
			os << "No Connected Vertices.\n";

		return os;
	}

	T* GetIthNode(int i);

	Edge<T>* GetEdge(T);
	
};

#endif // !LINKEDLIST_H

