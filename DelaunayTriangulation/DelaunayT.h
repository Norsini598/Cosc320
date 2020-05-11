#ifndef DELAUNAYT_H
#define DELAUNAYT_H
#include "RedBlueTree.h"
#include "LinkedList.h"
#include <fstream>
#include <list>

class DelaunayT {
private:
	RedBlueTree<Triangle>* Triangulation;
	LinkedList<Vertex>* PointsToFix;
	std::list<Triangle> IllegalTriangles;

	float minX, maxX, minY, maxY;

public:
	DelaunayT();
	~DelaunayT();
	void DeleteTriangulation(); //cleans the whole tree

	bool FindPointStart(const Vertex*);
	void FindPointRecursive(TreeNode<Triangle>*, const Vertex*, bool&);
	
	void GetTriangle(const Triangle*); //testing if get node works in the tree
	void DeleteTriangle(Triangle*); //test deleting of triangle
		
	void Insert(Vertex*);
	void GetIllegals(TreeNode<Triangle>*, Vertex*);

	void Insert(Triangle*);

	//void DeletePoint(Vertex*); 
	
	void PrintPreOder() { Triangulation->PrintPreOrder(Triangulation->GetRoot()); }
	void PrintPostOder() { Triangulation->PrintPostOrder(Triangulation->GetRoot()); }
	void PrintInOder() { Triangulation->PrintInOrder(Triangulation->GetRoot()); }

	//return the closest triangle given a point
	Triangle GetClosestStart(const Vertex*);
	void GetClosestRecursive(TreeNode<Triangle>*, const Vertex*, Triangle&, float&);

	//return the second closest triangle given a point- resolves base case of 3+ violations
	Triangle GetSecondClosestStart(const Vertex*);
	void GetSecondClosestRecursive(TreeNode<Triangle>*, const Vertex*, Triangle*, Triangle&, float&, float&);

	bool CheckValidity(TreeNode<Triangle>*, Triangle*, bool&);

	void Print();

	void BubbleSort(Vertex* array, int size);

};
#endif // !DELAUNAYT_H

