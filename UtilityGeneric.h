#ifndef UTILITYGENERIC_H
#define UTILITYGENERIC
#include <cmath>
#include "LinkedList.h"
#include "EscapeSequences.h"
#include <fstream>


const float PI = 3.14159265358979323846;

namespace Vectors {
	float DotProduct(float*, float*, int);
	float Magnitude(float*, int);
	
	
	float DotProduct(float* a, float* b, int size) {
		float result = 0;
		for (int i = 0; i < size; i++) {
			result += (a[i] * b[i]);
		}
		return result;
	}

	float Magnitude(float* a, int size) {
		float mag = 0;
		for (int i = 0; i < size; i++) {
			mag += (a[i] * a[i]);
		}
		mag = pow(mag, .5);
		return mag;
	}

}

float CalculateDistance(float x1, float y1, float x2, float y2);

float CalculateDistance(float x1, float y1, float x2, float y2) {
	float dist = 0;
	float temp1 = ((x1 - x2) * (x1 - x2));
	float temp2 = ((y1 - y2) * (y1 - y2));
	dist = temp1 + temp2;
	dist = pow(dist, .5); 
	return dist; //return the distance between two sets of points
}




#endif // !UTILITYGENERIC_H

