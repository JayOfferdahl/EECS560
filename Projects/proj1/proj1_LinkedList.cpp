//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#include "proj1_LinkedList.h"
#include <iostream>

// Constructs a linked list with null head and tail, and size 0
LinkedList::LinkedList() {
	setHead(nullptr);
	setTail(nullptr);
	m_size = 0;
}

// Properly deletes the list from memory
LinkedList::~LinkedList() {
	Node* current = getHead();
	Node* temp;

	while(current != nullptr) {
		temp = current->getNext();
		delete current;
		current = temp;
	}
}

// Adds a value to the list, if the list is empty, the value is the head and tail
void LinkedList::push(Fraction* frac) {
	Node* node = new Node(frac);

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

// Sorts the linked list in ascending order (head is smallest)
void LinkedList::sort() {
	if(m_size > 1) {
		Node *current, *post, *tempNode;
		current = post = tempNode = nullptr;

		Fraction* temp;
		bool swapped = true;

		while(swapped) {
			swapped = false;
			current = post = getHead();

			while(current->getNext() != nullptr) {
				int result = temp->less(current->getNext()->getFraction(), current->getFraction());
				// If A[i + 1] is less than or equal to A[i], swap em
				if(result == 1) {
					tempNode = current->getNext();
					current->setNext(current->getNext()->getNext());
					tempNode->setNext(current);

					if(current == getHead()) {
						setHead(tempNode);
						post = tempNode;
					}
					else {
						post->setNext(tempNode);
					}

					current = tempNode;
					swapped = true;
				}
				post = current;
				current = current->getNext();
			}
		}
		setTail(current);
	}
}

// Prints out the list of Fractions
void LinkedList::print() {
	Node* temp = getHead();
	std::cout << "[";

	while(temp != nullptr) {
		temp->getFraction()->print();

		if(temp->getNext() != nullptr) {
			std::cout << ", ";
		}
		temp = temp->getNext();
	}

	std::cout << "]\n";
}

// Returns the size of the list
int LinkedList::getSize() {
	return m_size;
}