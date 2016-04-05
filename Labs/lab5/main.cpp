//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	5
//
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <math.h>
#include "AVLTree.h"
#include "Node.h"

void printInRangeArr(int, int, double, Node**, int);
void loadDict(int, Node**, int&, AVLTree*);

int main(int argc, char** argv)
{
	// BOOLEAN TO TEST OR NOT TO TEST --> True if testing
	bool testingPerformance = false;
	int testingN = 10;


	std::cout << "********************************************************************\n\n";
	std::cout << "                        Lab 5 - Jay Offerdahl                       \n\n";
	std::cout << "********************************************************************\n";
	// Read in from file and add values to the array and Tree
	std::ifstream file;
	file.open("data5T.txt");

	std::string t1, t2, t3;
	int temp, arrSize = 0, x, y, compCounter;
	double distance, tempDist;

	Node** arr = new Node*[100000];
	AVLTree* tree = new AVLTree();

	/*if(!testingPerformance) {
		// While there's still input
		while(file >> t1) {
			file >> t2 >> t3;
			arr[arrSize] = new Node(t1, std::stoi(t2), std::stoi(t3));
			tree->insert(t1, std::stoi(t2), std::stoi(t3), false);
			arrSize++;
		}
		file.close();

		// Test the distance formula from file input
		file.open("lab5_testT.txt");
		while(file >> t1 >> t2 >> t3) {
			x = std::stoi(t1);
			y = std::stoi(t2);
			distance = std::stod(t3);

			printInRangeArr(x, y, distance, arr, arrSize);

			// Do the same for the tree
			tree->printInRange(x, y, distance);
		}
		file.close();
	}
	else
		loadDict(testingN, arr, arrSize, tree);*/

	while(true) {
		std::cout << "____________________________________________________________________\n"
				  << "Options:\n"
				  << "1. Insert Record\n" << "2. Print Array\n" << "3. Print Tree\n" 
				  << "4. Delete Record by Name\n" << "5. Delete Record by Coordinates\n\n"
				  << "Lab 5 Additions ************************\n\n"
				  << "6. Find Cities by Distance\n" << "7. Quit\n\n" << "Choice: ";
		std::cin >> temp;

		switch(temp) {
		case 1: {
			std::cout << "Enter the city and coordinates as follows: \"Name X Y\"\n";
			std::cin >> t1 >> t2 >> t3;

			arr[arrSize] = new Node(t1, std::stoi(t2), std::stoi(t3));
			arrSize++;
			std::cout << "Adding to the array took 0 comparisons! (Constant Time).\n";

			tree->insert(t1, std::stoi(t2), std::stoi(t3), true);
			break;
		}
		// Print the array
		case 2: {
			// Print out the unordered array
			for(int i = 0; i < arrSize; i++) {
				std::cout << "City " << i + 1 << ": ";
				arr[i]->print();
				std::cout << "\n";
			}
			break;
		}
		// Print the tree
		case 3: {
			// Print out the AVLTree
			tree->levelOrderPrint();
			break;
		}
		// Delete record by name
		case 4: {
			std::cout << "Enter the name of the city you want to delete: ";
			std::cin >> t1;

			//*************************************************************************************
			// Unordered Array - Delete a value from the array by name, replace it with the value 
			// in the last spot. (Order doesn't matter, so choose the most efficient way)
			compCounter = 0;

			for(int i = 0; i < arrSize; i++) {
				compCounter++;
				if(arr[i]->getName().compare(t1) == 0) {
					delete arr[i];
					arrSize--;
					arr[i] = arr[arrSize];
					break;
				}
			}
			std::cout << "Deleting from the array took " << compCounter << " list comparisons.\n";
			//*************************************************************************************

			std::cout << "Deleting from the tree took " << tree->remove(t1) << " list comparisons.\n";

			std::cout << "Operation executed successfully.\n\n";
			break;
		}
		// Delete record by coordinates
		case 5: {
			std::cout << "Enter the coordinates of the city you want to delete (\"x x\"): ";
			std::cin >> t1 >> t2;

			//*************************************************************************************
			// Unordered Array - Delete a value from the array by coordinates, replace it with the 
			// value in the last spot (order doesn't matter, so choose the most efficient way)
			compCounter = 0;
			for(int i = 0; i < arrSize; i++) {
				compCounter += 2;
				if(arr[i]->getX() == std::stoi(t1) && arr[i]->getY() == std::stoi(t2)) {
					t3 = arr[i]->getName();
					delete arr[i];
					arrSize--;
					arr[i] = arr[arrSize];
					break;
				}
			}
			std::cout << "Deleting from the array took " << compCounter << " list comparisons.\n";
			//*************************************************************************************

			std::cout << "Deleting from the tree took " << tree->remove(std::stoi(t1), std::stoi(t2))
					  << " list comparisons.\n";

			std::cout << "Operation executed successfully.\n\n";
			break;
		}
		// Find cities by distance
		case 6: {
			std::cout << "Enter the starting point as \"X Y\": ";
			std::cin >> t1 >> t2;
			std::cout << "Enter the range (distance in miles): ";
			std::cin >> t3;

			x = std::stoi(t1);
			y = std::stoi(t2);
			distance = std::stod(t3);

			// Print out from the array & the tree
			printInRangeArr(x, y, distance, arr, arrSize);
			tree->printInRange(x, y, distance);
			break;
		}
		// Quit
		case 7: {
			// Memory management and program exit
			for(int i = 0; i < arrSize; i++)
				delete arr[i];
			delete []arr;
			delete tree;
			return 0;
		}
		// Invalid input
		default:
			std::cout << "Invalid input, please try again.\n\n";
			break;
		}
	}
	return 0;
}

