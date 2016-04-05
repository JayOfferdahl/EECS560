//***********************************************
//
//	Author: Jay Offerdahl
//	Class:	EECS 560 (Data Structures)
//	Lab:	Tues. 11a - 12:50p
//	Lab #:	1
//
//***********************************************

#include <iostream>
#include <fstream>
#include "LinkedList.h"

int main(int argc, char** argv)
{
	std::ifstream input(argv[1]);
	std::string line;
	
	// Create a new list to store the contents of the file
	LinkedList* list = new LinkedList();

	if(input.is_open()) {
		// Parse the file
		while (getline(input, line)) {
			// Grab each integer by normalizing the string obtained from the file
			int size = line.length();
			std::string temp;
			for(int i = 0; i < size; i++) {
				// If we're not at an empty space, add the char to the temp string
				if(line.at(i) != ' ') {
					temp += line.at(i);
				}
				// Reset the temp string (at a space)
				else {
					temp = "";
				}

				// If at the end of the string, push the last number
				if(i == size - 1) {
					list->push(std::stoi(temp));
				}
				// If the next char is a space and the word isn't empty, push it
				else if(line.at(i + 1) == ' ' && temp != "") {
					list->push(std::stoi(temp));
				}
			}
		}
		input.close();
	}	
	
	std::cout << "Initialized List: ";
	list->print();
	
	std::cout << "\n\nReversed List: ";
	list->reverse();
	list->print();
	
	std::cout << "\n\n";
	
	// User workflow
	bool cont = true;

	while(cont) {
		int temp;

		std::cout << "\nOptions:\n";
		std::cout << "1. Add\n" << "2. Reverse\n" << "3. Print\n" << "4. Quit\n\n" << "Choice: ";
		std::cin >> temp;

		switch(temp) {
		// Add a value to the list
		case 1:
			std::cout << "Enter a value to add to the list: ";
			std::cin >> temp;

			list->push(temp);

			std::cout << temp << " added to the list!\n\n";
			break;
		// Reverse the list
		case 2:
			list->reverse();

			std::cout << "The list has been reversed!\n\n";
			break;
		// Print the list
		case 3:
			list->print();
			break;
		// Quit
		case 4:
			cont = false;
			break;
		// Invalid input
		default:
			std::cout << "Invalid input, please try again.\n\n";
			break;
		}
	}
	return 0;
}

