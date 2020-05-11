#include "Vertex.h"
#include <iostream>

template<typename T>
Vertex<T>::Vertex(T d) {
	Data = d;
	color = WHite;
	Connections = NULL; //this vertex is not connected to any other vertices
	detailedprint = false;
}
template<typename T>
Vertex<T>::Vertex() {
	Data = 0;
	color = WHite;
	Connections = NULL; //this vertex is not connected to any other vertices
	detailedprint = false;
}

template<typename T>
Vertex<T>::~Vertex() {
	if (Connections) {
		//std::cout << "Deleting connections" << std::endl;
		delete Connections; //calls linked list deconstructor
		//std::cout << "Connections deleted" << std::endl;
	}
	//std::cout << "Noting to remove" << std::endl;
}

template<typename T>
void Vertex<T>::RemoveAllConnections() {
	Connections->EmptyList();
}

template<typename T>
void Vertex<T>::AddConnection(T obj, int dist) {
	if (Connections == NULL)
		Connections = new LinkedList<T>;
	Connections->AddNode(obj, dist);
}

template<typename T>
void Vertex<T>::operator+(Edge<T> obj) {
	Connections->AddNode(&obj);
}

template<typename T>
bool Vertex<T>::IsConnected(const T obj) {
	bool r = false;
	if(Connections)
		if(Connections->InList(obj))
			r = true;
	return r;
}

template<typename T>
bool Vertex<T>::operator==(const T obj) {
	bool r = false;
	if (Data == obj)
		r = true;
	return r;
}

/*template<typename T>
std::ostream& operator<<(std::ostream& os, const Vertex<T>& obj) {
	if (obj.detailedprint)
		os << "This vertex (" << obj.Data << ") is connected to " << obj.Connections->GetNodesInList() << " other vertices.\n";
	else
		os << "Vertex: " << obj.Data;
	//print connection list
	os << "\n{ " << obj.Connections << "}\n";

	return os;

}*/

template<typename T>
void Vertex<T>::RemoveConnection(T obj) {
	//edge passed in is connected to this vertex
	if (Data == obj)
		Connections->RemoveNode(obj);
	//else do nothing or should we smite the user? ;}
}

template<typename T>
void Vertex<T>::operator-(T obj) {
	RemoveConnection(obj);
}

template<typename T>
T* Vertex<T>::GetIthConnection(int i) {
	T* temp = NULL;
	if(i < Connections->GetNodesInList())
		temp = (Connections->GetIthNode(i));
	return temp;
}

template<typename T>
int Vertex<T>::GetDistance(const T obj) {
	int r = 0;
	//if obj is connected to this
	if (Connections->InList(obj)) {
		Edge<T>* temp = Connections->GetEdge(obj);
		r = temp->distance;
	}
	return r;		
}

template<typename T>
bool Vertex<T>::operator<(const Vertex<T>& obj) {
	bool r = false;
	if (Data < obj.Data)
		r = true;
	return r;
}

template<typename T>
bool Vertex<T>::operator>(const Vertex<T>& obj) {
	bool r = false;
	if (Data > obj.Data)
		r = true;
	return r;
}

template<typename T>
bool Vertex<T>::operator==(const Vertex<T>& obj) {
	bool r = false;
	if (Data == obj.Data)
		r = true;
	return r;
}

template<typename T>
void Vertex<T>::PrintColor()
{
	if (color == WHite)
		std::cout << "White." << std::endl;
	else if (color == GRay)
		std::cout << "Gray." << std::endl;
	else if (color == REd)
		std::cout << "Red." << std::endl;
	else
		std::cout << "Black." << std::endl;
}