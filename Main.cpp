#include "Menus.h"
#include "MiscFunctions.h"
#include "BinaryTree.h"

#include <fstream>
#include <chrono>

using namespace Menus;
using namespace MiscFunctions;

int main() {

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

	BinaryTree<int> Tree; //Our tree
	TreeNode<int> NewNode; //used for adding new elements
	TreeNode<int>* FindNode; //used for case 4. Misc checking

	int value = 0;
	int num1 = 0; //takes misc uses like number of entries or deletes in bulk
	int num2 = 0; //used to store numnode while it changes
	do {
		printstop = false;
		misccheckstop = false;
		insertstop = false;
		deletestop = false;
		optionsmenustop = false;
		
		ans = ' ';
		value = 0; //reset for no reason
		num1 = 0;

		manualentry = false;

		switch (MainMenu())
		{
			//insert elements
		case 1:
			do {
				//reset required for:
				num1 = 0;
				ans = ' ';
				manualentry = false;
				switch (InsertMenu())
				{
					//insert single element
				case 1:
					std::cout << "Input a value for the binary search tree to store: ";
					std::cin >> value;
					//prep newnode for insertion
					NewNode.key = value;
					NewNode.count = 0;
					NewNode.Parent = NULL;
					NewNode.LChild = NULL;
					NewNode.RChild = NULL;
					//put into the BST
					Tree.Insert(&NewNode); //timed inside
					
				break;
					//Insert many elements
				case 2:
					num2 = Tree.GetNumNode(); //store number of nodes in tree before beginning inserts
					while (num1 < 1) {
						std::cout << "Input the number of elements that will be added to the binary search tree: ";
						std::cin >> num1;
					}
					do {
						std::cout << "Enter a 1 for manual entry or 0 to use random values: ";
						std::cin >> value;
					} while (value < 0 || value > 1);

					if (value == 1)
						manualentry = true;
					while(Tree.GetNumNode() < num1+num2){
						//prep newnode for insertion
						if (manualentry) {
							std::cout << "Input a value to add to the tree: ";
							std::cin >> value;
						}
						else {
							value = GetRandomNumber(-10000000, (num1 + num2) * 10000000);
						}

						NewNode.key = value;//use default values
						NewNode.count = 0;
						NewNode.Parent = NULL;
						NewNode.LChild = NULL;
						NewNode.RChild = NULL;
						//put into the BST
						Tree.Insert(&NewNode);						
						//resets
					}
				break;
					//return to menu
				case 3:
					insertstop = true;
					break;
				}//end switch
				if (!insertstop) {
					while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
						std::cout << "Do you want to print the tree (Y/N): ";
						std::cin >> ans;
					}
					if (ans == 'Y' || ans == 'y') {
						std::cout << "Pre-Order Print" << std::endl;
						Tree.PrintPreOrder(Tree.GetRoot());
					}
				}
			} while (!insertstop);
		break;
			//delete elements
		case 2:
			do {
				ans = ' ';
				if (Tree.GetRoot() == NULL)
					std::cout << "The Binary Tree is empty. Try inserting an element." << std::endl;
				else {
					num1 = DeleteMenu();
					if (num1 == 1) {
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
						if (Tree.Search(value)) {

							Tree.Delete(value);
							if (Tree.GetRoot() != NULL) {
								std::cout << "Pre-Order Print" << std::endl;
								Tree.PrintPreOrder(Tree.GetRoot());
							}
							else
								std::cout << "Tree now empty." << std::endl;
						}
						else
							std::cout << "Value not in list" << std::endl;
					}
					//empty whole tree
					else if (num1 == 2)
						Tree.EmptyTree();
					//stop deleting
					else
						deletestop = true;
				}
			} while (!deletestop && Tree.GetRoot() != NULL);//need to want to be here and need a tree to let you int
		break;
			//Print Menu
		case 3:
			do {
				switch (PrintMenu())
				{
				//in order
				case 1:
					if (Tree.GetRoot())
						Tree.PrintInOrder(Tree.GetRoot());
					else
						std::cout << "Empty Tree" << std::endl;
					break;
				//pre order
				case 2:
					if (Tree.GetRoot())
						Tree.PrintPreOrder(	Tree.GetRoot());
					else
						std::cout << "Empty Tree" << std::endl;
					break;
				//post order
				case 3:
					if (Tree.GetRoot())
						Tree.PrintPostOrder(Tree.GetRoot());
					else
						std::cout << "Empty Tree" << std::endl;
					break;
				//print help
				case 4:
					PrintHelp();
					break;
				case 5:
					printstop = true;
				}
			} while (!printstop);
		break;
			//Misc Tests
		case 4:
			if (Tree.GetRoot()) {
				do {
					switch (MiscelaneousCheckingMenu())
					{
						//print stats
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
						//return to menu
					case 2:
						misccheckstop = true;
						break;
					}
				} while (!misccheckstop);
			}
			else
				std::cout << "Empty Tree." << std::endl;
		break;
			//options menu
		case 5:
			do {
				switch (OptionsMenu(Tree.GetDuplicantRule()))
				{
					//turn on/off duplicant rule
				case 1:
					if (Tree.GetDuplicantRule())
						Tree.SetDuplicantRule(false);
					else
						Tree.SetDuplicantRule(true);
					break;
				case 2:
					AboutMenu();
					break;
					//return to menu
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



	return 0;
}