//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #:	2
//
//*****************************************************************************

#include <iostream>
#include <stdexcept>
#include "proj2_HashTable.h"

/**
 * Create a hashtable object with all table elements initialized to null
 * @param type - the type of input, e.g. name, area code, or number
 *             - 0 is CUST_NAME
 *             - 1 is CUST_AREA
 *             - 2 is CUST_NUM
 */
HashTable::HashTable(int type) {
	// Set our table type (name, number, area)
	tableType = (HashType) type;

	// Initialize all slots to nullptr
	for(int i = 0; i < tableSize; i++)
		table[i] = nullptr;
}

/**
 * Computes the hash value of the input customer (depends on tableType)
 * @param  customer - the customer object to be examined
 * @return      	- the integer table location of this input in the table
 */
int HashTable::hash(Customer* customer) {
	if(tableType == CUST_NAME) {
		std::string name = customer->name;
		if(name.length() < 13) {
			if(name.length() < 7) {
				if(name.length() < 2)
					return 0;
				return name[1] % 47;
			}
			return (name[1] + name[6]) % 47;
		}
		return (name[1] + name[6] + name[12]) % 47;
	}
	else if(tableType == CUST_NUM) {
		std::string number = std::to_string(customer->number);
		return std::stoi(number.substr(3, 4)) % 53;
	}
	else if(tableType == CUST_AREA) {
		std::string number = std::to_string(customer->number);
		int area = std::stoi(number.substr(0, 3));
		return (area * (area + 3)) % 113;
	}
}

/**
 * Computes the hash value of the input string
 * @param  name - the name to be hashed
 * @return      - the integer table location of this input in the table
 */
int HashTable::hash(std::string name) {
	if(name.length() < 13) {
		if(name.length() < 7) {
			if(name.length() < 2)
				return 0;
			return name[1] % 47;
		}
		return (name[1] + name[6]) % 47;
	}
	return (name[1] + name[6] + name[12]) % 47;
}

/**
 * Computes the hash value of the input number (either area or phone number)
 * @param  number - the number to be hashed
 * @return        - the integer table location of this input in the table
 */
int HashTable::hash(double number) {
	if(tableType == CUST_NUM) {
		std::string num = std::to_string(number);
		return std::stoi(num.substr(3, 4)) % 53;
	}
	else if(tableType == CUST_AREA) {
		std::string num = std::to_string(number);
		int area = std::stoi(num.substr(0, 3));
		return (area * (area + 3)) % 113;
	}
}

/**
 * Inserts a customer object into the hashtable, depending on the hashType
 * @param customer - the customer object to be inserted
 */
void HashTable::insert(Customer* customer) {
	if(find(customer->number) != nullptr)
			throw std::runtime_error("Run-time exception: Customer already exists in the database.\n");

	int index = hash(customer);
	Customer* temp = table[index];

	// If the slot is empty, put this customer in there
	if(temp == nullptr) {
		table[index] = customer;
		return;
	}

	// Make sure customer doesn't already exist (testing)
	if(tableType == CUST_NAME) {
		while(temp->nextName != nullptr)
			temp = temp->nextName;

		temp->nextName = customer;
	}
	else if(tableType == CUST_NUM) {
		while(temp->nextNum != nullptr)
			temp = temp->nextNum;

		temp->nextNum = customer;
	}
	else if(tableType == CUST_AREA) {
		while(temp->nextArea != nullptr)
			temp = temp->nextArea;

		temp->nextArea = customer;
	}
}

/**
 * Removes a customer's record from this table
 * @param customer - the customer to remove from the table
 */
void HashTable::removeRecord(Customer* customer) {
	int index = hash(customer);
	Customer* temp = table[index];

	// Find the record before this customer
	if(tableType == CUST_NAME) {
		if(temp->name == customer->name)
			table[index] = temp->nextName;
		else {
			while(temp->nextName != nullptr) {
				if(temp->nextName->name == customer->name)
					break;
				temp = temp->nextName;
			}

			temp->nextName = temp->nextName->nextName;
		}
	}
	else if(tableType == CUST_NUM) {
		if(temp->number == customer->number)
			table[index] = temp->nextNum;
		else {
			while(temp->nextNum != nullptr) {
				if(temp->nextNum->number == customer->number)
					break;
				temp = temp->nextNum;
			}

			temp->nextNum = temp->nextNum->nextNum;
		}
	}
	else if(tableType == CUST_AREA) {
		if(temp->address == customer->address)
			table[index] = temp->nextArea;
		else {
			while(temp->nextArea != nullptr) {
				if(temp->nextArea->address == customer->address)
					break;
				temp = temp->nextArea;
			}

			temp->nextArea = temp->nextArea->nextArea;
		}
	}
}

/**
 * Prints out the hash table in order (index 1 contents..index 2 contents..etc.)
 * @note - this is array ordered (from 1 to arraysize)
 */
void HashTable::print() {
	Customer* temp;

	for(int i = 0; i < tableSize; i++) {
		temp = table[i];

		while(temp != nullptr) {
			if(tableType == CUST_NAME) {
				std::cout << temp->name << "\n";
				temp = temp->nextName;
			}
			else if(tableType == CUST_AREA) {
				std::cout << temp->address << "\n";
				temp = temp->nextArea;
			}
			else { // tableType == CUST_NUM
				std::cout << temp->number << "\n";
				temp = temp->nextNum;
			}
		}
	}
}

/**
 * Determines if a cusotmer exists in the database by searching for their number
 * @pre 		  - the input corresponds with the type of table (numTable)
 * @param  number - the customer's number to search for in the database
 * @return        - The customer if the customer exists, else nullptr
 */
Customer* HashTable::find(double number) {
	// Find the right slot
	Customer* temp = table[hash(number)];

	// While we haven't found the customer by number (only true unique field)
	while(temp != nullptr) {
		if(temp->number == number)
			return temp;

		temp = temp->nextNum;
	}

	return nullptr;
}

/**
 * Determines if a cusotmer exists in the database by searching for their name
 * @pre 		- the input corresponds with the type of table (nameTable)
 * @param  name - the customer's name to search for in the database
 * @return      - The customer if the customer exists, else nullptr
 */
Customer* HashTable::find(std::string name) {
	// Find the right slot
	Customer* temp = table[hash(name)];

	// While we haven't found the customer by name (only true unique field)
	while(temp != nullptr) {
		if(temp->name == name)
			return temp;

		temp = temp->nextName;
	}

	return nullptr;
}