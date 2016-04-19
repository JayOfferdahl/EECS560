//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #: 	11
//
//*****************************************************************************

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Timer.cpp"

void printArr(int*, int);
void printTable(int, int, std::string[][3]);
void fillArr(int, int*, int*, int);
void shellSort(int*, int, std::string);
void insertionSort(int*, int);
bool checkSorted(int*, int);

int main(int argc, char* argv[])
{
	std::cout << "*************************************************\n\n";
	std::cout << "             Jay Offerdahl - Lab 11              \n\n";
	std::cout << "*************************************************\n\n";

	if(argc  < 2) {
		std::cout << "Invalid usage: Please specify an input file: ./lab [filename]\n";
		return 1;
	}
	std::ifstream file(argv[1]);

	if(!file) {
		std::cout << "There was an error opening the input file...\n";
		return 1;
	}

	// Initialize arrays and their current sizes
	int* arr = new int[400000]();
	int arrSize = 0, row;
	int dataSizes[] = {100000, 200000, 300000, 400000};
	int seeds[] = { 
		8104, 1947, 5381, 3198, 6423, 
		9983, 1642, 7642, 2349, 8829,
		6349, 3342, 9174, 7183, 4326,
		7543, 2893, 1943, 8883, 1019
	};
	double duration;
	char buffer[256];
	std::string line;

	/*
		Table Layout

		N 		Seed 		Time to sort 		Increment Scheme
		100000	8104		X.XXXXXXX			[First line from txt file]
		.
		.
		.
		400000	1019		X.XXXXXXX			[Last line from txt file]
	 */
	std::string output[21][3];

	Timer* tim = new Timer();

	output[0][0] = "Size (n)";
	output[0][1] = "Srand";
	output[0][2] = "Sort Time";

	double average = 0.0;

	for(int i = 0; i < 4; i++) {
		int currentSize = dataSizes[i];
		getline(file, line);

		// Do five tests for this data size
		for(int j = 1; j <= 5; j++) {
			arrSize = 0;
			row = i * 5 + j;

			// Fill the array with random numbers from -3n to 3n
			fillArr(seeds[row], arr, &arrSize, currentSize);
			output[row][0] = std::to_string(currentSize); 
			output[row][1] = std::to_string(seeds[row - 1]);

			// Sort the array using shell sort
			tim->start();
			shellSort(arr, arrSize, line);
			duration = tim->stop();

			average += duration;

			// Assert this array is sorted
			if(!checkSorted(arr, arrSize)) {
				std::cout << "The array was not sorted after shell sort...\n";
				return 1;
			}

			sprintf(buffer, "%5.6f", duration);
			output[row][2] = buffer;
		}
		std::cout << "Average for n = " << i + 1 << "00000: " << average / 5 << "\n";
		average = 0.0;
	}

	// Print out the output
	printTable(21, 3, output);

	delete tim; // Sorry tim
	delete arr;

	std::cout << "\nProgram Exiting...\n\n";

	// Exit the programs
	return 0;
}


/**
 * Sorts the input array using shellsort
 * @param arr     - the input array to be sorted
 * @param arrSize - the size of the input array
 * @param stream  - a stream holding the increments to use with shellsort
 */
void shellSort(int* arr, int arrSize, std::string scheme) {
	int inc, temp = 0, j;
	std::string line = scheme;

	// Fix the input to not have any commas
	temp = line.find_first_of(", ", temp + 1);

	while(temp != std::string::npos) {
		line[temp] = ' ';
		temp = line.find_first_of(", ", temp + 1);
	}

	std::stringstream stream(line);
	stream >> line;

	while(stream) {
		// Get the nezt value of increment
		inc = std::stoi(line);

		for(int i = inc; i <= arrSize; i++) {
			temp = arr[i];
			j = i - inc;
			while(j > 0 && arr[j] > temp) {
				arr[j + inc] = arr[j];
				j -= inc;
			}
			arr[j + inc] = temp;
		}

		stream >> line;
	}
}


/**
 * Sorts the input array using insertion sort
 * @param  arr  - the input array to sort
 * @param  size - the size of the input array
 */
void insertionSort(int* arr, int size) {
	int j, temp;

	for(int i = 1; i < size; i++) {
		j = i;
		temp = arr[i];
		while(temp < arr[j - 1]) {
			arr[j] = arr[j - 1];
			j--;

			if(j == 0)
				break;
		}
		arr[j] = temp;
	}
}


/**
 * Determines if the input array is sorted or not
 * @param  arr  - the input array to check
 * @param  size - the size of the input array
 * @return      - return true if sorted in ascending order
 */
bool checkSorted(int* arr, int size) {
	for(int i = 1; i < size; i++) {
		if(arr[i] > arr[i + 1]) 
			return false;
	}
	return true;
}


/**
 * Prints out the input one dimensional array
 * @param size - the size of the input array
 * @param arr  - the input array to print
 */
void printArr(int* arr, int size) {
	std::cout << "[";
	for(int i = 1; i <= size; i++) {
		std::cout << arr[i];
		if(i != size)
			std::cout << ", ";
	}
	std::cout << "]\n";
}


/**
 * Prints out the input two dimensional array
 * @param rows - the number of rows in the array
 * @param cols - the number of columns in the array
 * @param arr  - the input array to pring
 */
void printTable(int rows, int cols, std::string arr[][3]) {
	std::cout << "\nshell-sort output:\n";
	std::cout << "\n|-----------------------------------------------|\n";
	for(int i = 0; i < rows; i++) {
		if(i == 1)
			std::cout << "|-----------------------------------------------|\n";
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
	std::cout << "|-----------------------------------------------|\n";
}


/**
 * Fills the input array with randomly generated numbers, srands with seed
 * @param seed     - the input value to seed the RNG with
 * @param arr      - the input array to fill
 * @param arrSize  - the size of the input array
 * @param fillSize - the number of values to put into the array
 * @note           - modifies the arrSize variable to reflect correct size
 */
void fillArr(int seed, int* arr, int* arrSize, int fillSize) {
	int i = 1;
	srand(seed);

	// Randomly generate the values in the array
	while(i <= fillSize) {
		int val = rand() % (fillSize * 6) - fillSize * 3;

		arr[(*arrSize)++] = val;
		i++;
	}
}