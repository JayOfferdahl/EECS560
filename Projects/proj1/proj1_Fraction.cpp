//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#include "proj1_Fraction.h"
#include <iostream>
#include <stdexcept>
#include <math.h>

// Creates a Fraction with value 0
Fraction::Fraction() {
	// Fraction Variables
	setNum(0);
	setDenom(1);

	// Mixed number variables
	setMixedN(0);
}

// Creates a Fraction with input numerator and denominator
// @param numerator - the top half of the Fraction
// @param denominator - the lower half of the Fraction
Fraction::Fraction(int numerator, int denominator) {
	// Fraction Variables
	setNum(numerator);

	if(denominator < 0) {
		setNum(getNum() * -1);
		setDenom(-1 * denominator);
	}
	else
		setDenom(denominator);

	// Mixed number variables
	setMixedN(0);
}

// Creates a Fraction with input numerator and denominator and mixed integer value
// @param numerator - the top half of the Fraction
// @param denominator - the lower half of the Fraction
// @param mixedN - the value of the integer overflow of the mixed number
Fraction::Fraction(int numerator, int denominator, int mixedN) {
	setNum(numerator);

	if(denominator < 0) {
		setNum(getNum() * -1);
		setDenom(-1 * denominator);
	}
	else
		setDenom(denominator);

	// This is a mixed number
	setMixedN(mixedN);
}

// Returns the whole integer part of the mixed number stored in this Fraction instance
// @return - the whole mixed number integer
int Fraction::getMixedN() {
	return m_mixedN;
}

// Sets the whoe interger part of this Fraction
// @param numerator - the new mixedN to be stored in this Fraction
void Fraction::setMixedN(int mixedN) {
	m_mixedN = mixedN;
}

// Returns the numerator stored in this Fraction instance
// @return - the private numerator
int Fraction::getNum() {
	return m_numerator;
}

// Sets the numerator of this Fraction
// @param numerator - the new numerator to be stored in this instance
void Fraction::setNum(int numerator) {
	m_numerator = numerator;
}

// Returns the denominator stored in this Fraction instance
// @return - the private denominator
int Fraction::getDenom() {
	return m_denominator;
}

// Sets the denominator of this Fraction
// @param denominator - the new denominator to be stored in this instance
// @throw run time exception if trying to set the denominator to 0
void Fraction::setDenom(int denominator) {
	if(denominator == 0) {
		throw std::runtime_error("Run-time exception: 0 is not a valid denominator.\n");
	}

	m_denominator = denominator;
}

// Prints out the fraction, if it's a mixed number, does in the form 1 3/4, else
// it simply prints out the fraction as 3/4
void Fraction::print() {
	if(getMixedN() != 0)
		std::cout << m_mixedN << " ";

	std::cout << getNum() << "/" << getDenom();
}

// Adds the two Fractions and returns the result
// @param first - the first Fraction to add
// @param second - the second Fraction to add
// @return the Fraction result of first + second
Fraction* Fraction::add(Fraction* first, Fraction* second) {
	Fraction* result = new Fraction(first->getNum() * second->getDenom() + second->getNum() * first->getDenom(),
									first->getDenom() * second->getDenom());

	return red(result);
}

// Adds the two Fractions and returns the result as a mixed 
// number if the result is an improper Fraction
// @param first - the first Fraction to add
// @param second - the second Fraction to add
// @return the Fraction result of first + second (mixed flag set if applicable)
Fraction* Fraction::xadd(Fraction* first, Fraction* second) {
	return mix(add(first, second));
}

// Subtracts the two Fractions and returns the result (F1 - F2)
// @param first - the Fraction to be subtracted from
// @param second - the Fraction to subtract from the first Fraction
// @return the Fraction result of first - second
Fraction* Fraction::sub(Fraction* first, Fraction* second) {
	Fraction* result = new Fraction(first->getNum() * second->getDenom() - second->getNum() * first->getDenom(),
									first->getDenom() * second->getDenom());

	return red(result);
}

// Multiplies the two Fractions and returns the result
// @param first - the first Fraction to multiply
// @param second - the second Fraction to multiply
// @return the Fraction result of first * second
Fraction* Fraction::mul(Fraction* first, Fraction* second) {
	Fraction* result = new Fraction(first->getNum() * second->getNum(),
									first->getDenom() * second->getDenom());

	return red(result);
}

// Divides the two Fractions and returns the result
// @param first - the numerator of this division
// @param second - the denominator of this division
// @throw run time exception if dividing by 0
// @return the Fraction result of first / second
Fraction* Fraction::div(Fraction* first, Fraction* second) {
	if(second->getDenom() == 0)
		throw std::runtime_error("Run-time exception: attempted division by 0.\n");
	return mul(first, rec(second));
}

// Divides the two Fractions and returns the result as mixed
// @param first - the numerator of this division
// @param second - the denominator of this division
// @return the Fraction result of first / second (mixed flag set if applicable)
Fraction* Fraction::xdiv(Fraction* first, Fraction* second) {
	return mix(div(first, second));
}

// Finds the reciprocal of this Fraction (inverts F)
// @param frac - the input Fraction
// @throw run time exception if denominator will be 0
// @return the reciprocal of this Fraction (a / b --> b / a)
Fraction* Fraction::rec(Fraction* frac) {
	int num = frac->getNum();
	int denom = frac->getDenom();
	
	if(num == 0)
		throw std::runtime_error("Run-time exception: 0 is not a valid denominator.\n");

	frac->setNum(denom);
	frac->setDenom(num);

	return red(frac);
}

