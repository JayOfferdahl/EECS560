//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	4
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

// Return the value stored in this queue
Node* Queue::peekFront() {
	return m_front;
}

// Return the node at the end of the queue
Node* Queue::getBack() {
	return m_back;
}

// Set the node at the front of the queue to the input node
void Queue::setFront(Node* node) {
	m_front = node;
}

// Set the node at the back of the queue
void Queue::setBack(Node* node) {
	m_back = node;
}

// Adds an element to the back of the queue (use parent as next)
void Queue::push(Node* node) {
	// Make a new node for this queue
	Node* temp = new Node(node->getName(), node->getX(), node->getY());
	temp->left = node->left;
	temp->right = node->right;

	// The queue is empty
	if(size() < 1) {
		setFront(temp);
		setBack(temp);
	}
	// Queue has size 1
	else if(size() == 1) {
		setBack(temp);
		peekFront()->parent = temp;
	}
	// Add the new Node to the back of the queue
	else {
		getBack()->parent = temp;
		setBack(temp);
	}

	m_size++;
}

// Removes the first element of the queue and returns the value
Node* Queue::pop() {
	if(size() < 1) {
		std::cout << "Pop attempted on empty queue.\n";
	}
	else {
		Node* front = peekFront();
		setFront(front->parent);
		m_size--;

		return front;
	}
}

// Print out the queue in normal order
void Queue::print() {
	std::cout << "\n[";
	Node* temp = peekFront();

	// While not past the end of the queue
	while(temp != nullptr) {
		temp->print();

		// Formatting
		if(temp->parent != nullptr) {
			std::cout << ", ";
		}

		temp = temp->parent;
	}

	std::cout << "]\n";
}

// Returns true if m_front is null
bool Queue::isEmpty() {
	if(size() < 1) {
		return true;
	}
	else {
		return false;
	}
}

// Return the size of the queue
int Queue::size() {
	return m_size;
}