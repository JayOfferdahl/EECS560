//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	5
//
//*****************************************************************************

#include <math.h>
#include <iostream>
#include <exception>
#include "AVLTree.h"

// Initialize an AVL tree with no root
AVLTree::AVLTree() {
	root = nullptr;
}

// Add a city to the AVL Tree, balance if necessary
void AVLTree::insert(std::string name, int x, int y, bool print) {
	Node* node = new Node(name, x, y);

	// Comparison counter starts at 1 (check root against nullptr)
	int compCounter = 1;

	if(root == nullptr) {
		root = node;
		if(print)
			std::cout << "Adding to the tree took 1 comparison!\n";
	}
	else
		insert(node, root, compCounter, print);
}

// Add a city to the AVL Tree, and balance it (must be recursive)
void AVLTree::insert(Node* val, Node*& temp, int compCounter, bool print) {
	// Search for the correct spot for this node
	// If two nodes are equal, put it to the right
	if(temp == nullptr) {
		temp = new Node(val->getName(), val->getX(), val->getY());

		if(print)
			std::cout << "Adding to the tree took " << ++compCounter << " comparisons!\n";

		// Delete the temporary node that was created
		delete val;
	}
	else if(val->getName().compare(temp->getName()) < 0) {
		compCounter += 2;
		insert(val, temp->left, compCounter, print);
	}
	else if(val->getName().compare(temp->getName()) >= 0) {
		compCounter += 3;
		insert(val, temp->right, compCounter, print);
	}

	balance(temp);
}

// Remove a city from the AVL Tree by name
int AVLTree::remove(std::string name) {
	return remove(name, root);
}

// Remove a city from the AVL Tree by coordinates
int AVLTree::remove(int x, int y) {
	// Find the node to remove (tree isn't organized by coordinates)
	Node* toRemove = search(x, y);
	if(toRemove->getName().compare("NOT_A_CITY") == 0)
		return toRemove->comps;

	int searchComps = toRemove->comps;
	
	return remove(toRemove->getName(), root) + searchComps;
}

// Removes the node from the AVL Tree
int AVLTree::remove(std::string name, Node*& temp) {
	int comps = 0;
	// The item is not in the list
	if(temp == nullptr)
		return 1;

	// Remove from left side
	if(name.compare(temp->getName()) < 0) {
		comps += remove(name, temp->left) + 2;
	}
	// Remove from right side
	else if(name.compare(temp->getName()) > 0) {
		comps += remove(name, temp->right) + 3;
	}
	// If the node has two children, replace this one with the 
	// smallest value in the right sub tree
	else if(temp->left != nullptr && temp->right != nullptr) {
		Node* replace = findSmallest(temp->right);
		temp->setName(replace->getName());
		temp->setX(replace->getX());
		temp->setY(replace->getY());
		comps += remove(replace->getName(), temp->right) + 5;
	}
	// One or no children
	else {
		Node* node = temp;
		if(temp->left != nullptr)
			temp = temp->left;
		else
			temp = temp->right;

		delete node;
		comps += 6;
	}

	// Balance the tree in case it became unbalanced
	balance(temp);
	return comps;
}

// Balance the selected node
void AVLTree::balance(Node*& node) {
	// Can't balance nothing
	if(node == nullptr)
		return;

	// Left Side
	if(height(node->left) - height(node->right) == 2) {
		if(height(node->left->left) >= height(node->left->right))
			rotateLeftChild(node);
		else
			doubleLeftChild(node);
	}
	// Right side
	else if(height(node->right) - height(node->left) == 2) {
		if(height(node->right->right) >= height(node->right->left))
			rotateRightChild(node);
		else
			doubleRightChild(node);
	}

	// Update height (max of left & right children, plus 1)
	int h = height(node->left) > height(node->right)
		? height(node->left) : height(node->right);
	node->setHeight(h + 1);
}

// Do a single rotation (RR) on the tree. Update the stored height values
void AVLTree::rotateLeftChild(Node*& node) {
	//std::cout << "Rotating Right. Val: " << node->getName() << "\n";
	Node* temp = node->left;
	node->left = temp->right;
	temp->right = node;

	// Update heights (max of left & right children, plus 1)
	int h = height(node->left) > height(node->right) 
		  ? height(node->left) : height(node->right);
	node->setHeight(h + 1);
	h = height(temp->left) > node->getHeight()
		? height(temp->left) : node->getHeight();
	temp->setHeight(h + 1);

	node = temp;
}

// Do a double rotation (RL) on the tree
void AVLTree::doubleLeftChild(Node*& node) {
	//std::cout << "Doing a double rotation...LEFT RIGHT\n";
	rotateRightChild(node->left);
	rotateLeftChild(node);
}

// Do a single rotation (LL) on the tree. Update the stored height values
void AVLTree::rotateRightChild(Node*& node) {
	//std::cout << "Rotating Left. Val: " << node->getName() << "\n";
	Node* temp = node->right;
	node->right = temp->left;
	temp->left = node;

	// Update heights (max of left & right children, plus 1)
	int h = height(node->left) > height(node->right)
		? height(node->left) : height(node->right);
	node->setHeight(h + 1);
	h = height(temp->right) > node->getHeight()
		? height(temp->right) : node->getHeight();
	temp->setHeight(h + 1);

	node = temp;
}

