#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

template<typename T>
BinaryTree<T>::BinaryTree() {
	Root = NULL;
	Nodenum = 0;
	allowduplicants = false;//default, duplicants not allowed
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
	/*
	Has O(n!) runtime (if whole tree is a linked list) - yuck lol. Heres my thought:
	run through n times each n is one less than one before
	8 ... 7 ... 6 ... ... ... 2 ... 1
	*/
	std::ofstream Out;
	if (Root) {
		Out.open("DeleteTreeTime.txt", std::ios::app);
		Out << Nodenum << ",";
		TreeNode<T>* temp = NULL;
		TreeNode<T>* behindtemp = NULL;
		int right = 0; //0 no change, 1 moved left, 2 moved right
		//while root has a child

		//start timer
		auto start = std::chrono::system_clock::now();

		//do delete
		while (Root->LChild || Root->RChild) {
			right = 0; //reset
			temp = Root; //moving variable- intialize at root
			while (temp) {
				//std::cout << "Print temp:\n";
				//temp->PrintNode();
				//if temp isn't null then right gets reset by a movement
				if (temp->LChild != NULL) {
					behindtemp = temp;
					temp = temp->LChild;
					right = 1;
				}
				else if (temp->RChild != NULL) {
					behindtemp = temp;
					temp = temp->RChild;
					right = 2;
				}
				else //temp is a leaf- delete it and set behind temp child to null
				{
					temp->Parent = NULL; //detach
					Nodenum--;
					if (temp != Root) {
						delete temp;
						temp = NULL;
						//set the behindtemp children depedning on which right temp was on
						if (right == 1)
							behindtemp->LChild = NULL;
						else if (right == 2)
							behindtemp->RChild = NULL;
					}
				}
			}
			//Root = NULL;
		}
		delete Root;
		Root = NULL;

		//end time
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		Out << elapsed_seconds.count() << std::endl;

		Out.close();
	}
}

template<typename T>
void BinaryTree<T>::EmptyTree() {
	std::ofstream Out;
	if(Root){
		Out.open("DeleteTreeTime.txt", std::ios::app);
		Out << Nodenum << ",";
		TreeNode<T>* temp = NULL;
		TreeNode<T>* behindtemp = NULL;
		int right = 0; //0 no change, 1 moved left, 2 moved right
		//while root has a child

		//start timer
		auto start = std::chrono::system_clock::now();

		//do delete
		while (Root->LChild || Root->RChild) {
			right = 0; //reset
			temp = Root; //moving variable- intialize at root
			while (temp) {
				//std::cout << "Print temp:\n";
				//temp->PrintNode();
				//if temp isn't null then right gets reset by a movement
				if (temp->LChild != NULL) {
					behindtemp = temp;
					temp = temp->LChild;
					right = 1;
				}
				else if (temp->RChild != NULL) {
					behindtemp = temp;
					temp = temp->RChild;
					right = 2;
				}
				else //temp is a leaf- delete it and set behind temp child to null
				{
					temp->Parent = NULL; //detach
					Nodenum--;
					if (temp != Root) {
						delete temp;
						temp = NULL;
						//set the behindtemp children depedning on which right temp was on
						if (right == 1)
							behindtemp->LChild = NULL;
						else if (right == 2)
							behindtemp->RChild = NULL;
					}
				}
			}
			//Root = NULL;
		}
		delete Root;
		Root = NULL;

		//end time
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		Out << elapsed_seconds.count() << std::endl;

		Out.close();
	}
}

template<typename T>
void BinaryTree<T>::Insert(TreeNode<T>* o) {
	
	TreeNode<T>* obj;// the newnode
	obj = new TreeNode<T>;
	std::ofstream Outfile;
	float insertime = 0;

	Nodenum++;

	obj->count = o->count;
	obj->key = o->key;
	obj->LChild = o->LChild;
	obj->RChild = o->RChild;
	obj->Parent = NULL; //change upon entry
	
	Outfile.open("Insertingtimes.txt", std::ios::app); //open a file to write the amount of time an insertion takes

		//start the timer
	auto start = std::chrono::system_clock::now();

	TreeNode<T>* temp = Root; //movement variable
	TreeNode<T>* behindtemp = NULL;

	//first node
	if (temp == NULL)
		Root = obj;
	//move until reaching a leaf
	else {
		//keep moving through tree until reaching a temp of NULL
		while (temp) {
			
			behindtemp = temp; //temp about to move forward

			if (obj->key > temp->key)
				temp = temp->RChild;
			else if (obj->key < temp->key)
				temp = temp->LChild;
			else if (temp->key == obj->key)
			{
				if (allowduplicants)
					temp->count++; //duplicant
				else //duplicant not allowed fix the Numnode incrmeent
					Nodenum--;
				delete obj; //obj not being used so delete it
				break;//temp wont reach NULL and therefore next condition will fail

			}
		}
		//timer only stops if actually being inserted
		if (temp == NULL) {
			//decompose obj
			temp = obj;
			//set the family tree 
			temp->Parent = behindtemp; //parent should NOT be NULL- append the tree to the top of node
			if (temp->key > behindtemp->key)
				behindtemp->RChild = temp;
			else
				behindtemp->LChild = temp;

			//end time
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::time_t end_time = std::chrono::system_clock::to_time_t(end);

			insertime = elapsed_seconds.count();

			//wrtie data to file
			//insert: nodes in tree before insert, and the time
			Outfile << Nodenum - 1 << "," << insertime << std::endl;
		}
	}
	Outfile.close();
}

