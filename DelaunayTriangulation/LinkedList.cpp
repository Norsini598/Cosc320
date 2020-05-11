#include "LinkedList.h"
#include "Triangle.h"

template<typename T>
LinkedList<T>::LinkedList()
{
	head = NULL; //nothing in the list
	NodesinList = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	if (head) {
		Node<T>* temp;
		Node<T>* Behindtemp;
		//while the head's next is not NULL
		while (head->next) {
			temp = head;
			//get to the end of the list
			while (temp->next) {
				Behindtemp = temp;
				temp = temp->next;
			}
			delete temp;
			temp = NULL;
			Behindtemp->next = NULL;
		}
		delete head;
		head = NULL;
	}
}

template<typename T>
void LinkedList<T>::AddNode(Node<T>* obj) {
	NodesinList++;
	//append a new node to the front move head back one by making current head obj->next

	//esentially a Node copy constructor
	Node<T>* temp;
	temp = new Node<T>;
	temp->data = obj->data;
	temp->next = obj->next;

	//first element set head equal to temp
	if (head == NULL)
		head = temp; //head now has the pointer and the above new is deleted in the LinkedList deconstructor.
	//not first element obj (temp) becomes the first element so temp->next is set to head
	else {
		temp->next = head; //link the new node to the rest of the preexisting list
		head = temp;
	}
}

template<typename T>
void LinkedList<T>::AddNode(T* obj) {
	NodesinList++;
	//append a new node to the front move head back one by making current head obj->next

	//esentially a Node copy constructor
	Node<T>* temp;
	temp = new Node<T>;
	temp->data = *obj;
	temp->next = NULL;

	//first element set head equal to temp
	if (head == NULL)
		head = temp; //head now has the pointer and the above new is deleted in the LinkedList deconstructor.
	//not first element obj (temp) becomes the first element so temp->next is set to head

	else {
		temp->next = head; //link the new node to the rest of the preexisting list
		head = temp;
	}
}

template<typename T>
void LinkedList<T>::AddNode(T obj) {
	NodesinList++;
	//append a new node to the front move head back one by making current head obj->next

	//esentially a Node copy constructor
	Node<T>* temp;
	temp = new Node<T>;
	temp->data = obj;
	temp->next = NULL;

	//first element set head equal to temp
	if (head == NULL)
		head = temp; //head now has the pointer and the above new is deleted in the LinkedList deconstructor.
	//not first element obj (temp) becomes the first element so temp->next is set to head

	else {
		temp->next = head; //link the new node to the rest of the preexisting list
		head = temp;
	}
}

template<typename T>
void LinkedList<T>::PrintList()
{
	bool stop = false;
	if (head) {
		std::cout << std::endl << "Printing Linked List: " << std::endl;
		std::cout << "======================" << std::endl;
		Node<T>* temp = head;
		int i = 0;
		std::cout << "Node #" << i + 1 << " of " << NodesinList << ":" << std::endl;
		std::cout << temp->data << std::endl;

		while (temp->next && !stop) {
			std::cout << "Node #" << ++i + 1 << " of " << NodesinList << ":" << std::endl;
			temp = temp->next;
			std::cout << temp->data << std::endl;
			if (temp->next == NULL) {
				std::cout << "End of list. " << std::endl;
				stop = true;
			}
		}
	}
	else
		std::cout << "Empty List. " << std::endl;
}

//return the head point and remove it form the list
template<typename T>
T* LinkedList<T>::GetHead() {
	T* rvalue = NULL; //Vertex
	if (head) {
		rvalue = new T(head->data);
		
		
		Node<T>* removing = head;
		head = head->next;
		removing->next = NULL;
		
		delete removing;
		NodesinList--;
	}
	return rvalue;
}

template<typename T>
int LinkedList<T>::GetNodesInList() {
	
	
	return NodesinList;
}

template<typename T>
void LinkedList<T>::EmptyList() {
	int i = 0;
	while (head) {
		std::cout << ++i << std::endl;
		Node<T>* oldhead = head;
		head = head->next;
		delete oldhead;
	}
	std::cout << "Done" << std::endl;
}

