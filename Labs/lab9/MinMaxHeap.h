//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	9
//
//*****************************************************************************

#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

class MinMaxHeap
{
public:
	// Initialize a min heap with nothing in it
	MinMaxHeap();

	// Builds the initial heap from the input array and array size
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void buildHeap(int arrSize, int* arr);

	// Inserts a value into the minmax heap
	// @param val - the value to be inserted into the heap
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void insert(int val, int* arrSize, int* arr);

	// Delete the minimum value from the min-max heap
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void deleteMin(int* arrSize, int* arr);

	// Deletes the maximum value from the min-max heap
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void deleteMax(int* arrSize, int* arr);

	// Trickles down the heap until the correct posisiton for the element at index i
	// is found, checks what level the index is on (max or min).
	// @param index - the position in the array of the element we're examining
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void trickleDown(int index, int arrSize, int* arr);

	// Trickles down the heap on min levels until the correct position is found
	// @param index - the position in the array of the element we're examining
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void trickleDownMin(int index, int arrSize, int* arr);

	// Trickles down the heap on max levels until the correct position is found
	// @param index - the position in the array of the element we're examining
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void trickleDownMax(int index, int arrSize, int* arr);

	// Bubbles up the heap until the correct posisiton is found for the element at index index.
	// @param index - the position in the array of the element we're examining
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void bubbleUp(int index, int arrSize, int* arr);

	// Bubbles up the heap on min levels until the correct position is found
	// @param index - the position in the array of the element we're examining
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void bubbleUpMin(int index, int arrSize, int* arr);

	// Bubbles up the heap on max levels until the correct position is found
	// @param index - the position in the array of the element we're examining
	// @param arrSize - the size of the input array
	// @param arr - the input array to fill with random values
	void bubbleUpMax(int index, int arrSize, int* arr);

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