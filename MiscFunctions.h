#include <iostream>
#include <cstdlib>
#include <ctime>

namespace MiscFunctions {
	
	int GetRandomNumber(int = -100000, long = 200000);
	int CalculateStringLength(std::string);


	int GetRandomNumber(int low, long range) {
		return rand() % (range) + low;//values between -100000 and 100000
	}
	int CalculateStringLength(std::string s) {
		int length = 0;
		while (s[length] != '\0')
			length++;
		return length;
	}
}
