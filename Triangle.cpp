#include "Triangle.h"

using namespace Vectors;

//default construct
Triangle::Triangle() {
	A = new Vertex;
	B = new Vertex;
	C = new Vertex;
	Circumscriber = new Circle; //center = 0,0
	
	TotalTriangleCount++;
	ExtantTriangleCount++;
}

//constructr with points
Triangle::Triangle(Vertex* a, Vertex* b, Vertex* c) {
	A = a;
	B = b;
	C = c;
	Circumscriber = new Circle(A, B, C); 

	TotalTriangleCount++;
	ExtantTriangleCount++;
}
Triangle::Triangle(Vertex a, Vertex* b, Vertex* c) {
	A = new Vertex(a);
	B = b;
	C = c;
	Circumscriber = new Circle(A, B, C);

	TotalTriangleCount++;
	ExtantTriangleCount++;
}
Triangle::Triangle(Vertex a, Vertex b, Vertex c) {
	A = new Vertex(a);
	B = new Vertex(b);
	C = new Vertex(c);
	Circumscriber = new Circle(A, B, C);

	TotalTriangleCount++;
	ExtantTriangleCount++;
}
Triangle::Triangle(Vertex a, Vertex* b, Vertex c) {
	A = new Vertex(a);
	B = b;
	C = new Vertex(c);
	Circumscriber = new Circle(A, B, C);

	TotalTriangleCount++;
	ExtantTriangleCount++;
}

Triangle::Triangle(const Triangle& obj) {
	A = new Vertex(*obj.A);
	B = new Vertex(*obj.B);
	C = new Vertex(*obj.C);
	Circumscriber = new Circle(*obj.Circumscriber);
	
	TotalTriangleCount++;
	ExtantTriangleCount++;
}

//deconstructor
Triangle::~Triangle()	 {
	//if (this) {
		//if (A)
			delete A;
		//if (B)
			delete B;
		//if (C)
			delete C;
		//if (Circumscriber)
			delete Circumscriber;

		ExtantTriangleCount--;
	//}
}

//assignment opperator Triangle A = Triangle B
Triangle& Triangle::operator=(const Triangle& obj) {
	if (A == NULL) {
		A = new Vertex(*obj.A);
	}
	else
		*A = *obj.A;
	if (B == NULL) {
		B = new Vertex(*obj.B);
	}
	else
		*B = *obj.B;
	if (C == NULL) {
		C = new Vertex(*obj.C);
	}
	else
		*C = *obj.C;
	//set circle
	if (Circumscriber == NULL) {
		Circumscriber = new Circle(*obj.Circumscriber);
	}
	else
		*Circumscriber = *obj.Circumscriber;

	/*ExtantTriangleCount++;
	TotalTriangleCount++;*/

	return *this;

	/*ExtantTriangleCount++;
	TotalTriangleCount++;*/

}

//Print details of this triangle
std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
	if(obj.A)
		os << "Point A: " << *obj.A << std::endl;;
	if (obj.B)
		os << "Point B: " << *obj.B << std::endl;;
	if (obj.C)
		os << "Point C: " << *obj.C << std::endl;;
	if (obj.Circumscriber)
		os << *obj.Circumscriber << std::endl;
	
	return os;
}

//is a point in the circumcircle of this triangle
bool Triangle::InCircumscriber(Vertex* obj) {
	return Circumscriber->IsinCircle(obj);
}
bool Triangle::InCircumscriber(Triangle* obj) {
	bool r = false;
	if (Circumscriber->IsinCircle(obj->A))
		r = true;
	else if (Circumscriber->IsinCircle(obj->B))
		r = true;
	else if (Circumscriber->IsinCircle(obj->C))
		r = true;
	return r;
}