template<typename T>
bool LinkedList<T>::InList(T* obj) {
	bool r = false; //assume the value in obj is not in the list
	Node<T>* temp = head;
	if (temp) {
		if (temp->data == *obj)
			r = true;
		else {
			while (temp->next && !r) {
				temp = temp->next;
				if (temp->data == *obj)
					r = true;
			}
		}
	}
	return r;
}

template<typename T>
T* LinkedList<T>::GetClosestItem(T* from) {
	float closestdistance = 0;
	T* closestitem = new T;
	Node<T>* temp = head;
	float tempdist = 0;
	if (temp) {
		closestdistance = CalculateDistance(from->X, from->Y, temp->data.X, temp->data.Y); //assume the first is the closest
		closestitem->SetX(temp->data.X);
		closestitem->SetY(temp->data.Y);
		tempdist = closestdistance;
		while (temp->next) {
			temp = temp->next;

			tempdist = CalculateDistance(from->X, from->Y, temp->data.X, temp->data.Y);
			if (tempdist < closestdistance && tempdist != 0) {
				//change the x and y coordinates of the point
				closestitem->SetX(temp->data.X);
				closestitem->SetY(temp->data.Y);
				closestdistance = tempdist;
			}
		}
	}
	if (closestdistance == 0) {
		delete closestitem;
		closestitem = NULL;
	}
	return closestitem;
}

template<typename T>
T* LinkedList<T>::GetSecondClosestItem(T* from) {
	T* closest = new T;
	T* secondclosest = new T;
	float closestdistance = 0;
	float secondclosestdistance = 0;
	float tempdistance = 0;

	Node<T>* temp = head;
	if (temp) {
		closestdistance = CalculateDistance(from->X, from->Y, temp->data.X, temp->data.Y);
		closest->SetX(temp->data.X);
		closest->SetY(temp->data.Y);
		int i = 0;
		while (temp->next) {
			temp = temp->next;
			tempdistance = CalculateDistance(from->X, from->Y, temp->data.X, temp->data.Y);
			if (i == 0) {
				if (tempdistance > closestdistance) {
					secondclosest->SetX(temp->data.X);
					secondclosest->SetY(temp->data.Y);
					secondclosestdistance = tempdistance;
				}
				//tempdistance is closer, swap the 2.
				else /*secondclosestdistance < closestdistance*/{
					secondclosest->SetX(closest->X);
					secondclosest->SetY(closest->Y);

					closest->SetX(temp->data.X);
					closest->SetY(temp->data.Y);
					
					secondclosestdistance = closestdistance;
					closestdistance = tempdistance;
				}
			}
			else {
				//new closest found
				if (tempdistance < closestdistance && tempdistance != 0) {
					//set second closest to previous closest
					secondclosest->SetX(closest->X);
					secondclosest->SetY(closest->Y);
					//set closest to temp
					closest->SetX(temp->data.X);
					closest->SetY(temp->data.Y);

					secondclosestdistance = closestdistance;
					closestdistance = tempdistance;
				}
				//new value is the second closest (in between current second and current closest
				else if (tempdistance < secondclosestdistance && tempdistance > closestdistance) {
					//closest stays the same but secondclosest changes
					secondclosest->SetX(temp->data.X);
					secondclosest->SetY(temp->data.Y);

					secondclosestdistance = tempdistance;
				}
			}
			i++;
		}
	}
	delete closest;
	closest = NULL;	
	return secondclosest;
}

