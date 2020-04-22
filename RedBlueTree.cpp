#include "RedBlueTree.h"
#include "Colors.h"
#include <iomanip>
#include <ctime>
#include <chrono>
#include <fstream>

/*
as you will see I write != NULL and != NILL many times this is 
because I have not decided if I want the root to point to NIL to.
*/

//Building and Destructing
template<typename T>
RedBlueTree<T>::RedBlueTree() {
	//initialize NIL
	NIL = new TreeNode<T>;
	NIL->Colr = blue;
	NIL->Parent = NULL;
	NIL->LChild = NULL;
	NIL->RChild = NULL;
	//-----------------

	//root will point to NILL
	Root = NIL;
	Nodenum = 0;
}

template<typename T>
RedBlueTree<T>::~RedBlueTree() {
	std::ofstream Out;
	if (Root!= NIL && Root != NULL) {
		Out.open("DeleteTreeTime.txt", std::ios::app);
		Out << Nodenum << ",";
		TreeNode<T>* temp = NULL;
		TreeNode<T>* behindtemp = NULL;
		int right = 0; //0 no change, 1 moved left, 2 moved right
		//while root has a child

		//start timer
		auto start = std::chrono::system_clock::now();

		//do delete: delete everything but NIL- all twigs point to NIL (the leaf)- we will mulch up the leaves
		//at the end
		while (Root->LChild != NIL || Root->RChild != NIL) {
			right = 0; //reset
			temp = Root; //moving variable- intialize at root
			while (temp != NIL) {
				//std::cout << "Print temp:\n";
				//temp->PrintNode();
				//if temp isn't null then right gets reset by a movement
				if (temp->LChild != NIL) {
					behindtemp = temp;
					temp = temp->LChild;
					right = 1;
				}
				else if (temp->RChild != NIL) {
					behindtemp = temp;
					temp = temp->RChild;
					right = 2;
				}
				else //temp is a twig- delete it and set behind temp child to null
				{
					temp->Parent = NULL; //detach from branches
					Nodenum--;
					if (temp != Root) {
						delete temp;
						temp = NIL;
						//set the behindtemp children depedning on which right temp was on
						if (right == 1)
							behindtemp->LChild = NIL;
						else if (right == 2)
							behindtemp->RChild = NIL;
					}
				}
			}
			//Root = NULL;
		}
		delete Root;
		Root = NULL;

		delete NIL;
		NIL = NULL;

		//end time
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		Out << elapsed_seconds.count() << std::endl;

		Out.close();
	}
	//else nothing to do
}

template<typename T>
void RedBlueTree<T>::EmptyTree() {
	std::ofstream Out;
	if (Root != NIL && Root) {
		Out.open("DeleteTreeTime.txt", std::ios::app);
		Out << Nodenum << ",";
		TreeNode<T>* temp = NULL;
		TreeNode<T>* behindtemp = NULL;
		int right = 0; //0 no change, 1 moved left, 2 moved right
		//while root has a child

		//start timer
		auto start = std::chrono::system_clock::now();

		//do delete: delete everything but NIL- all twigs point to NIL (the leaf)- we will mulch up the leaves
		//at the end
		while (Root->LChild != NIL || Root->RChild != NIL) {
			right = 0; //reset
			temp = Root; //moving variable- intialize at root

			while (temp != NIL) {
				//std::cout << "Print temp:\n";
				//temp->PrintNode();
				//if temp isn't null then right gets reset by a movement
				if (temp->LChild != NIL) {
					behindtemp = temp;
					temp = temp->LChild;
					right = 1;
				}
				else if (temp->RChild != NIL) {
					behindtemp = temp;
					temp = temp->RChild;
					right = 2;
				}
				else { //child of temp is NIL
					temp->Parent = NULL; //detach from branches
					Nodenum--;
					//take care of the root outside.
					if (temp != Root) {
						delete temp;
						temp = NIL;
						//set the behindtemp children depedning on which right temp was on. They are the new leaves
						if (right == 1)
							behindtemp->LChild = NIL;
						else if (right == 2)
							behindtemp->RChild = NIL;
					}
				}
			}
			//Root = NIL;
		}
		delete Root;
		Root = NIL;
		Nodenum--;

		//end time
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		Out << elapsed_seconds.count() << ", " << std::endl;

		Out.close();

		/*
		Notice we do not delete NILL here, only the tree.		
		*/
	}
	//else nothing to do
}

