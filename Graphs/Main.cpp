#include "Edge.h"
#include "Graph.h"
#include "Menus.h"
#include "EscapeSequences.h"

int main() {
	using namespace Menus;
	srand(time(NULL));

	Graph<int>* G1 = new Graph<int>;
	int input = 0;
	int val = 0; //miscelaneously used variable 1
	int option = 0; //user selection
	char ans = ' ';

//-----------------------------------------------------------------------------------------------------------
	do {
		std::cout << "Do you wish to import a premade graph? (Y/N): ";
		std::cin >> ans;
	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
	if (ans == 'y' || ans == 'Y')
		G1->ReadConnectionsFromFile();
	G1->CheckIfDAG();
	std::cout << FirstTimePrompt << std::endl;

	do {
		val = 0;
		ans = ' ';

		option = Menu(MainMenuMainPrompt, MMO, MainMenuPromptOpen);

		//create vertices
		if (option == 1) {
			int to = 0, fro = 0;
			do {
				to = fro = 0;
				bool in = false;

				option = Menu(CreateVertexMainPrompt, CVO, CreateVertexPromptOpen);
				if (option == 1) {
					std::cout << "Input a value for a vertex to add to your graph: ";
					std::cin >> val;
					G1->AddVertex(val);
					//if there are multiple veritces, allow the user to add an edge now
					if (G1->GetVertexCount() != 1) { //i.e more than one node, ask if theyd like to make an edge
						do {
							std::cout << "Do you want to add an edge to your graph (Y/N) ";
							std::cin >> ans;
						} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
						if (ans == 'Y' || ans == 'y') {
							std::cout << "These are all of the vertices in your graph: " << std::endl;
							G1->PrintVertices();
							G1->AssistConnections();						
						}
					}
				}
				//else(option == CVO)
			} while (option != CVO);
		}
		//create an edge
		else if (option == 2) {
			do {
				option = Menu(CreateEdgeMainPrompt, CEO, CreateEdgePromptOpen);
				//create edge
				if (option == 1) {
					if (G1->GetVertexCount() > 1) { //i.e more than one node, ask if theyd like to make an edge
						std::cout << "These are all of the vertices in your graph: " << std::endl;
						G1->PrintVertices();
						G1->AssistConnections();
					}
				}
				//else(option == CEO)
			} while (option != CEO);
		}

		//Run BFS
		else if (option == 3) {
			int val = 0;
			do {
				option = Menu(PerformBFSMainPrompt, PBFSO, PerformBFSPromptOpen);
				if (option == 1) {
					bool in = false;
					if (G1->GetVertexCount() > 0) {
						std::cout << "These are all of the vertices in your graph: " << std::endl;
						G1->PrintVertices();
						int i = 0;
						do {
							if (i > 0)
								std::cout << "Enter a valid vertex to perform BFS on: ";
							else
								std::cout << "BFS on ";
							std::cin >> input;
							i++;
						} while (!(*G1 == input));
						G1->BFS(input);
					}
					else
						std::cout << YELLOW << "There are no vertices in this graph!" << DEFAULT << std::endl;
				}
				//else(option == PBFSO)
			} while (option != PBFSO);
		}

		//Run DFS
		else if (option == 4) {
			do {
				option = Menu(PerformDFSMainPrompt, PDFSO, PerformDFSPromptOpen);
				if (option == 1) {
					if (G1->GetVertexCount() > 0) {
						std::cout << "These are all of the vertices in your graph: " << std::endl;
						G1->PrintVertices();
						int i = 0;
						do {
							if (i > 0)
								std::cout << "Enter a valid vertex to perform DFS on: ";
							else
								std::cout << "DFS on ";
							std::cin >> input;
							i++;
						} while (!(*G1 == input));
						G1->CheckIfDAG();
						G1->DFS(input);
					}
					else
						std::cout << YELLOW << "There are no vertices in this graph!" << DEFAULT << std::endl;
				}
				//else(option == PDFSO)
			} while (option != PDFSO);
		}

		//Print TopoLogicalSort
		else if (option == 5) {
			do {
				option = Menu(PrintTopoSortMainPrompt, PTSO, PrintTopoSortPromptOpen);
				if (option == 1) {
					if (G1->GetVertexCount() > 0) {
						/*std::cout << "These are all of the vertices in your graph: " << std::endl;
						G1->PrintVertices();
						int i = 0;
						do {
							if (i > 0)
								std::cout << "Enter a valid vertex to perform a topo sort on: ";
							else
								std::cout << "Topo Sort on ";
							std::cin >> input;
							i++;
						} while (!(*G1 == input));
						G1->DFS(input);
						*/
						G1->TopoSort();
					}
					else
						std::cout << YELLOW << "There are no vertices in this graph!" << DEFAULT << std::endl;

				}
			} while (option != PTSO);
		}

		//print adjacency list
		else if (option == 6) {
			do {
				option = Menu(PrintAdjacencyListMainPrompt, PALO, PrintAdjacencyListPromptOpen);
				if (option == 1) {
					G1->PrintAdjacencyList();
				}
				//else(option == PALO)
			} while (option != PALO);
		}

		else if (option == 7)
		{
			/*std::cout << "Printing Strongly Connected Components: " << std::endl;
			G1->PrintStronglyConnectedComponents();*/
			std::cout << "Doesn't Work!" << std::endl;
		}
		else if (option == 8) {
			G1->CalculateVectorCover1();
		}
		//else(option == MMO)

	} while (option != MMO);

	std::cout << "Goodbye!" << std::endl;
	
	G1->EmptyGraph();
	delete G1;

	return 0;
}