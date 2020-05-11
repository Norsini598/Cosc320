#ifndef RedBlueTree_H
#define RedBlueTree_H

#include "TreeNode.h"
#include "Triangle.h"
/*a templated red black tree with a templated TreeNode*/


template<typename T>
class RedBlueTree
{
	friend class DelaunayT; //graph can access me just fine
private:
	TreeNode<T>* Root; //start of the RB Tree
	TreeNode<T>* NIL;
	//just variables I want to keep track of for sake of data collections
	int Nodenum; //number of elements in the tree
	int internalNodenum; //number of internal nodes in the tree

	//a nill node instances of TreeNodes in this class will share. All leafes point to NIL.
	//instead of search for if(X == NULL) now we will write if( X == NIL)
	//a NILL node is blue, NULL children. I will have a parent but it wont get to point to into. NIL is a little orphan child.
	//parent come to check it out but never fully adopted. As for it data, thay CAN remian uninitialized?

public:
	RedBlueTree();
	~RedBlueTree();

	//Is a particular value in the tree
	bool Search(const T);
	//Is a particular node in the tree
	bool Search(TreeNode<T>*);
	//Get the node if it is in the tree
	TreeNode<T>* GetNode(const T*);
	TreeNode<T>* GetNode(const T);

	//Get the minimum node of a subtree
	TreeNode<T>* GetMinimum(TreeNode<T>*);
	//Get the maximum node of a subtree
	TreeNode<T>* GetMaximum(TreeNode<T>*);

	//add a node to the BST
	//void Insert(TreeNode<T>*);
	void Insert(T*);

	//remove a node by taking in the key value from the BST
	void Delete(T*);
	//remove all nodes in the tree (except NILL)- that is only deleted in deconstructor
	void EmptyTree();

	TreeNode<T>* GetSuccessor(TreeNode<T>*);

	//print functions
		//print tree functions
	void PrintInOrder(TreeNode<T>*);
	void PrintPreOrder(TreeNode<T>*);
	void PrintPostOrder(TreeNode<T>*);
	//Print node functions
	void PrintNodeData(TreeNode<T>*);

	int GetNumNode(); //get the number of nodes in the RB tree

	TreeNode<T>* GetRoot() { return Root; }
	TreeNode<T>* GetNIL() { return NIL; }

	void RightRotate(TreeNode<T>*);
	void LeftRotate(TreeNode<T>*);

	void Insert_FixUP(TreeNode<T>*);
	void DeleteFix_UP(TreeNode<T>*);

	//Family reunions
	TreeNode<T>* GetUncle(TreeNode<T>*);
	TreeNode<T>* GetGrandParent(TreeNode<T>*);
	TreeNode<T>* GetSibling(TreeNode<T>*);

	void Transplant(TreeNode<T>*, TreeNode<T>*);

	void ConverttoArray(TreeNode<T>*, Vertex*, int&);

};
#endif // !RedBlueTree_H