//Searching
template<typename T>
bool RedBlueTree<T>::Search(const T obj) {
	TreeNode<T>* temp = Root;
	bool found = false;
	while (!found) {
		if (temp->key < obj)
			temp = temp->RChild;
		else if (temp->key > obj)
			temp = temp->LChild;
		else if (temp->key == obj)
			found = true;
		else if (temp == NIL) //end of tree
			break;
	}
	return found;
}

//Is a particular node in the tree
template<typename T>
bool RedBlueTree<T>::Search(TreeNode<T>* obj) {
	TreeNode<T>* temp = Root;
	bool found = false;
	while (!found) {
		if (temp->key < obj->key)
			temp = temp->RChild;
		else if (temp->key > obj->key)
			temp = temp->LChild;
		else if (temp->key == obj->key)
			found = true;
		else if (temp == NIL) //end of tree
			break;
	}
	return found;
}

//Get the node if it is in the tree
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetNode(const T obj) {
	TreeNode<T>* temp = Root;
	bool found = false;
	while (!found) {
		if (temp->key < obj)
			temp = temp->RChild;
		else if (temp->key > obj)
			temp = temp->LChild;
		else if (temp->key == obj)
			return temp;
		else if (temp == NIL) //end of tree
			break;
	}
	return NULL;
}

//Get the successor of any node
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetSuccessor(TreeNode<T>* obj) {
	TreeNode<T>* temp = NULL;
	if (obj->RChild)
		temp = GetMinimum(obj->RChild);
	else {
		temp = obj->Parent;
		while (temp != NIL && obj == temp->RChild) {
			obj = temp;
			temp = temp->Parent;//treaverse upward until obj is left child of temp
		}
	}
	return temp; //the successor of obj or NULL
}

//GetMin of any subtree
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetMinimum(TreeNode<T>* obj) {
	TreeNode<T>* temp = obj;
	if (temp != NIL && temp != NULL) {
		while (temp->LChild != NIL)
			temp = temp->LChild;
	}
	return temp;
}

//Get the maximum node of any subtree
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetMaximum(TreeNode<T>* obj) {
	TreeNode<T>* temp = obj;
	while (temp->RChild != NIL)
		temp = temp->RChild;
	return temp;
}

template<typename T>
void RedBlueTree<T>::PrintInOrder(TreeNode<T>* obj) {
	if (obj != NIL)
	{
		PrintInOrder(obj->LChild);
		if (obj->key > 0) {
			if (obj->Colr == red)
				std::cout << " " << std::left << std::setw(8) << RED << obj->key << DEFAULT << std::endl;
			else
				std::cout << " " << std::left << std::setw(8) << BLUE << obj->key  << DEFAULT << std::endl;
		}
		else {
			if (obj->Colr == red)
				std::cout << " " << std::left << std::setw(9) << RED << obj->key << DEFAULT << std::endl;
			else
				std::cout << " " << std::left << std::setw(9) << BLUE << obj->key << DEFAULT << std::endl;
		}
		PrintInOrder(obj->RChild);
	}
}

template<typename T>
void RedBlueTree<T>::PrintPreOrder(TreeNode<T>* obj) {
	if (obj != NIL)
	{
		if (obj->key > 0) {
			if (obj->Colr == red)
				std::cout << " " << std::left << std::setw(8) << RED << obj->key << DEFAULT << std::endl;
			else
				std::cout << " " << std::left << std::setw(8) << BLUE << obj->key << DEFAULT << std::endl;
		}
		else {
			if (obj->Colr == red)
				std::cout << " " << std::left << std::setw(9) << RED << obj->key << DEFAULT << std::endl;
			else
				std::cout << " " << std::left << std::setw(9) << BLUE << obj->key << DEFAULT << std::endl;
		}
		PrintPreOrder(obj->LChild);
		PrintPreOrder(obj->RChild);
	}
}

