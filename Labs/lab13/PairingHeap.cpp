//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	13/14
//
//*****************************************************************************

#include <exception>
#include "PairingHeap.h"
#include "Queue.h"

#define DEBUG 1


/**
 * Constructs a new PairingHeap with a null root
 */
PairingHeap::PairingHeap() {
	m_root = nullptr;
}


/**
 * Inserts a value into the PairingHeap
 * @param value - the value to be inserted into the heap
 */
void PairingHeap::insert(int value) {
	PairingNode *temp = new PairingNode(value, nullptr, nullptr);

	if(m_root == nullptr)
		m_root = temp;
	else
		compareAndLink(m_root, temp);
}


/**
 * Deletes the smallest value stored in the PairingHeap (the root)
 * Afterwards, reforms the heap structure
 */
void PairingHeap::deleteMin() {
	if(m_root == nullptr) {
		std::cout << "Error: deleteMin attempted on empty heap.\n";
		return;
	}

	PairingNode *temp = m_root;

	if(m_root->leftChild == nullptr)
		m_root = nullptr;
	else
		m_root = combineSiblings(m_root->leftChild);

	delete temp;
}


/**
 * Links the first and second nodes together to satisfy heap order
 * @param first  - the root of the first tree
 * @param second - the root of the second tree
 * @note         - first becomes the new root as a result of the merge
 *               - first->rightSibling must be nullptr
 */
void PairingHeap::compareAndLink(PairingNode *& first, PairingNode * second) {
	if(second == nullptr)
		return;

	if(second->val < first->val) {
		// Attach first as leftmost child of second
		first->rightSibling = second->leftChild;
		second->leftChild = first;
		first = second;
	}
	else {
		// Attach second as leftmost child of first
		first->rightSibling = second->rightSibling;
		second->rightSibling = first->leftChild;
		first->leftChild = second;
	}
}


/**
 * Method to combine the siblings of a starting node, uses two-pass merging
 * @param  node - the node to start at (should be leftmost)
 * @return      - the root of the output heap
 */
PairingNode* PairingHeap::combineSiblings(PairingNode *node) {
	// If there's no sibling, this node is already the root
	if(node->rightSibling == nullptr)
		return node;

	PairingNode *temp = node->rightSibling,
				*prev = node;
	int 		numSiblings = 1,
				leftPass = 0,
				rightPass;

	// Calculate the number of siblings we'll be combining
	while(temp != nullptr) {
		temp = temp->rightSibling;
		numSiblings++;
	}

	// Store all of the siblings in direct access
	PairingNode *siblings[numSiblings];

	// Reset temp
	temp = node;

	for(int i = 0; i < numSiblings; i++) {
		siblings[i] = temp;
		temp = temp->rightSibling;
		prev->rightSibling = nullptr;
		prev = temp;
	}

	// Combine subtrees two at a time (left to right)
	for(leftPass = 0; leftPass + 1 < numSiblings; leftPass += 2)
		compareAndLink(siblings[leftPass], siblings[leftPass + 1]);

	rightPass = leftPass - 2;

	if(rightPass == numSiblings - 3)
		compareAndLink(siblings[rightPass], siblings[rightPass + 2]);

	// Merge right to left
	for(; rightPass >= 2; rightPass -= 2)
		compareAndLink(siblings[rightPass - 2], siblings[rightPass]);

	return siblings[0];
}


/**
 * Prints the heap by using a level order search
 */
void PairingHeap::printHeap() {
	// Strategy: Add nodes to the queue, and while the queue isn't empty, print them out.
	if(m_root != nullptr) {
		Queue* queue = new Queue();
		PairingNode *temp, *holder, *scout;
		PairingNode *dummy = new PairingNode(-1000000, nullptr, nullptr);
		int level = 0, levelSize;

		queue->push(m_root);

		while(!queue->isEmpty()) {
			// Determine how many nodes are on this level
			levelSize = queue->size();
			std::cout << "Level " << level << ": ";

			// Print out the right siblings
			while(levelSize > 0) {
				temp = queue->pop();

				if(temp->val == -1000000)
					std::cout << " * ";
				else {
					temp->print();

				#if DEBUG
					if(temp->leftChild != nullptr)
						std::cout << "(" << temp->leftChild->val << ") ";
				#endif

					// See if the next is nullptr
					if(temp->rightSibling != nullptr)
						std::cout << "->";

					if(levelSize == 1)
						std::cout << " * ";

					if(temp->leftChild != nullptr) {
						queue->push(temp->leftChild);
						scout = temp->leftChild->rightSibling;
						
						while(scout != nullptr) {
							queue->push(scout);
							scout = scout->rightSibling;
						}
					}
					else {
						dummy = new PairingNode(-1000000, nullptr, nullptr);
						queue->push(dummy);
					}
				}
				levelSize--;
			}
			// Move onto a new level
			std::cout << "\n";
			level++;
		}
		delete queue;
	}
	else
		std::cout << "The Pairing Heap is empty!\n";
}