template<typename T>
TreeNode<T>* BinaryTree<T>::GetMaximum(TreeNode<T>* obj){
	TreeNode<T>* temp = obj;
	while (temp->RChild)
		temp = temp->RChild;
	return temp;
}

template<typename T>
TreeNode<T>* BinaryTree<T>::GetMinimum(TreeNode<T>* obj) {
	TreeNode<T>* temp = obj;
	while (temp->LChild)
		temp = temp->LChild;
	return temp;
}

template<typename T>
bool BinaryTree<T>::Search(T obj) {
	TreeNode<T>* temp = Root;
	bool found = false;
	while (!found) {
		if (temp->key < obj)
			temp = temp->RChild;
		else if (temp->key > obj)
			temp = temp->LChild;
		else if (temp->key == obj)
			found = true;
		else if (temp == NULL) //end of tree
			break;
	}
	return found;
}

template<typename T>
bool BinaryTree<T>::Search(TreeNode<T>* obj) {
	TreeNode<T>* temp = Root;
	bool found = false;
	while (!found) {
		if (temp->key < obj->key)
			temp = temp->RChild;
		else if (temp->key > obj->key)
			temp = temp->LChild;
		else if (temp->key == obj->key)
			found = true;
		else if (temp == NULL) //end of tree
			break;
	}
	return found;
}

template<typename T>
TreeNode<T>* BinaryTree<T>::GetNode(const T obj) {
	TreeNode<T>* temp = Root;
	bool found = false;
	while (!found) {
		if (temp->key < obj)
			temp = temp->RChild;
		else if (temp->key > obj)
			temp = temp->LChild;
		else if (temp->key == obj)
			return temp;
		else if (temp == NULL) //end of tree
			return NULL;
	}
}

template<typename T>
TreeNode<T>* BinaryTree<T>::GetSuccessor(TreeNode<T>* obj) {
	TreeNode<T>* temp = NULL;
	if (obj->RChild)
		temp = GetMinimum(obj->RChild); 
	else {
		temp = obj->Parent;
		while (temp && obj == temp->RChild) {
			obj = temp;
			temp = temp->Parent;//treaverse upward until obj is left child of temp
		}
	}	
	return temp; //the successor of obj or NULL
}

template<typename T>
TreeNode<T>* BinaryTree<T>::GetSuccessor(const T obj) {
	/*
	should work for all nodes in tree or not
	*/
	TreeNode<T>* temp = Root;
	TreeNode<T>* successor = NULL;
	bool found = false;
	while (!found) { //ifinite loop exited upon reaching a leaf
		if (temp) {
			if (obj < temp->key) { //successor is at most temp
				successor = temp;
				temp = temp->LChild; //check a smaller value
			}
			else if (obj > temp->key) //obj is greater than temp so temp is not successor and must be larger
				temp = temp->RChild;
			else //obj == temp->key
				temp = temp->RChild;
		}
		else //at a leaf
			return successor;
	}
}

