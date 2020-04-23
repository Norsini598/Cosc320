#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>

template<typename T>
struct TreeNode {
	T key;
	TreeNode<T>* Parent;
	TreeNode<T>* RChild;
	TreeNode<T>* LChild;
	int count = 0; //handle duplicates
	//compare any nodes
	//bool operator>(const TreeNode<T>&);
	//bool operator<(const TreeNode<T>&);
	//definition of operator>

	bool operator>(const TreeNode<T>& obj);
	bool operator<(const TreeNode<T>& obj);

	TreeNode& operator=(const TreeNode<T>& obj);

	friend std::ostream& operator<<(std::ostream&, const TreeNode<T>&);

	void PrintNode();
};
#endif // !TREENODE_H

