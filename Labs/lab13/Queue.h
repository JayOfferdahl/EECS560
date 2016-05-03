//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	13/14
//
//*****************************************************************************

#ifndef QUEUE_H
#define QUEUE_H

#include "PairingHeap.h"

class Queue
{
public:
	// Create a queue with no elements
	Queue();

	// Creat a queue with an initial starting value
	Queue(PairingNode*);
	
	// Return the node at the front of the queue
	PairingNode* peekFront();

	// Return the node at the back of the queue
	PairingNode* getBack();

	// Set the value stored in this Node to the input int
	void setFront(PairingNode*);

	// Set the back of the queue to input Node
	void setBack(PairingNode*);

	// Adds an element to the back of the queue
	void push(PairingNode*);

	// Removes the first element of the queue and returns the value
	PairingNode* pop();

	// Print out the queue in normal order
	void print();

	// Returns true if m_front is null
	bool isEmpty();

	// Return the size of the queue
	int size();

private:
	// Private pointers to the front & back of the queue
	PairingNode* m_front;
	PairingNode* m_back;

	int m_size;
};

#endif
