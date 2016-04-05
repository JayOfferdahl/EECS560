//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "proj1_Fraction.h"
#include "proj1_LinkedList.h"

void sum	(int, LinkedList*);
void sort	(int, LinkedList*);
void mean 	(int, LinkedList*);
void median	(int, LinkedList*);
void mode	(int, LinkedList*);

int main(int argc, char** argv)
{
	// Read in from the data file and execute each command
	std::ifstream file;
	file.open("proj1.data.txt");

	std::string input, t1, t2, t3, t4, t5, t6;
	Fraction *f1, *f2, *tempFrac;
	int temp, size;
	bool terminate = false;

	// While there's still input
	while(file >> input) {
		terminate = false;
		std::cout << "\nInput: " << input << "\t";

		if(input == "ADD" || input == "XADD" || input == "SUB" || input == "MUL" ||
			input == "DIV" || input == "XDIV" || input == "LESS") {
			file >> t1 >> t2 >> t3 >> t4;
			try {
				f1 = new Fraction(std::stoi(t1), std::stoi(t2));
				f2 = new Fraction(std::stoi(t3), std::stoi(t4));
			} catch(const std::runtime_error& e ) {
				std::cout << e.what();
				terminate = true;
			}
		}

		// If no exception was raised (so far)
		if(!terminate) {
			if(input == "ADD") {
				f1->print();
				std::cout << " + ";
				f2->print();
				std::cout << " = ";
				tempFrac = f1;
				f1 = f1->add(f1, f2);
				f1->print();

				delete f1;
				delete f2;
			}
			else if(input == "XADD") {
				f1->print();
				std::cout << " + ";
				f2->print();
				std::cout << " = ";
				tempFrac = f1;
				f1 = f1->xadd(f1, f2);
				f1->print();

				delete f1;
				delete f2;
			}
			else if(input == "SUB") {
				f1->print();
				std::cout << " - ";
				f2->print();
				std::cout << " = ";
				tempFrac = f1;
				f1 = f1->sub(f1, f2);
				f1->print();

				delete f1;
				delete f2;
			}
			else if(input == "MUL") {
				f1->print();
				std::cout << " * ";
				f2->print();
				std::cout << " = ";
				tempFrac = f1;
				f1 = f1->mul(f1, f2);
				f1->print();

				delete f1;
				delete f2;
			}
			else if(input == "DIV") {
				// Catch any divide by 0 exceptions
				try {
					tempFrac = tempFrac->div(f1, f2);
					f1->print();
					std::cout << " / ";
					f2->print();
					std::cout << " = ";
					f1 = tempFrac;
					f1->print();

					delete f1;
					delete f2;
				} catch(const std::runtime_error& e) {
					std::cout << e.what();
				}
			}
			else if(input == "XDIV") {
				// Catch any divide by 0 exceptions
				try {
					tempFrac = tempFrac->xdiv(f1, f2);
					f1->print();
					std::cout << " / ";
					f2->print();
					std::cout << " = ";
					f1 = tempFrac;
					f1->print();

					delete f1;
					delete f2;
				} catch(const std::runtime_error& e) {
					std::cout << e.what();
				}
			}
			else if(input == "REC") {
				file >> t1 >> t2;
				// If the fraction is 0 / X, the reciprocal is invalid
				try {
					f1 = new Fraction(std::stoi(t1), std::stoi(t2));
					f1->print();
					std::cout << " inverted is ";
					tempFrac = f1;
					f1 = f1->rec(f1);
					f1->print();

					delete f1;
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else if(input == "RED") {
				file >> t1 >> t2;
				try {
					f1 = new Fraction(std::stoi(t1), std::stoi(t2));
					f1->print();
					std::cout << " reduced is ";
					tempFrac = f1;
					f1 = f1->red(f1);
					f1->print();

					delete f1;
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else if(input == "D2F") {
				file >> t1;
				std::cout << t1 << " converted is ";
				f1 = f1->d2f(t1);
				f1->print();

				delete f1;
			}
			else if(input == "MIX") {
				file >> t1 >> t2;
				try {
					f1 = new Fraction(std::stoi(t1), std::stoi(t2));
					f1->print();
					std::cout << " mixed is ";
					tempFrac = f1;
					f1 = f1->mix(f1);
					f1->print();

					delete f1;
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else if(input == "UNM") {
				file >> t1 >> t2 >> t3;
				try {
					f1 = new Fraction(std::stoi(t2), std::stoi(t3));
					std::cout << std::stoi(t1) << " ";
					f1->print();
					std::cout << " unmixed is ";
					tempFrac = f1;
					f1 = f1->unm(std::stoi(t1), f1);
					f1->print();

					delete f1;
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else if(input == "AMIX") {
				file >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
				try {
					f1 = new Fraction(std::stoi(t2), std::stoi(t3));
					f2 = new Fraction(std::stoi(t5), std::stoi(t6));
					tempFrac = tempFrac->amix(std::stoi(t1), f1, std::stoi(t4), f2);
					std::cout << std::stoi(t1) << " ";
					f1->print();
					std::cout << " + ";
					std::cout << std::stoi(t4) << " ";
					f2->print();
					std::cout << " = ";
					f1 = tempFrac;
					f1->print();

					delete f1;
					delete f2;
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else if(input == "LESS") {
				f1->print();
				std::cout << " < ";
				f2->print();
				std::cout << " = ";
				tempFrac = f1;
				temp = f1->less(f1, f2);
				
				if(temp != 1)
					std::cout << "False.";
				else
					std::cout << "True.";

				delete f1;
				delete f2;
			}
			else {
				std::cout << "Invalid file input.\n";
			}
		}
	}

	file.close();

	//*************************************************************************
	// User options for testing outside functions
	std::cout << "\n\nFunction Testing\n";
	LinkedList* list = new LinkedList();

	file.open("proj1.data2.txt");

	// Loop exits upon end of file
	while(file >> input) {
		temp = std::stoi(input);

		size = list->getSize();

		switch(temp) {
		// Add to list
		case 1: {
			file >> t1 >> t2;

			try {
				f1 = new Fraction(std::stoi(t1), std::stoi(t2));
				list->push(f1);
			} catch(const std::runtime_error& e) {
				std::cout << e.what();
			}

			break;
		}
		// Print list
		case 2: {
			list->print();
			break;
		}
		// Sum list
		case 3: {
			if(size > 0)
				sum(size, list);
			else
				std::cout << "Please add Fractions to the list.\n";
			break;
		}
		// Sort list
		case 4: {
			if(size > 0)
				sort(size, list);
			else
				std::cout << "Please add Fractions to the list.\n";
			break;
		}
		// Find mean
		case 5: {
			if(size > 0)
				mean(size, list);
			else
				std::cout << "Please add Fractions to the list.\n";
			break;
		}
		// Find median
		case 6: {
			if(size > 0)
				median(size, list);
			else
				std::cout << "Please add Fractions to the list.\n";
			break;
		}
		// Find mode
		case 7: {
			if(size > 0)
				mode(size, list);
			else
				std::cout << "Please add Fractions to the list.\n";
			break;
		}
		// Reset List
		case 8: {
			try {
				delete list;
				list = new LinkedList();
				std::cout << "The list has been reset!\n";
			} catch(const std::exception& e) {
				std::cout << e.what();
				std::cout << "There was an error deleting the list...\n";
			}
			break;
		}
		// Invalid input
		default:
			std::cout << "Invalid input, please try again.\n\n";
			break;
		}
	}

	// Final memory management & exit
	delete list;
	file.close();
	return 0;
}

// Computes the sum of the Fractions in the list and outputs
// the size of the list and the sum to the console
void sum(int size, LinkedList* list) {
	Node* current = list->getHead();
	Fraction* temp = new Fraction();

	while(current != nullptr) {
		temp = temp->add(temp, current->getFraction());
		current = current->getNext();
	}

	std::cout << "Operation: SUM\nList size: " << size << "\nSum: ";
	temp->print();
	std::cout << "\n\n";

	delete current;
	delete temp;
}

// Sorts the list of Fractions and outputs the sorted list
// to the console in increasing order
void sort(int size, LinkedList* list) {
	std::cout << "Operation: SORT\nSorted List:\n";
	list->sort();
	list->print();
	std::cout << "\n";
}

// Computes the mean of the Fractions in the list and outputs
// the size of the list and the mean (average) to the console
void mean(int size, LinkedList* list) {
	Node* current = list->getHead();
	Fraction* temp = new Fraction();
	Fraction* sizeTemp = new Fraction(size, 1);

	while(current != nullptr) {
		temp = temp->add(temp, current->getFraction());
		current = current->getNext();
	}

	temp = temp->div(temp, sizeTemp);

	std::cout << "Operation: MEAN\nList size: " << size << "\nMean (average): ";
	temp->print();
	std::cout << "\n\n";

	delete temp;
	delete sizeTemp;
}

// Computes the median of the Fractions in the list and outputs
// this to the console. If size is odd, it's the average of the 
// two "middle" values.
void median(int size, LinkedList* list) {
	if(list)
	// Sort the list and then take the middle of it.
	list->sort();
	int counter = 1;
	Fraction *med, *temp, *evenFrac;
	Node* tempNode = list->getHead();

	evenFrac = new Fraction(2, 1);

	if(size == 1)
			med = tempNode->getFraction();
	else {
		while(counter <= (size / 2)) {
			// If we're at the left half of the middle (if even, first middle)
			if(counter == size / 2) {
				med = tempNode->getNext()->getFraction();
				temp = tempNode->getFraction();
			}
			tempNode = tempNode->getNext();
			counter++;
		}

		if(size % 2 == 0)
			med = med->div(med->add(med, temp), evenFrac);
	}

	std::cout << "Operation: MEDIAN\nList size: " << size << "\nMedian: ";
	med->print();
	std::cout << "\n\n";

	delete evenFrac;
}

// Computes the mode of the Fractions in the list and outputs
// this to the console. If there's more than one mode, they are 
// all reported.
void mode(int size, LinkedList* list) {
	int maxSoFar = 0;
	int currentLen = 0;

	list->sort();

	LinkedList* modeList = new LinkedList();
	Node* temp = list->getHead();
	Fraction* sentinal = temp->getFraction();
	Fraction* current = temp->getFraction();

	// Loop will exit as soon as the end of the list is reached
	while(true) {
		currentLen++;
		// If the fractions are equal
		if(currentLen > 0) {
			if(currentLen > maxSoFar) {
				// Start over
				delete modeList;
				modeList = new LinkedList();
				modeList->push(current);

				maxSoFar = currentLen;
			}
			else if(currentLen == maxSoFar)
				modeList->push(current);
		}

		if(temp->getNext() != nullptr) {
			temp = temp->getNext();
			current = temp->getFraction();

			if(current->less(current, sentinal) != -1) {
				currentLen = 0;
				sentinal = current;
			}
			else
				currentLen++;
		}
		else {
			break;
		}
	}

	std::cout << "Operation: MODE\nList size: " << size << "\nMode(s): ";
	modeList->print();
	std::cout << "\n";

	delete modeList;
}