// Reduces this Fraction to lowest terms
// @param frac - the input Fraction to reduce
// @return the reduced terms Fraction
Fraction* Fraction::red(Fraction* frac) {
	int m = gcd(frac->getNum(), frac->getDenom());

	frac->setNum(frac->getNum() / m);
	frac->setDenom(frac->getDenom() / m);

	// Account for negative numbers (gcd result might be negative,
	// causing the denominator to be negative as well.)
	if(frac->getDenom() < 0) {
		frac->setNum(frac->getNum() * -1);
		frac->setDenom(frac->getDenom() * -1);
	}
	return frac;
}

// Converts the decimal to a Fraction in lowest terms
// @param real - the input real number (decimal)
// @note - the input decimal cannot be >= the integer max range: 2,147,483,647
//		   so, only accepted values are 0 to 2,147,483,646
// @return the Fraction converted from this decimal number
Fraction* Fraction::d2f(std::string real) {
	bool integer = true, negCheck = false;
	std::string intStr = "";
	std::string decStr = "";

	// Separate the integer part of the string with the decimal part
	for(int i = 0; i < real.length(); i++) {
		if(real.at(i) == '.') {
			if(i == 0)
				intStr = "0";
			else if(i == 1 && intStr == "-") {
				intStr = "0";
				negCheck = true;
			}
			integer = false;
		}
		else if(integer)
			intStr += real.at(i);
		else
			decStr += real.at(i);
	}
	int temp = negCheck ? -1 : 1;
	temp *= std::stoi(decStr);

	Fraction* frac = new Fraction(temp, pow(10, decStr.length()), std::stoi(intStr));
	return red(frac);
}

// Converts an improper Fraction to a mixed number
// @param frac - the input improper Fraction
// @return the Fraction in mixed form (mixed flag set as true, if applicable)
Fraction* Fraction::mix(Fraction* frac) {
	// Account for negative fractions
	bool negative = false;
	if(frac->getNum() < 0) {
		negative = true;
		frac->setNum(frac->getNum() * -1);
	}

	if(frac->getNum() > frac->getDenom()) {
		int mixedAdder = 0;

		while(frac->getNum() > frac->getDenom()) {
			if(negative)
				mixedAdder--;
			else
				mixedAdder++;

			frac->setNum(frac->getNum() - frac->getDenom());
		}
		frac->setMixedN(mixedAdder);
	}

	return red(frac);
}

// Converts a mixed number to a Fraction (improper)
// @param mixedN - the integer portion of the mixed number
// @param frac - the Fraction portion of the mixed number
// @pre - the fraction does not hold a mixed number integer value & fraction is not negative
// @throw run time exception if sign is included in the fraction instead of the mixedN
// @return the unmixed Fractional result
Fraction* Fraction::unm(int mixedN, Fraction* frac) {
	if((frac->getNum() < 0 || frac->getDenom() < 0) && mixedN != 0)
		throw std::runtime_error("Invalid input exception. Sign should be paired with N, not fractions.\n");

	int adder = mixedN;
	if(adder < 0)
		frac->setNum(frac->getNum() * -1);

	while(adder != 0) {
		if(adder < 0 ) {
			frac->setNum(frac->getNum() - frac->getDenom());
			adder++;
		}
		else {
			frac->setNum(frac->getNum() + frac->getDenom());
			adder--;
		}
	}

	frac->setMixedN(0);

	return red(frac);
}

// Adds two mixed numbers and returns as a mixed number
// @param mixedN1 - the integer portion of the first mixed number
// @param first - the Fraction portion of the first mixed number
// @param mixedN2 - the integer portion of th second mixed number
// @param second - the Fraction portion of the second mixed number
// @throw run time exception the sign is included in one or both of the fractions
// @return the mixed number Fraction result m1 + m2
Fraction* Fraction::amix(int mixedN1, Fraction* first, int mixedN2, Fraction* second) {
	if(first->getNum() < 0 || first->getDenom() < 0 || second->getNum() < 0 || second->getDenom() < 0)
		throw std::runtime_error("Invalid input exception. Sign should be paired with N, not fractions.\n");

	// If the mixedN integer is negative, make the fraction negative
	bool neg1 = false;
	bool neg2 = false;

	if(mixedN1 < 0) {
		first->setNum(first->getNum() * -1);
		neg1 = true;
	}
	if(mixedN2 < 0) {
		second->setNum(second->getNum() * -1);
		neg2 = true;
	}
	Fraction* result = xadd(first, second);
	result->setMixedN(mixedN1 + mixedN2);

	return result;
}

// Calculates which fraction is less and returns that fraction
// @param first - the first Fraction to compare
// @param second - the second Fraction to compare
// @return the smaller of the two fractions
int Fraction::less(Fraction* first, Fraction* second) {
	// Calculate the least common denominator
	int lcd = first->getDenom() * second->getDenom() / gcd(first->getDenom(), second->getDenom());
	
	int temp1 = lcd / first->getDenom();
	int temp2 = lcd / second->getDenom();

	temp1 *= first->getNum();
	temp2 *= second->getNum();

	if(temp1 == temp2) // Fractions are equal
		return -1;
	else if(temp1 < temp2) // Fraction 1 is smaller
		return 1;
	else // Fraction 1 is bigger
		return 0;
}

// Returns the greated common divisor by implementing Euclid's Algorithm
// @param num - the numerator of the fraction
// @param denom - the denominator of the fraction
// @return the integer greatest common divisor
int Fraction::gcd(int num, int denom) {
	if(num % denom == 0)
		return denom;
	else
		return gcd(denom, num % denom);
}