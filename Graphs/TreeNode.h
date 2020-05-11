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
	T key; //in this lab this represents a vertex. A vertex has an edge
	TreeNode<T>* Parent;
	TreeNode<T>* RChild;
	TreeNode<T>* LChild;

	Color Colr;
};
#endif // !TREENODE_H

