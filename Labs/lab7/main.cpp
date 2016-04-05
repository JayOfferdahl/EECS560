//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #: 	7
//
//*****************************************************************************

#include <iostream>
#include <stdlib.h>
#include <string>

#define HEAP_SIZE 2000
#define ITERATIONS 10

// Global to track the number of comparsions made
int comps;

// General functions
void printArr(int, int*);
void fillArr(int, int*, int*, int);

// Heap functions
void buildHeap(int, int*);
void pushDown(int, int, int*, int);
void pushUp(int, int*);
void heapSort(int, int*, int);

int main()
{
	int temp, arrSize = 0;
	int arr[HEAP_SIZE];

	std::cout << "********************************************************************\n\n";
	std::cout << "                       Jay Offerdahl - Lab 7                        \n\n";
	std::cout << "********************************************************************\n\n";

	// Part 1: show buildheap and heapsort are working
	std::cout << "Part 1: Build-heap & heap sort verification\n\n";
	std::cout << "____________________________________________________________________\n\n";
	std::cout << "Filling array with 25 random values...\n";
	fillArr(234, arr, &arrSize, 25);
	std::cout << "\nInitial array:\n";
	printArr(arrSize, arr);

	buildHeap(arrSize, arr);
	std::cout << "\nMin-heap array:\n";
	printArr(arrSize, arr);

	heapSort(arrSize, arr, 0);
	std::cout << "\nHeap sorted array (largest to smallest):\n";
	printArr(arrSize, arr);

	// Part 2: show number of comparisons for generated data sets using both versions
	std::cout << "\n********************************************************************\n\n";
	std::cout << "Part 2: Compare two versions of heap sort (HEAP_SIZE = " << HEAP_SIZE << ")\n\n";
	std::cout << "____________________________________________________________________\n\n";
	for(int iteration = 1; iteration <= ITERATIONS; iteration++) {
		std::cout << "Iteration " << iteration << "\n";
		// Fill, build, and sort the heap using the normal method
		arrSize = 0;
		fillArr(iteration * 15, arr, &arrSize, HEAP_SIZE);
		buildHeap(arrSize, arr);
		heapSort(arrSize, arr, 0);

		// Report # of comparisons while sorting with normal version
		std::cout << "# of heap item comparisons (normal):\t" << comps << "\n";

		// Fill, build, and sort the heap using the improved version
		arrSize = 0;
		fillArr(iteration * 15, arr, &arrSize, HEAP_SIZE);
		buildHeap(arrSize, arr);
		heapSort(arrSize, arr, 1);

		// Report # of comparisons while sorting with modified version
		std::cout << "# of heap item comparisons (modified):\t" << comps << "\n\n";
	}

	// Exit the program on user request
	std::cout << "\nPress enter to exit...";
	std::string str;
	std::getline(std::cin, str);
	return 0;
}

// Prints out the input array
// @param size - the size of the input array
// @param arr - the input array to reset
void printArr(int size, int* arr) {
	std::cout << "[";
	for(int i = 0; i < size; i++) {
		std::cout << arr[i];
		if(i != size - 1)
			std::cout << ", ";
	}
	std::cout << "]\n";
}

// Fills the input array with randomly generated numbers based on the input seed
// @param seed - the input value to seed the randomly generated number with
// @param arr - the input array to fill with random values
// @param arrSize - the size of the input array
// @note - modifies the arrSize variable, so make sure to pass by reference
void fillArr(int seed, int* arr, int* arrSize, int fillSize) {
	// Seed the random number generator
	srand(seed);

	// Randomly generate the values in the array
	for(int j = 0; j < fillSize; j++)
		arr[(*arrSize)++] = rand() % 2001 - 1000;
}

//*****************************************************************************
//
//		Heap Methods (Min heap)
//
//*****************************************************************************

// Builds the initial heap from the input array and array size by percolating
// down each node until the node's value is in the correct spot
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void buildHeap(int arrSize, int* arr) {
	for(int i = arrSize / 2; i > 0; i--) 
		pushDown(i, arrSize, arr, 0);
}

// Moves an item down the heap until the correct spot for it is found
// @param index - the index of the heap to push down (the node position) - 1 based
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void pushDown(int index, int arrSize, int* arr, int version) {
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
		else {
			temp = arr[child - 1] < arr[child] ? child : child + 1;
			comps++;
		}

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
			comps++; // Account for comparison in "else-if" block
			arr[position - 1] = arr[temp - 1];
			position = temp;
		}
		// The correct position has been found, no further action required
		else {
			comps++; // Account for comparison in "else-if" block
			arr[position - 1] = val;
			break;
		}
	}
}

// Moves an item up the heap until it's parent is smaller than it
// @param index - the index of the heap to push up (the node position) - 1 based
// @param arrSize - the size of the input array
// @param arr - the input array to fill with random values
void pushUp(int index, int* arr) {
	int val = arr[index - 1];
	int position = index;

	while(position > 1) {
		if(val < arr[position / 2 - 1]) {
			comps++; // Account for comparison made this iteration
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
void heapSort(int arrSize, int* arr, int version) {
	// Reset comparison counter
	comps = 0;

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