template<typename T>
void RedBlueTree<T>::PrintPostOrder(TreeNode<T>* obj) {
	if (obj != NIL)
	{
		PrintPostOrder(obj->LChild);
		PrintPostOrder(obj->RChild);
		if (obj->key > 0) {
			if (obj->Colr == red)
				std::cout << " " << std::left << std::setw(8) << RED << obj->key << DEFAULT << std::endl;
			else
				std::cout << " " << std::left << std::setw(8) << BLUE << obj->key << DEFAULT << std::endl;
		}
		else {
			if (obj->Colr == red)
				std::cout << " " << std::left << std::setw(9) << RED << obj->key << DEFAULT << std::endl;
			else
				std::cout << " " << std::left << std::setw(9) << BLUE << obj->key << DEFAULT << std::endl;
		}
	}
}

template<typename T>
void RedBlueTree<T>::PrintNodeData(TreeNode<T>* obj) {
	std::cout << "--------------------" << std::endl;
	if (obj != NIL && obj != NULL) {
		if(obj->Colr == red)
			std::cout << "|Node Data: " << RED << obj->key << DEFAULT << std::endl;
		else
			std::cout << "|Node Data: " << BLUE << obj->key << DEFAULT << std::endl;
		if (obj->Parent != NIL && obj->Parent != NULL) {
			if (obj->Parent->Colr == red)
				std::cout << "|Parent value: " << RED << obj->Parent->key << DEFAULT << std::endl;
			else
				std::cout << "|Parent value: " << BLUE << obj->Parent->key << DEFAULT << std::endl;
		}
		else if (obj->Parent == NIL)
			std::cout << "|NILL Parent" << std::endl;
		else
			std::cout << "|No Parent" << std::endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////
		if (obj->RChild && obj->RChild != NIL) {
			if (obj->RChild->Colr == red)
				std::cout << "|Right child value: " << RED << obj->RChild->key << DEFAULT << std::endl;
			else
				std::cout << "|Right child value: " << BLUE << obj->RChild->key << DEFAULT << std::endl;
		}
		else if (obj->RChild == NIL)
			std::cout << "|NIL Right Child" << std::endl;
		else
			std::cout << "|No Right Child" << std::endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////
		if (obj->LChild && obj->LChild != NIL) {
			if (obj->LChild->Colr == red)
				std::cout << "|Left child value: " << RED << obj->LChild->key << DEFAULT << std::endl;
			else
				std::cout << "|Left child value: " << BLUE << obj->LChild->key << DEFAULT << std::endl;
		}
		else if (obj->LChild == NIL)
			std::cout << "|NIL Left Child" << std::endl;
		else
			std::cout << "|No Left Child" << std::endl;

		std::cout << "--------------------" << std::endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////
		TreeNode<T>* temp = GetSuccessor(obj);
		if (temp != NULL && temp != NIL) {
			if (temp->Colr == red)
				std::cout << "|Successor Value: " << RED << temp->key << DEFAULT << std::endl;
			else
				std::cout << "|Successor Value: " << BLUE << temp->key << DEFAULT << std::endl;
		}
		else
			std::cout << "|No Successor" << std::endl;
		temp = NULL; //dont delete because clearly still need it
	}
	else
		std::cout << YELLOW << "Error! NIL or NULL node.\n------------------------" << DEFAULT << std::endl;
}

