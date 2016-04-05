//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #: 	9
//
//*****************************************************************************

#include "MinHeap.h"
#include "MinMaxHeap.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "Timer.cpp"


void printArr(int, int*);
void printTable(int, int, std::string[][8]);
void fillBoth(int, int*, int*, int*, int*, int);

int main()
{
	std::cout << "********************************************************************\n\n";
	std::cout << "                       Jay Offerdahl - Lab 9                        \n\n";
	std::cout << "********************************************************************\n\n";

	// Initialize arrays and their current sizes
	int* arr1 = new int[410000]();
	int* arr2 = new int[410000]();
	int arrSize1, arrSize2;
	int dataSizes[] = {100000, 200000, 400000};
	int seeds[] = {2349, 8829, 1019};
	double duration;
	char buffer[256];

	std::string output[25][8];

	MinHeap* min = new MinHeap();
	MinMaxHeap* minmax = new MinMaxHeap();
	Timer* tim = new Timer();

	output[0][0] = "Size (n)";
	output[0][1] = "Srand";
	output[0][2] = "Build-Time";
	output[0][3] = "NumOps";
	output[0][4] = "Op Time (s)";
	output[0][5] = "Build-Time";
	output[0][6] = "NumOps";
	output[0][7] = "Op Time (s)";

	for(int i = 0; i < 3; i++) {
		int currentSize = dataSizes[i];
		int seed = seeds[i], row, ops, val;
		srand(seeds[i]);

		// Do eight tests for this data size
		for(int j = 1; j <= 8; j++) {
			row = j + i * 8;
			arrSize1 = arrSize2 = 0;

			// Fill both arrays with the same data
			fillBoth(row, arr1, arr2, &arrSize1, &arrSize2, currentSize);
			output[row][0] = std::to_string(currentSize); 
			output[row][1] = std::to_string(seed);

			// Build the min heap
			tim->start();
			min->buildHeap(arrSize1, arr1);
			duration = tim->stop();
			sprintf(buffer, "%5.6f", duration);
			output[row][2] = buffer;

			// Build the minmax heap
			tim->start();
			minmax->buildHeap(arrSize2, arr2);
			duration = tim->stop();
			sprintf(buffer, "%5.6f", duration);
			output[row][5] = buffer;

			// Calculate the number of operations to perform
			ops = rand() % 50000 + 1;
			output[row][3] = std::to_string(ops);
			output[row][6] = std::to_string(ops);

			// Reset the random number generator
			srand(seeds[i]);

			tim->start();
			for(int k = 0; k < ops; k++) {
				if((double) rand() / RAND_MAX < 0.5)
					min->deleteMin(&arrSize1, arr1);
				else {
					val = rand() % (currentSize * 2 + 1) - currentSize;
					min->insert(val, &arrSize1, arr1);
				}
			}
			duration = tim->stop();

			sprintf(buffer, "%5.6f", duration);
			output[row][4] = buffer;

			// Reset the random number generator
			srand(seeds[i]);

			tim->start();
			for(int k = 0; k < ops; k++) {
				if((double) rand() / RAND_MAX < 0.5)
					minmax->deleteMin(&arrSize2, arr2);
				else {
					val = rand() % (currentSize * 2 + 1) - currentSize;
					minmax->insert(val, &arrSize2, arr2);
				}
			}
			duration = tim->stop();

			sprintf(buffer, "%5.6f", duration);
			output[row][7] = buffer;
		}
	}

	// Print out the output
	printTable(25, 8, output);

	delete min;
	delete minmax;
	delete tim; // Sorry tim

	// Exit the programs
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

// Prints out the 2D array of output
// @param rows - the number of rows in the array
// @param cols - the number of cols in the array
// @param arr - the input array to print
void printTable(int rows, int cols, std::string arr[][8]) {
	std::cout << "\n|-------------------------------------------------------------------------------------------------------------------------------|\n";
	for(int i = 0; i < rows; i++) {
		if(i == 1)
			std::cout << "|-------------------------------------------------------------------------------------------------------------------------------|\n";
		for(int j = 0; j < cols; j++) {
			if(j == 0)
				std::cout << "|";
			std::cout << arr[i][j];
			if(arr[i][j].length() >= 8)
				std::cout << "\t|";
			else
				std::cout << "\t\t|";	
		}
		std::cout << "\n";
	}
	std::cout << "|-------------------------------------------------------------------------------------------------------------------------------|\n";
}

// Fills the input array with randomly generated numbers based on the input seed
// @param seed - the input value to seed the randomly generated number with
// @param arr - the input array to fill with random values
// @param arrSize - the size of the input array
// @note - modifies the arrSize variable, so make sure to pass by reference
void fillBoth(int seed, int* arr1, int* arr2, int* arrSize1, int* arrSize2, int fillSize) {
	int i = 0;
	srand(seed);

	// Randomly generate the values in the array
	while(i < fillSize) {
		int val = rand() % (fillSize * 2 + 1) - fillSize;

		arr1[(*arrSize1)++] = val;
		arr2[(*arrSize2)++] = val;
		i++;
	}
}