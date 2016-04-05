//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #:	2
//
//*****************************************************************************

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "proj2_Customer.h"

class HashTable
{
public:
	// Type of hashtables (name, area code, or number)
	enum HashType {
		CUST_NAME,
		CUST_AREA,
		CUST_NUM
	};

	/**
	 * Create a hashtable object with all table elements initialized to null
	 * @param type - the type of input, e.g. name, area code, or number
	 */
	HashTable(int type);

	/**
	 * Computes the hash value of the input string
	 * @param  customer - the customer object to be examined
	 * @return      	- the integer table location of this input in the table
	 */
	int hash(Customer* customer);

	/**
	 * Computes the hash value of the input string
	 * @param  name - the name to be hashed
	 * @return      - the integer table location of this input in the table
	 */
	int hash(std::string name);

	/**
	 * Computes the hash value of the input number (either area or phone number)
	 * @param  number - the number to be hashed
	 * @return        - the integer table location of this input in the table
	 */
	int hash(double number);

	/**
	 * Inserts a customer object into the hashtable, depending on the hashType
	 * @param customer - the customer object to be inserted
	 */
	void insert(Customer* customer);

	/**
	 * Removes a customer's record from this table
	 * @pre            - assumes the customer exists in the database
	 * @param customer - the customer to remove from the table
	 */
	void removeRecord(Customer* customer);

	/**
	 * Prints out the hash table in order (index 1 contents..index 2 contents..etc.)
	 * @note - this is array ordered (from 1 to arraysize)
	 */
	void print();

	/**
	 * Determines if a cusotmer exists in the database by searching for their number
	 * @pre 		  - the input corresponds with the type of table (numTable)
	 * @param  number - the customer's number to search for in the database
	 * @return        - The customer if the customer exists, else nullptr
	 */
	Customer* find(double number);

	/**
	 * Determines if a cusotmer exists in the database by searching for their name
	 * @pre 		- the input corresponds with the type of table (nameTable)
	 * @param  name - the customer's name to search for in the database
	 * @return      - The customer if the customer exists, else nullptr
	 */
	Customer* find(std::string name);

	// Size of the database (prime)
	static const size_t tableSize = 113;

	HashType tableType;

	// The actual array for the hash table
	Customer* table[tableSize];
};

#endif
