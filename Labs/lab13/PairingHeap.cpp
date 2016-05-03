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
					if(levelSize >= 1)
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
}


/**
 * Returns the root of the PairingHeap
 * @return the root stored in this heap
 */
PairingNode* PairingHeap::getRoot() {
	return m_root;
}