//Simpler Getters 
template<typename T>
int RedBlueTree<T>::GetNumNode() { return Nodenum; }

	//family reunions
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetUncle(TreeNode<T>* obj) {
	//child->parent  parent->parent->otherchild
	TreeNode<T>* uncle = NULL;
	//must be a NODE with data!
	if (obj != NULL && obj != NIL) {
		uncle = GetGrandParent(obj); //either NULL or grandparent
		if (uncle) {
			//unclide is either L or R child of temp
			//if obj > temp then obj is on the right so uncle is left child
			//obj right of grandparent, return left of grapdparent
			if (obj->key > uncle->key)
				uncle = uncle->LChild; //either NULL or a NODE
			else
				uncle = uncle->RChild;
		}
	}
	return uncle;
}
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetGrandParent(TreeNode<T>* obj) {
	TreeNode<T>* GrandParent = NULL;
	TreeNode<T>* temp = obj; //used to move around
	int i = 0; //used to loop twice, to get to grandparent
	do {
		if (temp) {
			if (temp->Parent != NULL && temp->Parent != NIL)
				temp = temp->Parent;
		}
		else //no parent exists there
			temp = NULL;
		i++;
	} while (i < 2);

	if (temp != NULL && temp != NIL)
		GrandParent = temp;
	return GrandParent;
}
template<typename T>
TreeNode<T>* RedBlueTree<T>::GetSibling(TreeNode<T>* obj) {
	TreeNode<T>* Sibling = NULL;
	//there is a node here
	if (obj != NULL && obj != NIL) {
		//there is a parrent
		if (obj->Parent != NULL && obj->Parent != NIL) {
			//obj is on the right of parent
			if (obj->key > obj->Parent->key)
				Sibling = obj->Parent->LChild;
			else
				Sibling = obj->Parent->RChild;
		}
	}
	return Sibling;
}

//Rotations
template<typename T>
void RedBlueTree<T>::LeftRotate(TreeNode<T>* x) {
	//x must be a valid node
	if (x && x != NIL) {
		std::ofstream Out;
		Out.open("RotateTimes.txt", std::ios::app);
		Out << 1 << ", " << Nodenum << ", ";
		//start timer
		auto start = std::chrono::system_clock::now();

		TreeNode<T>* y = x->RChild; //this is node y in diagram on p.313
			x->RChild = y->LChild;
			//if left child not a leaf it needs a parent
			if (y->LChild != NIL)
				y->LChild->Parent = x;
			//set y's parent to x's parent
				y->Parent = x->Parent;
			//if the parent is the root
				if (x->Parent == NIL)
					Root = y;
			//if x is a left child now y is a left child
				else if (x == x->Parent->LChild)
					x->Parent->LChild = y;
		//if x is a right child now y is a right child
				else
					x->Parent->RChild = y;
		y->LChild = x; //y is now the parent of x and
		x->Parent = y; //x's parent is y

		//end time
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = end - start;
		
		Out << elapsed_seconds.count() << std::endl;

		Out.close();
	}
}

template<typename T>
void RedBlueTree<T>::RightRotate(TreeNode<T>* x) {	//x must be a valid node
	if (x && x != NIL) {
		std::ofstream Out;
		Out.open("RotateTimes.txt");
		Out << 0 << ", " << Nodenum << ", ";
		//start timer
		auto start = std::chrono::system_clock::now();
		TreeNode<T>* y = x->LChild;
		x->LChild = y->RChild;
		if (y->RChild != NIL)
			y->RChild->Parent = x;
		y->Parent = x->Parent;
		if (x->Parent == NIL)
			Root = y;
		else if (x == x->Parent->RChild)
			x->Parent->RChild = y;
		else
			x->Parent->LChild = y;
		y->RChild = x;
		x->Parent = y;

		//end time
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = end - start;
		
		Out << elapsed_seconds.count() << std::endl;

		Out.close();

	}
}