//return minimum angle of this triangle
float Triangle::GetMinAngle() {
	float min = 0;
	/*float min = 0;

	//3 vectors to represent distances between points in the triangle
	float vec1[2];
	float vec2[2];
	float vec3[2];
	
	vec1[0] = A->X - B->X;
	vec1[1] = A->Y - B->Y;

	vec2[0] = C->X - B->X;
	vec2[1] = C->Y - B->Y;
	
	vec3[0] = C->X - A->X;
	vec3[1] = C->Y - A->Y;

	std::cout << "Printing Vectors: " << std::endl;
	std::cout << "Vec1: " << vec1[0] << " " << vec1[1] << std::endl;
	std::cout << "Vec2: " << vec2[0] << " " << vec2[1] << std::endl;
	std::cout << "Vec3: " << vec3[0] << " " << vec3[1] << std::endl;
	std::cout << std::endl;


	float temp = 0;
	float dot = 0;
	float mag = 0;
	for (int i = 0; i < 3; i++) {
		std::cout << "i = ";
		if (i == 0) {
			dot = DotProduct(vec1, vec2, 2);
			mag = Magnitude(vec1, 2) * Magnitude(vec2, 2);
		}
		else if (i == 1) {
			dot = DotProduct(vec2, vec3, 2);
			mag = Magnitude(vec2, 2) * Magnitude(vec3, 2);
		}
		else  {
			dot = DotProduct(vec1, vec3, 2);
			mag = Magnitude(vec1, 2) * Magnitude(vec3, 2);
		}
		
		temp = acos(dot / mag);
		//min = (i == 0) ? temp : (temp < min) ? temp : min;
		if (i == 0)
			min = temp;
		else
			if (temp < min)
				min = temp;
	}
	min *= 180;
	min /= PI;
	return min;
	*/
	if(A && B && C)
		min = GetMinAngle(A, B, C);
	return min;
	
}

//return minimum angle of a triangle formed by any 3 points
float Triangle::GetMinAngle(const Vertex* a, const Vertex* b, const Vertex* c) {

	float min = 0;

	//3 vectors to represent distances between points in the triangle
	float vec1[2];
	float vec2[2];
	float vec3[2];

	vec1[0] = a->X - b->X;
	vec1[1] = a->Y - b->Y;

	vec2[0] = c->X - b->X;
	vec2[1] = c->Y - b->Y;

	vec3[0] = c->X - a->X;
	vec3[1] = c->Y - a->Y;


	float temp = 0;
	float dot = 0;
	float mag = 0;
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			dot = DotProduct(vec1, vec2, 2);
			mag = Magnitude(vec1, 2) * Magnitude(vec2, 2);
		}
		else if (i == 1) {
			dot = DotProduct(vec2, vec3, 2);
			mag = Magnitude(vec2, 2) * Magnitude(vec3, 2);
		}
		else /* (i == 2)*/ {
			dot = DotProduct(vec1, vec3, 2);
			mag = Magnitude(vec1, 2) * Magnitude(vec3, 2);
		}

		temp = acos(dot / mag);
		//min = (i == 0) ? temp : (temp < min) ? temp : min;
		if (i == 0)
			min = temp;
		else
			if (temp < min)
				min = temp;
	}
	min *= 180;
	min /= PI;
	return min;

}

//return minimum angle of a triangle
float Triangle::GetMinAngle(const Triangle* obj) {
	float min = 0;
	if (obj) {
		if (obj->A && obj->B && obj->C)
			min = GetMinAngle(obj->A, obj->B, obj->C);
	}
	return min;
}

//< == >, bvased on the x location of the circumscriber's center
bool Triangle::operator<(const Triangle& obj) {
	bool r = false; //assume to the right
	if (Circumscriber->Center->X < obj.Circumscriber->Center->X)
			r = true;
	return r;
}
bool Triangle::operator>(const Triangle& obj) {
	bool r = false; //assume to the left
	if (Circumscriber->Center->X > obj.Circumscriber->Center->X)
		r = true;
	return r;
}
//are the two trianlges the same triangle
bool Triangle::operator== (const Triangle& obj) {
	bool r = false;//assume not same x value
	//will only have the same center if they have the same A, B, and C vertices
	if (Circumscriber && obj.Circumscriber) {
		if (*A == *obj.A && *B == *obj.B && *C == *obj.C)
			r = true;
	}
	return r;
}

//compare minimum angles- goal of DT is to maximize minimum angles
bool Triangle::operator<=(const Triangle* obj) {
	bool r = false; //assume the minimum angle of this triangle is larger than the minimum angle of the input
	if (GetMinAngle() < GetMinAngle(obj))
		r = true; //sike its smaller or equal to
	return r;
}

bool Triangle::operator>=(const Triangle* obj) {
	bool r = false; //assume the minimum angle of this triangle is smaller than the minimum angle of the input
	if (GetMinAngle() > GetMinAngle(obj))
		r = true; //sike its greater or equal to.
	return r;
}


