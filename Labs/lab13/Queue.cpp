//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	13/14
//
//*****************************************************************************

#include "Queue.h"
#include <iostream>

// Create a queue with no elements
Queue::Queue() {
	setFront(nullptr);
	setBack(nullptr);
	m_size = 0;
}

// Creat a queue with an initial starting value
Queue::Queue(PairingNode* node) {
	m_size = 0;
	push(node);
}

// Return the value stored in this queue
PairingNode* Queue::peekFront() {
	return m_front;
}

// Return the PairingNode at the end of the queue
PairingNode* Queue::getBack() {
	return m_back;
}

// Set the PairingNode at the front of the queue to the input PairingNode
void Queue::setFront(PairingNode* node) {
	m_front = node;
}

// Set the PairingNode at the back of the queue
void Queue::setBack(PairingNode* node) {
	m_back = node;
}

// Adds an element to the back of the queue
void Queue::push(PairingNode* node) {
	// The queue is empty
	if(size() < 1) {
		setFront(node);
		setBack(node);
	}
	// Queue has size 1
	else if(size() == 1) {
		setBack(node);
		peekFront()->next = node;
	}
	// Add the new PairingNode to the back of the queue
	else {
		getBack()->next = node;
		setBack(node);
	}

	m_size++;
}

// Removes the first element of the queue and returns the value
PairingNode* Queue::pop() {
	if(size() < 1)
		std::cout << "Pop attempted on empty queue.\n";
	else {
		PairingNode* front = peekFront();
		setFront(front->next);
		m_size--;

		return front;
	}
}

// Print out the queue in normal order
void Queue::print() {
	std::cout << "\n[";
	PairingNode* temp = peekFront();

	// While not past the end of the queue
	while(temp != nullptr) {
		std::cout << temp->val;

		// Formatting
		if(temp->next != nullptr)
			std::cout << ", ";

		temp = temp->next;
	}

	std::cout << "]\n";
}

// Returns true if m_front is null
bool Queue::isEmpty() {
	if(size() < 1)
		return true;
	else
		return false;
}

// Return the size of the queue
int Queue::size() {
	return m_size;
}