////////////////////////////////////////////////////////////////////////
template<typename T>
void RedBlueTree<T>::Insert(T a) {
	Nodenum++;

	TreeNode<T>* newnode = new TreeNode<T>;
	newnode->Colr = red;
	newnode->key = a;
	newnode->LChild = NIL;
	newnode->RChild = NIL;
	int f = 0;
	
	TreeNode<T>* temp = Root; //moving variable
	TreeNode<T>* behindtemp = NULL;

	std::ofstream Outfile;
	Outfile.open("Inserttimes.txt", std::ios::app); //will include time to do regular insertion
	//time to do fix up and total time
	//start timer
	Outfile << Nodenum << ", ";

	auto start = std::chrono::system_clock::now();

	//not empty tree
	if (temp != NIL) {
		while (temp != NIL) {
			behindtemp = temp;
			if (newnode->key > temp->key)
				temp = temp->RChild;
			else //if (obj->key <= temp->key)
				temp = temp->LChild;
		}
		temp = newnode;
		temp->Parent = behindtemp;
		if (temp->key > behindtemp->key)
			behindtemp->RChild = temp;
		else
			behindtemp->LChild = temp;

		auto end1 = std::chrono::system_clock::now(); //end of regular insertime
		std::chrono::duration<double> elapsed_seconds = end1 - start;

		Outfile << elapsed_seconds.count() << ", ";

		if (temp->Parent->Colr == red) {
			Insert_FixUP(temp);
			f++; //if had to fix is 1
		}
		//otherwise no fix up is required

		auto end2 = std::chrono::system_clock::now(); //end of fix insertime
		elapsed_seconds = end2 - start;
		Outfile << f << ", " << elapsed_seconds.count() << ", ";
	}
	//empty tree
	else {
		Outfile << "0, 0, ";
		Root = newnode;
		Root->Colr = blue; //roots are "black"
		Root->Parent = NIL;
	}
	//entire time
	auto end3 = std::chrono::system_clock::now(); //end of insertime
	std::chrono::duration<double> elapsed_seconds = end3 - start;
	Outfile << elapsed_seconds.count() << ", " << std::endl;

	Outfile.close();
}

template<typename T>
void RedBlueTree<T>::Insert_FixUP(TreeNode<T>* start) {
	std::ofstream Out;
	Out.open("InsertFixTimes.txt", std::ios::app);
	TreeNode<T>* temp = start;
	TreeNode<T>* y = NULL;

	auto strt = std::chrono::system_clock::now();
	//if red red violation
	if (temp->Parent->Colr == red) {
		//keep checking until violation cleared
		while (temp->Parent->Colr == red) { 
			if (temp->Parent == temp->Parent->Parent->LChild) {
				y = GetUncle(temp);
				if (y != NIL) {
					if (y->Colr == red) {
						//make generation above temp "black"
						temp->Parent->Colr = blue;
						y->Colr = blue;
						temp = GetGrandParent(temp); //move up the tree
						temp->Colr = red;
					}
				}
				else {
					if (temp == temp->Parent->RChild) {
						temp = temp->Parent;
						LeftRotate(temp);
					}
					
					temp->Parent->Colr = blue;
					temp->Parent->Parent->Colr = red;
					RightRotate(GetGrandParent(temp));
				}
			}
			else {
				y = GetUncle(temp);
				if (y != NIL) {
					if (y->Colr == red) {
						temp->Parent->Colr = blue;
						y->Colr = blue;
						temp = GetGrandParent(temp);
						if(temp)
							temp->Colr = red;
					}
				}
				else {
					if (temp == temp->Parent->LChild) {
						temp = temp->Parent;
						RightRotate(temp);
					}
					temp->Parent->Colr = blue;
					temp->Parent->Parent->Colr = red;
					LeftRotate(GetGrandParent(temp));
				}
			}
		}
		Root->Colr = blue; //ensure its "black"
	}
	auto end = std::chrono::system_clock::now(); //end of insertime
	std::chrono::duration<double> elapsed_seconds = end - strt;
	Out << elapsed_seconds.count() << ", " << std::endl;

	Out.close();
	//else (temp->Parent->Colr == black){} 
	//parent is black and a black followed by a red does not create a violation


}

