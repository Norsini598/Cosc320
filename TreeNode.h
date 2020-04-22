#ifndef TREENODE_H
#define TREENODE_H

/*
Making a Red and Blue tree as blue is a color that I can print, black is
the same color as the console, also blue and black both begin with bl
so its close enough. Blue = Black in RedBlackTrees
*/
enum Color {
	red = 0,
	blue = 1 //a color than can print on console, black on black just doesnt work.
};

template<typename T>
struct TreeNode {
	T key;
	TreeNode<T>* Parent;
	TreeNode<T>* RChild;
	TreeNode<T>* LChild;

	Color Colr;

	//compare any nodes
	//bool operator>(const TreeNode<T>&);
	//bool operator<(const TreeNode<T>&);
	//definition of operator>

	/*bool operator>(const TreeNode<T>& obj);
	bool operator<(const TreeNode<T>& obj);

	TreeNode& operator=(const TreeNode<T>& obj);

	friend std::ostream& operator<<(std::ostream&, const TreeNode<T>&);

	void PrintNode();*/
};
#endif // !TREENODE_H

