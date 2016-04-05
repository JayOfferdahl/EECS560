//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	2
//
//***********************************************

#include <math.h>
#include <iostream>
#include "BinarySearchTree.h"

// Initialize a BST with no root
BinarySearchTree::BinarySearchTree() {
	setRoot(nullptr);
}

// Initialize a BST with a root value
BinarySearchTree::BinarySearchTree(int value) {
	push(value);
}

// Add a value to the BST
void BinarySearchTree::push(int value) {
	Node* node = new Node(value);

	// Size is 0, set the root
	if(getRoot() == nullptr) {
		setRoot(node);
	}
	else {
		Node* temp = getRoot();

		// Search for the correct spot for this node
		// If two nodes are equal, put it to the right
		while(temp != nullptr) {
			if(value < temp->getValue()) {
				if(temp->getLeft() == nullptr) {
					temp->setLeft(node);
					break;
				}
				else {
					temp = temp->getLeft();
				}
			}
			else if(value >= temp->getValue()) {
				if(temp->getRight() == nullptr) {
					temp->setRight(node);
					break;
				}
				else {
					temp = temp->getRight();
				}
			}
		}
	}
}

// Returns the root Node of the BST
Node* BinarySearchTree::getRoot() {
	return m_root;
}

// Sets the root node of the BST
void BinarySearchTree::setRoot(Node* node) {
	m_root = node;
}

// Search for the selected value in the tree
bool BinarySearchTree::search(int value) {
	Node* temp = getRoot();

	// While not past a leaf
	while(temp != nullptr) {
		if(value == temp->getValue()) {
			return true;
		}
		// Search left
		else if(value < temp->getValue()) {
			temp = temp->getLeft();
		}
		// Search right
		else {
			temp = temp->getRight();
		}
	}

	// No value found
	return false;
}

// Prints the BST out in level order
void BinarySearchTree::levelOrderPrint() {
	// Strategy: Add nodes to the queue, and while the queue isn't empty, print them out.
	if(getRoot() != nullptr) {
		Queue* queue = new Queue();
		Node* temp;
		bool firstPrint = true;
		int level = 0, levelSize = 1;

		queue->push(getRoot());

		while(!queue->isEmpty()) {
			// Determine how many nodes are on this level
			levelSize = queue->size();

			std::cout << "Level " << level << ": ";

			// While there are still nodes on this level
			while(levelSize > 0) {
				temp = queue->pop();

				// Add this nodes children to the queue
				if(temp->getLeft() != nullptr) {
					queue->push(temp->getLeft());
				}
				if(temp->getRight() != nullptr) {
					queue->push(temp->getRight());
				}

				// Formatting
				if(!firstPrint) {
					std::cout << ", ";
				}
				else {
					firstPrint = false;
				}

				// Print out this node's value
				std::cout << temp->getValue();

				levelSize--;
			}

			// Move onto a new level
			std::cout << "\n";
			firstPrint = true;
			level++;
		}
	}
}

// Load the sorted array (with more than 2 elements) into this binary search tree
// Assumes this tree is empty to begin with
Node* BinarySearchTree::loadBST(int* arr, int start, int end) {
	if(start > end) {
		return nullptr;
	}
	else {
		int middle = (start + end) / 2;
		
		Node* node = new Node(arr[middle]);

		node->setLeft(loadBST(arr, start, middle - 1));
		node->setRight(loadBST(arr, middle + 1, end));

		return node;
	}
}