////////////////////////////////////////////////////////////////////////
/*
template<typename T>
void RedBlueTree<T>::Delete(T a) {
	TreeNode<T>* deletingnode = GetNode(a);
	TreeNode<T>* deletingnodeparent = NULL;
	TreeNode<T>* x = NULL; //deleting node's child- called fixup on
	if (deletingnode == NULL)
		std::cout << "This value is not in the binary search tree." << std::endl;
	else {
		if (deletingnode->Colr == red)
			std::cout << "Deleting: " << RED << deletingnode->key << DEFAULT << std::endl;
		else
			std::cout << "Deleting: " << BLUE << deletingnode->key << DEFAULT << std::endl;
		//-------------------------------------------------------------------------------
		int origcolor = deletingnode->Colr; //0 red, 1 blue important to fix if blue
		Nodenum--;
		bool right = false; //left right
		//behind node
		if (deletingnode->Parent != NULL)
			deletingnodeparent = deletingnode->Parent;

		//Side determination
		//if there is a parent identify what right of parent deletingnode is on: right or left
		if (deletingnodeparent != NIL && deletingnodeparent != NULL)
		{
			if (deletingnodeparent != NIL) {
				if(deletingnodeparent->RChild != NIL)
					if (deletingnode->key == deletingnodeparent->RChild->key)
						right = true; //deletingnode is a right child of its parent
			}
				//otherwise deletingnode is a left child of its parent
		}

		//Leaf: 0 children
		if (deletingnode->RChild == NIL && deletingnode->LChild == NIL) {
			std::cout << "No children " << std::endl;
			//set parent child to NULL, then delete node. detach delete. 
			if (deletingnodeparent != NIL) {
				//deletingnode has a parent - therfore fix its children - not root
				if (right) //right side
					deletingnodeparent->RChild = NIL;
				else //left
					deletingnodeparent->LChild = NIL;
				delete deletingnode;
				deletingnode = NULL;
			}
			//only node being deleted (the root- a lonely root)
			else {
				delete Root;
				Root = NIL;
			}
		}

		//1 child: Has Left child
		else if (deletingnode->LChild != NIL && deletingnode->RChild == NIL) {
			x = deletingnode->LChild;
			std::cout << "One Child: Left" << std::endl;
			if (deletingnodeparent != NIL) {
				//append child to parent child
				if (right) //right. deletingnode is right child of its parent
					deletingnodeparent->RChild = deletingnode->LChild;
				else
					deletingnodeparent->LChild = deletingnode->LChild;
				deletingnode->LChild->Parent = deletingnodeparent; //He's not the Father!
			}
			//deleting root
			else {
				Root = deletingnode->LChild;
				Root->Colr = blue;
			}
			deletingnode->LChild = NULL;//detach
			delete deletingnode; //delete
		}
		//1 child: Has Right child
		else if (deletingnode->RChild != NIL && deletingnode->LChild == NIL) {
			x = deletingnode->RChild;
			std::cout << "One Child: Right" << std::endl;
			if (deletingnodeparent != NIL) {
				//append child to parent child
				if (right) //right. if deletingnode is right child of temp
					deletingnodeparent->RChild = deletingnode->RChild;
				else
					deletingnodeparent->LChild = deletingnode->RChild;
				deletingnode->RChild->Parent = deletingnodeparent; //He's not the Father!
			}
			//deleting root (no parent)- root with one child. its child becomes root
			else {
				Root = deletingnode->RChild;
				Root->Colr = blue;
			}
			deletingnode->RChild = NULL; //detach
			delete deletingnode; //delete
		}

		//2 children
		else
		{
			TreeNode<T>* successor = GetSuccessor(deletingnode);
			x = successor->RChild;
			//copy over content of successor and then call delete on successor
			T Key = successor->key; //save for later
			//recurrsively delete successor- if it too has 2 children find its successor otherwise different solution enacted. etc.
			Delete(successor->key);
			deletingnode->key = Key;
		}

		if (origcolor == blue && Nodenum > 1)
			DeleteFix_UP(x);
	}
}*/

