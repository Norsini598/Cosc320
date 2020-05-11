#ifndef EDGE_H
#define EDGE_H

/*
What about this thought:
	A vertex has a linked list of edges.
	Those vertices would then have their list of edges
*/

template<typename T>
struct Edge {
	T vert; //vertex this edge connects "someone" to. A vertex has a linkedlist of edges, each edge goes to vertex
	float distance; //distance or weight from the vertex containing this edge- default value = 1
	
	Edge<T>* next; //multiple connections
	
	bool operator==(const Edge<T>& obj) {
		bool r = false;
		if (vert == obj.vert)
			r = true;
		return r;
	}
};
#endif // !EDGE_H


