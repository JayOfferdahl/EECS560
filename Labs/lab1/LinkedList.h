//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	1
//
//***********************************************

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

class LinkedList
{
public:
	// Constructor Method
	LinkedList();
	
	// Deconstructor
	~LinkedList();

	// Adds an integer to the list
	void push(int);

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

	// Prints out the list
	void print();

private:
	// Private pointer to store the head
	Node* m_head;

	// Private pointer to store the tail
	Node* m_tail;
	
	// Size of the list
	int m_size;
};

#endif
