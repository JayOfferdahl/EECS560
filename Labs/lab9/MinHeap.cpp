//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	9
//
//*****************************************************************************

#include <iostream>
#include "MinHeap.h"

// Initialize a min heap with nothing in it
MinHeap::MinHeap() {}

// Builds the initial heap from the input array and array size by percolating
// down each node until the node's value is in the correct spot
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinHeap::buildHeap(int arrSize, int* arr) {
	for(int i = arrSize / 2; i > 0; i--) 
		pushDown(i, arrSize, arr, 0);
}

// Inserts a value into the minmax heap
// @param val - the value to be inserted into the heap
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinHeap::insert(int val, int* arrSize, int* arr) {
	arr[(*arrSize)++] = val;
	pushUp(*arrSize, arr);
}

// Delete the minimum value from the min-max heap
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinHeap::deleteMin(int* arrSize, int* arr) {
	if(*arrSize > 0) {
		arr[0] = arr[(*arrSize)-- - 1];
		pushDown(1, *arrSize, arr, 0);
	}
}

// Moves an item down the heap until the correct spot for it is found
// @param index - the index of the heap to push down (the node position) - 1 based
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinHeap::pushDown(int index, int arrSize, int* arr, int version) {
	int val = arr[index - 1];
	int position = index, temp, child;

	while(position <= arrSize) {
		child = position * 2;

		// Store the smaller child in temp, if there are any
		if(child + 1 > arrSize) {
			// Has left child but no right child
			if(child <= arrSize)
				temp = child;
			else
				temp = 0;
		}
		// Has two children
		else
			temp = arr[child - 1] < arr[child] ? child : child + 1;

		// If on a leaf, we found the correct spot
		if(temp == 0) {
			arr[position - 1] = val;
			// If improved version, pushup the value
			if(version == 1)
				pushUp(position, arr);
			break;
		}
		// If improved version, don't compare parent and smaller child
		else if(version == 1) {
			arr[position - 1] = arr[temp - 1];
			position = temp;
		}
		// Check to see if child is smaller than parent, if so, push parent down
		else if(val > arr[temp - 1]) {
			arr[position - 1] = arr[temp - 1];
			position = temp;
		}
		// The correct position has been found, no further action required
		else {
			arr[position - 1] = val;
			break;
		}
	}
}

// Moves an item up the heap until it's parent is smaller than it
// @param index - the index of the heap to push up (the node position) - 1 based
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinHeap::pushUp(int index, int* arr) {
	int val = arr[index - 1];
	int position = index;

	while(position > 1) {
		if(val < arr[position / 2 - 1]) {
			arr[position - 1] = arr[position / 2 - 1];
			position = position / 2;
		}
		else
			break;
	}

	arr[position - 1] = val;
}

// Sorts the list in descending order (min heap sort)
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinHeap::heapSort(int arrSize, int* arr, int version) {
	int heapSize = arrSize;
	int temp;

	// Strategy: loop through the list, do a deletemin operation, continue
	while(heapSize > 0) {
		heapSize--;

		// Delete the minimum value & fix heap properties
		temp = arr[0];
		arr[0] = arr[heapSize];
		arr[heapSize] = temp;
		pushDown(1, heapSize, arr, version);
	}
}

// Swaps the two specified indexes in the array
// @pre - assumes the indexes are in range within the array
// @param index1 - the input value to seed the randomly generated number with
// @param index2 - the input array to fill with random values
// @param arr - the size of the input array
// @note - modifies the array
void MinHeap::swap(int index1, int index2, int* arr) {
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

// Prints out the input array
// @param size - the size of the input array
// @param arr - the input array to reset
void MinHeap::printArr(int size, int* arr) {
	std::cout << "[";
	for(int i = 0; i < size; i++) {
		std::cout << arr[i];
		if(i != size - 1)
			std::cout << ", ";
	}
	std::cout << "]\n";
}