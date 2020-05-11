#include <iostream>

namespace UtilityFunctions {

	int CalculateStringLength(std::string);
	
	int CalculateStringLength(std::string s) {
		int length = 0;
		while (s[length] != '\0')
			length++;
		return length;
	}
}

void About();
void About() {
	std::cout << "======================================" << std::endl;
	std::cout << "|            About Lab 7             |" << std::endl;
	std::cout << "|------------------------------------|" << std::endl;
	std::cout << "|Programmer: Nicholas A. Orsini      |" << std::endl;
	std::cout << "|------------------------------------|" << std::endl;
	std::cout << "|This program demonstrates the use of|" << std::endl;
	std::cout << "|hash functions and hash tables.     |" << std::endl;
	std::cout << "|There are 3 different hashing funct-|" << std::endl;
	std::cout << "|ions implemented in this lab. 1 for |" << std::endl;
	std::cout << "|numerical entries and 2 for string  |" << std::endl;
	std::cout << "|entries. This means there is a total|" << std::endl;
	std::cout << "|of 3 hash tables and all utilize op-|" << std::endl;
	std::cout << "|en addressing with a singly linked  |" << std::endl;
	std::cout << "|list.                               |" << std::endl;
	std::cout << "======================================" << std::endl;
}
