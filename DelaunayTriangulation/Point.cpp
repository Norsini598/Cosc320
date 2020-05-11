#include "Point.h"


Vertex::Vertex(float a, float b) {
	X = a;
	Y = b;
}
Vertex::Vertex(const Vertex& obj) {
	X = obj.X;
	Y = obj.Y;
}
Vertex::~Vertex() {
	//no pointer variables yet.
}

Vertex& Vertex::operator=(const Vertex& obj) {
	X = obj.X;
	Y = obj.Y;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vertex& obj) {
	os << "(" << obj.X << ", " << obj.Y << ")" << std::endl;
	return os;
}

bool Vertex::operator==(const Vertex& obj) {
	bool r = false; //assume they are not the same
	if ((X == obj.X) && (Y == obj.Y))
		r = true;
	return r;
}
bool Vertex::operator==(const Vertex* obj) {
	bool r = false; //assume they are not the same
	if ((X == obj->X) && (Y == obj->Y))
		r = true;
	return r;
}

float Vertex::GetDistance(Vertex* obj) {
	return CalculateDistance(X, Y, obj->X, obj->Y);
}