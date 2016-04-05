//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	1
//
//***********************************************

#include "LinkedList.h"
#include <iostream>

// Constructs a linked list with null head and tail, and size 0
LinkedList::LinkedList() {
	setHead(nullptr);
	setTail(nullptr);
	m_size = 0;
}

// Properly deletes the list from memory
LinkedList::~LinkedList() {

}

// Adds a value to the list, if the list is empty, the value is the head and tail
void LinkedList::push(int value) {
	Node* node = new Node(value);

	if(m_size == 0) {
		setHead(node);
		setTail(node);
	}
	else {
		Node* temp = getTail();
		setTail(node);
		temp->setNext(node);
	}

	m_size++;
}

// Reverses the linked list and swaps head and tail pointers
void LinkedList::reverse() {
	// Single item
	if(m_size <= 1) {
		// Ok, it's reversed.
	}
	// 2 Elements
	else if(m_size == 2) {
		m_head->setNext(nullptr);
		m_tail->setNext(m_head);
		m_head = m_tail;
		m_tail = m_head->getNext();
	}
	// More than 2 elements
	else {
		Node* temp = nullptr;
		Node* current = m_head;
		Node* next = m_head->getNext();
		
		m_tail = current;

		while(current != nullptr) {
			current->setNext(temp);
			temp = current;
			current = next;
			
			if(next != nullptr) {
				next = next->getNext();
			}
		}

		m_head = temp;
	}
}

// Prints out the linked list in array format
void LinkedList::print() {
	Node* current = getHead();
	std::cout << "[";

	while(current != nullptr) {
		// Print out the node's value
		std::cout << current->getValue();

		if(current->getNext() != nullptr) {
			std::cout << ", ";
		}

		current = current->getNext();
	}
	std::cout << "]";
}

// Sets the head to the input Node
void LinkedList::setHead(Node* node) {
	m_head = node;
}

// Returns the head of the list
Node* LinkedList::getHead() {
	return m_head;
}

// Sets the tail to the input Node
void LinkedList::setTail(Node* node) {
	m_tail = node;
}

// Returns the tail of the list
Node* LinkedList::getTail() {
	return m_tail;
}
