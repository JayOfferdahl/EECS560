//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	5
//
//*****************************************************************************

#include "Node.h"
#include <iostream>
#include <exception>

// Construct a Node with the input name, x, and y coordinates
Node::Node(std::string name, int x, int y) {
	// Initialize stored information
	setName(name);
	setX(x);
	setY(y);

	// Initialize Pointers
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Return the city stored in this Node
std::string Node::getName() {
	return m_name;
}

// Return the x coordinate of this Node
int Node::getX() {
	return m_x;
}

// Return the y coordinate of this Node
int Node::getY() {
	return m_y;
}

// Set the citry name stored in this Node to the input string
void Node::setName(std::string name) {
	m_name = name;
}

// Set the x coordinate of this Node
void Node::setX(int x) {
	m_x = x;
}

// Set the y coordinate of this Node
void Node::setY(int y) {
	m_y = y;
}

// Return the balance factor of this Node
int Node::getHeight() {
	return m_height;
}

// Set the balance factor of this Node
void Node::setHeight(int height) {
	m_height = height;
}

// Prints out the Node
void Node::print() {
	std::cout << getName();
}