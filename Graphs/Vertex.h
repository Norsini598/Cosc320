#ifndef VERTEX_H
#define VERTEX_H


#include "LinkedList.h"
#include <iostream>
#include <fstream>

/*
Vertex is used in the class Graph- a graph is composed of vertices 

A vertex has data and a linked list of vertices <- will this cause dependecy issues because 
Linked List have vertex and vertex has linked list. Yes if Linked List constructor called upon 
creation of a vertex. When a vertex is created it will first have no connections, i.e NULL

Edge lengths will probably be a thing we will need later
	Could implement now by changing the linked list structure- for instance could:
	1. have 2 vertex-es in a node (edge) -> Edge will have 2 vertices and a size (int) default 1.,
	
	could just add 
*/

enum CLOR { WHite = 0, 
			GRay = 1, 
			BLack = 2,
			REd = 3 //only used for DAG checking
}; //wierd spelling to not inflict with redblack trees and escape sequeuences



template<typename T>
class Vertex {
private:
	CLOR color; //the current color of this vertex
	T Data; //data stored in this vertex
	LinkedList<T>* Connections; //a list of all of the edges (vertices) that this vertex is connected to
	//each vertex that this is connected to will have their own lists of vertices- just go through this list when running BFS and DFS
	//then located the next vertex using the [] overload

	bool detailedprint; //stupid variable incase more is necessary by choice?- AKA not sure what needs to be printed- let the user decide

public:
	Vertex(T);
	Vertex();
	~Vertex();
	
	void RemoveAllConnections(); //empties the linked list

	//both directed, create undirected connection by adding to both vertices in graph
	void AddConnection(T, int = 1); //this vertex "goes" to another
	void operator+(Edge<T>);
	
	bool IsConnected(const T);//is this vertex connected to another? 3 == 4 true if 3 is connected to 4
	bool operator==(const T);


	void RemoveConnection(T);
	void operator-(T);

	friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& obj) {
		if (obj.detailedprint) {
			if(obj.Connections != NULL)
				os << "This vertex (" << obj.Data << ") is connected to " << obj.Connections->GetNodesInList() << " other vertices.\n";
		}
		else
			os << "Vertex: " << obj.Data;
		
		//print connection list	
		if (obj.Connections != NULL) {
				os << "\n" << obj.Connections->GetNodesInList() << " Connections:\n{" << *obj.Connections << "}\n";
		}
		else
			os << "\nNo connections.\n";

		return os;

	}
	
	
	/*friend std::ostream& operator<<(std::ostream& os, const Vertex<T>* obj) {
		os << "Pointer print\n";
		if (obj->detailedprint)
			os << "This vertex (" << obj->Data << ") is connected to " << obj->Connections->GetNodesInList() << " other vertices.\n";
		else
			os << "Vertex: " << obj->Data;
		//print connection list
		if (obj->Connections->GetNodesInList() != 0)
			os << "\n{ " << obj->Connections << "}\n";
		else
			os << "\nNo connections.\n";

		return os;

	}*/


//------------------------------------------------------------------------------
//Getters and Setters
	//changing color
	void SetColor(CLOR a) { color = a; } //white = 0, gray = 1, black = 2
	void SetWhite() { SetColor(WHite); }
	void SetGray() { SetColor(GRay); }
	void SetBlack() { SetColor(BLack); }
	void SetRed() { SetColor(REd); }
	void PrintColor();

	//printsettings
	void SetPrintDetailSetting(bool a) { detailedprint = a; }
	bool GetPrintDetailSetting() { return detailedprint; }

	CLOR GetColor() { return color; }
	
	//data related
	T GetData() { return Data; }
	void SetData(T a) { Data = a; }

	LinkedList<T>* GetConnections() { return Connections; }
	int GetConnectionNum() { return Connections->GetNodesInList(); }

	T* GetIthConnection(int i);

	int GetDistance(const T);

	bool operator<(const Vertex<T>&);
	bool operator>(const Vertex<T>&);
	bool operator==(const Vertex<T>&);
	bool Empty() { return (Connections) ? false : true; }
	int GetNodesInList() { return (Connections) ? Connections->GetNodesInList() : 0; }

};

#endif // !VERTEX_H

