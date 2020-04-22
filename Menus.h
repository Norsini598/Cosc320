#ifndef MENUS_H
#define MENUS_H
#include <iostream>
#include "Colors.h"

namespace Menus {
	int MainMenu();
	int PrintMenu();
	int MiscelaneousCheckingMenu();
	int InsertMenu();
	int OptionsMenu();

	void PrintHelp();
	void AboutMenu();
	void AboutRedBlackTrees();


	int PrintMenu()
	{
		short i = 0;
		bool quit = false;
		int option = 0;

		while (!quit) {
			option = 0;
			if (i == 0) {
				std::cout << "|         Print Menu          |" << std::endl;
				std::cout << "|Input a corresponding option |" << std::endl;
			}
			else
				std::cout << GREEN << "|Input a value between 1 and 5|" << DEFAULT << std::endl;
			std::cout << "-------------------------------" << std::endl;
			std::cout << "|1. In-Order Print            |" << std::endl;
			std::cout << "|2. Pre-Order Print           |" << std::endl;
			std::cout << "|3. Post-Order Print          |" << std::endl;
			std::cout << "|4. Print Help                |" << std::endl;
			std::cout << "|5. Return to Main Menu       |" << std::endl;
			std::cout << "|Make Input: ";
			std::cin >> option;
			if (option < 1 || option > 5) {
				quit = false;
				i++;
			}
			else
				quit = true;
		}
		return option;
	}

	int MainMenu()
	{
		short i = 0;
		bool quit = false;
		int option = 0;

		while (!quit) {
			option = 0;
			if (i == 0) {
				std::cout << "|          Main Menu          |" << std::endl;
				std::cout << "|Input a corresponding option |" << std::endl;
			}
			else
				std::cout << GREEN << "|Input a value between 1 and 6|" << DEFAULT << std::endl;
			std::cout << "-------------------------------" << std::endl;
			std::cout << "|1. Open Insert Elements Menu |" << std::endl;
			std::cout << "|2. Open Delete Elements Menu |" << std::endl;
			std::cout << "|3. Open Print Menu           |" << std::endl;
			std::cout << "|4. Miscellaneous Checking    |" << std::endl;
			std::cout << "|5. Options                   |" << std::endl;
			std::cout << "|6. Quit                      |" << std::endl;
			std::cout << "|Make Input: ";
			std::cin >> option;
			std::cout << option << std::endl;
			if (option < 1 || option > 6) {
				quit = false;
				i++;
			}
			else
				quit = true;
		}
		return option;
	}

	int MiscelaneousCheckingMenu()
	{
		short i = 0;
		bool quit = false;
		int option = 0;

		while (!quit) {
			option = 0;
			if (i == 0) {
				std::cout << std::endl;
				std::cout << "|  Miscellaneous Checking Menu |" << std::endl;
				std::cout << "| Input a corresponding option |" << std::endl;
			}
			else
				std::cout << GREEN << "|Input a value between 1 and 5|" << DEFAULT << std::endl;
			std::cout << "-------------------------------" << std::endl;
			std::cout << "|1. Input Value to Print Data |" << std::endl;
			std::cout << "|2. Return to Menu            |" << std::endl;
			std::cout << "|Make Input: ";
			std::cin >> option;
			if (option < 1 || option > 2) {
				quit = false;
				i++;
			}
			else
				quit = true;
		}
		return option;
	}

	int InsertMenu() {
		short i = 0;
		bool quit = false;
		int option = 0;

		while (!quit) {
			option = 0;
			if (i == 0) {
				std::cout << "|         Insert Menu         |" << std::endl;
				std::cout << "|Input a corresponding option |" << std::endl;
			}
			else
				std::cout << GREEN << "|Input a value between 1 and 3|" << DEFAULT << std::endl;
			std::cout << "-------------------------------" << std::endl;
			std::cout << "|1. Insert Single Element     |" << std::endl;
			std::cout << "|2. Insert Several Elements   |" << std::endl;
			std::cout << "|3. Return to Menu            |" << std::endl;
			std::cout << "|Make Input: ";
			std::cin >> option;
			if (option < 1 || option > 3) {
				quit = false;
				i++;
			}
			else
				quit = true;
		}
		return option;
	}

