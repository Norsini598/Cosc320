#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include "UtilityGeneric.h"

class Vertex {
	friend class Circle;
	friend class Triangle;
	friend class DelaunayT;
	template<typename J>
	friend class LinkedList;
	template<typename F>
	friend class RedBlueTree;

private:
	float X;
	float Y;

public:
	Vertex(float = 0, float = 0);
	Vertex(const Vertex&);
	~Vertex();

	bool isLeft(const Vertex& obj) { return (obj.X < X) ? true : false; } //if input X is less than this return true, false otherwise
	bool isRight(const Vertex& obj) { return (obj.X > X) ? true : false; } //if input X is greater than this return true, false otherwise

	Vertex& operator=(const Vertex&);

	friend std::ostream& operator<< (std::ostream&, const Vertex&);

	bool operator==(const Vertex&);
	bool operator==(const Vertex*);

	void SetX(float x) { X = x; }
	void SetY(float y) { Y = y; }	

	float GetDistance(Vertex*);

};
#endif // !VERTEX_H

