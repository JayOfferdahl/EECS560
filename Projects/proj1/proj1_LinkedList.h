//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "proj1_Node.h"
#include "proj1_Fraction.h"

class LinkedList
{
public:
	// Constructor Method
	LinkedList();
	
	// Deconstructor
	~LinkedList();

	// Adds an integer to the list
	void push(Fraction*);

	// Reverses the list
	void reverse();

	// Changes the head of the list to the input Node
	void setHead(Node*);

	// Returns the head of the list
	Node* getHead();

	// Changes the tail of the list to the input Node
	void setTail(Node*);
	
	// Returns the tail of the list
	Node* getTail();

	// Sorts the linked list in ascending order (head is smallest)
	void sort();

	// Prints the list of Fractions
	void print();

	// Returns the size of the list
	int getSize();

private:
	// Private pointer to store the head
	Node* m_head;

	// Private pointer to store the tail
	Node* m_tail;
	
	// Size of the list
	int m_size;
};

#endif