template<typename T>
void BinaryTree<T>::Delete(T obj) {
	TreeNode<T>* deletingnode = GetNode(obj);
	TreeNode<T>* deletingnodeparent = NULL;
	if (deletingnode == NULL)
		std::cout << "This value is not in the binary search tree." << std::endl;
	else {
		Nodenum--;
		bool right = false; //left right
		//behind node
		if(deletingnode->Parent != NULL)
			deletingnodeparent = deletingnode->Parent;

		//Side determination
		//if there is a parent identify what right of parent deletingnode is on: right or left
		if (deletingnodeparent)
		{
			if (deletingnodeparent->RChild)
				if (deletingnode->key == deletingnodeparent->RChild->key)
					right = true; //deletingnode is a right child of its parent
			//otherwise deletingnode is a left child of its parent
		}
		
		//Multiple Nodes of that value- just decrement the counter
		if (deletingnode->count > 0)
			deletingnode->count--;

		//Leaf: 0 children
		else if (deletingnode->RChild == NULL && deletingnode->LChild == NULL) {
			std::cout << "No children " << std::endl;
			//set parent child to NULL, then delete node. detach delete
			//deletingnode has a parent- therfore fix its children- not root
			if (deletingnodeparent) {
				if (right) //right side
					deletingnodeparent->RChild = NULL;
				else //left
					deletingnodeparent->LChild = NULL;
			}
			//only node being deleted (the root- a lonely root)
			else {
				Root = NULL; //detach
			}
			delete deletingnode;
			deletingnode = NULL;
		}
		
		//1 child: Has Left child
		else if(deletingnode->LChild && deletingnode->RChild == NULL){
			std::cout << "One Child: Left" << std::endl;
			if (deletingnodeparent) {
				//append child to parent child
				if (right) //right. deletingnode is right child of its parent
					deletingnodeparent->RChild = deletingnode->LChild;
				else
					deletingnodeparent->LChild = deletingnode->LChild;
				deletingnode->LChild->Parent = deletingnodeparent; //He's not the Father!
			}
			else
				Root = deletingnode->LChild;
			
			deletingnode->LChild = NULL;//detach
			delete deletingnode; //delete
		}
		//1 child: Has Right child
		else if (deletingnode->RChild && deletingnode->LChild == NULL) {
			std::cout << "One Child: Right" << std::endl;
			if (deletingnodeparent) {
				//append child to parent child
				if (right) //right. if deletingnode is right child of temp
					deletingnodeparent->RChild = deletingnode->RChild;
				else
					deletingnodeparent->LChild = deletingnode->RChild;
				deletingnode->RChild->Parent = deletingnodeparent; //He's not the Father!
			}
			//deleting root (no parent)- root with one child. its child becomes root
			else
				Root = deletingnode->RChild;

			deletingnode->RChild = NULL; //detach
			delete deletingnode; //delete
		}
		
		//2 children
		else
		{
			TreeNode<T>* successor = GetSuccessor(deletingnode);
			/*copy over content of successor and then call delete on successor*/
			T Key = successor->key; //save for later
			//recurrsively delete successor- if it too has 2 children find its successor otherwise different solution enacted. etc.
			Delete(successor->key);
			deletingnode->key = Key;
		}
	}
}

template<typename T>
void BinaryTree<T>::PrintInOrder(TreeNode<T>* obj) {
	if (obj != NULL)
	{
		PrintInOrder(obj->LChild);
		if (obj->key > 0)
			std::cout << " " << std::left << std::setw(8) << obj->key << " (" << obj->count << ")" << std::endl;
		else
			std::cout << std::left << std::setw(9) << obj->key << " (" << obj->count << ")" << std::endl;
		PrintInOrder(obj->RChild);
	}
}

template<typename T>
void BinaryTree<T>::PrintPreOrder(TreeNode<T>* obj) {
	if (obj != NULL)
	{
		if(obj->key > 0)
			std::cout << " " << std::left << std::setw(8) << obj->key << " (" << obj->count << ")" << std::endl;
		else
		std::cout << std::left << std::setw(9) << obj->key << " (" << obj->count << ")" << std::endl;
		PrintPreOrder(obj->LChild);
		PrintPreOrder(obj->RChild);
	}
}

template<typename T>
void BinaryTree<T>::PrintPostOrder(TreeNode<T>* obj) {
	if (obj != NULL)
	{
		PrintPostOrder(obj->LChild);
		PrintPostOrder(obj->RChild);
		if (obj->key > 0)
			std::cout << " " << std::left << std::setw(8) << obj->key << " (" << obj->count << ")" << std::endl;
		else
			std::cout << std::left << std::setw(9) << obj->key << " (" << obj->count << ")" << std::endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintNodeData(TreeNode<T>* obj) {
	std::cout << "--------------------" << std::endl;
	std::cout << "|Node Data: " << obj->key << std::endl;
	if (obj->Parent)
		std::cout << "|Parent value: " << obj->Parent->key << std::endl;
	else
		std::cout << "|No Parent" << std::endl;
	if (obj->RChild)
		std::cout << "|Right child value: " << obj->RChild->key << std::endl;
	else
		std::cout << "|No Right Child" << std::endl;
	if (obj->LChild)
		std::cout << "|Left child value: " << obj->LChild->key << std::endl;
	else
		std::cout << "|No Left Child" << std::endl;
	std::cout << "--------------------" << std::endl;
	TreeNode<T>* temp = GetSuccessor(obj);
	if (temp)
		std::cout << "|Successor Value: " << temp->key << std::endl;
	else
		std::cout << "|No Successor" << std::endl;
	temp = NULL; //dont delete because clearly still need it
}

template<typename T>
int BinaryTree<T>::GetNumNode() { return Nodenum; }

template<typename T>
bool BinaryTree<T>::GetDuplicantRule() { return allowduplicants; }

template<typename T>
void BinaryTree<T>::SetDuplicantRule(bool a) { allowduplicants = a; }