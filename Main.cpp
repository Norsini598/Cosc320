#include <iostream>
#include "RedBlueTree.h"
#include "Menus.h"
#include "MiscFunctions.h"

using namespace Menus;
using namespace MiscFunctions;

int main(){
	srand(time(NULL));

	//menus loopers
	bool stop = false;
	bool printstop = false;
	bool misccheckstop = false;
	bool insertstop = false;
	bool deletestop = false;
	bool optionsmenustop = false;

	bool manualentry = false;
	char ans = ' ';
	
	RedBlueTree<int> Tree; //The holy tree. Alas! Thy world hast brought life.
	TreeNode<int>* FindNode; //used for case 4: misc checking
	
	int value = 0;
	int num1 = 0; //takes misc uses like number of entries or deletes in bulk
	int num2 = 0; //used to store numnode while it changes
	int q = 0;
	do {
		//reset menu items
		printstop = misccheckstop = insertstop = deletestop = optionsmenustop = false;
		ans = ' ';
		value = q = num1 = num2 = 0;

		switch (MainMenu())
		{
			//insert elements
		case 1:
			do {
				switch (InsertMenu())
				{
				//insert single item
				case 1:
					std::cout << "Input a value for the binary search tree to store: ";
					std::cin >> value;
					Tree.Insert(value); //add value to the Red Black tree
				break;
				//insert several items
				case 2:
					num2 = Tree.GetNumNode(); //store number of nodes in tree before beginning inserts
					q = 0;
					do {
						if (q > 0)
							std::cout << "Input a positive value: ";
						else
							std::cout << "Input the number of node you want to add to your Red Blue Tree: ";
						std::cin >> num1;
						q++;
					} while (num1 < 1);
					
					do {
						std::cout << "Enter a 1 for manual entry or 0 to use random values: ";
						std::cin >> value;
					} while (value < 0 || value > 1);

					if (value == 1)
						manualentry = true;

					while (Tree.GetNumNode() < num1 + num2) {
						//prep newnode for insertion
						if (manualentry) {
							std::cout << "Input a value to add to the tree: ";
							std::cin >> value;
						}
						else 
							value = GetRandomNumber(-100000, 100000);
						Tree.Insert(value);
					}
					break;
				//quit insert
				case 3: 
					insertstop = true;
					break;
				}
			} while (!insertstop);
			
			while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
				std::cout << "Do you want to print the tree (Y/N): ";
				std::cin >> ans;
			}
			if (ans == 'Y' || ans == 'y') {
				std::cout << "Pre-Order Print" << std::endl;
				Tree.PrintPreOrder(Tree.GetRoot());
			}
		break;
		
		//delete elements
		case 2:
			do {
				if (Tree.GetNumNode() != 0) {
				ans = ' ';
					switch (DeleteMenu())
					{
						//delete single item
					case 1:
						std::cout << "Remove a Node" << std::endl;
						std::cout << "-------------" << std::endl;
						while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
							std::cout << "Do you want to print the tree (Y/N): ";
							std::cin >> ans;
						}
						if (ans == 'Y' || ans == 'y') {
							std::cout << "Pre-Order Print" << std::endl;
							Tree.PrintPreOrder(Tree.GetRoot());
						}
						std::cout << "Input the value of the node you want to remove: ";
						std::cin >> value;
						//value must be in the tree
						if (Tree.Search(value)) {
							Tree.Delete(value);
							if (Tree.GetNumNode() != 0) {
								std::cout << "Updated Tree: " << std::endl;
								Tree.PrintPreOrder(Tree.GetRoot());
							}
							else
								std::cout << "The tree is now empty. " << std::endl;
						}
						else
							std::cout << "Value not in the tree!" << std::endl;
						break;
						//delete whole tree
					case 2:
						Tree.EmptyTree();
						std::cout << "Tree Emptied. " << std::endl;
						break;
						//quit delete
					case 3:
						deletestop = true;
						break;
					}
				}
				else {
					std::cout << YELLOW << "Empty Tree! Try inserting an element. " << DEFAULT << std::endl;
					deletestop = true;
				}
			} while (!deletestop);
		break;
		
		//print menu
		case 3:
			do {
				switch (PrintMenu())
				{
				//in order
				case 1:
					Tree.PrintInOrder(Tree.GetRoot());
					break;
				//Pre order
				case 2:
					Tree.PrintPreOrder(Tree.GetRoot());
					break;
				//post order
				case 3:
					Tree.PrintPostOrder(Tree.GetRoot());
					break;
				//print help
				case 4:
					PrintHelp();
					break;
				//quit
				case 5:
					printstop = true;
					break;
				}
			} while (!printstop);
		break;
		
		//misc checking
		case 4:
			if (Tree.GetNumNode() != 0) {
				do {
					switch (MiscelaneousCheckingMenu())
					{
						//misc check a value
					case 1:
						std::cout << "Input a value in your tree to print data on it: ";
						std::cin >> value;
						if (Tree.Search(value)) {
							FindNode = Tree.GetNode(value);
							Tree.PrintNodeData(FindNode);
						}
						else
							std::cout << "This node is not in the binary search tree." << std::endl;
						break;
						//quit
					case 2:
						misccheckstop = true;
						break;
					}
				} while (!misccheckstop);
			}
			else
				std::cout << YELLOW << "Empty Tree" << DEFAULT << std::endl;
		break;
		
		//options
		case 5:
			do {
				switch (OptionsMenu())
				{
				case 1:
					AboutRedBlackTrees();
					break;
				case 2:
					AboutMenu();
					break;
				case 3:
					optionsmenustop = true;
					break;
				}
			} while (!optionsmenustop);
			break;
		
			//quit
		case 6:
			stop = true;
			break;
		}



	} while (!stop);

	std::cout << "Good bye!" << std::endl;

	return 0;
}