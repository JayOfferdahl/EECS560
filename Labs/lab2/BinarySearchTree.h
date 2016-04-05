//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	2
//
//***********************************************

#ifndef BST_H
#define BST_H

#include "Node.h"
#include "Queue.h"

class BinarySearchTree
{
public:
	// Initialize a BST with no root
	BinarySearchTree();

	// Initialize a BST with a root value
	BinarySearchTree(int);

	// Add a value to the BST
	void push(int);

	// Returns the root Node of the BST
	Node* getRoot();

	// Sets the root Node of the BST
	void setRoot(Node*);

	// Search for the selected value in the tree
	bool search(int);

	// Prints the BST out in level order
	void levelOrderPrint();

	// Loads the sorted array into this tree
	// Assumes this tree is empty
	Node* loadBST(int*, int, int);

private:
	// Private Node pointer to the root of the BST
	Node* m_root;
};

#endif
