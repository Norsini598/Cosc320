#ifndef READINS_H
#define READINS_H
#include "LinkedList.h"
#include "Point.h"


LinkedList<Vertex>* ReadDataIn(std::string filename = "DataPoints.txt");
void ReadDataIn(LinkedList<Vertex>* , std::string filename = "DataPoints.txt");

LinkedList<Vertex>* ReadDataIn(std::string filename) {
	LinkedList<Vertex>* list = new LinkedList<Vertex>;
	std::ifstream In;
	In.open(filename, std::ios::in);
	float x, y;
	Vertex* newpoint = new Vertex;
	//In >> i;
	int i = 0;
	while (!In.eof())
		/*for(int j =0 ; j < i; j++)*/ {
		i++;
		//std::cout << YELLOW << i << DEFAULT << std::endl;
		In >> x >> y;
		//std::cout << GREEN << x << ", " << y << DEFAULT << std::endl;
		newpoint->SetX(x);
		newpoint->SetY(y);
		list->AddNode(newpoint);
	}
	delete newpoint;
	return list;
}

void  ReadDataIn(LinkedList<Vertex>*  list, std::string filename) {
	std::ifstream In;
	In.open(filename, std::ios::in);
	float x, y;
	Vertex* newpoint = new Vertex;
	In >> x >> y;
	int i = 0;
	while (!In.eof())
		/*for(int j =0 ; j < i; j++)*/ {
		i++;
		//std::cout << YELLOW << i << DEFAULT << std::endl;
		In >> x >> y;
		//std::cout << GREEN << x << ", " << y << DEFAULT << std::endl;
		newpoint->SetX(x);
		newpoint->SetY(y);
		list->AddNode(newpoint);
	}
	delete newpoint;
}
#endif // !READINS_H

