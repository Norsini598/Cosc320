#include <iostream>
#include "EscapeSequences.h"

namespace Menus {

	const int MMO = 9; //main menu option
	
	const int CVO = 2; //create vertex options
	const int CEO = 2; //create edge options
	
	const int PALO = 2; //print adjacency lists options
	
	const int PBFSO = 2; //perform BFS options
	const int PDFSO = 2; //perform DFS options

	const int PTSO = 2; //perform Topo Sort options

	//first time prompt
	const std::string FirstTimePrompt = "|    Lab 12: FUN WITH GRAPHS     |\n| Programmer: Nicholas A.Orsini  |\n|================================|";

	const std::string MainMenuPromptOpen = "|           Main Menu            |\n|================================|";
	const std::string MainMenuMainPrompt = "| Select a corresponding option  |\n| 1. Create Vertices             |\n| 2. Create Edges                |\n| 3. Run Breadth First Search    |\n| 4. Run Depth First Search      |\n| 5. Print Topological Sort      |\n| 6. Print Adjacency List        |\n| 7. Print SCCs                  |\n| 8. Calculate Vertex Cover      |\n| 9. Quit                        |";

	const std::string CreateVertexPromptOpen = "|        Create Vertices         |\n|================================|";
	const std::string CreateVertexMainPrompt = "| 1. Add a vertex                |\n| 2. Return to Main Menu         |";

	const std::string PrintAdjacencyListPromptOpen = "|          Print Graph           |\n|================================|";
	const std::string PrintAdjacencyListMainPrompt = "| 1. Print Adjacency List        |\n| 2. Return to Main Menu         |";

	const std::string PerformBFSPromptOpen = "|  Perform Breadth First Search  |\n|================================|";
	const std::string PerformBFSMainPrompt = "| 1. Perform BFS                 |\n| 2. Return to Main Menu         |";

	const std::string CreateEdgePromptOpen = "|   Create Edges in the Graph    |\n|================================|";
	const std::string CreateEdgeMainPrompt = "| 1. Create an Edge              |\n| 2. Return to Main Menu         |";

	const std::string PerformDFSPromptOpen = "|   Perform Depth First Search   |\n|================================|";
	const std::string PerformDFSMainPrompt = "| 1. Perform DFS                 |\n| 2. Return to Main Menu         |";

	const std::string PrintTopoSortPromptOpen = "|   Print Topolgoical Sort       |\n|================================|";
	const std::string PrintTopoSortMainPrompt = "| 1. Perform Topo Sort           |\n| 2. Return to Main Menu         |";

	int Menu(std::string Open, int Optionnum, std::string Main = "");

	int Menu(std::string mainprompt, int options, std::string open) {
		short option = 0;
		int loop = 0;

		std::cout << open << std::endl;

		do {
			if (loop > 0)
				std::cout << "----------------------------------\n|" << RED << "         Invalid input!         " << DEFAULT << "|\n| Appropriate values:   (1 - " << options << ")  |\n|--------------------------------|" << std::endl;
			std::cout << mainprompt << std::endl;
			std::cout << "| Make Input: ";
			std::cin >> option;
			//error check
			while (!std::cin.good()) {
				//clear stream
				std::cin.clear();
				std::cin.ignore(INT8_MAX, '\n');
				//send back to the top
				option = MMO + 1;
			}
			loop++;
		} while (option < 1 || option > options);
		std::cout << std::endl;
		return option;
	}
}
