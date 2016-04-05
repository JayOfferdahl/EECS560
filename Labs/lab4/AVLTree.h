//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	4
//
//*****************************************************************************

#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include "Queue.h"

class AVLTree
{
public:
	// Initialize an AVL tree with no root
	AVLTree();

	// Add a value to the AVL Tree
	void insert(std::string, int, int);

	// Internal function to recursively insert the Node
	Node* insert(Node*, Node*&);

	// Remove a city from the AVL Tree by name
	void remove(std::string);

	// Remove a city from the AVL Tree by coordinates
	void remove(int, int);

	// Removes the node from the AVL Tree
	void remove(std::string, Node*&);

	// Balances the tree at the current Node
	void balance(Node*&);

	// Do a single rotation (LL) on the tree. Update the stored height values
	void rotateLeftChild(Node*&);

	// Do a double rotation (LR) on the tree
	void doubleLeftChild(Node*&);

	// Do a single rotation (RR) on the tree. Update the stored height values
	void rotateRightChild(Node*&);

	// Do a dobule rotation (RL) on the tree
	void doubleRightChild(Node*&);

	// Return the height of the node in the tree while accounting for nullptrs
	int height(Node*);

	// Search for the selected value in the tree
	// @return the node, if it exists (nullptr otherwise)
	Node* search(std::string);

	// Search for the city by coordinates (use breadth first search)
	// @return the node, if it exists (nullptr otherwise)
	Node* search(int, int);

	// Prints the BST out in level order
	void levelOrderPrint();

	// Find the smallest value in the tree
	Node* findSmallest(Node*);

	// Pointer to the root of this tree
	Node* root;	
};

#endif