#include <iostream>
#include "Node.h"

//global functions


namespace Menus {
	
	int MainMenu();
	int OptionsMenu();
	
	int MainMenu() {
	bool quit = false;
	static int i = 0;
	int j = 0;
	int option = 0;
	do {
		if (i == 0) {
			std::cout << "====================================" << std::endl;
			std::cout << "|     Lab 7: Hashing Functions     |" << std::endl;
			std::cout << "|             Main Menu            |" << std::endl;
			std::cout << "------------------------------------" << std::endl;
			std::cout << "|       Select a valid option      |" << std::endl;
		}
		//called ever first entry but the actual very first
		else if (j == 0) {
			std::cout << "====================================" << std::endl;
			std::cout << "|             Main Menu            |" << std::endl;
			std::cout << "------------------------------------" << std::endl;
			std::cout << "|       Select a valid option      |" << std::endl;
		}
		else
			std::cout << "|    Input a proper value (1-4)    |" << std::endl;
		std::cout << "| 1. Open Integer Menu             |" << std::endl;
		std::cout << "| 2. Open String Menu              |" << std::endl;
		std::cout << "| 3. Options                       |" << std::endl;
		std::cout << "| 4. Quit                          |" << std::endl;
		std::cout << "| Make Input: ";
		std::cin >> option;
		std::cout << "------------------------------------" << std::endl;
		if (option < 1 || option > 4)
			quit = false;
		else
			quit = true;
		i++;
		j++;
	} while (!quit);
	if (j > 5)
		j = 0; // reset so user can be reprompted they on the main menu next time
	return option;
}
	
	
	int OptionsMenu() {
		bool quit = false;
		static int i = 0;
		int j = 0;
		int option = 0;
		do {
			if (i == 0) {
				std::cout << "====================================" << std::endl;
				std::cout << "|           Options Menu           |" << std::endl;
				std::cout << "------------------------------------" << std::endl;
				std::cout << "|       Select a valid option      |" << std::endl;
			}
			if(j > 0)
				std::cout << "|    Input a proper value (1-2)    |" << std::endl;
			std::cout << "| 1. About                         |" << std::endl;
			if(PrintHex)
				std::cout << "| 2. Turn off hexadecimal prints   |" << std::endl;
			else
				std::cout << "| 2. Turn on hexadecimal prints    |" << std::endl;
			std::cout << "| 3. Return to Main Menu           |" << std::endl;
			std::cout << "| Make Input: ";
			std::cin >> option;
			std::cout << "====================================" << std::endl;
			if (option < 1 || option > 3)
				quit = false;
			else
				quit = true;
			i++;
			j++;
		} while (!quit);
		return option;
	}

	namespace HashMenus {
		//Declarations:
		int HashNumMenu();
		int HashStringMenu();

		//Implementations:
		int HashNumMenu() {
			bool quit = false;
			int i = 0;
			int option = 0;
			do {
				if (i == 0) {
					std::cout << "====================================" << std::endl;
					std::cout << "|         Hash Integer Menu        |" << std::endl;
					std::cout << "------------------------------------" << std::endl;
					std::cout << "|       Select a valid option      |" << std::endl;
				}
				else
					std::cout << "|    Input a proper value (1-4)    |" << std::endl;
				std::cout << "| 1. Hash Another Integer          |" << std::endl;
				std::cout << "| 2. Print Integer Hash Table      |" << std::endl;
				std::cout << "| 3. Print Summary Stats of Table  |" << std::endl;
				std::cout << "| 4. Return to Main Menu           |" << std::endl;
				std::cout << "| Make Input: ";
				std::cin >> option;
				std::cout << "------------------------------------" << std::endl;
				if (option < 1 || option > 4)
					quit = false;
				else
					quit = true;
				i++;
			} while (!quit);
			return option;
		}

		int HashStringMenu() {
			bool quit = false;
			int i = 0;
			int option = 0;
			do {
				if (i == 0) {
					std::cout << "====================================" << std::endl;
					std::cout << "|         Hash String Menu         |" << std::endl;
					std::cout << "------------------------------------" << std::endl;
					std::cout << "|       Select a valid option      |" << std::endl;
				}
				else
					std::cout << "|    Input a proper value (1-3)    |" << std::endl;
				std::cout << "| 1. Hash Another String           |" << std::endl;
				std::cout << "| 2. Print String Hash Table       |" << std::endl;
				std::cout << "| 3. Print Summary Stats of Table  |" << std::endl;
				std::cout << "| 4. Return to Main Menu           |" << std::endl;
				std::cout << "| Make Input: ";
				std::cin >> option;
				std::cout << "------------------------------------" << std::endl;
				if (option < 1 || option > 4)
					quit = false;
				else
					quit = true;
				i++;
			} while (!quit);
			return option;
		}
	}
}
