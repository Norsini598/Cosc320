#include "DelaunayT.h"
#include "ReadIns.h"
#include "Menus.h"
#include <stdlib.h>
#include <ctime>
using namespace Menus;

int main() {
	srand(time(NULL));

	LinkedList<Vertex>* WaitingRoom = ReadDataIn();
	DelaunayT* thing = new DelaunayT;
	Vertex* A = NULL;
	Vertex* B = NULL;
	Vertex* C = NULL;
	Triangle* tri = NULL;

	int lowerbound = -20;
	int upperbound = 20;

	WaitingRoom->PrintList();
	int i = 0;
	i++;
	//while(WaitingRoom->GetNodesInList() > 0){
	for (int i = 0; i < 1; i++) {
		std::cout << "Reading in the first triangle: " << std::endl;
		A = WaitingRoom->GetHead();
		delete A;
		A = WaitingRoom->GetHead();
		B = WaitingRoom->GetHead();
		C = WaitingRoom->GetHead();
		std::cout << WaitingRoom->GetNodesInList() << " remain in waiting room " << std::endl;

		std::cout << *A << *B << *C << std::endl;

		tri = new Triangle(A, B, C);

		thing->Insert(tri);
		thing->PrintPreOder();
	}

	int option = 0;
	std::cout << FirstTimePrompt << std::endl;
	do {
		option = Menu(MainMenuMainPrompt, MMO, MainMenuPromptOpen);
		//imprt data
		if (option == 3) {
			do {
				option = Menu(ReadFileMainPrompt, RFO, ReadFilePromptOpen);
				char ans = ' ';
				if (option == 1) {
					bool cancel = false;
					std::string filename = " ";
					while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
						std::cout << "Do you wish to discard the current triangulation (Y/N): ";
						std::cin >> ans;
					}
					if (ans == 'Y' || ans == 'y') {
						thing->DeleteTriangulation();
					}
					ans = ' ';
					while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
						std::cout << WaitingRoom->GetNodesInList() << " remain in the stack." << std::endl;
						std::cout << "Do you wish to discard the current stack of vertices (Y/N): ";
						std::cin >> ans;
					}
					if (ans == 'Y' || ans == 'y') {
						WaitingRoom->EmptyList();
						delete WaitingRoom;
					}
					std::cout << "Input the name of your file space delimted x y data file WITHOUT \".txt\"" << std::endl;
					std::cout << "Or enter a 0 to cancel." << std::endl;
					std::cout << "Make input: ";
					std::cin >> filename;
					if (filename == "0")
						cancel = true;
					if (!cancel) {
						filename = filename + ".txt";

						if (ans == 'Y' || ans == 'y')
							ReadDataIn(filename);
						else
							ReadDataIn(WaitingRoom, filename);
					}
				}
			//else option == RFO
			} while (option != RFO);
			option = 0;
		}
		//create vertex
		else if (option == 1) {
			do {
				option = Menu(AddVertexMainPrompt, AVO, AddVertexPromptOpen);
				//stack to triangulation
				if (option == 1) {
					do {
						option = Menu(AddToTriangulationPromptMain, StTO, AddToTriangulationPromptOpen);
						if (option == 1) {
							A = WaitingRoom->GetHead();
							if (thing->FindPointStart(A))
								std::cout << RED << *A << " is already in the triangulation it it being discarded." << DEFAULT << std::endl;
							else
								thing->Insert(A);
							delete A;
						}
					} while (option != StTO && WaitingRoom->GetNodesInList() > 0);

					if (WaitingRoom->GetNodesInList() == 0)
						std::cout << "Stack Now Empty. Try Creating or generating some vertices. " << std::endl;
					else
						std::cout << WaitingRoom->GetNodesInList() << " vertices remain in the stack. " << std::endl;
				}
				//generate random vertex
				else if (option == 2) {
					std::cout << "Generating random vertex between " << lowerbound << " and " << upperbound << std::endl;
					std::cout << "------------------------------------------" << std::endl;
					Vertex* newvert = new Vertex;
					int i = 0;
					do {
						if(i > 0)
							std::cout << "Point in triangulation already, generating new vertex." << std::endl;
						int x = rand() % (upperbound + abs(lowerbound)) + lowerbound;
						int y = rand() % (upperbound + abs(lowerbound)) + lowerbound;
						newvert->SetX(x);
						newvert->SetY(y);
						i++;
					} while (thing->FindPointStart(newvert));

					option = Menu(DowhatwithVertexPromptMain, DWwVO, DowhatwithVertexPromptOpen);
					if (option == 1)
						WaitingRoom->AddNode(newvert);
					else
						thing->Insert(newvert);
					delete newvert;
				}
				//generate custom vertex
				else if (option == 3) {
					Vertex* newvert = new Vertex;
					float X = 0;
					float Y = 0;
					do {
						std::cout << "Input an X value: ";
						std::cin >> X;
						newvert->SetX(X);
						std::cout << "Input a Y value: ";
						std::cin >> Y;
						newvert->SetY(Y);

					} while (thing->FindPointStart(newvert));

					option = Menu(DowhatwithVertexPromptMain, DWwVO, DowhatwithVertexPromptOpen);
					if (option == 1)
						WaitingRoom->AddNode(newvert);
					else
						thing->Insert(newvert);
					delete newvert;
				}
			} while (option != AVO);
			option = 0;
		}
		//print triangulation
		else if (option == 2) {
			do {
				option = Menu(PrintTriangulationPromptMain, PTO, PrintTriangulationPromptOpen);
				if (option == 1)
					thing->PrintPreOder();
				else if (option == 2)
					thing->PrintPostOder();
				else if (option == 3)
					thing->PrintInOder();
				else if (option == 4)
					thing->Print();
			} while (option != PTO);
			option = 0;
		}
		//options menu
		else if (option == 4) {
			do {
				option = Menu(OptionsMainPrompt, OMO, OptionsPromptOpen);
				if (option == 1)
					About();
				else if (option == 2) {
					std::cout << "Current Lower Bound: " << lowerbound << std::endl;
					std::cout << "Current Upper Bound: " << upperbound << std::endl;
					int i = 0;
					do {
						if (i > 0) {
							std::cout << "Upperbound must be greater than lower bound." << std::endl;
							std::cout << "Also the two must be at least 20 digits apart." << std::endl;
						}
						std::cout << "Input a new Lower Bound: ";
						std::cin >> lowerbound;
						std::cout << "Input a new Upper Bound: ";
						std::cin >> upperbound;
						i++;
					} while (upperbound < lowerbound || upperbound - lowerbound < 20);
				}
			} while (option != OMO);
			option = 0;
		}
		//else option == 5
	} while (option != MMO);
	
	delete thing; //DT
	delete WaitingRoom; //points to be added
	
	return 0;
}