template<typename T>
T* LinkedList<T>::GetThirdClosestItem(T* from) {
	float Closestdist = 0;
	float SecondClosestdist = 0;
	float ThirdClosestdist = 0;
	float tempdistance = 0;

	//create default vertices ... T's
	T* closest = new T;
	T* secondclosest = new T;
	T* thirdclosest = new T;
	Node<T>* temp = head;
	int i = 0;
	if (temp) {
		if (NodesinList < 3) {
			delete thirdclosest;
			thirdclosest = NULL;
		}
		else {
			Closestdist = CalculateDistance(from->X, from->Y, temp->data.X, temp->data.Y);
			closest->SetX(temp->data.X);
			closest->SetY(temp->data.Y);

			while (temp->next) {
				temp = temp->next; //move iteration forward
				tempdistance = CalculateDistance(from->X, from->Y, temp->data.X, temp->data.Y);
				//second can be initiated
				if (i == 0) {
					SecondClosestdist = tempdistance;
					if (SecondClosestdist > Closestdist) {
						secondclosest->SetX(temp->data.X);
						secondclosest->SetY(temp->data.Y);
					}
					//tempdistance is closer, swap the 2.
					else /*secondclosestdistance < closestdistance*/ {
						secondclosest->SetX(closest->X);
						secondclosest->SetY(closest->Y);

						closest->SetX(temp->data.X);
						closest->SetY(temp->data.Y);

						SecondClosestdist = Closestdist;
						Closestdist = tempdistance;
					}
				}
				//third can be initiated
				else if (i == 1) {
					ThirdClosestdist = tempdistance;

					if (ThirdClosestdist < Closestdist) {
						thirdclosest->SetX(secondclosest->X);
						thirdclosest->SetY(secondclosest->Y);
						secondclosest->SetX(closest->X);
						secondclosest->SetY(closest->Y);
						closest->SetX(temp->data.X);
						closest->SetY(temp->data.Y);
						ThirdClosestdist = SecondClosestdist;
						SecondClosestdist = Closestdist;
						Closestdist = tempdistance;
					}
					else if (ThirdClosestdist < SecondClosestdist) {
						thirdclosest->SetX(secondclosest->X);
						thirdclosest->SetY(secondclosest->Y);

						secondclosest->SetX(temp->data.X);
						secondclosest->SetY(temp->data.Y);

						ThirdClosestdist = SecondClosestdist;
						SecondClosestdist = tempdistance;
					}
					else {
						thirdclosest->SetX(temp->data.X);
						thirdclosest->SetY(temp->data.Y);
					}
				}
				//now move values forward as needed
				else {
					if (tempdistance < Closestdist) {
						thirdclosest->SetX(secondclosest->X);
						thirdclosest->SetY(secondclosest->Y);
						secondclosest->SetX(closest->X);
						secondclosest->SetY(closest->Y);
						closest->SetX(temp->data.X);
						closest->SetY(temp->data.Y);
						ThirdClosestdist = SecondClosestdist;
						SecondClosestdist = Closestdist;
						Closestdist = tempdistance;
					}
					else if (tempdistance < SecondClosestdist) {
						thirdclosest->SetX(secondclosest->X);
						thirdclosest->SetY(secondclosest->Y);

						secondclosest->SetX(temp->data.X);
						secondclosest->SetY(temp->data.Y);

						ThirdClosestdist = SecondClosestdist;
						SecondClosestdist = tempdistance;
					}
					else if(tempdistance < ThirdClosestdist) {
						thirdclosest->SetX(temp->data.X);
						thirdclosest->SetY(temp->data.Y);
						ThirdClosestdist = tempdistance;
					}
				}
				i++;
			}
		}	
	}
	else {
		delete thirdclosest;
		thirdclosest = NULL;
	}

	//delete these T's they are unneeded ultimately
	delete closest;
	closest = NULL;
	delete secondclosest;
	secondclosest = NULL;

	//either returns a T or NULL
	return thirdclosest;
}


template<typename T>
void LinkedList<T>::RemoveItem(T* find) {
	Node<T>* temp = head;
	Node<T>* behindtemp = NULL;
	if (temp) {
		//deleting the first item
		if (temp->data == *find) {
			head = head->next;
			temp->next = NULL;
			delete temp;
		}
		else {
			while (temp->next) {
				behindtemp = temp;
				temp = temp->next;

				if (temp->data == *find) {
					behindtemp->next = temp->next;
					temp->next = NULL;
					delete temp;
					break;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
