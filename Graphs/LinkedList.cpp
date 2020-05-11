#include "LinkedList.h"
#include <iostream>
#include "EscapeSequences.h"

template<typename T>
LinkedList<T>::LinkedList()
{
	head = NULL; //nothing in the list
	NodesinList = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	if (head != NULL) {
		Edge<T>* temp = NULL;
		Edge<T>* Behindtemp = NULL;
		//while the head's next is not NULL
		while (head->next) {
			temp = head;
			//get to the end of the list
			while (temp->next) {
				Behindtemp = temp;
				temp = temp->next;
			}
			delete temp;
			Behindtemp->next = NULL;
		}
		delete head;
		head = NULL;
	}
}

template<typename T>
void LinkedList<T>::AddNode(T vertval, int dist) {
	//append a new node to the front move head back one by making current head obj->next
	//esentially an edge copy constructor
	Edge<T>* temp = new Edge<T>;
	temp->vert = vertval;
	temp->distance = dist;
	temp->next = NULL;
	bool inserted = false;

	//bool inserted = false; //has the edge been added?

	//first element set head equal to temp
	if (head == NULL) {
		head = temp; //head now has the pointer and the above new is deleted in the LinkedList deconstructor.
	//not first element obj (temp) becomes the first element so temp->next is set to head
		NodesinList++;
	}

	//unlike a hashtable- we wont just append to the front of the list- this list is ordered by edge length
	//ties are beat by appending in front
	else {
		Edge<T>* variable = head;
		Edge<T>* behindvariable = NULL;
		
		//while not at end of the list AND the edge has not been inserted
		while (variable->next != NULL && !inserted) {
			behindvariable = variable;
			variable = variable->next; //move to the next edge
			
			//distance of new edge is less than node we are at, therefore insert the node after behind and before 
			if (temp->distance <= variable->distance) {
				inserted = true; //get out of the loop
				if (temp->vert == vertval)
					std::cout << "Error! Vertex already in this graph." << std::endl;
				else {
					behindvariable->next = temp; //variable retains the rest of its list
					temp->next = variable;
					NodesinList++;
				}
			}				
		}
		//the end of the list was reached or the edge was inserted

		//if not inserted  means the end of the list was reached variable->next still at the end to the list i.e. NULL
		if (!inserted) {
			variable->next = temp;
			temp->next = NULL;
			NodesinList++;
		}
	}
}

template<typename T>
void LinkedList<T>::AddNode(Edge<T>* obj) {
	//first element set head equal to temp
	if (head == NULL) {
		head = obj; //head now has the pointer and the above new is deleted in the LinkedList deconstructor.
		NodesinList++;
	}
	//not first element obj (temp) becomes the first element so temp->next is set to head

	//unlike a hashtable- we wont just append to the front of the list- this list is ordered by edge length
	//ties are beat by appending in front
	else {
		Edge<T>* variable = head;
		Edge<T>* behindvariable = NULL;
		
		bool inserted = false;
		
		//while not at end of the list AND the edge has not been inserted
		while (variable->next != NULL && !inserted) {
			behindvariable = variable;
			variable = variable->next; //move to the next edge
			//distance of new edge is less than node we are at, therefore insert the node after behind and before 
			if (obj->distance <= variable->distance) {
				inserted = true; //get out of the loop
				if(obj->vert == variable->vert)
					std::cout << "Error! Vertex already in this graph." << std::endl;
				else {
					behindvariable->next = obj; //variable retains the rest of its list
					obj->next = variable;
					NodesinList++;
				}
			}
		}
		//the end of the list was reached or the edge was inserted

		//if not inserted  means the end of the list was reached
		//variable->next still at the end to the list i.e. NULL
		if (!inserted) {
			variable->next = obj;
			NodesinList++;
		}
	}
}

