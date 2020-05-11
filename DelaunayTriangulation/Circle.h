#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle {
	friend class Triangle;
	friend class DelaunayT;
	
private:
	Vertex* Center;
	float radius;
	float A;
	float B;
	float C;
	float D;
	//equation for a circle Ax^2 + Ay^2  + Bx + Cy + D = 0
public:
	
	Circle(); //create points inside the circle
	Circle(Vertex*, Vertex*, Vertex*); //pass in three points
	Circle(const Circle&);
	
	Circle& operator=(Circle&);
	//Circle(const Circle&); //copy constructor
	~Circle(); //deconstructor

	void SetPoints(Vertex*, Vertex*, Vertex*);

	Vertex* GetPointCenter() { return Center; }

	void CalculateA(Vertex*, Vertex*, Vertex*);
	void CalculateB(Vertex*, Vertex*, Vertex*);
	void CalculateC(Vertex*, Vertex*, Vertex*);
	void CalculateD(Vertex*, Vertex*, Vertex*);
	void CalulateRadius();

	bool IsinCircle(Vertex*);//returns true if the point is within the circle
	friend std::ostream& operator<<(std::ostream&, const Circle&);

	bool operator==(const Circle&);
	
};
#endif // !CIRCLE_H