// Do a double rotation (LR) on the tree
void AVLTree::doubleRightChild(Node*& node) {
	//std::cout << "Doing a double rotation...RIGHT LEFT\n";
	rotateLeftChild(node->right);
	rotateRightChild(node);
}

// Return the height of the node, and account for nullptr
int AVLTree::height(Node* node) {
	if(node == nullptr)
		return -1;

	return node->getHeight();
}

// Search for the city by name in the tree
// @return the node, if it exists (nullptr otherwise)
Node* AVLTree::search(std::string name) {
	Node* temp = root;

	// While not past a leaf
	while(temp != nullptr) {
		if(name.compare(temp->getName()) == 0)
			return temp;
		// Search left
		else if(name.compare(temp->getName()) < 0)
			temp = temp->left;
		// Search right
		else
			temp = temp->right;
	}

	// No value found
	return temp;
}

// Search for the city by coordinates. A full tree search has to be
// performed as the tree is not organized by coordinates, but names instead
// @return the node, if it exists (nullptr otherwise)
Node* AVLTree::search(int x, int y) {
	int compCounter = 1;
	if(root != nullptr) {
		Queue* queue = new Queue();
		Node* temp;

		queue->push(root);

		while(!queue->isEmpty()) {
			temp = queue->pop();
			// Account for the two comparisons here (before returning)
			compCounter += 2;
			if(x == temp->getX() && y == temp->getY()) {
				delete queue;
				temp->comps = compCounter;
				return temp;
			}

			// Add this nodes children to the queue
			if(temp->left != nullptr)
				queue->push(temp->left);
			if(temp->right != nullptr)
				queue->push(temp->right);

			// Account for the two children comparisons
			compCounter += 2;
		}
		delete queue;
	}

	// Return the number of comparisons in a dummy node
	Node* compNode = new Node("NOT_A_CITY", -1, -1);
	compNode->comps = compCounter;
	return compNode;
}


// Prints the AVLTree out in level order
void AVLTree::levelOrderPrint() {
	// Strategy: Add nodes to the queue, and while the queue isn't empty, print them out.
	if(root != nullptr) {
		Queue* queue = new Queue();
		Node* temp;
		bool firstPrint = true;
		int level = 0, levelSize = 1;

		queue->push(root);

		while(!queue->isEmpty()) {
			// Determine how many nodes are on this level
			levelSize = queue->size();

			std::cout << "Level " << level << ": ";

			// While there are still nodes on this level
			while(levelSize > 0) {
				temp = queue->pop();

				// Add this nodes children to the queue
				if(temp->left != nullptr)
					queue->push(temp->left);
				else if(temp->getName().compare("*") != 0)
					queue->push(new Node("*", -1, -1));
				if(temp->right != nullptr)
					queue->push(temp->right);
				else if(temp->getName().compare("*") != 0)
					queue->push(new Node("*", -1, -1));

				// Formatting
				if(!firstPrint)
					std::cout << ", ";
				else
					firstPrint = false;

				// Print out this node's value
				temp->print();

				levelSize--;
			}

			// Move onto a new level
			std::cout << "\n";
			firstPrint = true;
			level++;
		}
		delete queue;
	}
}

// Find the smallest value in the tree
Node* AVLTree::findSmallest(Node* node) {
	Node* current = node;

	while(current->left != nullptr)
		current = current->left;

	return current;
}

// Prints out all the cities within the input distance (as the crow flys)
void AVLTree::printInRange(int x, int y, double distance) {
	// Make sure there are cities to check against
	if(root != nullptr) {
		Queue* queue = new Queue();
		Node* temp;
		double tempDist;

		queue->push(root);

		std::cout << "\n********************************************************************\n";
		std::cout << "                               AVL Tree                             \n";
		std::cout << "********************************************************************\n";

		std::cout << "\nCities in a " << distance << " mile range of (" 
				  << x << ", " << y << "):\n";

		temp = search(x, y);
		if(temp != nullptr) {
			std::cout << temp->getName() << " is located at (" << x << ", " << y << ")!\n";
		}

		while(!queue->isEmpty()) {
			temp = queue->pop();

			// Calculate the distance from the input point
			tempDist = sqrt(pow(temp->getX() - x, 2) + pow(temp->getY() - y, 2));

			// If the calculated distance is within range
			if(tempDist <= distance) {
				if(tempDist == 0) {}
					// Do nothing, we already printed it!
				else
					std::cout << temp->getName() << "\n   Distance: " << tempDist << "\n";
			}

			// Add this nodes children to the queue
			if(temp->left != nullptr)
				queue->push(temp->left);
			if(temp->right != nullptr)
				queue->push(temp->right);
		}
		delete queue;
	}
	else
		std::cout << "There are no cities on record.\n";
}