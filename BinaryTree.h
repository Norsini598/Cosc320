#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
/*a templated binaary search tree with a templated Tree Node*/

/*
template<typename T>
std::ostream& operator<< (std::ostream&, const TreeNode<T>&);

*/


template<typename T>
class BinaryTree
{
private:
	TreeNode<T>* Root;
	int Nodenum;
	bool allowduplicants;
public:
	BinaryTree();
	~BinaryTree();

	//Is a particular value in the tree
	bool Search(const T);
	//Is a particular node in the tree
	bool Search(TreeNode<T>*);
	//Get the node if it is in the tree
	TreeNode<T>* GetNode(const T);

	//Get the minimum node of a subtree
	TreeNode<T>* GetMinimum(TreeNode<T>*);
	//Get the maximum node of a subtree
	TreeNode<T>* GetMaximum(TreeNode<T>*);

	//add a node to the BST
	void Insert(TreeNode<T>*);

	//remove a node by taking in the key value from the BST
	void Delete(T);

	void EmptyTree();


	TreeNode<T>* GetSuccessor(const T);
	TreeNode<T>* GetSuccessor(TreeNode<T>*);
	

	void PrintInOrder(TreeNode<T>*);
	void PrintPreOrder(TreeNode<T>*);
	void PrintPostOrder(TreeNode<T>*);

	int GetNumNode();
	bool GetDuplicantRule();
	void SetDuplicantRule(bool);

	TreeNode<T>* GetRoot() { return Root; }

	void PrintNodeData(TreeNode<T>*);

	//friend std::ostream& operator<< <>(std::ostream&, const BinaryTree<T>&);
};
#endif // !BINARYTREE_H

