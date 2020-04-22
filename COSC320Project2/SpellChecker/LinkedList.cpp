#include "LinkedList.h"

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
			Behindtemp->next = NULL;
		}
		delete head;
	}
}

template<typename T>
void LinkedList<T>::AddNode(Node<T> obj) {
	NodesinList++;
	//append a new node to the front move head back one by making current head obj->next
	//"transform a node into a node pointer"

	//esentially a Node copy constructor
	Node<T>* temp;
	temp = new Node<T>;
	temp->data = obj.data;
	temp->hashvalue = obj.hashvalue;
	temp->next = obj.next;

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

		temp->PrintNode(); //print first node
		while (temp->next && !stop) {
			std::cout << "Node #" << ++i + 1 << " of " << NodesinList << ":" << std::endl;
			temp = temp->next;
			temp->PrintNode();
			if (temp->next == NULL) {
				std::cout << "End of list. " << std::endl;
				stop = true;
			}
		}
	}
	else
		std::cout << "Empty List. " << std::endl;
}

template<typename T>
void LinkedList<T>::EmptyList()
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
			Behindtemp->next = NULL;
		}
		delete head;
	}
	head = NULL;
	NodesinList = 0;
}

template<typename T>
bool LinkedList<T>::InList(T d) {
	bool r = false;
	bool stop = false;
	if (head) {
		//prufen Sie die erste
		if (head->data == d)
			r = true;
		//prufen Sie die anderen
		else if (head->next) {
			Node<T>* temp = head;
			while (temp->next && !stop) {
				if (temp->data == d) {
					r = true;
					break;//found, so get out
				}
				else {
					temp = temp->next;
					if (temp->next == NULL)
						stop = true;
				}
			}
		}
	}
	return r;
}