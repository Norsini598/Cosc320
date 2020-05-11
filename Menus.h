#include <iostream>
#include "EscapeSequences.h"

namespace Menus {

	//constants
	const int MMO = 5; //main menu option
	const int RFO = 2; //read from file options
	const int AVO = 4; //add vertex options
	const int OMO = 3; //options menu options
	const int PTO = 5; //print triangulation options
	const int DWwVO = 2; //do what with vertex options 
	const int StTO = 2; //stack to triangulation options

	//first time prompt
	const std::string FirstTimePrompt = "|      COSC CCCXX Project 3      |\n|     Delnauney Triangulation    |\n| Programmers: Nicholas A.Orsini |\n|        Sherene Phillip         |\n|================================|";

	//main menu
	const std::string MainMenuPromptOpen = "|           Main Menu            |\n|================================|";
	const std::string MainMenuMainPrompt = "| Select a corresponding option  |\n| 1. Add vertex                  |\n| 2. Print Triangulation         |\n| 3. Import Data                 |\n| 4. Options                     |\n| 5. Quit                        |";

	//option 1
	const std::string ReadFilePromptOpen = "|        Read From File        |\n|==============================|";
	const std::string ReadFileMainPrompt = "| 1. Read from custom .txt     |\n| 2. Return to Main Menu       | ";

	//option 2
	const std::string AddVertexPromptOpen = "|          Add Vertex           |\n|===============================|";
	const std::string AddVertexMainPrompt = "| 1. Move Vertex from Stack     |\n| 2. Construct Random Vertex    |\n| 3. Construct Custom Vertex    |\n| 4. Return to Main Menu        |";

	//optoin 3
	const std::string OptionsPromptOpen = "|           Options              |\n|================================|";
	const std::string OptionsMainPrompt = "| 1. About                       |\n| 2. Modify Radom Point Bounds   |\n| 3. Return to Main Menu         |";

	//optoin 4
	const std::string PrintTriangulationPromptOpen = "|          Print Options         |\n|================================|";
	const std::string PrintTriangulationPromptMain = "| 1. Triangulation in PreOrder   |\n| 2. Triangulation in PostOrder  |\n| 3. Triangulation in Order      |\n| 4. Print Vertices in Grid      |\n| 5. Return to Main Menu         |";

	const std::string DowhatwithVertexPromptOpen = "|      Do What With Vertex?     |\n|===============================|";
	const std::string DowhatwithVertexPromptMain = "| 1. Add to stack               |\n| 2. Add to triangulation       |";

	const std::string AddToTriangulationPromptOpen = "| Move Stack to Triangulation   |\n|===============================|";
	const std::string AddToTriangulationPromptMain = "| 1. Add Vertex to DT           |\n| 2. Return to Add Vertex Menu  |";

	//functions

	int Menu(std::string Open, int Optionnum, std::string Main = "");
	void About();
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

	void About() {
		char ans = ' ';
		std::cout << "                                A Brief About                                 " << std::endl;
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << "| This project demostrates properties of the Delaunary Triangulation (DT).   |" << std::endl;
		std::cout << "| DT is a unique and powerful method to construct triangulations due to      |   " << std::endl;
		std::cout << "| This is because of the Min-Max property, that enforces the triangulations  |" << std::endl;
		std::cout << "| to minimize the maximum angle. Given any quadrilateral there are two ways  | " << std::endl;
		std::cout << "| to split it into two unique triangles. Only one split is valid in the a DT.|" << std::endl;
		std::cout << "| The program reads data in from a file, from the user, or is randomly       |" << std::endl;
		std::cout << "| generated by the machine and can be inserted into a preexisting DT.        |" << std::endl;
		std::cout << "| The triangulation is stored in a Red Black Tree based on the center of a   |" << std::endl;
		std::cout << "| triangle's corresponding circle's X value.                                 |" << std::endl;
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << "| Input any key to continue: ";
		std::cin >> ans;
	}
}