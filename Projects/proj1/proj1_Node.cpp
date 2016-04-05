//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#include "proj1_Node.h"

// Construct a Node with the specified value and nullptr next Node
Node::Node(Fraction* frac) {
	setNext(nullptr);
	Fraction* temp = new Fraction(frac->getNum(), frac->getDenom(), frac->getMixedN());
	setValue(temp);
}

// Deallocates any memory associated with this Node
Node::~Node() {
	delete m_frac;
}

// Returns the value stored in the Node
Fraction* Node::getFraction() {
	return m_frac;
}

// Returns the next Node this Node is pointing at
Node* Node::getNext() {
	return m_next;
}

// Sets the value stored in the Node
void Node::setValue(Fraction* frac) {
	m_frac = frac;
}

// Sets the next Node for this Node to point at
void Node::setNext(Node* next) {
	m_next = next;
}