void printInRangeArr(int x, int y, double distance, Node** arr, int arrSize) {
	double tempDist;

	if(arrSize > 0) {
		std::cout << "\n********************************************************************\n";
		std::cout << "                            Unordered Array                         \n";
		std::cout << "********************************************************************\n";
		std::cout << "\nCities in a " << distance << " mile range of (" 
		  << x << ", " << y << "):\n";
	}
	else
		std::cout << "There are no cities on record.\n";

	// Search for this a location at this point
	for(int i = 0; i < arrSize; i++) {
		if(arr[i]->getX() == x && arr[i]->getY() == y) {
			std::cout << arr[i]->getName() << " is located at (" << x << ", " << y << ")!\n";
		}
	}

	for(int i = 0; i < arrSize; i++) {
		// Calculate the distance from the input point
		tempDist = sqrt(pow(arr[i]->getX() - x, 2) + pow(arr[i]->getY() - y, 2));
		if(tempDist <= distance) {
			if(tempDist == 0) {}
				// Do nothing, we already accounted for this city
			// Else, simple show the city and the range from the point
			else
				std::cout << arr[i]->getName() << "\n   Distance: " << tempDist << "\n";
		}
	}
}

// Loads values into the unordered array and tree until the input size has been reached
void loadDict(int n, Node** arr, int& arrSize, AVLTree* tree) {
	// Open the file
	std::ifstream file;
	file.open("dict.txt");
	int counter = 0, x = 0, y = 0;
	std::string input;

	// Insert "AAAAAAAA" into both
	arr[arrSize] = new Node("AAAAAAAA", x, y);
	arrSize++;

	tree->insert("AAAAAAAA", x++, y++, false);
	counter++;


	// Load the dictionary the array and tree
	while(file >> input && counter < n - 1) {
		if(counter == n / 2) {
			// Insert "MMMMM" into both
			arr[arrSize] = new Node("MMMMM", x, y);
			arrSize++;

			tree->insert("MMMMM", x++, y++, false);
			counter++;
		}
		arr[arrSize] = new Node(input, x, y);
		arrSize++;

		tree->insert(input, x++, y++, false);
		counter++;
	}
	file.close();

	// Insert "ZZZZZZZZZZZ" into both
	arr[arrSize] = new Node("ZZZZZZZZZZ", x, y);
	arrSize++;

	tree->insert("ZZZZZZZZZZ", x++, y++, false);
	counter++;
}