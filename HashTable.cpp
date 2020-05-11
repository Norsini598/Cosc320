#include "HashTable.h"

template<typename T>
HashTable<T>::HashTable(){
	table = new LinkedList<T>[tablesize];
} 

template<typename T>
HashTable<T>::~HashTable() {

	delete[]table;
	table = NULL;
}
template<typename T>
void HashTable<T>::AddNode(Node<T> obj) {
	int indx = obj.hashvalue % tablesize; //index of which this node will be added to
	table[indx].AddNode(&obj);
}

template<typename T>
void HashTable<T>::PrintSummaryStats()
{
	std::cout << "# of nodes in each list: " << std::endl;
	for (int i = 0; i < tablesize; i++)
	{
		std::cout << "List #" << i + 1 << std::endl;
		std::cout << "    " << table[i].GetNodesInList() << " nodes in this list." << std::endl;
	}
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const HashTable<T>& obj)
{
	for (int i = 0; i < tablesize; i++)
	{
		std::cout << "List " << i + 1 << ":" << std::endl;
		std::cout << "---------------" << std::endl;
		obj.table[i].PrintList();
		std::cout << std::endl;
	}
	return os;
}

template<typename T>
void HashTable<T>::PrintTable() {
	for (int i = 0; i < tablesize; i++)
	{
		std::cout << "List " << i + 1 << ":" << std::endl;
		std::cout << "---------------" << std::endl;
		std::cout << "Nodes in this list: " << table[i].GetNodesInList() << std::endl;
		table[i].PrintList();
		std::cout << std::endl;
	}
}