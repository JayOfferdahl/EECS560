//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #:	4
//
//*****************************************************************************

#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
public:
	// Create a Node with city name and coordinates
	Node(std::string, int, int);
	
	// Return the city stored in this Node
	std::string getName();

	// Return the x coordinate of this Node
	int getX();

	// Return the y coordinate of this Node
	int getY();

	// Set the citry name stored in this Node to the input string
	void setName(std::string);

	// Set the x coordinate of this Node
	void setX(int);

	// Set the y coordinate of this Node
	void setY(int);

	// Return the height of this Node
	int getHeight();

	// Set the height of this Node
	void setHeight(int);

	// Prints out the Node
	void print();

	// Pointers to children nodes
	Node* left;
	Node* right;
	Node* parent;

private:
	// Integer to store the balance factor of this Node
	int m_height;
	
	// Value stored in this Node
	std::string m_name;
	int m_x;
	int m_y;
};

#endif