//Get the ____ respect to an input vertex
Vertex* Triangle::GetClosest(const Vertex* obj) {
	Vertex* returnval = NULL;
	if (obj) {
		returnval = new Vertex;
		float Adist = CalculateDistance(A->X, A->Y, obj->X, obj->Y);
		float Bdist = CalculateDistance(B->X, B->Y, obj->X, obj->Y);
		float Cdist = CalculateDistance(C->X, C->Y, obj->X, obj->Y);

		bool set = false;
		if (Adist != 0) {
			if (Adist < Bdist && Adist < Cdist) {
				returnval->SetX(A->X);
				returnval->SetY(A->Y);
				set = true;
			}
		}
		else if(Adist == 0) {
			if (Bdist < Cdist) {
				returnval->SetX(B->X);
				returnval->SetY(B->Y);
			}
			else {
				returnval->SetX(C->X);
				returnval->SetY(C->Y);
			}
			set = true;
		}
		if (set == false) {
			if (Bdist != 0) {
				if (Bdist < Adist && Bdist < Cdist) {
					returnval->SetX(B->X);
					returnval->SetY(B->Y);
				set = true;
				}
			}
			else if (Bdist == 0) {
				if (Adist < Cdist) {
					returnval->SetX(A->X);
					returnval->SetY(A->Y);
				}
				else {
					returnval->SetX(C->X);
					returnval->SetY(C->Y);
				}
				set = true;
			}
		}
		if (set == false) {
			if (Cdist != 0) {
				if (Cdist < Adist && Cdist < Bdist) {
					returnval->SetX(C->X);
					returnval->SetY(C->Y);
					set = true;
				}
			}
			else if (Cdist == 0) {
				if (Adist < Bdist) {
					returnval->SetX(A->X);
					returnval->SetY(A->Y);
				}
				else {
					returnval->SetX(B->X);
					returnval->SetY(B->Y);
				}
				set = true;
			}
		}
	}
	return returnval;
}

Vertex* Triangle::GetMiddle(const Vertex* obj) {
	Vertex* returnval = NULL;
	if (obj) {
		returnval = new Vertex;
		float Adist = CalculateDistance(A->X, A->Y, obj->X, obj->Y);
		float Bdist = CalculateDistance(B->X, B->Y, obj->X, obj->Y);
		float Cdist = CalculateDistance(C->X, C->Y, obj->X, obj->Y);

		if ((Adist < Bdist && Bdist < Cdist) || (Cdist < Bdist && Bdist < Adist)) {
			returnval->SetX(B->X);
			returnval->SetY(B->Y);
		}
		else if ((Bdist < Adist && Adist < Cdist) || (Cdist < Adist && Adist < Bdist)) {
			returnval->SetX(A->X);
			returnval->SetY(A->Y);
		}
		else {
			returnval->SetX(C->X);
			returnval->SetY(C->Y);
		}
	}
	return returnval;
}

Vertex* Triangle::GetFurthest(const Vertex* obj) {
	Vertex* returnval = NULL;
	float Adist = CalculateDistance(A->X, A->Y, obj->X, obj->Y);
	float Bdist = CalculateDistance(B->X, B->Y, obj->X, obj->Y);
	float Cdist = CalculateDistance(C->X, C->Y, obj->X, obj->Y);

	if (Adist > Bdist && Adist > Cdist)
		returnval = new Vertex(*A);
	else if (Bdist > Adist && Bdist > Cdist)
		returnval = new Vertex(*A);
	else
		returnval = new Vertex(*C);
	return returnval;
}

float Triangle::GetMaxX() {
	float max = A->X;
	if (B->X > max)
		max = B->X;
	if (C->X > max)
		max = C->X;
	return max;
}

float Triangle::GetMinX() {
	float min = A->X;
	if (B->X < min)
		min = B->X;
	if (C->X < min)
		min = C->X;
	return min;
}
float Triangle::GetMaxY() {
	float max = A->Y;
	if (B->Y > max)
		max = B->Y;
	if (C->Y > max)
		max = C->Y;
	return max;
}
float Triangle::GetMinY() {
	float min = A->Y;
	if (B->Y < min)
		min = B->Y;
	if (C->Y < min)
		min = C->Y;
	return min;
}

//given 2 triangles return the one that is closerr to from
Triangle* Triangle::GetCloserTriangle(Triangle* T1, Triangle* T2, const Vertex* from) {
	Vertex* T1compare = T1->GetClosest(from);
	Vertex* T2compare = T2->GetClosest(from);
	float T1dist = CalculateDistance(from->X, from->Y, T1compare->X, T1compare->Y);
	float T2dist = CalculateDistance(from->X, from->Y, T2compare->X, T2compare->Y);
	
	if (T1dist == T2dist) {
		T1dist = CalculateDistance(from->X, from->Y, T1->Circumscriber->Center->X, T1->Circumscriber->Center->Y);
		T2dist = CalculateDistance(from->X, from->Y, T2->Circumscriber->Center->X, T2->Circumscriber->Center->Y);
	}

	delete T1compare;
	delete T2compare;

	if (T1dist < T2dist)
		return T1;
	else
		return T2;
}


