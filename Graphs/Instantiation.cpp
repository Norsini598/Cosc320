#include "Graph.cpp"
#include "LinkedList.cpp"
#include "RedBlueTree.cpp"
#include "Vertex.cpp"
#include "Main.cpp"

template class Graph<int>;

template class Vertex<int>;

template class TreeNode<Vertex<int>>;
template class RedBlueTree<Vertex<int>>;

template class LinkedList<int>;
//template class LinkedList<Edge<int>>;
//template class LinkedList<Vertex<int>>;

template class Edge<int>;