template<typename T>
void RedBlueTree<T>::DeleteFix_UP(TreeNode<T>* obj) {
	std::ofstream Out;
	Out.open("DeleteFixTime.txt", std::ios::app);
	
	auto start = std::chrono::system_clock::now();

	TreeNode<T>* sib = NULL;
	if (obj != NULL) {
		while (obj != Root && obj->Colr == blue) {

			if (obj->Parent)
				sib = obj->Parent->RChild;
			//if there is a sibling
			if (sib != NULL) {

				//obj left of parent (smaller)
				if (obj == obj->Parent->LChild) {
					//1
					if (sib->Colr == red) {
						sib->Colr = blue;
						obj->Parent->Colr = red;
						LeftRotate(obj->Parent);
						sib = obj->Parent->RChild; //new sibling
					}
					//2	sibling has 2 "black" children
					else if (sib->LChild->Colr == blue && sib->RChild->Colr == blue) {
						sib->Colr = red;
						obj = obj->Parent; //move up the tree
					}
					//3
					else if (sib->RChild->Colr == blue) {
						sib->LChild->Colr = blue;
						sib->Colr = red;
						RightRotate(sib);
						sib = obj->Parent->RChild; //move to uncle
					}
					else {
						sib->Colr = obj->Parent->Colr;
						obj->Parent->Colr = blue;
						sib->RChild->Colr = blue;
						LeftRotate(obj->Parent);
						obj = Root;
					}
				}
				//right of parent (larger)
				else {
					sib = obj->Parent->LChild;
					if (sib->Colr == red) {
						sib->Colr = blue;
						obj->Parent->Colr = red; //move red up the chain
						RightRotate(obj->Parent);
						sib = obj->Parent->LChild; //new sibling after the roation
					}
					//2 "black" children
					if (sib->RChild->Colr == blue && sib->LChild->Colr == blue) {
						sib->Colr = red;
						obj = obj->Parent;
					}
					else if (sib->LChild->Colr == blue) {
						sib->RChild->Colr = blue;
						sib->Colr = red;
						LeftRotate(sib);
						sib = obj->Parent->LChild;
					}
					else {
						sib->Colr = obj->Parent->Colr;
						obj->Parent->Colr = blue;
						sib->LChild->Colr = blue;
						RightRotate(obj->Parent);
						obj = Root;
					}
				}
			}
		}//while
		obj->Colr = blue; //at root- root is blue uhh, uh, shit, I mean black :}

		auto end = std::chrono::system_clock::now(); //end of regular insertime
		std::chrono::duration<double> elapsed_seconds = end - start;

		Out << elapsed_seconds.count() << ", ";

		Out.close();
	}
}

/*
template<typename T>
void RedBlueTree<T>::Delete(T a) {
	TreeNode<T>* x = NULL; //deleting node's children- called fixup on
	TreeNode<T>* y GetNode(a);
	if (deletingnode == NULL)
		std::cout << "This value is not in the binary search tree." << std::endl;
	else {
		if (deletingnode->Colr == red)
			std::cout << "Deleting: " << RED << deletingnode->key << DEFAULT << std::endl;
		else
			std::cout << "Deleting: " << BLUE << deletingnode->key << DEFAULT << std::endl;
		//-------------------------------------------------------------------------------
		//delete deletingnode (z)
		if (deletingnode->LChild != NIL || deletingnode->RChild != NIL)
			y = deletingnode;
		else
			y = GetSuccessor(deletingnode);

		if (y->LChild != NIL)
			x = y->LChild;
		else
			x = y->RChild;
		x->Parent = y->Parent;
		if (x->Parent == NIL)
			Root = x;
		else {
			if (y->Parent->LChild != NIL) {
				if (y == y->Parent->LChild)
					y->Parent->LChild = x;
			}
			else
				y->Parent->RChild = x;
		}
		if (y != deletingnode)
			deletingnode->key = y->key;
		if (y->Colr == blue)
			DeleteFix_UP(x);	
	}
}*/

template<typename T>
void RedBlueTree<T>::Delete(T a) {
	TreeNode<T>* Z = GetNode(a);
	TreeNode<T>* y = NULL;
	TreeNode<T>* x = NULL;
	if (Z == NULL)
		std::cout << "This value is not in the binary search tree." << std::endl;
	else {
		//the node is in the tree
		if (Z->RChild == NIL || Z->LChild == NIL)
			y = Z;
		else
			y = GetSuccessor(Z);
		if (y->LChild != NIL)
			x = y->LChild;
		else
			x = y->RChild;
		x->Parent = y->Parent;

		if (x->Parent == NIL)
			Root = x;
		else {
			//if y is left child
			if (y->Parent != NIL) {
				if (y->Parent->LChild == y)
					y->Parent->LChild = x;
				else
					y->Parent->RChild = x;
			}
		}
		if (y != Z)
			Z->key = y->key;
		if (y->Colr == blue)
			DeleteFix_UP(x);

	}
}