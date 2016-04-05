//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	9
//
//*****************************************************************************

#ifndef MINHEAP_H
#define MINHEAP_H

class MinHeap
{
public:
	// Initialize a min heap with nothing in it
	MinHeap();

	// Builds the initial heap from the input array and array size by percolating
	// down each node until the node's value is in the correct spot
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void buildHeap(int arrSize, int* arr);

	// Inserts a value into the min heap
	// @param val - the value to be inserted into the heap
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void insert(int val, int* arrSize, int* arr);

	// Delete the minimum value from the min heap
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void deleteMin(int* arrSize, int* arr);

	// Moves an item down the heap until the correct spot for it is found
	// @param index - the index of the heap to push down (the node position) - 1 based
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void pushDown(int index, int arrSize, int* arr, int version);

	// Moves an item up the heap until it's parent is smaller than it
	// @param index - the index of the heap to push up (the node position) - 1 based
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void pushUp(int index, int* arr);

	// Sorts the list in descending order (min heap sort)
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void heapSort(int arrSize, int* arr, int version);

	// Swaps the two specified indexes in the array
	// @pre - assumes the indexes are in range within the array
	// @param index1 - the input value to seed the randomly generated number with
	// @param index2 - the input array to fill with random values
	// @param arr - the size of the input array
	// @note - modifies the array
	void swap(int index1, int index2, int* arr);

	// Prints out the input array
	// @param size - the size of the input array
	// @param arr - the input array to reset
	void printArr(int size, int* arr);
};

#endif