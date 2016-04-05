//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	9
//
//*****************************************************************************

#include <iostream>
#include <math.h>
#include "MinMaxHeap.h"

// Initialize a min heap with nothing in it
MinMaxHeap::MinMaxHeap() {}

// Builds the initial heap from the input array and array size
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::buildHeap(int arrSize, int* arr) {
	for(int i = arrSize / 2; i > 0; i--) 
		trickleDown(i, arrSize, arr);
}

// Inserts a value into the minmax heap
// @param val - the value to be inserted into the heap
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::insert(int val, int* arrSize, int* arr) {
	arr[(*arrSize)++] = val;
	bubbleUp(*arrSize, *arrSize, arr);
}

// Delete the minimum value from the min-max heap
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::deleteMin(int* arrSize, int* arr) {
	if(*arrSize > 0) {
		arr[0] = arr[(*arrSize)-- - 1];
		trickleDownMin(1, *arrSize, arr);
	}
}

// Deletes the maximum value from the min-max heap
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::deleteMax(int* arrSize, int* arr) {
	if(*arrSize >= 1) {
		int deleted;
		// Both children exist
		if(*arrSize >= 3) {
			int index = arr[1] > arr[2] ? 2 : 3;
			deleted = arr[index - 1];
			arr[index - 1] = arr[(*arrSize)-- - 1];
			trickleDownMax(index, *arrSize, arr);
		}
		// Left child exists only
		else if(*arrSize >= 2) {
			deleted = arr[1];
			(*arrSize)--;
		}
		// No children, remove the root
		else {
			deleted = arr[0];
			(*arrSize)--;
		}
	}
}

// Trickles down the heap until the correct posisiton for the element at index i
// is found, checks what level the index is on (max or min).
// @param index - the position in the array of the element we're examining
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::trickleDown(int index, int arrSize, int* arr) {
	// If on an even level (min level)
	if((int) log2(index) % 2 == 0)
		trickleDownMin(index, arrSize, arr);
	else
		trickleDownMax(index, arrSize, arr);
}

// Trickles down the heap on min levels until the correct position is found
// @param index - the position in the array of the element we're examining
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::trickleDownMin(int index, int arrSize, int* arr) {
	int child = index * 2;
	int grandChild = child * 2;

	int temp = 0;

	// Store the smaller child in temp, if there are any
	if(child + 1 > arrSize) {
		// Has left child but no right child (no grandchildren)
		if(child <= arrSize)
			temp = child;
		else
			return;
	}
	// Has two children (and possibly grandchildren)
	else {
		// Find smaller of two children then compare with any grandchildren
		temp = arr[child - 1] < arr[child] ? child : child + 1;
		if(grandChild <= arrSize) { // At least 1 grandChild
			temp = arr[grandChild - 1] < arr[temp - 1] ? grandChild : temp;
			if(grandChild + 1 <= arrSize) { // At least 2 grandChildren
				temp = arr[grandChild] < arr[temp - 1] ? grandChild + 1 : temp;
				if(grandChild + 2 <= arrSize) { // At least 3 grandChildren
					temp = arr[grandChild + 1] < arr[temp - 1] ? grandChild + 2 : temp;
					if(grandChild + 3 <= arrSize) // All four grandChildren exist
						temp = arr[grandChild + 2] < arr[temp - 1] ? grandChild + 3 : temp;
				}
			}
		}
	}

	// If the smallest value is a grandChild
	if(temp >= grandChild) {
		if(arr[temp - 1] < arr[index - 1]) {
			swap(temp - 1, index - 1, arr);
			if(arr[temp - 1] > arr[temp / 2 - 1])
				swap(temp - 1, temp / 2 - 1, arr);
			trickleDownMin(temp, arrSize, arr);
		}
	}
	// Else, the smallest value was in a child
	else {
		if(arr[temp - 1] < arr[index - 1])
			swap(temp - 1, index - 1, arr);
	}
}

