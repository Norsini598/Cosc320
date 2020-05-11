#include "Main.cpp"
#include "HashTable.cpp"
#include "LinkedList.cpp"
#include "Node.cpp"

template class Node<unsigned long long>;
template class Node<std::size_t>;
template class Node<std::string>;

template class LinkedList<unsigned long long>;
template class LinkedList<std::size_t>;
template class LinkedList<std::string>;

template class HashTable<unsigned long long>;
template class HashTable<std::size_t>;
template class HashTable<std::string>;
