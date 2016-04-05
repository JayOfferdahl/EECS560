//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #:	2
//
//*****************************************************************************

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
public:
	/**
	 * Creates a customer object with input variables and a charge (bill) of 0
	 * @param in_name    - the name of the customer
	 * @param in_number  - the phone number used by the customer
	 * @param in_address - the address associated with the customer
	 */
	Customer(std::string in_name, double in_number, std::string in_address, double in_charges);

	/**
	 * Makes a payment to this customer's account, which should reduce the charges
	 * @param amount - the amount to reduce this customer's charges
	 */
	void makePayment(double amount);

	/**
	 * Adds a charge to this customer's account, which should raise the charges
	 * @param amount - the amount to be billed to the customer
	 */
	void addCharge(double amount);

	/**
	 * Prints out the information stored in this record
	 */
	void print();

	// Customer information
	std::string name;
	std::string address;
	double number;
	double charges;

	// "next" pointers
	Customer* nextName;
	Customer* nextNum;
	Customer* nextArea;
};

#endif
