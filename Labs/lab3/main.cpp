//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #: 	3
//
//*****************************************************************************

#include <iostream>
#include <stdlib.h>
#include "Timer.cpp"

#define TEST_1_SIZE 200001
#define TEST_2_SIZE 400001

int* insertionSort(int*, int);
bool checkSorted(int*, int);

int main(int argc, char** argv)
{
	// Timing variables
	Timer* timer = new Timer();
	double duration;
	
	// User workflow
	bool cont = true;
	int temp;

	int arr1[TEST_1_SIZE];
	int arr2[TEST_2_SIZE];

	while(cont) {
		std::cout 	<< "\nOptions:\n";
		std::cout 	<< "1. Timing Tests (Part 1)\n"
					<< "2. Timing Tests (Part 2)\n" 
					<< "3. Quit\n\n"
					<< "Choice: ";

		std::cin >> temp;

		switch(temp) {
		case 1: {
			temp = 10;
			srand(5);

			std::cout << "\nn = " << TEST_1_SIZE - 1<< "\n\n";

			while(temp > 0) {
				// Generate new data
				for(int i = 1; i < TEST_1_SIZE; i++) {
					arr1[i] = rand() % 80001 - 40000;
				}
				
				// Set the sentinal
				arr1[0] = -100000;

				// Start counting and sort the data
				timer->start();
				insertionSort(arr1, TEST_1_SIZE);

				// Stop counting and print the duration
				duration = timer->stop();

				if(!checkSorted(arr1, TEST_1_SIZE))
					std::cout << "The list is not sorted.\n";

				timer->printTime(duration);
				temp--;
			}
			break;
		}
		case 2: {
			temp = 5;
			double durations[5];
			srand(15);

			std::cout << "\nn = " << TEST_2_SIZE - 1<< "\n\n";

			while(temp > 0) {
				// Generate new data
				for(int i = 1; i < TEST_2_SIZE; i++) {
					arr2[i] = rand() % 160001 - 80000;
				}

				// Set the sentinal
				arr2[0] = -100000;
				
				// Start counting and sort the data
				timer->start();
				insertionSort(arr2, TEST_2_SIZE);

				// Stop counting and print the duration
				duration = timer->stop();
				durations[5 - temp] = duration;

				if(!checkSorted(arr2, TEST_2_SIZE))
					std::cout << "The list is not sorted.\n";

				timer->printTime(duration);
				temp--;
			}

			double sum = 0;

			for(int i = 0; i < 5; i++) {
			    sum += durations[i];
			}

			std::cout << "The average time to sort this input size was: " << sum / 5 << "\n";
			break;
		}
		// Quit
		case 3: {
			cont = false;
			break;
		}
		// Invalid input
		default:
			std::cout << "Invalid input, please try again.\n\n";
			break;
		}
	}
	delete timer;
	return 0;
}


// Sort the input array using insertion sort
// @param arr - the input array who's length is size
// @param size - the size of the input array
// @pre - Assume the first element is in arr[1] and arr[0] is a sentinal
// @post - The array is sorted in place, sentinal remains
// @return the sorted array
int* insertionSort(int* arr, int size) {
	int j, temp;

	for(int i = 1; i < size; i++) {
		j = i;
		temp = arr[i];
		while(temp < arr[j - 1]) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = temp;
	}
}


bool checkSorted(int* arr, int size) {
	for(int i = 0; i < size - 1; i++) {
		if(arr[i] > arr[i + 1]) 
			return false;
	}
	return true;
}
