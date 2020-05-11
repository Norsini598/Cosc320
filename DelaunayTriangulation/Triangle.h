#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Circle.h"

class Triangle {
private:
	friend class DelaunayT;
	template<typename J>
	friend class LinkedList;
	template<typename F>
	friend class RedBlueTree;
	//friend class Vertex;
	//A triangle is defined by 3 points
	Vertex* A;
	Vertex* B;
	Vertex* C;

	Circle* Circumscriber;//the circle defined by these 3 points

	static int TotalTriangleCount; //number of triangles created overall
	static int ExtantTriangleCount; //number of triangles in existence right now
public:
	Triangle();
	Triangle(Vertex*, Vertex*, Vertex*);
	Triangle(Vertex, Vertex*, Vertex*);
	Triangle(Vertex, Vertex, Vertex);
	Triangle(Vertex, Vertex*, Vertex);
	Triangle(const Triangle&);
	Triangle& operator=(const Triangle&);

	~Triangle();

	Vertex* GetA() { return A; }
	Vertex* GetB() { return B; }
	Vertex* GetC() { return C; }

	/*
	void SetA(Vertex*);
	void SetB(Vertex*);
	void SetC(Vertex*);
	*/	
	bool InCircumscriber(Vertex*);
	bool InCircumscriber(Triangle*);

	//Minimum angle of triangle
	float GetMinAngle();
	float GetMinAngle(const Triangle*);
	float GetMinAngle(const Vertex*, const Vertex*, const Vertex*);

	friend std::ostream& operator<<(std::ostream&, const Triangle&);
	
	//compare location of circle center- for tree placement
	bool operator< (const Triangle&);
	bool operator> (const Triangle&);

	//are the triangles the same- for tree searching
	bool operator== (const Triangle&);

	//compare minimum angles- for creating proper triangulations
	bool operator<= (const Triangle*); //min angle of this is less than input
	bool operator>= (const Triangle*); //min angle of this is greater than input

	Vertex* GetClosest(const Vertex*);
	Vertex* GetMiddle(const Vertex*);
	Vertex* GetFurthest(const Vertex*);

	float GetMaxX();
	float GetMaxY();
	float GetMinX();
	float GetMinY();


	Triangle* GetCloserTriangle(Triangle*, Triangle*, const Vertex*);
};

//initalize static values
int Triangle::ExtantTriangleCount = 0;
int Triangle::TotalTriangleCount = 0;
#endif // !TRIANGLE_H

