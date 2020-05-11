#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>

template<typename T>
struct Node {
	T data;
	Node<T>* next;
};
#endif // !NODE_H

