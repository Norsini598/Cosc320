#include "HashTable.h"
#include "Menus.h"
#include "HashFunctions.h"


int main() {
	using namespace Menus;
	using namespace HashFunctions;

	//Hash Tables
		//Number hash table
	HashTable<int> IntHT;
		//string hash table
	HashTable<std::string> StringHTs[stringhashes];

	//input nodes- used when calling "AddNode"
	Node<int> newnode1; 
	Node<std::string> newnode2; 

	//entry inputs
	int numentry = 0;
	std::string stringentry = "";
	char response = ' ';
	//menu continuation
	bool quit = false;
	bool integerquit = false;
	bool stringquit = false;
	bool optionquit = false;

	do {
		//reset variables
		integerquit = false;
		stringquit = false;
		optionquit = false;

		switch (MainMenu())
		{
		case 1:
			//integer menu
			do {
				switch (HashMenus::HashNumMenu())
				{
				case 1:
					//add another integer to the table
					std::cout << "Input a value: ";
					std::cin >> numentry;
					newnode1.data = numentry;
					newnode1.hashvalue = HashNum(numentry);
					newnode1.next = NULL;
					IntHT.AddNode(newnode1);
					break;
				case 2:
					//print the table
					IntHT.PrintTable();
					break;
				case 3: 
					//print integer hash table summary stats, currently just nodes in each list, more coming soon
					IntHT.PrintSummaryStats();
					break;
				case 4:
					//return to main menu
					integerquit = true;
					break;
				}
			} while (!integerquit);
			break;
//----------------------------------------------------------------------------------
		case 2:
			//string menu
			do {
				switch (HashMenus::HashStringMenu())
				{
				case 1:
					//hash another string
					/*
					has the same string for all implemented string hashes
					*/
					std::cout << "Input any string: ";
					std::cin >> stringentry;
					newnode2.data = stringentry;
					for (int i = 0; i < stringhashes; i++) {
						if (i == 0)
							newnode2.hashvalue = ComputeHashString1(stringentry);
						else if (i == 1)
							newnode2.hashvalue = ComputeHashString2(0, CalculateStringLength(stringentry) - 1, stringentry);
						std::cout <<"String's hash: " << newnode2.hashvalue << std::endl;
						newnode2.next = NULL;
						StringHTs[i].AddNode(newnode2);
					}
					break;
				case 2:
					//Print hash tables
					for (int i = 0; i < stringhashes; i++) {
						std::cout << "Table #" << i + 1 << std::endl;
						std::cout << "------------------------------" << std::endl;
					StringHTs[i].PrintTable();
					std::cout << "------------------------------" << std::endl << std::endl;
					
					//if not last iteration
					if (i != stringhashes - 1) {
						std::cout << "Hit Any Key to Continue: ";
						std::cin >> response;
					}
					std::cout << "------------------------------" << std::endl;

					}
					break;
				case 3:
					//Print tables summary stats
					for (int i = 0; i < stringhashes; i++) {
						std::cout << "Table #" << i + 1 << std::endl;
						std::cout << "------------------------------" << std::endl;
						StringHTs[i].PrintSummaryStats();
						std::cout << "------------------------------" << std::endl << std::endl;
						
						//if not last iteration
						if (i != stringhashes - 1) {
							std::cout << "Hit Any Key to Continue: ";
							std::cin >> response;
						}
						std::cout << "------------------------------" << std::endl;
					}
					break;
				case 4:
					//return to main menu
					stringquit = true;
					break;
				}
			} while (!stringquit);
			break;

		case 3:
			//options
			do {
				switch (OptionsMenu())
				{
				case 1:
					//about
					About();
					break;
				case 2:
					if (PrintHex)
						PrintHex = false;
					else
						PrintHex = true;
					break;
				case 3:
					optionquit = true;
					break;
				}
			} while (!optionquit);
			break;
		case 4:
			//quit
			quit = true;
			break;
		}
	} while (!quit);	
	/*
	No deletes to be called from main	
	*/
	return 0;
}