	int DeleteMenu()
	{
		short i = 0;
		bool quit = false;
		int option = 0;

		while (!quit) {
			option = 0;
			if (i == 0) {
				std::cout << "|         Delete Menu         |" << std::endl;
				std::cout << "|Input a corresponding option |" << std::endl;
			}
			else
				std::cout << GREEN << "|Input a value between 1 and 3|" << DEFAULT << std::endl;
			std::cout << "-------------------------------" << std::endl;
			std::cout << "|1. Delete Single Element     |" << std::endl;
			std::cout << "|2. Delete Whole Tree         |" << std::endl;
			std::cout << "|3. Return to Menu            |" << std::endl;
			std::cout << "|Make Input: ";
			std::cin >> option;
			if (option < 1 || option > 3) {
				quit = false;
				i++;
			}
			else
				quit = true;
		}
		return option;
	}

	int OptionsMenu()
	{
		short i = 0;
		bool quit = false;
		int option = 0;

		while (!quit) {
			option = 0;
			if (i == 0) {
				std::cout << "|          Options Menu           |" << std::endl;
				std::cout << "|   Input a corresponding option  |" << std::endl;
				std::cout << "-----------------------------------" << std::endl;
			}
			else
			std::cout << GREEN << "|  Input a value between 1 and 3  |" << DEFAULT << std::endl;
			std::cout << "-------------------------------" << std::endl;
			std::cout << "|1. Tell me about Red-Black Trees |" << std::endl;
			std::cout << "|2. About                         |" << std::endl;
			std::cout << "|3. Return to Menu                |" << std::endl;
			std::cout << "|Make Input: ";
			std::cin >> option;
			if (option < 1 || option > 3) {
				quit = false;
				i++;
			}
			else
				quit = true;
		}
		return option;
	}

	void PrintHelp()
	{
		std::cout << "|       About each print order       |" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "|In-Order Print Order:               |" << std::endl;
		std::cout << "|	Go Left -> Print Value -> Go Right |" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "|Pre-Order Print Order:              |" << std::endl;
		std::cout << "|	Print Value -> Go Left -> Go Right |" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "|Post-Order Print Order:             |" << std::endl;
		std::cout << "|	Go Left -> Go Right -> Print Value |" << std::endl;
		std::cout << std::endl;
	}

	void AboutMenu()
	{
		std::cout << "-------------------------------" << std::endl;
		std::cout << "|            About            |" << std::endl;
		std::cout << "-------------------------------" << std::endl;
		std::cout << "|Programmer: Nicholas A Orsini|" << std::endl;
		std::cout << "|This program demonstrates the|" << std::endl;
		std::cout << "|functions of a Red-Black tree|" << std::endl;
		std::cout << "|You can insert and  delete   |" << std::endl;
		std::cout << "|elements, and print the tree |" << std::endl;
		std::cout << "|usings the pre, post, and in |" << std::endl;
		std::cout << "|order print methods. When an |" << std::endl;
		std::cout << "|element is inserted or delet-|" << std::endl;
		std::cout << "|ed RBTree properties become  |" << std::endl;
		std::cout << "|violated, so fix up routines |" << std::endl;
		std::cout << "|are called to ensure the five|" << std::endl;
		std::cout << "|Red-Black Tree properties.   |" << std::endl;
		std::cout << "-------------------------------" << std::endl;
	}

	void AboutRedBlackTrees() {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "|    About  Red-Black  Trees      |" << std::endl;
		std::cout << "-----------------------------------" << std::endl; 
		std::cout << "| Red-Black Trees are a self-bal- |" << std::endl;
		std::cout << "| ancing type of Binary Search T- |" << std::endl;
		std::cout << "| ree. They do this by following  |" << std::endl;
		std::cout << "| five different propertires:     |" << std::endl;
		std::cout << "| 1. Nodes are red or black (blue |" << std::endl;
		std::cout << "|    in this case)                |" << std::endl;
		std::cout << "| 2. The root is black (blue)     |" << std::endl;
		std::cout << "| 3. Every leaf is NIL and blue   |" << std::endl;
		std::cout << "| 4. A red node has blue children |" << std::endl;
		std::cout << "| 5. Every nodes has a well-defi- |" << std::endl;
		std::cout << "|    ned black height             |" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}
}
#endif // !MENUS_H

