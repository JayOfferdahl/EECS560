//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	13/14
//
//*****************************************************************************

#ifndef PAIRINGHEAP_H
#define PAIRINGHEAP_H

#include <iostream>

/**
 * Struct for the nodes that will make up the pairing heap
 *
 * Each PairingNode can progress to it's left child, or right sibling, but not
 * to the parent, left sibling, or right child. (To get to right child,
 * move to left child, and then to the right sibling of the left child.)
 */
struct PairingNode {
	int val;

	PairingNode *leftChild;
	PairingNode *rightSibling;

	PairingNode *next;

	PairingNode(int value, PairingNode *left, PairingNode *right) :
		val(value), leftChild(left), rightSibling(right), next(nullptr) {}

	void print() {
		std::cout << " " << val << " ";
	}
};

class PairingHeap
{
public:
	PairingHeap();

	void insert(int);

	void compareAndLink(PairingNode *&, PairingNode*);

	void printHeap();

	PairingNode* getRoot();

private:
	PairingNode *m_root;	
};

#endif