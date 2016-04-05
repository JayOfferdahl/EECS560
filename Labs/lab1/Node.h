//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	1
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

	// Return the next Node this Node is pointing at
	Node* getNext();

	// Set the value stored in this Node to the input int
	void setValue(int);

	// Set the next Node this Node is pointint at to the input
	void setNext(Node*);

private:
	// Private pointer to the next Node
	Node* m_next;
	
	// Value stored in this Node
	int m_value;
};

#endif
