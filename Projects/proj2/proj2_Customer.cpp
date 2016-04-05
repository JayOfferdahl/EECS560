//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #:	2
//
//*****************************************************************************

#include "proj2_Customer.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

/**
 * Creates a customer object with input variables and a charge (bill) of 0
 * @param in_name    - the name of the customer
 * @param in_number  - the phone number used by the customer
 * @param in_address - the address associated with the customer
 */
Customer::Customer(std::string in_name, double in_number, std::string in_address, double in_charges) {
	name = in_name;
	number = in_number;
	address = in_address;
	charges = in_charges;

	nextName = nullptr;
	nextArea = nullptr;
	nextNum = nullptr;
}

/**
 * Makes a payment to this customer's account, which should reduce the charges
 * @param amount - the amount to reduce this customer's charges
 */
void Customer::makePayment(double amount) {
	if(amount <= 0) {
		std::string error = "Run-time exception: Invalid payment amount: " + std::to_string(amount) + "\n\n";
		throw std::runtime_error(error);
	}
	else if(charges - amount < 0) {
		std::string error = "Run-time exception: Payment exceeds charges: " + std::to_string(amount) + "\n\n";
		throw std::runtime_error(error);
	}
	else {
		charges -= amount;
	}
}

/**
 * Adds a charge to this customer's account, which should raise the charges
 * @param amount - the amount to be billed to the customer
 */
void Customer::addCharge(double amount) {
	if(amount <= 0) {
		std::string error = "Run-time exception: Invalid billing amount: " + std::to_string(amount) + "\n\n";
		throw std::runtime_error(error);
	}
	else {
		charges += amount;
	}
}

/**
 * Prints out the information stored in this record
 */
void Customer::print() {
	std::string num = std::to_string(number);

	std::cout << "\nCustomer Record:\nName:\t\t" << name << "\nAddress:\t" << address
			  << "\nNumber:\t\t(" << num.substr(0, 3) << ")-" << num.substr(3, 3) << "-" << num.substr(6, 4)
			  << "\nCharges:\t$" << std::fixed << std::setprecision(2) << charges << "\n\n";
}