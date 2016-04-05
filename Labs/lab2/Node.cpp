//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	2
//
//***********************************************

#include "Node.h"

// Construct a Node with the specified value left and right children as nullptr
Node::Node(int value) {
	setValue(value);
	setNext(nullptr);
	setLeft(nullptr);
	setRight(nullptr);
}

// Returns the value stored in the Node
int Node::getValue() {
	return m_value;
}

// Sets the value stored in the Node
void Node::setValue(int value) {
	m_value = value;
}

// Return the left child of this Node
Node* Node::getLeft() {
	return m_left;
}

// Return the right child of this Node
Node* Node::getRight() {
	return m_right;
}

// Return the next Node of this Node
Node* Node::getNext() {
	return m_next;
}

// Sets the left child Node for this Node
void Node::setLeft(Node* node) {
	m_left = node;
}

// Sets the right child Node for this Node
void Node::setRight(Node* node) {
	m_right = node;
}

// Sets the next Node for this Node
void Node::setNext(Node* node) {
	m_next = node;
}
