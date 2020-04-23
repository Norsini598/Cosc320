#include <iostream>
#include "MiscFunctions.h"
#include <cmath>

using namespace MiscFunctions;

namespace HashFunctions {

	const unsigned int w = 64;
	const unsigned int p = 61; //a prime number less than w
	const unsigned int a = 101; //another prime number

	const int stringhashes = 2; //number of implemented string hash functions

					//Declarations:
	
	//Integer Hashes
	std::size_t HashNum(std::size_t);

	//String Hashes
	unsigned long long ComputeHashString1(std::string);
	unsigned long long ComputeHashString2(int, int, std::string);
	//============================================================\\

	//Implementations
	//Not sure if this is correct
	std::size_t HashNum(std::size_t t) {
		unsigned long long W = pow(2, w); //2^w = Big Big #
		unsigned long long M = pow(2, p); //2^p = Big #
		//right shift make smaller by 2^(w-p)
		return ((((long long)a * t) % W) >> (w - p));
	}


	unsigned long long ComputeHashString1(std::string s) {
		int strlngth = CalculateStringLength(s);
		//2^64 not good practice instead:
		long unsigned m = pow(10, 9) + 9; //big prime
		long long unsigned M = pow(2, p); //2^p = Big #
		long long hashvalue = 0; //the value of the string's hash
		long long multiple = 1;
		int g = 53; //prime near 52| 26*2

		//using polynomial rolling hash function
		//asume upper and lower case string
		//sum the ascii values then mod size of hash table
		//A->65, B->66, ... Z->90, a->97, b->98, z->122 

		for (int i = 0; i < strlngth; i++) {
			hashvalue += (((((int)s[i]) - ((int)'a') + 1) * multiple) % m);
			multiple = (multiple * g) % m;
		}
		return hashvalue;
	}

	unsigned long long ComputeHashString2(int f, int b, std::string s) {
		/*
		Characteristics of a good hash function:
		1. Deterministic
		2. Uses all input data
		3. Uniform distribution of hashes
		4. Very different values for similar strings
		*/
		//if the string is over 30 characters hash substrings of 10 characters
		/*
		Idea: employ merge sort-like process
		partition in halves repeatitively until size 1
			Option A: append these length 1 strings back together by sum of their values?
			Option B: Take the first and last indeces multiply the ascii value of the char, decrement b increment f
		*/
		int length = CalculateStringLength(s);
		unsigned long long m = pow(10, 9) + 9; //big prime
		unsigned long long M = pow(2, p); //2^p = Big #
		unsigned long long hashvalue = 0; //the value of the string's hash
		unsigned long long temp = 0; //store subarray hashvalues
		long long multiple = 1; //changes with every iteration
		int g = 53; //prime near 127 for all ascii
		//splitter
		const int subdividelength = 5;
		//iterator
		int i = 0;

		if (length < 31)
			for (i = 0; i < length; i++) {
				hashvalue += (pow((((int)s[i] - (int)'a') + 1) + (((int)s[length - i - 1] - (int)'a') + 1), (i + 1)) * multiple);
				hashvalue += hashvalue % m;
				multiple += (multiple * g) % m;
			}
		else {
			int current = i;
			while (current < length) {
				//loop 10 times
				for (i = current; i < current + subdividelength; i++) {
					temp += (pow((((int)s[i] - (int)'a') + 1) + (((int)s[length - i - 1] - (int)'a') + 1), (i + 1)) * multiple);
					temp += temp % m;
					multiple += (multiple * g) % m;
				}
				current = current + subdividelength; //after one iteration current is at 10
				hashvalue += temp % (m >> 1);
				temp = 0;
			}
		}

		return hashvalue;


	}







}
