//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	2
//
//***********************************************

#ifndef NODE_H
#define NODE_H

class Node
{
public:
	// Create a Node with value value
	Node(int);
	
	// Return the value stored in this Node
	int getValue();

	// Set the value stored in this Node to the input int
	void setValue(int);

	// Return the left child of this Node
	Node* getLeft();

	// Return the right child of this Node
	Node* getRight();

	// Return the next Node of this Node
	Node* getNext();

	// Set the left child node of this Node
	void setLeft(Node*);

	// Set the right child Node of this Node
	void setRight(Node*);

	// Set the next Node of this Node
	void setNext(Node*);

private:
	// Private pointers to the children Nodes
	Node* m_left;
	Node* m_right;
	Node* m_next;
	
	// Value stored in this Node
	int m_value;
};

#endif
