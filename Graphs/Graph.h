#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h" //includes: edges, vertex, and LinkedList
#include "RedBlueTree.h"//includes: RedBlueTrees and TreeNode
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <stack>
#include <queue>
/*
A graph is made with many vertices and edges.
Should it be a list of vertices or rather an array of vertices?
Array:
	-easy access
	-hard to make a bigger than X graph
List:
	-easy to make big graphs
	-hard to access a particular vertex
---------------------------------------
List of small arrays?
	Create a special node that contains a double pointer of vertices of size, say 5. They are initialized with NULL
	but still dificult acess to find that group of array
---------------------------------------
http://www.cplusplus.com/reference/map/map/ says maps are implemented as binary search trees- why not do the same?
so we would have a tree of vertices- I suppose that would work- would it be better to be a RedBlack Tree- yah,
well let me rephrase, "Should" it be a RedBlack tree?-- I don't see why not, right?-- Unless we want the first node to be 
"fixed"- but I don't see why that should matter. So I suppose we will use a redblue tree. More efficient right!

The tree will not reflect the graph structure- just stores vertices!

Other map functionalities must be coded such as:
First- easier- first node in the tree,
Last- rightmost (get maxiumum from root)
Empty- part of tree functionality easy.
maxsize- get tree size- easy- get nodenum()
operator[]- okay- basically underneath would search tree for that elemnent.
	should we overload with index or with vertex value?
	I think 

Swap- dont think that is necessary? unless we want to swap edges say A has an edge going to B. a swap could make B have an edge to A?

Emplace- just add a vertex
Find- see operator[]
Operator=


*/
template<typename T>
class Graph {
private:
	RedBlueTree<Vertex<T>>* graph; //storage for all vertices
	int VertexCount; //size of this graph
	bool isDirected; //true if this is a directed graph
	bool isDAG; //true if this graph is a dag
	bool isAcyclic;//true if no cycles
	bool checkedDAG;

public:
	Graph();
	Graph(bool);
	Graph(Graph<T>&);
	~Graph();

	void BFS(T); //run Breadth-First-Search. Input a T data- Find that vetex in the tree
	void DFS(T, bool = true); //bool val to denote if we care its a dag or not
	void AugmentedDFS(T);
	//void RecursiveDFS(T, int*, int*, int*, int* int&);
	void RecursiveDFS(T startval, int* distance, int* vertices, int* discoveries, int* finshes, int& opcount);
	void RecursiveAugmentedDFS(Vertex<T>*, int*, int&, int&); //component array and index
	void TopoSort();
	bool GetIsDag() { return isDAG; }

	void CalculateVectorCover1(); //returns string of the vertex values necessary to construct a vertex cover

	//remove all contents from this graph
	void EmptyGraph();

	//get isdirected
	bool GetIsDirected() { return isDirected; }

	//reset color
	void RecolorAllWhite(); //makes all vertices white
	void MakeWhite(TreeNode<Vertex<T>>*); //uses recursion to make a vertices white

	void AddVertex(T);
	void operator+(T); //pass in a T and add it to the Graph

	void RemoveVertex(T);//starter
	void RemoveVertex(TreeNode<Vertex<T>>*, T); //recursive friendly
	void operator-(T);//pass in a T and remove that T from the Graph-- if it is in there

	//Print Graph
	void PrintAdjacencyList();//starter
	void PAL(TreeNode<Vertex<T>>*); //recursive friendly

	//Get a vertex give the value in a vertex- only works if in graph
	Vertex<T>* operator[](const T); //pass in a vetex value and get that vertex back. list[i] return int

	//ingraph?
	Vertex<T>* Find(const T); //starter
	Vertex<T>* Find(TreeNode<Vertex<T>>*, const T); //recursive friendly
	bool operator== (T); //is a value in the graph?

	void AddUndirectedConnection(const T, const T); //assume undirected
	void AddDirectedConnection(const T to, const T from);
	void RemoveConnection(const T, const T); //remove the connection between these two values

	void PrintVertices();

	int GetDistanceBetween(const T, const T);

	void SimplePrint();//just prints the tree

	void AssistConnections();

	int GetVertexCount() { return VertexCount; }

	void ReadConnectionsFromFile();

	Graph<T>& transpose(Graph<T>&); //takes the transpose of this graph

	void CopySetUp(Graph<T>&, Graph<T>&);

	void Copy(TreeNode<Vertex<T>>*, Graph<T>&); //returns a copy of this tree

	void InvertConnections(Graph<T>&, Graph<T>&); //starter-- bring in old version
	void InvertConnections(TreeNode<Vertex<T>>*, Graph<T>&);


	void CheckIfDAG();
	void RecursiveCheckIfDAG(Vertex<T>*);

	void DecsendingBubbleSort(int*, int*);

	void PrintStronglyConnectedComponents();
};
#endif // !GRAPH_H