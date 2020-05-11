#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"

const int tablesize = 10;

template<typename T>
class HashTable {
	/*
	A hashtable is just an array of 10 linked lists
	*/
private:
	LinkedList<T>* table;
public:
	HashTable();
	~HashTable();


	void AddNode(Node<T>);

	friend std::ostream& operator<<(std::ostream&, const HashTable<T>&);
	
	
	void PrintTable();
	void PrintSummaryStats();
};

#endif // !HASHTABLE_H

