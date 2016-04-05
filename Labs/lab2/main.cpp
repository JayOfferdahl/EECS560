//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	2
//
//***********************************************

#include <iostream>
#include <fstream>

#include "BinarySearchTree.h"
#include "Queue.h"

int main(int argc, char** argv)
{
	BinarySearchTree* tree = new BinarySearchTree();

	// Assume input is no larger than 100 integers
	int input[100];
	int temp, counter = 0;
	
	std::ifstream file;
	file.open("data2.txt");

	// Pull input from file
	while(file >> temp) {
		input[counter] = temp;
		counter++;
	}

	file.close();

	// Load the values into the BST
	tree->setRoot(tree->loadBST(input, 0, counter - 1));

	// Print out the tree
	tree->levelOrderPrint();

	// User workflow
	bool cont = true;

	while(cont) {
		std::cout << "\nOptions:\n";
		std::cout << "1. Add to BST\n" << "2. Level Order Print\n" << "3. Search BST\n" << "4. Quit\n\n" << "Choice: ";
		std::cin >> temp;

		switch(temp) {
		// Add value to the BST
		case 1: {
			std::cout << "Value to add: ";

			std::cin >> temp;
			tree->push(temp);

			std::cout << "Added " << temp << " to the tree!\n";
			break;
		}
		// Level order print
		case 2: {
			std::cout << "\nThe tree in printed in level order: \n";
			tree->levelOrderPrint();
			std::cout << std::endl;
			break;
		}
		// Search for value
		case 3: {
			std::cout << "Enter a value you want to search for: ";
			std::cin >> temp;
			bool found = tree->search(temp);

			if(found) {
				std::cout << "The value was found in the tree!\n";
			}
			else {
				std::cout << "The value is not in the tree.\n";
			}
			break;
		}
		// Quit
		case 4: {
			cont = false;
			break;
		}
		// Invalid input
		default:
			std::cout << "Invalid input, please try again.\n\n";
			break;
		}
	}

	return 0;
}