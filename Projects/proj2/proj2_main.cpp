//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #:	2
//
//*****************************************************************************

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include "proj2_Customer.h"
#include "proj2_HashTable.h"

std::string trim(std::string);
std::string pad(std::string, int);

int main(int argc, char* argv[])
{
	if(argc != 2) {
		std::cout << "Invalid usage: please specify input test file.\n";
		return 0;
	}

	std::cout << "********************************************************************\n\n";
	std::cout << "                     Jay Offerdahl - Project 2                      \n\n";
	std::cout << "********************************************************************\n";

	int choice;
	double number, charges;
	std::string line, str1, str2;
	HashTable* nameTable = new HashTable(0);
	HashTable* areaTable = new HashTable(1);
	HashTable* numTable  = new HashTable(2);

	// Insert all the records in the phonebook
	std::ifstream file;

	file.open("phonebook.txt");

	while(getline(file, line)) {
		number = std::stod(line.substr(49, 10));
		charges = std::stod(line.substr(62, line.length() - 62));

		// Trim the name and address
		str1 = trim(line.substr(0, 20));
		str2 = trim(line.substr(21, 25));

		Customer* temp = new Customer(str1, number, str2, charges);

		try {
			nameTable->insert(temp);
			areaTable->insert(temp);
			numTable->insert(temp);
		} catch(const std::runtime_error& e ) {
			std::cout << e.what();
		}
	}

	file.close();
	file.open(argv[1]);

	/*
	std::cout << "\nOptions:\n";
	std::cout << "1. Insert by Name\n2. Insert by Number\n3. Remove by Name\n" 
			  << "4. Remove by Number\n5. Make Payment\n6. Charge Customer\n"
			  << "7. Print Bill by Name\n8. Print Bill by Number\n9. Print in Hash Range\n"
			  << "10. Output Bills for Day\n11. Output Records by Area\n12. Quit\n\nChoice: ";
	std::cin >> choice;
	*/

	// Parse the test file and execute its commands
	while(getline(file, line)) {
		choice = std::stoi(line);

		// Insert by Name (name:20, address:25, number:10, charges:remaining)
		if(choice == 1) {
			// Grab the line, break it up and create the customer
			getline(file, line);
			std::cout << "\nInserting record by name: " << line << "\n";

			number = std::stod(line.substr(49, 10));
			charges = std::stod(line.substr(62, line.length() - 62));

			// Trim the name and address
			str1 = trim(line.substr(0, 20));
			str2 = trim(line.substr(21, 25));

			Customer* temp = new Customer(str1, number, str2, charges);

			// Try to find this customer by number, if not found, continue
			Customer* check = numTable->find(number);
			if(check != nullptr)
				std::cout << "\nError: That account number already exists in the database.\n";
			else {
				// Try inserting into all three tables and verify placement
				try {
					nameTable->insert(temp);
					areaTable->insert(temp);
					numTable->insert(temp);

					std::cout << "\nVerifying record placement...\n";
					Customer* check = numTable->find(temp->number);
					if(check != nullptr) {
						std::cout << "Record found!\n";
						check->print();
					}
					else
						std::cout << "\nError: The record was not found...\n";
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
		}
		// Insert by Number
		else if(choice == 2) {
			// Grab the line, break it up and create the customer
			getline(file, line);
			std::cout << "\nInserting record by number: " << line << "\n";

			number = std::stod(line.substr(0, 10));
			charges = std::stod(line.substr(58, line.length() - 58));

			// Trim the name and address
			str1 = trim(line.substr(11, 20));
			str2 = trim(line.substr(32, 25));

			Customer* temp = new Customer(str1, number, str2, charges);

			// Try to find this customer by name, if not found, continue
			Customer* check = numTable->find(number);
			if(check != nullptr) {
				std::cout << "\nError: That account number already exists in the database.\n";
			}
			else {
				// Try inserting into all three tables and verify placement
				try {
					nameTable->insert(temp);
					areaTable->insert(temp);
					numTable->insert(temp);

					std::cout << "\nVerifying record placement...\n";
					Customer* check = numTable->find(temp->number);
					if(check != nullptr) {
						std::cout << "Record found!\n";
						check->print();
					}
					else
						std::cout << "\nError: The record was not found...\n";
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			
		}
		// Remove by Name
		else if(choice == 3) {
			getline(file, line);
			std::cout << "\nRemoving record by name: " << line << "\n";

			Customer* temp = nameTable->find(line);

			// If the search returned a valid customer, try to remove them
			if(temp != nullptr) {
				temp->print();
				try {
					std::cout << "\nFinal bill for " << temp->name << ":\n";
					std::cout << "Charges: $" << std::fixed << std::setprecision(2) 
						  << temp->charges << "\n";

					// Update all pointers in tables to reflect removal
					nameTable->removeRecord(temp);
					areaTable->removeRecord(temp);
					numTable->removeRecord(temp);

					std::cout << "\nVerifying record removal...\n";
					Customer* checkNum = numTable->find(temp->number);

					if(checkNum == nullptr)
						std::cout << "Record not found in the database.\n";
					else {
						std::cout << "\nError: The record still exists in the database.\n";
						checkNum->print();
					}

					// Free memory
					delete temp;			
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else
				std::cout << "\nError: Customer not found in database.\n";
		}
		// Remove by Number
		else if(choice == 4) {
			getline(file, line);
			std::cout << "\nRemoving record by number: " << line << "\n";

			Customer* temp = numTable->find(std::stod(line));

			// If the search returned a valid customer, try to remove them
			if(temp != nullptr) {
				temp->print();
				try {
					std::cout << "\nFinal bill for " << temp->name << ":\n";
					std::cout << "Charges: $" << std::fixed << std::setprecision(2) 
						  << temp->charges << "\n";

					// Update all pointers in tables to reflect removal
					nameTable->removeRecord(temp);
					areaTable->removeRecord(temp);
					numTable->removeRecord(temp);

					std::cout << "\nVerifying record removal...\n";
					Customer* checkNum = numTable->find(temp->number);

					if(checkNum == nullptr)
						std::cout << "Record not found in the database.\n";
					else {
						std::cout << "\nError: The record still exists in the database.\n";
						checkNum->print();
					}

					// Free memory
					delete temp;			
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else
				std::cout << "\nError: Customer not found in database.\n";
		}
		// Make Payment
		else if(choice == 5) {
			getline(file, line);
			std::cout << "\nMaking a payment: " << line << "\n";

			int firstSpace = line.find_first_of(" ", 0);
			double payment = std::stod(line.substr(0, firstSpace));
			Customer* temp;
			
			// Check remaining string for digits (number)
			if (std::string::npos != line.find_first_of("0123456789", firstSpace)) {
				number = std::stod(line.substr(firstSpace + 1, 10));

				// Find the customer by their number
				temp = numTable->find(number);
			}
			else {
				str1 = line.substr(firstSpace + 1, 20);
				// Find the customer by name
				temp = nameTable->find(str1);
			}

			// If the search returned a valid customer, try to make the payment
			if(temp != nullptr) {
				// Print out cusotmer record
				temp->print();
				std::cout << "\nOriginal Balance: $" << std::fixed 
						  << std::setprecision(2) << temp->charges << "\n";
				try {
					temp->makePayment(payment);
					std::cout << "\nPayment made!\n";
					std::cout << "\nNew Balance: $" << std::fixed 
						  << std::setprecision(2) << temp->charges << "\n";
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else
				std::cout << "\nError: Customer not found in database.\n";
		}
		// Charge Customer
		else if(choice == 6) {
			getline(file, line);
			std::cout << "\nCharging customer: " << line << "\n";

			int firstSpace = line.find_first_of(" ", 0);
			charges = std::stod(line.substr(0, firstSpace));
			Customer* temp;
			
			// Check remaining string for digits (number)
			if (std::string::npos != line.find_first_of("0123456789", firstSpace)) {
				number = std::stod(line.substr(firstSpace + 1, 10));

				// Find the customer by their number
				temp = numTable->find(number);
			}
			else {
				str1 = line.substr(firstSpace + 1, 20);
				// Find the customer by name
				temp = nameTable->find(str1);
			}

			// If the search returned a valid customer, try to make the payment
			if(temp != nullptr) {
				// Print out cusotmer record
				temp->print();
				std::cout << "\nOriginal Balance: $" << std::fixed 
						  << std::setprecision(2) << temp->charges << "\n";
				try {
					temp->addCharge(charges);
					std::cout << "\nAccount charged!\n";
					std::cout << "\nNew Balance: $" << std::fixed 
						  << std::setprecision(2) << temp->charges << "\n";
				} catch(const std::runtime_error& e ) {
					std::cout << e.what();
				}
			}
			else
				std::cout << "\nError: Customer not found in database.\n";
		}
		// Print Bill by Name
		else if(choice == 7) {
			getline(file, line);
			std::cout << "\nPrinting bill by name: " << line << "\n";

			Customer* temp = nameTable->find(trim(line));

			// If the search returned a valid customer, print their bill
			if(temp != nullptr) {
				std::cout << "\nCurrent period bill for " << temp->name << ":\n";
				std::cout << "Current charges: $" << std::fixed << std::setprecision(2) 
						  << temp->charges << "\n";
			}
			else
				std::cout << "\nError: Customer not found in database.\n";
		}
		// Print Bill by Number
		else if(choice == 8) {
			getline(file, line);
			std::cout << "\nPrinting bill by number: " << line << "\n";
			number = std::stod(line);

			Customer* temp = numTable->find(number);

			// If the search returned a valid customer, print their bill
			if(temp != nullptr) {
				std::cout << "\nCurrent period bill for " << temp->name << ":\n";
				std::cout << "Current charges: $" << std::fixed << std::setprecision(2) 
						  << temp->charges << "\n";
			}
			else
				std::cout << "\nError: Customer not found in database.\n";
		}
		// Print in Hash Range
		else if(choice == 9) {
			getline(file, line);
			std::cout << "\nPrinting in hash range: " << line << "\n";
			choice = std::stoi(line);

			// Check for in range arguments
			if(choice >= 47 || choice < 0) {
				std::cout << "\nError: Invalid index: Index must be between 0 and 46. (0-based)\n";
			}
			else {
				// Print out the chain of customers at this hash
				Customer* temp = nameTable->table[choice];

				std::cout << "\nCustomer list whose names hash to " << choice << ":\n";
				while(temp != nullptr) {
					std::cout << pad(temp->name, 20) << " " << temp->address << "\n";
					temp = temp->nextName;
				}
			}
		}
		// Output Bills for Day
		else if(choice == 10) {
			getline(file, line);
			std::cout << "\nPrinting bills for day: " << line << "\n";
			choice = std::stoi(line);

			// Check for in range arguments
			if(choice >= 32 || choice <= 0) {
				std::cout << "\nError: Invalid index: Index must be between 1 and 31. (1-based, 31 days max)\n";
			}
			else {
				std::string ending;

				if(choice % 10 == 1 && choice != 11)
					ending = "st";
				else if(choice % 10 == 2 && choice != 12)
					ending = "nd";
				else if(choice % 10 == 3 && choice != 13)
					ending = "rd";
				else
					ending = "th";

				std::cout << "\nBills going out on the " << choice << ending << ":\n";

				choice = (choice - 1) * 2;

				// Print out the chain of customers at this hash
				Customer* temp = nameTable->table[choice];

				while(temp != nullptr) {
					std::cout << pad(temp->name, 20) << " " << pad(temp->address, 25) << "$"
							  << std::fixed << std::setprecision(2) << temp->charges << "\n";
					temp = temp->nextName;
				}

				temp = nameTable->table[choice + 1];

				while(temp != nullptr) {
					std::cout << pad(temp->name, 20) << " " << pad(temp->address, 25) << "$"
							  << std::fixed << std::setprecision(2) << temp->charges << "\n";
					temp = temp->nextName;
				}
			}
		}
		// Output Records by Area
		else if(choice == 11) {
			getline(file, line);
			std::cout << "\nPrinting records by area: " << line << "\n";
			choice = std::stoi(line);

			// Check for in range arguments
			if(choice < 100 || choice > 999) {
				std::cout << "\nError: Invalid area code: Please choose a positive three digit number.\n";
			}
			else {
				std::cout << "\nCustomers in located in zone " << choice << ":\n";

				// Print out the chain of customers at this hash
				Customer* temp = areaTable->table[areaTable->hash(choice)];
				std::string num;
				int area;
				bool found = false;

				while(temp != nullptr) {
					num = std::to_string(temp->number);
					area = std::stoi(num.substr(0, 3));
					if(area == choice) {
						found = true;
						std::cout << pad(temp->name, 20) << " (" << num.substr(0, 3) 
								  << ")-" << num.substr(3, 3) << "-" << num.substr(6, 4) << "\n";
					}
					temp = temp->nextArea;
				}
				if(!found)
					std::cout << "\nThere are no customers located in this area code.\n";
			}
		}
		// Quit
		else if(choice == 12) {
			Customer* temp, *next;
			// Remove all database records from the tables
			for(int i = 0; i < 113; i++) {
				// Let nameTable lead the pack
				temp = nameTable->table[i];

				while(temp != nullptr) {
					next = temp->nextName;

					nameTable->removeRecord(temp);
					areaTable->removeRecord(temp);
					numTable->removeRecord(temp);

					delete temp;
					temp = next;
				}
			}
			delete nameTable;
			delete areaTable;
			delete numTable;
			
			std::cout << "\nExiting...\n";
			file.close();
			return 0;
		}
		else
			std::cout << "\nInvalid input.\n";

		std::cout << "\n--------------------------------------------------------------------\n";
	}
}

/**
 * Trims the input string of trailing whitespace
 * @param  input - the input string to be trimmed
 * @return       - the trimmed string
 */
std::string trim(std::string input) {
	int back = input.length() - 1;
	for(int i = back; i >= 0; i--) {
		if(input[i] == ' ')
			back--;
		else
			break;
	}

	return back == 0 ? "" : input.substr(0, back + 1);
}

/**
 * Pads the input string with the desired amount of trailing whitespace
 * @param  input   - the input string to be trimmed
 * @param  padSize - the desired final length of the string
 * @return         - the trimmed string
 */
std::string pad(std::string input, int padSize) {
	if(input.length() > padSize)
		throw std::runtime_error("\nError: Invalid pad size.\n");
	else {
		int back = input.length() - 1;
		for(int i = back; i < padSize; i++) {
			input += " ";
		}

		return input;
	}
}