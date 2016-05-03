//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	13/14
//
//*****************************************************************************

#include <iostream>
#include "PairingHeap.h"

int main()
{
	std::cout << "********************************************************************\n\n";
	std::cout << "                      Lab 13/14 - Jay Offerdahl                     \n\n";
	std::cout << "********************************************************************\n";
	
	PairingHeap *heap = new PairingHeap();
	int choice, temp;

	while(true) {
		std::cout << "Options:\n1. Insert\n2. Delete Min\n3. Print\n4. Exit\nChoice: ";
		std::cin >> choice;

		switch(choice) {
			// Insert
			case 1: {
				std::cin >> temp;

				heap->insert(temp);
				heap->printHeap();
				std::cout << "\n";
				break;
			}
			// Delete Min
			case 2: {
				// finish this
				break;
			}
			case 3: {
				heap->printHeap();
				break;
			}
			case 4: {
				std::cout << "\nExiting...\n\n";
				delete heap;
				return 0;
			}
			default:
				std::cout << "Invalid input, please try again.\n";
		}
	}
}