template<typename T>
void LinkedList<T>::RemoveNode(T obj) {
	//nothing to remove
	if (head == NULL)
		std::cout << "Error! Empty List." << std::endl;
	//there are nodes in this list
	else {
		Edge<T>* variable = head;
		Edge<T>* behindvariable = NULL;

		if (variable->vert == obj) {
			//remove that node
			Edge<T>* deleteing = variable;
			delete deleteing;
			deleteing = NULL;

			variable = variable->next; //set variable to the next one
			head = variable; //new head
		}

		bool found = false;
		while(variable->next != NULL && !found){
			behindvariable = variable;
			variable = variable->next;

			if (variable->vert == obj) {
				found = true;
				//remove that node
				Edge<T>* deleteing = variable;
				delete deleteing;
				deleteing = NULL;

				variable = variable->next; //set variable to the next one
				behindvariable->next = variable; //new head
			}
		}
		if (found == false)
			std::cout << "There is no edge connecting " << obj << " to this node." << std::endl;
	}
}

template<typename T>
void LinkedList<T>::RemoveNode(Edge<T>* obj) {
	//nothing to remove
	if (head == NULL)
		std::cout << "Error! Empty List." << std::endl;
	else {
		Edge<T>* variable = head;
		Edge<T>* behindvariable = NULL;

		//first node
		if (variable->vert == obj->vert) {
			//remove that node
			Edge<T>* deleteing = variable;
			delete deleteing;
			deleteing = NULL;

			variable = variable->next; //set variable to the next one
			head = variable; //new head
		}
		bool found = false;
		while (variable->next != NULL && !found) {
			behindvariable = variable;
			variable = variable->next;

			if (variable->vert == obj->vert) {
				found = true;
				//remove that node
				Edge<T>* deleteing = variable;
				delete deleteing;
				deleteing = NULL;

				variable = variable->next; //set variable to the next one
				behindvariable->next = variable; //new head
			}
		}
		if (found == false)
			std::cout << "There is no edge connecting " << obj << " to this node." << std::endl;
	}
}

template<typename T>
bool LinkedList<T>::InList(T vert) {
	bool r = false;
	if (head) {
		if (head->vert == vert)
			r = true;
		else {
			Edge<T>* temp = head;
			Edge<T>* behindtemp = NULL;
			while (temp->next && !r) {
				behindtemp = temp;
				temp = temp->next;
				if (temp->vert == vert)
					r = true;
			}
		}
	}
	return r;
}

template<typename T>
void LinkedList<T>::EmptyList() {
	NodesinList = 0;
	if (head) {
		Edge<T>* temp;
		Edge<T>* Behindtemp;
		//while the head's next is not NULL
		while (head->next) {
			temp = head;
			//get to the end of the list
			while (temp->next) {
				Behindtemp = temp;
				temp = temp->next;
			}
			delete temp;
			Behindtemp->next = NULL;
		}
		delete head;
		head = NULL;
	}
}

template<typename T>
bool LinkedList<T>::operator==(T obj) {
	return InList(obj);
}

template<typename T>
void LinkedList<T>::operator+(const Edge<T>* obj) {
	AddNode(obj->vert,obj->distance);
}

template<typename T>
T* LinkedList<T>::GetIthNode(int i) {
	T* rtrn = NULL;
	if (i >= 0 && i < NodesinList) {
		if (head) {
			int j = 0;
			if (i == 0)
				rtrn = &head->vert;
			else {
				j++;
				bool r = false;
				Edge<T>* temp = head;
				Edge<T>* behindtemp = NULL;
				while (temp->next && !r) {
					behindtemp = temp;
					temp = temp->next;
					if (j == i) {
						r = true;
						rtrn = &temp->vert;
					}
					else
						continue;
				}
			}
		}
	}
	return rtrn;		
}

template<typename T>
Edge<T>* LinkedList<T>::GetEdge(T obj) {
	Edge<T>* rtrn = NULL;
	if (head) {
		if (head->vert == obj)
			rtrn = head;
		else {
			bool r = false;
			Edge<T>* temp = head;
			Edge<T>* behindtemp = NULL;

			while (temp->next && !r) {
				behindtemp = temp;
				temp = temp->next;
				if (temp->vert == obj) {
					r = true;
					rtrn = temp;
				}
				else
					continue;
			}
		}
	}
	return rtrn;
}