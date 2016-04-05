//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#ifndef NODE_H
#define NODE_H

#include "proj1_Fraction.h"

class Node
{
public:
	// Create a Node with Fraction Fraction
	Node(Fraction*);

	// Deallocates any memory associated with this Node
	~Node();
	
	// Return the Fraction stored in this Node
	Fraction* getFraction();

	// Return the next Node this Node is pointing at
	Node* getNext();

	// Set the value stored in this Node to the input int
	void setValue(Fraction*);

	// Set the next Node this Node is pointing at to the input
	void setNext(Node*);

private:
	// Private pointer to the next Node
	Node* m_next;
	
	// Value stored in this Node
	Fraction* m_frac;
};

#endif
