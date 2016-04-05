//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	4
//
//*****************************************************************************

#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include "Node.h"

int main(int argc, char** argv)
{
	// Read in from file and add values to the array and Tree
	std::ifstream file;
	file.open("lab4.data.txt");

	std::string t1, t2, t3;
	int temp, arrSize = 0;

	Node** arr = new Node*[100];
	AVLTree* tree = new AVLTree();

	// While there's still input
	while(file >> t1) {
		file >> t2 >> t3;
		arr[arrSize] = new Node(t1, std::stoi(t2), std::stoi(t3));
		tree->insert(t1, std::stoi(t2), std::stoi(t3));
		arrSize++;
	}
	file.close();

	// Print out the unordered array
	for(int i = 0; i < arrSize; i++) {
		std::cout << "City " << i + 1 << ": ";
		arr[i]->print();
		std::cout << "\n";
	}

	// Print out the AVLTree
	tree->levelOrderPrint();

	while(true) {
		std::cout << "\nOptions:\n";
		std::cout << "1. Insert Record\n" << "2. Print Array\n" << "3. Print Tree\n" 
				  << "4. Delete Record by Name\n" << "5. Delete Record by Coordinates\n"
				  << "6. Quit\n\n" << "Choice: ";
		std::cin >> temp;

		switch(temp) {
		case 1: {
			std::cout << "Enter the city and coordinates as follows: \"LosAngeles 6 9\"\n";
			std::cin >> t1 >> t2 >> t3;

			arr[arrSize] = new Node(t1, std::stoi(t2), std::stoi(t3));
			arrSize++;

			tree->insert(t1, std::stoi(t2), std::stoi(t3));
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

			// Delete a value from the array by name, replace it with
			// the value in the last spot.
			for(int i = 0; i < arrSize; i++) {
				if(arr[i]->getName().compare(t1) == 0) {
					delete arr[i];
					arrSize--;
					arr[i] = arr[arrSize];
					break;
				}
			}

			tree->remove(t1);

			std::cout << t1 << " has been deleted from both databases.\n\n";
			break;
		}
		// Delete record by coordinates
		case 5: {
			std::cout << "Enter the coordinates of the city you want to delete (\"x x\"): ";
			std::cin >> t1 >> t2;

			// Delete a value from the array by coordinates, replace it with
			// the value in the last spot
			for(int i = 0; i < arrSize; i++) {
				if(arr[i]->getX() == std::stoi(t1) && arr[i]->getY() == std::stoi(t2)) {
					t3 = arr[i]->getName();
					delete arr[i];
					arrSize--;
					arr[i] = arr[arrSize];
					break;
				}
			}

			tree->remove(std::stoi(t1), std::stoi(t2));

			std::cout << t3 << " has been deleted from both databases." << " Coordinates: "
					  << t1 << ", " << t2 << "\n\n";
			break;
		}
		// Quit
		case 6: {
			// Memory management and program exit
			for(int i = 0; i < arrSize; i++) {
				delete arr[i];
			}
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