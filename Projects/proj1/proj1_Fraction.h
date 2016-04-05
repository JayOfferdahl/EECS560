//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Proj #: 1
//
//*****************************************************************************

#ifndef Fraction_H
#define Fraction_H

#include <string>

class Fraction {
public:
	// Creates a Fraction with value 0
	Fraction();

	// Creates a Fraction with input numerator and denominator
	// @param numerator - the top half of the Fraction
	// @param denominator - the lower half of the Fraction
	Fraction(int numerator, int denominator);

	// Creates a Fraction with input numerator and denominator and mixed integer value
	// @param numerator - the top half of the Fraction
	// @param denominator - the lower half of the Fraction
	// @param mixedN - the value of the integer overflow of the mixed number
	Fraction(int numerator, int denominator, int mixedN);

	// Returns the whole integer part of the mixed number stored in this Fraction instance
	// @return - the whole mixed number integer
	int getMixedN();

	// Sets the whoe interger part of this Fraction
	// @param mixedN - the new mixedN to be stored in this Fraction
	void setMixedN(int mixedN);

	// Returns the numerator stored in this Fraction instance
	// @return - the private numerator
	int getNum();

	// Sets the numerator of this Fraction
	// @param numerator - the new numerator to be stored in this instance
	void setNum(int numerator);

	// Returns the denominator stored in this Fraction instance
	// @return - the private denominator
	int getDenom();

	// Sets the denominator of this Fraction
	// @param denominator - the new denominator to be stored in this instance
	void setDenom(int denominator);

	// Prints out the fraction, if it's a mixed number, does in the form 1 3/4, else
	// it simply prints out the fraction as 3/4
	void print();

	/////////////////////////////////////////////////////////////////////////////////////

	// Adds the two Fractions and returns the result
	// @param first - the first Fraction to add
	// @param second - the second Fraction to add
	// @return the Fraction result of first + second
	Fraction* add(Fraction* first, Fraction* second);

	// Adds the two Fractions and returns the result as a mixed 
	// number if the result is an improper Fraction
	// @param first - the first Fraction to add
	// @param second - the second Fraction to add
	// @return the Fraction result of first + second (mixed flag set if applicable)
	Fraction* xadd(Fraction* first, Fraction* second);

	// Subtracts the two Fractions and returns the result (F1 - F2)
	// @param first - the Fraction to be subtracted from
	// @param second - the Fraction to subtract from the first Fraction
	// @return the Fraction result of first - second
	Fraction* sub(Fraction* first, Fraction* second);

	// Multiplies the two Fractions and returns the result
	// @param first - the first Fraction to multiply
	// @param second - the second Fraction to multiply
	// @return the Fraction result of first * second
	Fraction* mul(Fraction* first, Fraction* second);

	// Divides the two Fractions and returns the result
	// @param first - the numerator of this division
	// @param second - the denominator of this division
	// @return the Fraction result of first / second
	Fraction* div(Fraction* first, Fraction* second);

	// Divides the two Fractions and returns the result as mixed
	// @param first - the numerator of this division
	// @param second - the denominator of this division
	// @return the Fraction result of first / second (mixed flag set if applicable)
	Fraction* xdiv(Fraction* first, Fraction* second);

	// Finds the reciprocal of this Fraction (inverts F)
	// @param frac - the input Fraction
	// @return the reciprocal of this Fraction (a / b --> b / a)
	Fraction* rec(Fraction* frac);

	// Reduces this Fraction to lowest terms
	// @param frac - the input Fraction to reduce
	// @return the reduced terms Fraction
	Fraction* red(Fraction* frac);

	// Converts the decimal to a Fraction in lowest terms
	// @param real - the input real number (decimal)
	// @return the Fraction converted from this decimal number
	Fraction* d2f(std::string real);

	// Converts an improper Fraction to a mixed number
	// @param frac - the input improper Fraction
	// @return the Fraction in mixed form (mixed flag set as true, if applicable)
	Fraction* mix(Fraction* frac);

	// Converts a mixed number to a Fraction (improper)
	// @param mixedN - the integer portion of the mixed number
	// @param frac - the Fraction portion of the mixed number
	// @return the unmixed Fractional result
	Fraction* unm(int mixedN, Fraction* frac);

	// Adds two mixed numbers and returns as a mixed number
	// @param mixedN1 - the integer portion of the first mixed number
	// @param first - the Fraction portion of the first mixed number
	// @param mixedN2 - the integer portion of th second mixed number
	// @param second - the Fraction portion of the second mixed number
	// @return the mixed number Fraction result m1 + m2
	Fraction* amix(int mixedN1, Fraction* first, int mixedN2, Fraction* second);

	// Calculates which fraction is less and returns the result
	// @param first - the first Fraction to compare
	// @param second - the second Fraction to compare
	// @return -1 the fractions are equal
	// @return  0 the first fraction is bigger
	// @return  1 the first fraction is smaller
	int less(Fraction* first, Fraction* second);

	// Returns the greated common divisor by implementing Euclid's Algorithm
	// @param n - the first number to compare
	// @param m - the second number to compare
	// @return the integer greatest common divisor
	int gcd(int n, int m);

private:
	// Private variables to hold this Fractions numerator and denominator
	// If the fraction is negative, m_numerator should be negative, not 
	// m_denomiator
	int m_numerator;
	int m_denominator;

	// Integer number of this mixed number (0 by default)
	int m_mixedN;
};

#endif // Fraction_H
