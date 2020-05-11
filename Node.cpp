#include "Node.h"
//#include <iostream>

template<typename T>
Node<T>::Node(T t, unsigned long long h)
{
	data = t;
	hashvalue = h;
	next = NULL; //doesnt point to another node
}

template<typename T>
Node<T>::~Node()
{
	while (next) {
		Node* temp = next;
		//iterate until the end
		if (temp != NULL) { //this next is not the last next
			while (temp->next != NULL) {
				temp = temp->next; //set temp = to the next node
			}
			delete temp->next;
			temp->next = NULL;
		}
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& obj)
{
	std::cout << "Node Value: " << obj.data << std::endl;
	std::cout << "Corresponding Hash Value: " << obj.hashvalue << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	return os;
}