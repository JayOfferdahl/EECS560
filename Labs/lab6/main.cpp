//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #: 	6
//
//*****************************************************************************

#include <iostream>
#include <stdlib.h>

void dfs(int, int, int*, int*);
void printArr(int, int*);
void resetArr(int, int*);
int loc(int, int);
int connectionLoc(int, int, int);

#define EDGE_DENSITY 0.6

int main(int argc, char** argv)
{
	int temp, vertices, arrSize, seed;

	while(true) {
		std::cout 	<< "\nOptions:\n1. Generate Graph\n2. Quit\n\nChoice: ";
		std::cin >> temp;

		switch(temp) {
		// Generate a graph based on user input of # of vertices and the seed
		case 1: {
			std::cout << "\nNumber of vertices: ";
			std::cin >> vertices;

			// Check for valid input
			if(vertices < 1) {
				std::cout << "Invalid number of vertices. Please try again.\n";
				break;
			}

			std::cout << "Seed: ";
			std::cin >> seed;

			std::cout << "\nCreating graph of " << vertices << " vertices with seed " << seed << ".\n\n";

			// Compute the array size based on the number of vertices
			arrSize = 0;

			for(int i = 0; i < vertices; i++)
				arrSize += i;

			// Declare the arrays
			int arr[arrSize];
			int visited[vertices];

			// Generate the graph (edge density defined globally);
			srand(seed);
			for(int i = 0; i < arrSize; i++) {
				if((double) rand() / RAND_MAX <= EDGE_DENSITY)
					arr[i] = rand() % 21;
				else
					arr[i] = 0;
			}
			// Determine if the graph is connected using DFS
			bool disconnected = true;
			while(disconnected) {
				// Reset the visited array and do a dfs
				resetArr(vertices, visited);
				dfs(vertices, 1, visited, arr);

				// The first vertex is always visited, start at the second
				for(int i = 1; i < vertices; i++) {
					// If any 0s, connect it with the last visited node
					if(visited[i] == 0) {
						// Generate an edge weight and insert it in the last visited vertex
						std::cout << "(" << i + 1 << ") was not visited. Fixing...\n";
						arr[loc(i, vertices)] = rand() % 21;

						visited[i] = 1;
						// Break out and try another dfs
						break;
					}

					// If we reached the end of the list, it's no longer disconnected
					if(i == vertices - 1)
						disconnected = false;
				}
			}

			// Print out the array of the graph
			std::cout << "Connected undirected graph:\n";
			printArr(arrSize, arr);
			break;
		}
		// Quit
		case 2: {
			// Exit the program on user request
			return 0;
		}
		// Invalid input
		default:
			std::cout << "Invalid input, please try again.\n\n";
			break;
		}
	}
}

// Searches the array using a depth first algorithm
// @param vertices - the number of vertices in the graph
// @param vertex - the current vertex to be searched
// @param visited - the array holding visited vertices information
// @param graph - the array holding the undirected graph information
void dfs(int vertices, int vertex, int* visited, int* graph) {
	// Set this vertex as visited
	visited[vertex - 1] = true;
	int index;

	// Check all of the vertices
	for(int i = 1; i <= vertices; i++) {
		if(i != vertex) {
			// Get the correct index to check in the array
			if(i < vertex)
				index = connectionLoc(vertices, i, vertex);
			else // #TODO -- this can be replaced with connectionLoc(vertices, vertex, i)...dummy
				index = loc(vertex, vertices) + i - vertex - 1;

			// If there's an edge and we haven't visited it, visit it
			if(graph[index] != 0 && !visited[i - 1])
				dfs(vertices, i, visited, graph);
		}
	}
}

// Prints out the input array
// @param size - the size of the input array
// @param arr - the input array to reset
void printArr(int size, int* arr) {
	std::cout << "[";
	for(int i = 0; i < size; i++) {
		std::cout << arr[i];
		if(i != size - 1)
			std::cout << ", ";
	}
	std::cout << "]\n";
}

// Resets the input array to an array of 0s
// @param size - the size of the input array
// @param arr - the input array to reset
void resetArr(int size, int* arr) {
	for(int i = 0; i < size; i++)
		arr[i] = 0;
}

// Calculates the starting index location of the vertex given the number of verices
// @param vertex - current vertex to be examined
// @param vertices - the number of vertices in the graph
// @return the integer location of the row start (0-format)
int loc(int vertex, int vertices) {
	int location = 0;

	for(int i = 1; i < vertex; i++)
		location += vertices - i;

	return location;
}

// Calculates the reverse connection index given two coordinates
// @note - this function should only be used on cases where i < j
// @param vertices - the number of vertices in the graph
// @param i - the first coordinate, if looking for connection between 2 and 1,
//			  i would be 1, j would be 2.
// @param j - see above
// @return the integer location of the index (0-format)
int connectionLoc(int vertices, int i, int j) {
	int sum = 0;
	for(int k = 1; k < i; k++)
		sum += vertices - k;

	return sum + j - i - 1;
}