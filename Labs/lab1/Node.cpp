//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	1
//
//***********************************************

#include "Node.h"

// Construct a Node with the specified value and nullptr next Node
Node::Node(int value) {
	setNext(nullptr);
	setValue(value);
}

// Returns the value stored in the Node
int Node::getValue() {
	return m_value;
}

// Returns the next Node this Node is pointing at
Node* Node::getNext() {
	return m_next;
}

// Sets the value stored in the Node
void Node::setValue(int value) {
	m_value = value;
}

// Sets the next Node for this Node to point at
void Node::setNext(Node* next) {
	m_next = next;
}
