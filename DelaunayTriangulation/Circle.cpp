#include "Circle.h"

//default constructor
Circle::Circle() {
	radius = 0;
	A = B = C = D = 0;
	Center = new Vertex; //center at  (0, 0), since no circle
}
//deconstructor
Circle::~Circle() {
	if (Center) {
		delete Center;
		Center = NULL;
	}
}
//create circle with points on circumference
Circle::Circle(Vertex* a, Vertex* b, Vertex* c) {
	if (a && b && c) {
		CalculateA(a, b, c);
		CalculateB(a, b, c);
		CalculateC(a, b, c);
		CalculateD(a, b, c);
		CalulateRadius();

		Center = new Vertex(((-1 * B) / (2 * A)), ((-1 * C) / (2 * A)));
	}
	else {
		radius = 0;
		A = B = C = D = 0;
		Center = new Vertex; //center at  (0, 0), since no circle
		//got jipped with incomplete data LUL.
	}
}
//copy constructor
Circle::Circle(const Circle& obj) {
	
	Center = new Vertex(*obj.Center);
	radius = obj.radius;
	A = obj.A;
	B = obj.B;
	C = obj.C;
	D = obj.D;
}

//a = (x1, y1), b = (x2, y2), c = (x3, y3)
//formulas for A, B, C,  and D derived using determinant of x,y (general), x1,y1 (point 1), x2,y2 (point 2), and x3,y3 (point 3) system of equations using 
//equation of circle Ax^2+Ay^2+Bx+Cy+D
//hard to explain in comments
//see http://www.ambrsoft.com/trigocalc/circle3d.htm explains the derivation nicely.
void Circle::CalculateA(Vertex* a, Vertex* b, Vertex* c) {
	//A = x(y2-y3) - y1(x2-x3) + x2y2- x3y2
	A = ((a->X * (b->Y - c->Y)) - (a->Y * (b->X - c->X)) + (b->X * c->Y) - (c->X * b->Y));
}
void Circle::CalculateB(Vertex* a, Vertex* b, Vertex* c) {
	B = (((a->X * a->X) + (a->Y * a->Y)) * (c->Y - b->Y)) + (((b->X * b->X) + (b->Y * b->Y)) * (a->Y - c->Y)) + (((c->X * c->X) + (c->Y * c->Y)) * (b->Y - a->Y));
}
void Circle::CalculateC(Vertex* a, Vertex* b, Vertex* c) {
	
	C = (((a->X * a->X) + (a->Y * a->Y)) * (b->X - c->X)) + (((b->X * b->X) + (b->Y * b->Y)) * (c->X - a->X)) + (((c->X * c->X) + (c->Y * c->Y)) * (a->X - b->X));
}
void Circle::CalculateD(Vertex* a, Vertex* b, Vertex* c) {
	D = (((a->X * a->X) + (a->Y * a->Y)) * ((c->X * b->Y) - (b->X * c->Y))) + (((b->X * b->X) + (b->Y * b->Y)) * ((a->X * c->Y) - (c->X * a->Y))) + (((c->X * c->X) + (c->Y * c->Y)) * ((b->X * a->Y) - (a->X * b->Y)));
}

void Circle::CalulateRadius() {
	radius = pow((((B * B) + (C * C) - (4 * A * D)) / (4 * (A * A))), .5);
}
//change the circle
void Circle::SetPoints(Vertex* a, Vertex* b, Vertex* c) {
	if (Center)
		delete Center;
	Center = NULL;

	if (a && b && c) {
		CalculateA(a, b, c);
		CalculateB(a, b, c);
		CalculateC(a, b, c);
		CalculateD(a, b, c);

		CalulateRadius();

		Center = new Vertex(((-1 * B) / (2 * A)), ((-1 * C) / (2 * A)));
	}
	else {
		radius = 0;
		A = B = C = D = 0;
		Center = new Vertex; //center at  (0, 0), since no circle and is just  a vertex
	}
}

std::ostream& operator<<(std::ostream& os, const Circle& obj) {
	if (obj.Center) {
		os << "Ceneter: " << *obj.Center << std::endl;
		os << "A: " << obj.A << std::endl;
		os << "B: " << obj.B << std::endl;
		os << "C: " << obj.C << std::endl;
		os << "D: " << obj.D << std::endl;
		os << "Radius: " << obj.radius << std::endl;
	}
	else
		os << "NULL circle." << std::endl;
	return os;
}

//is a point in this circle
bool Circle::IsinCircle(Vertex* a) {
	//return true if a is withinin the circumference circle
	bool r = false; //assume that it does not collide- on circle circumference means no collision
	//both non-NULL data
	if (Center && a) {
		//(x2-x1)^2+
		float distsq = (((a->X - Center->X) * (a->X - Center->X)) + ((a->Y - Center->Y) * (a->Y - Center->Y)));
		if (distsq < (radius * radius))
			r = true;
	}
	return r;
}

//is a circle the same as this?
bool Circle::operator==(const Circle& obj) {
	bool r = false; //assume aren't the same circle
	if (Center == obj.Center && radius == obj.radius)
		r = true;
	return r;
}

//assignment operator
Circle& Circle::operator=(Circle& obj) {
	A = obj.A;
	B = obj.B;
	C = obj.C;
	D = obj.D;
	radius = obj.radius;
	*Center = *obj.Center;

	return *this;

}