// Trickles down the heap on max levels until the correct position is found
// @param index - the position in the array of the element we're examining
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::trickleDownMax(int index, int arrSize, int* arr) {
	int child = index * 2;
	int grandChild = child * 2;

	int temp = 0;

	// Store the smaller child in temp, if there are any
	if(child + 1 > arrSize) {
		// Has left child but no right child (no grandchildren)
		if(child <= arrSize)
			temp = child;
		else
			return;
	}
	// Has two children (and possibly grandchildren)
	else {
		// Find smaller of two children then compare with any grandchildren
		temp = arr[child - 1] > arr[child] ? child : child + 1;
		if(grandChild <= arrSize) { // At least 1 grandChild
			temp = arr[grandChild - 1] > arr[temp - 1] ? grandChild : temp;
			if(grandChild + 1 <= arrSize) { // At least 2 grandChildren
				temp = arr[grandChild] > arr[temp - 1] ? grandChild + 1 : temp;
				if(grandChild + 2 <= arrSize) { // At least 3 grandChildren
					temp = arr[grandChild + 1] > arr[temp - 1] ? grandChild + 2 : temp;
					if(grandChild + 3 <= arrSize) // All four grandChildren exist
						temp = arr[grandChild + 2] > arr[temp - 1] ? grandChild + 3 : temp;
				}
			}
		}
	}

	// If the smallest value is a grandChild
	if(temp >= grandChild) {
		if(arr[temp - 1] > arr[index - 1]) {
			swap(temp - 1, index - 1, arr);
			if(arr[temp - 1] < arr[temp / 2 - 1])
				swap(temp - 1, temp / 2 - 1, arr);
			trickleDownMax(temp, arrSize, arr);
		}
	}
	// Else, the smallest value was in a child
	else {
		if(arr[temp - 1] > arr[index - 1])
			swap(temp - 1, index - 1, arr);
	}
}

// Bubbles up the heap until the correct posisiton is found for the element at index index.
// @param index - the position in the array of the element we're examining
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::bubbleUp(int index, int arrSize, int* arr) {
	// If index has a parent
	if(index / 2 != 0) {
		// If on an even level (min level)
		if((int) log2(index) % 2 == 0) {
			
			if(arr[index - 1] > arr[index / 2 - 1]) {
				swap(index - 1, index / 2 - 1, arr);
				bubbleUpMax(index / 2, arrSize, arr);
			}
			else
				bubbleUpMin(index, arrSize, arr);
		}
		// Else, on an odd level (max level)
		else {
			if(arr[index - 1] < arr[index / 2 - 1]) {
				swap(index - 1, index / 2 - 1, arr);
				bubbleUpMin(index / 2, arrSize, arr);
			}
			else
				bubbleUpMax(index, arrSize, arr);
		}
	}
}

// Bubbles up the heap on min levels until the correct position is found
// @param index - the position in the array of the element we're examining
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::bubbleUpMin(int index, int arrSize, int* arr) {
	// If index has a grandparent
	if(index / 4 != 0) {
		if(arr[index - 1] < arr[index / 4 - 1]) {
			swap(index - 1, index / 4 - 1, arr);
			bubbleUpMin(index / 4, arrSize, arr);
		}
	}
}

// Bubbles up the heap on max levels until the correct position is found
// @param index - the position in the array of the element we're examining
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void MinMaxHeap::bubbleUpMax(int index, int arrSize, int* arr) {
	// If index has a grandparent
	if(index / 4 != 0) {
		if(arr[index - 1] > arr[index / 4 - 1]) {
			swap(index - 1, index / 4 - 1, arr);
			bubbleUpMax(index / 4, arrSize, arr);
		}
	}
}

// Swaps the two specified indexes in the array
// @pre - assumes the indexes are in range within the array
// @param index1 - the input value to seed the randomly generated number with
// @param index2 - the input array to fill with random values
// @param arr - the size of the input array
// @note - modifies the array
void MinMaxHeap::swap(int index1, int index2, int* arr) {
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

// Prints out the input array
// @param size - the size of the input array
// @param arr - the input array to reset
void MinMaxHeap::printArr(int size, int* arr) {
	std::cout << "[";
	for(int i = 0; i < size; i++) {
		std::cout << arr[i];
		if(i != size - 1)
			std::cout << ", ";
	}
	std::cout << "]\n";
}