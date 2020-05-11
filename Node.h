#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>

bool PrintHex = false;

template<typename T>
struct Node {

	unsigned long long hashvalue;
	T data;
	Node<T>* next;

	void PrintNode()
	{
		std::cout << "Node data: " << data << std::endl;
		std::cout << "Node hash value: " << hashvalue << std::endl;
		if(PrintHex)
			std::cout << "Hexadecimal form of hash value: " << std::hex << hashvalue << std::endl;
	}
};
#endif // !NODE_H

