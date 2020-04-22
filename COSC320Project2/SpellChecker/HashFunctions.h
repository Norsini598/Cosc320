#include <iostream>
#include "UtilityGeneric.h"
#include <cmath>

using namespace UtilityFunctions;

namespace HashFunctions {

	const unsigned int w = 32;
	const unsigned int p = 15; //defines the range of hashvalues and, therby, the size of the hashtable
	const unsigned int a = 101; //another prime number
	const unsigned int HashTableSize = (1 << p); //262144 table size //array of 262144 linked lists

	const int stringhashes = 2; //number of implemented string hash functions; only 1 compatible with HashTables

	//Declarations\\
	================

	//Integer Hashes
	std::size_t HashNum(std::size_t);

	//String Hashes
	size_t ComputeHashString1(std::string);
	size_t ComputeHashString2(int, int, std::string);
	size_t ComputeHashString3(std::string);
	//============================================================\\

	//Implementations\\
	===================

	//For Numbers
	std::size_t HashNum(std::size_t t) {
		unsigned long long W = pow(2, w); //2^w = Big Big #
		//unsigned long M = pow(2, p); //2^p = Big #
		size_t hashvalue;
		//right shift make smaller by 2^(w-p)
		hashvalue = ((((long long)a * t) & (W - 1)) >> (w - p));
		return hashvalue % HashTableSize;
	}
	//============================================================\\
	//For strings
	size_t ComputeHashString1(std::string s) {
		int strlngth = CalculateStringLength(s);
		//2^64 not good practice instead:
		long unsigned m = pow(10, 9) + 9; //big prime
		//unsigned long  M = pow(2, p); //2^p = Big #
		long long multiple = 1;
		size_t hashvalue = 0; //the value of the string's hash
		int g = 53; //prime near 52| 26*2
		const int shiftA = 3;

		//using polynomial rolling hash function
		//asume upper and lower case string
		//sum the ascii values then mod size of hash table
		//A->65, B->66, ... Z->90, a->97, b->98, z->122 

		//convert string to some number
		for (int i = 0; i < strlngth; i++) {
			hashvalue += (((int)s[i] - (int)'A') * multiple);
			if (i % 2 == 0)
				multiple = ((multiple * g) >> (shiftA + i));
			else
				multiple = ((multiple * g) << (shiftA - i));
		}
		/*else {
			size_t temp;
			int i = 0;
			int current = 0;
			const int subdividelength = 5;
			while (current < strlngth) {
				//loop 10 times
				for (i = current; i < current + subdividelength; i++) {
					temp += (pow((((int)s[i] - (int)'a') + 1) + (((int)s[strlngth - i - 1] - (int)'a') + 1), (i + 1)) * multiple);
					temp += temp & (m - 1);
					if (i % 2 == 0)
						multiple = ((multiple * g) >> shiftA);
					else
						multiple = ((multiple * g) << shiftA);
				}
				current = current + subdividelength; //after one iteration current is at 10
				hashvalue += temp % ((m >> 1) - 1);
				temp = 0;
			}
		}*/

		hashvalue = (hashvalue * g) & ((1 << w) - 1); //hv*g % w
		hashvalue = hashvalue % HashTableSize;

		return hashvalue;
	}

	size_t ComputeHashString2(int f, int b, std::string s) {
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
		size_t hashvalue = 0; //the value of the string's hash
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
				hashvalue += hashvalue & (m - 1);
				multiple += (multiple * g) & (m - 1);
			}
		else {
			int current = i;
			while (current < length) {
				//loop 10 times
				for (i = current; i < current + subdividelength; i++) {
					temp += (pow((((int)s[i] - (int)'a') + 1) + (((int)s[length - i - 1] - (int)'a') + 1), (i + 1)) * multiple);
					temp += temp & (m - 1);
					multiple += (multiple * g) & (m - 1);
				}
				current = current + subdividelength; //after one iteration current is at 10
				hashvalue += temp % ((m >> 1) - 1);
				temp = 0;
			}
		}
		return hashvalue & HashTableSize;
	}

	size_t ComputeHashString3(std::string S) {
		size_t hash = 0;
		size_t W = pow(2, 32);
		size_t a = pow(10, 9) + 9;
		size_t b = 1046527;
		for (int i = 0; i < CalculateStringLength(S); i++)
			hash += (b * (int)S[i]);
		hash = ((a * hash) % W) / (1 << (w-p));
		
		return hash % HashTableSize;
	}
}
