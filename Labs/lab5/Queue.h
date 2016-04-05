//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	5
//
//*****************************************************************************

#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue
{
public:
	// Create a queue with no elements
	Queue();
	
	// Return the node at the front of the queue
	Node* peekFront();

	// Return the node at the back of the queue
	Node* getBack();

	// Set the value stored in this Node to the input int
	void setFront(Node*);

	// Set the back of the queue to input Node
	void setBack(Node*);

	// Adds an element to the back of the queue
	void push(Node*);

	// Removes the first element of the queue and returns the value
	Node* pop();

	// Print out the queue in normal order
	void print();

	// Returns true if m_front is null
	bool isEmpty();

	// Return the size of the queue
	int size();

private:
	// Private pointers to the front & back of the queue
	Node* m_front;
	Node* m_back;

	int m_size;
};

#endif
