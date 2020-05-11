#include "TreeNode.h"


template<typename T>
bool TreeNode<T>::operator>(const TreeNode<T>& obj) {
	bool r = false;
	if (key > obj.key)
		r = true;
	return r;
}

template<typename T>
bool TreeNode<T>::operator<(const TreeNode<T>& obj) {
	bool r = false;
	if (key < obj.key)
		r = true;
	return r;
}

template<typename T>
TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& obj) {
	*Parent = *obj.Parent;
	*RChild = *obj.RChild;
	*LChild = *obj.LChild;
	count = obj.count;
	key = obj.key; //relies on T assignment operator

	return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const TreeNode<T>& obj) {
	std::cout << "--------------------" << std::endl;
	std::cout << "|Node Data: " << *obj.key << std::endl;
	if (obj.Parent)
		std::cout << "|Parent value: " << *obj.Parent->key << std::endl;
	else
		std::cout << "|No Parent" << obj.Parent->key << std::endl;
	if (obj.RChild)
		std::cout << "|Right child value: " << obj.RChild->key << std::endl;
	else
		std::cout << "|No Right Child" << std::endl;
	if (obj.LChild)
		std::cout << "|Left child value: " << obj.LChild->key << std::endl;
	else
		std::cout << "|No Left Child" << std::endl;
	std::cout << "--------------------" << std::endl;

	return os;
}

template<typename T>
void TreeNode<T>::PrintNode() {
	std::cout << "--------------------" << std::endl;
	std::cout << "|Node Data: " << key << std::endl;
	if (count > 0)
		std::cout << "|Node count: " << count << std::endl;
	if (Parent)
		std::cout << "|Parent value: " << Parent->key << std::endl;
	else
		std::cout << "|No Parent" << std::endl;
	if (RChild)
		std::cout << "|Right child value: " << RChild->key << std::endl;
	else
		std::cout << "|No Right Child" << std::endl;
	if (LChild)
		std::cout << "|Left child value: " << LChild->key << std::endl;
	else
		std::cout << "|No Left Child" << std::endl;
	std::cout << "--------------------" << std::endl;
}