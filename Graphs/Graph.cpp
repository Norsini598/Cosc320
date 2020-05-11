#include "Graph.h"
#include "EscapeSequences.h"
#include <stdlib.h>
#include <time.h>


template<typename T>
Graph<T>::Graph() {
	char ans = ' ';
	graph = new RedBlueTree<Vertex<T>>;
	VertexCount = 0;

	//user defines if this is a directed graph
	do {
		std::cout << "Is this a directed graph? (Y/N): ";
		std::cin >> ans;
	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
	if (ans == 'Y' || ans == 'y') {
		isDirected = true;
		isDAG = true; //has not violated the DAG rule, yet. Acyclic and directed
	}
	else {
		isDirected = false;
		isDAG = false;
	}

	isAcyclic = true; //no cycles yet.
	checkedDAG = false;
}

template<typename T>
Graph<T>::Graph(bool a) {
	graph = new RedBlueTree<Vertex<T>>;
	VertexCount = 0;

	if(a){
		isDirected = true;
		isDAG = true; //has not violated the DAG rule, yet. Acyclic and directed
	}
	else {
		isDirected = false;
		isDAG = false;
	}

	isAcyclic = true; //no cycles yet.
	checkedDAG = false;
}

template<typename T>
Graph<T>::Graph(Graph<T>& copy) {
	graph = new RedBlueTree<Vertex<T>>;
	VertexCount = copy.VertexCount;

	isDirected = copy.isDirected;
	isDAG = copy.isDAG;
	isAcyclic = copy.isAcyclic; //no cycles yet.
	checkedDAG = copy.checkedDAG;
}

template<typename T>
Graph<T>::~Graph() {
	graph->EmptyTree();
	delete graph;
	graph = NULL;
}

template<typename T>
void Graph<T>::RecolorAllWhite() {
	TreeNode<Vertex<T>>* temp = graph->Root;
	if (graph) {
		if (graph->Root != graph->NIL) {
			graph->Root->key.SetWhite();//set this node white
			//and prepare the recursive call to all of its children
			MakeWhite(graph->Root->LChild);
			MakeWhite(graph->Root->RChild);
		}
	}
}

template<typename T>
void Graph<T>::MakeWhite(TreeNode<Vertex<T>>* obj) {
	//recursively make all vertices in the tree white
	if (obj != graph->NIL) {
		obj->key.SetWhite();
		MakeWhite(obj->LChild);
		MakeWhite(obj->RChild);
	}
}

template<typename T>
void Graph<T>::AddVertex(T d) {
	bool again = false;
	do {
		if (graph) {
			again = false;
			//if not in the graph
			Vertex<T> temp(d); //create a vertex
			std::cout << temp << std::endl; //print that vertex
			if (!(graph->Search(temp))) {
				VertexCount++;
				graph->Insert(temp);
				checkedDAG = false;
			}
			else
				std::cout << RED << "Sorry, that vertex is already in the graph! " << DEFAULT << std::endl;
		}
		else {
			graph = new RedBlueTree<Vertex<T>>;
			again = true;
		}
	} while (again);
}

template<typename T>
void Graph<T>::PrintAdjacencyList() {
	if (graph->Root != graph->NIL && graph->Root != NULL) {
		std::cout << "There are " << graph->Nodenum << " vertices in this graph. " << std::endl;
		PAL(graph->GetRoot());
	}
	else {
		std::cout << YELLOW << "The Graph Is Empty, Try Inserting Two Vertices." << DEFAULT << std::endl;
	}
}

template<typename T>
void Graph<T>::PAL(TreeNode<Vertex<T>>* obj) {
	if (obj != graph->NIL) {
		std::cout << obj->key << std::endl;
		PAL(obj->LChild);
		PAL(obj->RChild);
	}
}

template<typename T>
void Graph<T>::SimplePrint() {
	std::cout << VertexCount << std::endl;
	graph->PrintPreOrder(graph->Root);
}

template<typename T>
void Graph<T>::PrintVertices() {
	if (graph) {
		std::cout << "Vertices in the graph: " << std::endl;
		graph->PrintInOrder(graph->Root); //print all vertices in order
	}
	else
		std::cout << "No vertices in this graph!" << std::endl;
}

template<typename T>
void Graph<T>::RemoveVertex(T obj) {
	/*First remove the vertex from all it connected vertices
	  all vertices connected to obj must no longer be connected to obj
	  Then remove it from the tree

	  obj is a vertex data
	*/
	//to get all of the values (vertices) that obj is connected to
	//if obj is in the graph
	if (*this == obj) {
		if (graph->Root->key == obj) {
			//do nothing
		}
		else
			graph->Root->key - obj;
		RemoveVertex(graph->Root->LChild, obj);
		RemoveVertex(graph->Root->RChild, obj);
		
		graph->Delete(obj); //delete this value from the stored vertices
	}
}

//recursive call to traverse the tree
template<typename T>
void Graph<T>::RemoveVertex(TreeNode<Vertex<T>>* obj, T pbj) {
	if (obj != graph->NIL && obj) { //not NIL and not null
		if (obj->key == pbj) {
			//do nothing
			//cant remove self from self
		}
		else
			obj->key - pbj;
		RemoveVertex(obj->LChild, pbj);
		RemoveVertex(obj->RChild, pbj);
	}
}

template<typename T>
void Graph<T>::operator-(T obj) {
	RemoveVertex(obj);
}

//add a vertex to the graph, has no edges yet
template<typename T>
void Graph<T>::operator+(T obj) {
	AddVertex(obj);
}

//is this value in the graph?
template<typename T>
bool Graph<T>::operator==(const T obj) {
	Vertex<T>* temp = Find(obj); //return the vertex associated with obj
	bool r = false;
	if (temp)
		r = true;
	return r;
}

//starter- given a vertex value, find that vertex
template<typename T>
Vertex<T>* Graph<T>::Find(const T obj) {
	/*
	Search the tree, at every tree node search if that tree node key's vertex contains obj
	*/
	Vertex<T>* returnval = NULL;
	if (graph) { //if graph is created
		if (graph->Root != graph->NIL) { //if root is not NIL
			if (graph->Root->key.GetData() == obj)
				returnval = &(graph->Root->key);
			else{
				returnval = Find(graph->Root->RChild, obj);
				if (returnval == NULL) //if not found by going right
					returnval = Find(graph->Root->LChild, obj);
			}
		}
	}
	return returnval;
}

//recursive friendly function
template<typename T>
Vertex<T>* Graph<T>::Find(TreeNode<Vertex<T>>* obj, T pbj) {
	Vertex<T>* returnval = NULL;
	if (obj != graph->NIL) {
		if (obj->key.GetData() == pbj)
			returnval = &(obj->key);
		else {
			returnval = Find(obj->RChild, pbj);
			if (returnval == NULL)
				returnval = Find(obj->LChild, pbj);
		}
	}
	return returnval;
}

//THE USER FRIENDLY FUNCTION!!!!!!!!!!!
template<typename T>
Vertex<T>* Graph<T>::operator[](const T searchfor) {
	Vertex<T>* temp = NULL;
	//only works if vertex in graph
	temp = Find(searchfor);
	//some exception would have to be thrown if not in the graph, what should be done???? can't return 0
	return temp;
}

template<typename T>
void Graph<T>::AddUndirectedConnection(const T to, const T from) { //nondirected edge (goes both directions)
	Vertex<T>* t = (*this)[to];
	Vertex<T>* f = (*this)[from];
	if (t && f) {
		//if there is not a connection in place already
		if (!(f->IsConnected(to)))
			f->AddConnection(to, 1);
		else
			std::cout << from << " and " << to << " were already connected." << std::endl;

		//if there is not a connection in place already
		if(!(t->IsConnected(from)))
			t->AddConnection(from, 1);
		else
			std::cout << to << " and " << from << "were already connected." << std::endl;
	}
	else {
		if (t == NULL)
			std::cout << t << " is not in the graph." << std::endl;
		if (f == NULL)
			std::cout << f << " is not in the graph." << std::endl;
	}
}

template<typename T>
void Graph<T>::AddDirectedConnection(const T to, const T from) {
	//ask user about distance -- NEEDS TO BE DONE ASP (at some point)
	Vertex<T>* t = (*this)[to];
	Vertex<T>* f = (*this)[from];
	if (t && f) {
		if(f->Empty())
			f->AddConnection(to); //passing "int"
		else if(!(f->IsConnected(to)))
			f->AddConnection(to); //passing "int"
		else
			std::cout << to << " and " << from << " were already connected." << std::endl;
	}
	else {
		if (t == NULL)
			std::cout << to << " is not in the graph." << std::endl;
		if (f == NULL)
			std::cout << from << " is not in the graph." << std::endl;
	}
}

//remove the connection between "to" and "from"
template<typename T>
void Graph<T>::RemoveConnection(const T to, const T from) {
	Vertex<T>* t = (*this)[to];
	Vertex<T>* f = (*this)[from];
	if (t && f) {
		if (t->IsConnected(from))
			t->RemoveConnection(from);
		else
			std::cout << "Error! " << t << " is not connected to " << f << "!" << std::endl;
	}
	else {
		if (t == NULL)
			std::cout << to << " is not in the graph." << std::endl;
		if (f == NULL)
			std::cout << from << " is not in the graph." << std::endl;
	}
}

template<typename T>
void Graph<T>::BFS(const T startval) {
	Vertex<T>* start = (*this)[startval];
	
	if (start) {
		/*
		Make a queue: add start to the queue, visit all neighbors increase distance, set parent of these
		need an i to correspond to a vertex data
		*/

		//INTIAL SETUP: distance, parents, and vertex values need to correspond with an i

		std::queue<T> Queue; //just store vertex values- not the vertex itself

		T parent[VertexCount];
		int distance[VertexCount]; //stores all the distance of all vertices from startval
		int vertices[VertexCount];

		//initialize all of the vertices
		for (int i = 0; i < VertexCount; i++) {
			int j = 0;
			graph->ConverttoArray(graph->Root, vertices, j);
			//initialize distance[]
			if (vertices[i] == startval)
				distance[i] = 0; //distance to self is 0
			else
				distance[i] = -1; //distance to all other vertices is -1 at the moment
			parent[i] = -1;
		}
		//--------------------------------------------------------------------------------------------------------------------
		std::ofstream Out;
		
		Out.open("BFSTimes.txt", std::ios::app);
		auto strt = std::chrono::system_clock::now();
		//dont need a color array, that data is in vertex
		Queue.push(startval);
		start->SetGray();//visited by not finished
		while (!Queue.empty()) {
			
			T wasfront = Queue.front();//store the previous front
			Queue.pop();			
			Vertex<T>* dequeuedvert = (*this)[wasfront]; //check dequeuedvert's connections. returns a pointer to wasfront vertex
			Vertex<T>* temp2 = NULL; //pointer to the vertex of dequeuedvert's ith connection
			
			//for all vertices connected to dequeuedvert
			for (int i = 0; i < dequeuedvert->GetNodesInList(); i++) {
				T* t = dequeuedvert->GetIthConnection(i); //a pointer to the value at the ith connection
				//if there is an ith connection t is nonNull
				if (t) {
					temp2 = (*this)[*t]; //pointer to the vertex with t as its data
					
					//if non visited vertex
					if (temp2->GetColor() == WHite) {
						temp2->SetGray(); //is visited
						
						//find this vertex's location in the arrays storing BFS data
						for (int i = 0; i < VertexCount; i++) {
							if (vertices[i] == *t) { //foud the ith vertex value 
								//corresponding with wasfront vertex (dequeuedvert)
								for (int j = 0; j < VertexCount; j++) {
									//now do the same with the partent (wasfront)
									if (vertices[j] == wasfront) {
										distance[i] = distance[j] + dequeuedvert->GetDistance(*t);//add the distance between temp2 and dequeuedvert
										//just realized there is no check to ensure the distance (if 2 directed connections) are the same
										//threfore the distance from A to B could be 1 but B to A 5 LOL
										parent[i] = wasfront;
										Queue.push(*t); //add this vetex value to the queue
									}
								}
							}
						}
						dequeuedvert->SetBlack();//completely visited this vertex
					}
				}
			}
		}
		//end of BFS- now fix
		RecolorAllWhite(); //fix vertex colors
		//now print:
		for (int i = 0; i < VertexCount; i++) {
			std::cout << "Distance between " << start->GetData() << " and " << vertices[i] << ": " << distance[i] << std::endl;
			std::cout << vertices[i] << "'s parent vertex: " << parent[i] << std::endl;
		}
		auto end = std::chrono::system_clock::now(); //end of insertime
		std::chrono::duration<double> elapsed_seconds = end - strt;
		Out << VertexCount << ", " << std::setprecision(5) << elapsed_seconds.count() << ", " << std::endl;

		Out.close();


		Out.open("BFSResults.txt", std::ios::app);
		Out << "Starting Vertex: " << startval << std::endl;
		Out << "Vertices:  ";
		for (int i = 0; i < VertexCount; i++)
			Out << vertices[i] << " ";
		Out << std::endl;
		Out << "Distances: ";
		for (int i = 0; i < VertexCount; i++)
			Out << distance[i] << " ";
		Out << std::endl;
		Out << "------------------------------" << std::endl;
		Out.close();
		

	} //end of if(start)
	else
		std::cout << startval << " is not in the graph." << std::endl;
 }

template<typename T>
int Graph<T>::GetDistanceBetween(const T to, const T from) {
	Vertex<T>* t = (*this)[to];
	Vertex<T>* f = (*this)[from];
	return t->GetDistance(f->GetData());
}

template<typename T>
void Graph<T>::EmptyGraph() {
	if (VertexCount != 0) {
		graph->EmptyTree();
		VertexCount = 0;
	}
}

template<typename T>
void Graph<T>::AssistConnections() {
	PrintVertices();
	bool valid = false;
	int val1 = 0, val2 = 0;
	Vertex<T>* temp1 = NULL;

	do {
		std::cout << "Input a vertex to create an edge to: ";
		std::cin >> val1;
		temp1 = (*this)[val1];
		if (temp1)
			valid = true;
		else
			std::cout << val1 << " not found :(" << std::endl;
	} while (!valid);
	
	valid = false;
	do {
		std::cout << "Input a vertex to create an edge from: ";
		std::cin >> val2;
		temp1 = (*this)[val2];
		if (temp1 && val1 != val2)
			valid = true;
		if(temp1 == NULL)
			std::cout << val2 << " not found :(" << std::endl;
		if (val1 == val2)
			std::cout << "Cannot create and edge to the same point in this graph, sorry!" << std::endl;
	} while (!valid);

	if (isDirected)
		AddDirectedConnection(val1, val2);
	else
		AddUndirectedConnection(val1, val2);
}

template<typename T>
void Graph<T>::ReadConnectionsFromFile() {
	char ans = ' ';
	std::ifstream In;
	std::string filename = "AdjacencyList";

	do {
		std::cout << "Import from default file? (Y/N): ";
		std::cin >> ans;
	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
	
	if (ans == 'Y' || ans == 'y') {
		filename += ".txt";
		In.open(filename, std::ios::in);
	}
	else {
		int i = 0;
		do {
			if (i < 3) {
				std::cout << "Input the name of the file you wish to read an adjacency list from WITHOUT the .txt" << std::endl;
				std::cin >> filename;
				filename += ".txt";
				In.open(filename, std::ios::in);
				i++;
			}
			else {
				std::cout << RED << "3 fails- defaulting to default input" << DEFAULT << std::endl;
				filename = "AdjacencyList";
				filename += ".txt";
				In.open(filename, std::ios::in);
			}
		} while (In.fail());
	}

	//read from file
	while(!In.eof()) {
		int connectionsadded;
		int val;
		int from = 0;
		int connection;

		In >> connectionsadded;

		int verticesadded[connectionsadded];
		In >> val; //place holder

		for (int i = 0; i < connectionsadded; i++) {
			In >> val;
			verticesadded[i] = val; //will be the "to" connection
			AddVertex(val); //wont be added if already in.
		}
		//read in adjacency list ocnnections
		for (int i = 0; i < connectionsadded; i++) {
			In >> from;
			for (int j = 0; j < connectionsadded; j++) {
				In >> connection;
				if (connection == 1) {
					std::cout << verticesadded[j] << " " << from << std::endl;
					if (isDirected)
						AddDirectedConnection(verticesadded[j], from);
					else
						AddUndirectedConnection(verticesadded[j], from);
				}
		    }
		}
	}
}

//takes the transpose of a graph that is passed it
//BROKEN BOI
template<typename T>
Graph<T>& Graph<T>::transpose(Graph<T>& original) {
	Graph<T> transposegraph(original);
	std::cout << "Now copying tree contents: " << std::endl;
	CopySetUp(transposegraph, original); //copy the tree of vertices with no connections
	//now recreate the connections.
	std::cout << "Now inverting connections: " << std::endl;
	InvertConnections(transposegraph, original); //recursively flips the directions of the connections
	
	return transposegraph;
}

//returns a separate and identical tree,
//by inserting a copy of the data for each vertex in the tree- this way there are no connections yet
template<typename T>
void Graph<T>::CopySetUp(Graph<T>& transposegraph, Graph<T>& pbj) {
	if (graph) {
		if (transposegraph.graph)
			transposegraph.graph = new RedBlueTree<Vertex<T>>;
		if (pbj.graph->Root != graph->NIL) {
			transposegraph.AddVertex(pbj.graph->Root->key.GetData());
			Copy(pbj.graph->Root->LChild, transposegraph);
			Copy(pbj.graph->Root->RChild, transposegraph);
		}
	}
}

template<typename T>
void Graph<T>::Copy(TreeNode<Vertex<T>>* original, Graph<T>& transposegraph) {
	if (original != graph->NIL && original) {
		transposegraph.AddVertex(original->key.GetData());
		Copy(original->LChild, transposegraph);
		Copy(original->RChild, transposegraph);
	}
}

template<typename T>
void Graph<T>::InvertConnections(Graph<T>& obj, Graph<T>& old) {
	// the root in graph has connections
	if (old.graph->Root != obj.graph->NIL) {
		//if the root has connections
		if (!(old.graph->Root->key.Empty())) {
			//for all the connections in this vertex
			for (int i = 0; i < old.graph->Root->key.GetNodesInList(); i++) {
				//get the ith conneciton value
				T* tempconnectionval = old.graph->Root->key.GetIthConnection(i);
				if (tempconnectionval) {
					std::cout << "Inverting: " << old.graph->Root->key.GetData() << "and " << *tempconnectionval << std::endl;
					
					obj.AddDirectedConnection(old.graph->Root->key.GetData(), *tempconnectionval);
				}
			}
			InvertConnections(old.graph->Root->RChild, obj);
			InvertConnections(old.graph->Root->LChild, obj);
		}
	}
}

template<typename T>
void Graph<T>::InvertConnections(TreeNode<Vertex<T>>* old, Graph<T>& pbj) {
	// the root in graph has connections
	if (old != graph->NIL) {
		//only invert if there are connections to invert
		if (!(old->key.Empty())) {
			
			//for all the connections in this vertex
			for (int i = 0; i < old->key.GetNodesInList(); i++) {
				T* tempconnectionval = old->key.GetIthConnection(i);
				if(tempconnectionval)
					pbj.AddDirectedConnection(old->key.GetData(), *tempconnectionval);
			}

			InvertConnections(old->RChild, pbj);
			InvertConnections(old->LChild, pbj);
		}
	}
}

template<typename T>
void Graph<T>::RecursiveDFS(T startval, int* distance, int* vertices, int* discoveries, int* finishes, int& opcount) {	
	int startindex = 0;
	Vertex<T>* start = (*this)[startval];
	if (start) {
		for (int i = 0; i < VertexCount; i++) {
			//initialize distance[]
			if (vertices[i] == startval) {
				startindex = i;
				break;
			}
		}

		std::stack<T> Stack;
		Stack.push(startval); //add the value passed in to a stack
		start->SetGray();//visited but not finished

		while (!Stack.empty()) {
			T wastop = Stack.top();//store the previous front
			Stack.pop();

			Vertex<T>* poppededvert = (*this)[wastop]; //check dequeuedvert's connections. returns a pointer to wasfront vertex 
			int popedverticeindex = 0;

			//store the index value of poppedvert
			for (int i = 0; i < VertexCount; i++) {
				if (vertices[i] == poppededvert->GetData()) {
					popedverticeindex = i;
					break;
				}
			}

			//pointer to the vertex of poppededvert's ith connection
			Vertex<T>* connection = NULL;

			//for all vertices connected to dequeuedvert
			for (int i = 0; i < poppededvert->GetNodesInList(); i++) {
				T* t = poppededvert->GetIthConnection(i); //a pointer to the value at the ith connection
				//if there is an ith connection t is nonNull
				if (t) {
					connection = (*this)[*t]; //pointer to the vertex with t as its data

					//if non visited vertex
					if (connection->GetColor() == WHite) {
						connection->SetGray(); //is visited

						//find this vertex's location in the arrays storing BFS data
						for (int m = 0; m < VertexCount; m++) {
							if (vertices[m] == *t) { //foud the ith vertex value 

								//corresponding with wasfront vertex (dequeuedvert)
								for (int j = 0; j < VertexCount; j++) {
									//now do the same with the partent (wasfront)
									if (vertices[j] == wastop) {
										Stack.push(*t);
										opcount++;
										distance[m] = distance[j] + poppededvert->GetDistance(*t);//add the distance between temp2 and dequeuedvert

										discoveries[m] = opcount;
										RecursiveDFS(connection->GetData(), distance, vertices, discoveries, finishes, opcount);
									}
								}
							}
						}
					}
					/*else if (connection->GetColor() == BLack) {
						isDAG = false;
					}*/
				}
			}
			poppededvert->SetBlack();//completely visited this vertex
			if(finishes[popedverticeindex] == -1)
				finishes[popedverticeindex] = ++opcount;
		}
	}
}

template<typename T>
void Graph<T>::DFS(T startval, bool DAGcare) {
	if (DAGcare) {
		if (!checkedDAG)
			CheckIfDAG();
	}
	if (isDAG || !DAGcare) {
		Vertex<T>* start = (*this)[startval];
		int operationscount = 0;//used to track discovery and end times

		RecolorAllWhite(); //incase they aren't

		std::ofstream Out;
		if (start) {
			std::stack<T> Stack; //just store vertex values- not the vertex itself

			int distance[VertexCount]; //stores all the distance of all vertices from startval
			int vertices[VertexCount];
			int discoveries[VertexCount]; //store find counts: 0 1 3 . . .
			int finishes[VertexCount]; //store finish counts: 5 2 4 . . .
			int startindex;
			{
				int j = 0; //indexing of vertices
				graph->ConverttoArray(graph->Root, vertices, j);
				//initialize all of the vertices
				for (int i = 0; i < VertexCount; i++) {
					//initialize distance[]
					if (vertices[i] == startval) {
						startindex = i;
						distance[i] = 0; //distance to self is 0
						discoveries[i] = 0;//start at this value
					}
					else {
						distance[i] = -1; //distance to all other vertices is -1 at the moment
					   //initialize all find and finish times to -1 to illustrate uncalculated
						discoveries[i] = -1;
					}
					finishes[i] = -1;
				}
			}
			//--------------------------------------------------------------------------------------------------------------------

			Out.open("DFSTimes.txt", std::ios::app);
			auto strt = std::chrono::system_clock::now();
			//------------------------------------------------------

			int j = 0;
			int q = 0;
			for (int k = 0; k < VertexCount; k++) { //DFS all vertices
				q = startindex + k;
				if (q > VertexCount - 1) //correct the vertice being checked respect to user specified start
					q = VertexCount - q;
				RecursiveDFS(vertices[q], distance, vertices, discoveries, finishes, j);
			}

			//finished- write results to file and consoles
			{
				//------------------------------------------------------
				//Write Discovery times to txt
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - strt;
				Out << VertexCount << ", " << std::setprecision(5) << elapsed_seconds.count() << ", " << std::endl;
				Out.close();

				Out.open("DFSDiscoveries.txt"); //override data
				Out << startval << std::endl;
				for (int i = 0; i < VertexCount; i++)
					Out << vertices[i] << " " << discoveries[i] << std::endl;
				Out.close();
				//-------------------------------------------------------------
				//Write Finish Times to txt

				Out.open("DFSFinishes.txt");//override data
				Out << startval << std::endl;
				for (int i = 0; i < VertexCount; i++)
					Out << vertices[i] << " " << finishes[i] << std::endl;
				Out.close();
				//-------------------------------------------------------------

				for (int i = 0; i < VertexCount; i++) {
					//if (isDAG) {
						std::cout << "Vertice:   " << vertices[i] << std::endl;
						std::cout << "\tDiscovery: " << discoveries[i] << std::endl;
						std::cout << "\tFinish:    " << finishes[i] << std::endl;
						std::cout << std::endl;
					//}
					/*else {
						std::cout << "This graph was discovered to be not a DAG. The process was terminated." << std::endl;
						break;
					}*/
				}
			}
		}
	}
	else
	std::cout << "This graph is not a DAG!" << std::endl;
	RecolorAllWhite();
}

template<typename T>
void Graph<T>::CheckIfDAG() {
	if (isDirected) {
		RecolorAllWhite();
		isDAG = true; //assume that it is a dag if directed
		
		int vertices[VertexCount];
		int j = 0; //indexing of vertices
		//initialize all of the vertices
		graph->ConverttoArray(graph->Root, vertices, j);
		
		//check all vertices
		
		for (int i = 0; i < VertexCount; i++) {
			Vertex<T>* current = (*this)[vertices[i]];

			current->SetRed();
			current->SetBlack(); //the current is done being checked
			RecursiveCheckIfDAG(current);
			//if it has been shown that this graph is not a dag- get out
			if (!isDAG)
				break;
			RecolorAllWhite();
		}
	}
	else
		isDAG = false;
}

template<typename T>
void Graph<T>::RecursiveCheckIfDAG(Vertex<T>* current) {
	if (current->GetNodesInList() > 0) {
		Vertex<T>* compare = NULL;
		//for all neighbors of current
		for (int i = 0; i < current->GetNodesInList(); i++) {
			//get neighbor
			T* compareval = current->GetIthConnection(i);
			if (compareval) {
				compare = (*this)[*compareval];

				//if neighbor already been looked at- it must not be a DAG
				if (compare->GetColor() == BLack)
					isDAG = false;
				else {
					compare->SetRed(); //set it to red
					RecursiveCheckIfDAG(compare); //now check compare's neighbors
				}
			}
		}
	}

}

template<typename T>
void Graph<T>::TopoSort() {
	if (!checkedDAG)
		CheckIfDAG();
	if (isDAG) {
		std::ifstream In;
		int start = 0;
		int i = 0;
		int vertices[VertexCount];
		int Finishes[VertexCount];
		bool again = false;
		bool stop = false;
		do {
			In.open("DFSFinishes.txt", std::ios::in);
			In >> start;
			while (!In.eof()) {
				In >> vertices[i];
				In >> Finishes[i];
				i++;
			}
			In.close();
			if (i == 0) { //file was empty(no DFS run)
				again = true;
				if (graph->Root != graph->NIL) {
					int b = graph->Root->key.GetData();
					DFS(b); //run a DFS on the first element
				}
				else
					stop = true;
			}
		} while (again && !stop);
		if (stop)
			std::cout << "Empty Graph!" << std::endl;
		else {
			//now sort finsihes in decending order (move vertices the same)
			DecsendingBubbleSort(vertices, Finishes);
			std::cout << "A topological sort of this graph based on DFS starting at vertex: " << start << std::endl;

			for (int i = 0; i < VertexCount; i++) {
				std::cout << "Vertex: " << vertices[i] << std::endl;
			}
		}
	}
}

template<typename T>
void Graph<T>::DecsendingBubbleSort(int* vertices, int* fin) {

	int temp = 0;
	for (int i = 0; i < VertexCount; i++) {
		for (int j = 0; j < VertexCount - i - 1; j++)
		{
			if (fin[j] < fin[j + 1]) {
				temp = fin[j];
				fin[j] = fin[j + 1];
				fin[j + 1] = temp;
				
				temp = vertices[j];
				vertices[j] = vertices[j + 1];
				vertices[j + 1] = temp;

			}
			else
				continue;
		}
	}
}

template<typename T>
void Graph<T>::PrintStronglyConnectedComponents() {

	CheckIfDAG();
	if (isDAG)
	{
		int vertices[VertexCount];
		int j = 0;
		graph->ConverttoArray(graph->Root, vertices, j);
		std::cout << "Strongly Connected Components of this graph:" << std::endl;
		for (int i = 0; i < VertexCount; i++) {
			std::cout << "Component #" << i + 1 << ": " << vertices[i] << std::endl;
		}
	}
	else {

		std::cout << "Running SCC alg." << std::endl;
		//first run DFS originally
		std::ifstream In;
		int start = 0;
		int i = 0;
		int vertices[VertexCount];
		int Finishes[VertexCount];
		
		int Transposevertices[VertexCount];
		int TransposeFinishes[VertexCount];

		DFS(graph->Root->key.GetData(), false); //run a DFS on the first element

		In.open("DFSFinishes.txt", std::ios::in);
		
		In >> start;
		while (!In.eof()) {
			In >> vertices[i];
			In >> Finishes[i];
			i++;
		}
		In.close();

		//now sort finsihes in decending order (move vertices the same)- of the original graph
		DecsendingBubbleSort(vertices, Finishes);
		
		std::cout << "creating transpose" << std::endl;

		Graph<T> Transpose = transpose(*this); //construct the transpose graph of this

		T b = Transpose.graph->Root->key.GetData();
		DFS(b);
		In.open("DFSFinishes.txt", std::ios::in);
		In >> start;
		while (!In.eof()) {
			In >> Transposevertices[i];
			In >> TransposeFinishes[i];
			i++;
		}
		In.close();

		//now sort finsihes in decending order (move vertices the same)- of the transpose graph
		DecsendingBubbleSort(vertices, Finishes);
		for (int i = 0; i < VertexCount; i++)
			AugmentedDFS(TransposeFinishes[i]); //Augmented DFS on transpose finsih
	}
}

//used for finding SCCs
template<typename T>
void Graph<T>::AugmentedDFS(T startval) {
	Vertex<T>* start = (*this)[startval];
	RecolorAllWhite(); //incase they aren't

	if (start) {
		std::stack<T> Stack; //just store vertex values- not the vertex itself
		if (start->GetConnectionNum() > 0) {

			int Components[VertexCount+1]; //store vertex value of this strongly connected component

			for (int i = 0; i < VertexCount + 1; i++) {
				//0th index denotes number of vertices in the SCC
				if (i == 1)
					Components[i] = start->GetData();
				else
					Components[i] = 0; //unset
			}
			int currentcomp = 1;
			//--------------------------------------------------------------------------------------------------------------------
			
			RecursiveAugmentedDFS(start, Components, ++currentcomp, currentcomp);
			
			//--------------------------------------------------------------------------------------------------------------------

			std::cout << "Number of vertices in the connected component of " << startval << ": " << Components[0] << std::endl;
			if (Components[0] > 0) {
				std::cout << "Connected Components of " << startval << ":" << std::endl;
				for (int i = 0; i < Components[0]; i++) {
					std::cout << i + 1 << ". " << Components[i + 1] << std::endl;
				}
			}
		}
	}
	RecolorAllWhite();
}

template<typename T>
void Graph<T>::RecursiveAugmentedDFS(Vertex<T>* start, int* Components, int& index, int& compsize) {
	Vertex<T>* connection = NULL;
	if (start) {
		std::stack<T> Stack;
		Stack.push(start->GetData()); //add the value passed in to a stack
		start->SetGray();//visited but not finished
		while (!Stack.empty()) {
			Stack.pop();
			
			for (int i = 0; i < start->GetConnectionNum(); i++) {
				T* t = start->GetIthConnection(i); //a pointer to the value at the ith connection
				//if there is an ith connection t is nonNull
				if (t) {
					connection = (*this)[*t]; //pointer to the vertex with t as its data
					//non visited neighbor
					if (connection->GetColor() == WHite) {
						connection->SetGray();
						Stack.push(*t);
						Components[index] = connection->GetData();
						compsize++;
						index++;
						RecursiveAugmentedDFS(connection, Components, index, compsize);
					}
				}
			}
		}
		start->SetBlack();//completely visited this vertex
	}
}


template<typename T>
void Graph<T>::CalculateVectorCover1() {
	int fakelist[VertexCount]; //array that stores each vertex value
	int j = 0;
	graph->ConverttoArray(graph->Root, fakelist, j);

	//build vertex cover set out of string of the vertex values
	std::string vertexcovers[VertexCount];

	for (int i = 0; i < VertexCount; i++)
		vertexcovers[i] = std::to_string(fakelist[i]);

	//now we have the values in an array. remove (set to "") values unnecessary in vertex cover- meaning they are connected to a vertex in fakelist
	std::ofstream Out;
	Out.open("VerexCoverTimes.txt", std::ios::app);
	char ans = ' ';
	int startval = 0;
	int startindex = 0;
	do {
		std::cout << " Vertex Cover Start Selection " << std::endl;
		std::cout << "         Input an Option      " << std::endl;
		std::cout << "1. Begin from first vertex    " << std::endl;
		std::cout << "2. Begin from a random vertex  " << std::endl;
		std::cout << "3. Begin from selected vertex " << std::endl;
		std::cout << "Make Input: ";
		std::cin >> ans;
		std::cout << std::endl;

	} while (ans != '1' && ans != '2' && ans != '3');
	
	if (ans == '2') {
		startindex = rand() % VertexCount;
	}
	if (ans == '3') {
		PrintVertices();
		int i = 0;
		do {
			if (i > 0)
				std::cout << startval << " is not in the graph! Try Again." << std::endl;

			std::cout << "Input a vertex to begin from: ";
			std::cin >> startval;
			i++;
		} while ((*this)[startval] == NULL);
		
		//find the index in fakelist corresponding to startval
		for (int j = 0; j < VertexCount; j++) {
			if (fakelist[j] == startval) {
				startindex = j;
				break;
			}
		}
	}
	//prep done- begin a timer
	auto start = std::chrono::system_clock::now();

	int val = 0;
	//start vertex cover with fakelist[0]
	for (int k = 0; k < VertexCount; k++) {
		val = k + startindex;
		if (val > VertexCount - 1) //will be at least vertex count
			val = val - VertexCount;

		//check if the value is in the vertex cover, if it is adjust the vertex cover
		//if fakelist val  is in vertexcover
		if (vertexcovers[val] != " ") { //" " == " " fakelist[val] is not in the vertex cover
			
			Vertex<T>* search = (*this)[fakelist[val]];
			//in the vertexcover at the moment- search its connections
			if (search) {
				//for all of its connections:
				if (search->GetConnections()) {
					for (int l = 0; l < search->GetConnectionNum(); l++) {
						T* temp = search->GetIthConnection(l);
						if (temp) {
							Vertex<T>* connection = (*this)[*temp];
							//now find where connection is in vertexcovers
							for (int j = 0; j < VertexCount; j++) {
								//find the connection, and ensure it is not a self connection- dont want to set that to empty
								if (fakelist[j] == connection->GetData())
									vertexcovers[j] = " ";
							}
						}
					}
				}
			}
		}
		else
		{
			//check if this one is connected to multiple values in the vertexcover array
			//if so replace those with this one
			Vertex<T>* search = (*this)[fakelist[val]];
			if (search) {
				if (search->GetConnections()) {
					int RepeatConnections[search->GetConnectionNum()];

					int connectionsincoverarray = 0;

					for (int l = 0; l < search->GetConnectionNum(); l++) {
						RepeatConnections[l] = 0;

						T* temp = search->GetIthConnection(l); //get the lth connection
						//if connection not NULL
						if (temp) {
							Vertex<T>* connection = (*this)[*temp]; //store the indices of the values that MAY get swapped out

							//now check if connection in vertexcover array- if there are 2 or more found set them to empty and put this one back in the array
							for (int j = 0; j < VertexCount; j++) {
								//find the connection
								if (fakelist[j] == connection->GetData()) {
									if (vertexcovers[j] != " ") {
										RepeatConnections[connectionsincoverarray] = j;
										connectionsincoverarray++;
									}
								}
							}
						}
					}
					//a swap is in order. Swap out all values in RepeatConnections. replace them with " " and add vertexcovers[val] back in there 2 or more
					if (connectionsincoverarray > 1) {
						for (int i = 0; i < connectionsincoverarray; i++) {
							vertexcovers[RepeatConnections[i]] = " ";
						}
						vertexcovers[val] = std::to_string(fakelist[val]); //put it back into the vertexcovers array
					}
				}
			}
		}
	}
	
	//----------------------------------------------------------------------------------

	auto end = std::chrono::system_clock::now(); //end of insertime
	
	Vertex<T>* temp = (*this)[fakelist[0 + startindex]];
	std::cout << "Vertices in the graph:" << std::endl;
	for (int i = 0; i < VertexCount; i++)
		std::cout << fakelist[i] << " ";
	std::cout << std::endl;

	std::cout << "Vertex Cover beginning from " << temp->GetData() << ":" << std::endl;
	for (int i = 0; i < VertexCount; i++) {
		if (vertexcovers[i] != " ") {
			if (i < VertexCount - 1)
				std::cout << vertexcovers[i] << ", ";
			else
				std::cout << vertexcovers[i] << std::endl;
		}
	}
	std::cout << std::endl;

	int vertexcovercount = 0;
	for (int i = 0; i < VertexCount; i++)
		if (vertexcovers[i] != " ")
			vertexcovercount++;
	std::chrono::duration<double> elapsed_seconds = end - start;
	Out << ans << ", " << VertexCount << ", " << std::setprecision(5) << elapsed_seconds.count() <<", " << vertexcovercount << std::endl;

	Out.close();


}


