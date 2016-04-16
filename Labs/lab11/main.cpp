//*****************************************************************************
//
//		Author: Jay Offerdahl
//		Class:	EECS 560 (Data Structures)
//		Lab:	Tues. 11a - 12:50p
//		Lab #: 	11
//
//*****************************************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

typedef struct CycleHelper {
	int maxEdge1;
	int maxEdge2;

	int maxEdgeSoFar;

	int cycleVertex;
	bool cycleComplete;
} CycleHelper;

void dfs(int, int, int, int*, int*, CycleHelper*);
void printArr(int, int*);
void printMST(int, int, int*);
void resetArr(int, int*);
int connectionLoc(int, int, int);
int unknownVertex(int, int*);
int graphIndex(int, int, int); 

int main(int argc, char* argv[])
{	
	if(argc < 2) {
		std::cout << "Invalid usage, please include a file name (./lab [filename])\n";
		return 1;
	}

	std::cout << "********************************************************************\n\n";
	std::cout << "                       Jay Offerdahl - Lab 11                       \n\n";
	std::cout << "********************************************************************\n\n";

	// Read in the first line of the file & determine the number of vertices
	std::ifstream file(argv[1]);

	if(file) {
		std::string line;
		getline(file, line);
		std::stringstream stream(line);
		std::stringstream copy(line);

		int vertices = -1, arrSize = 0, temp, index = 0;

		while(copy) {
			copy >> temp;
			vertices++;
		}

		std::cout << "Number of vertices: " << vertices << "\n\n";

		for(int i = 0; i < vertices; i++)
				arrSize += i;

		// Initialize the array, fill it with the input values
		int dfsMST[arrSize], primsMST[arrSize], primsMST2[arrSize], visited[vertices];

		resetArr(arrSize, primsMST2);

		for(int r = 0; r < vertices; r++) {
			stream.str(line + "\r");

			for(int c = 0; c < vertices; c++) {
				while(r + 1 - c > 0) {
					c++;
					stream >> temp;
				}

				stream >> dfsMST[index];
				primsMST[index] = dfsMST[index];

				index++;
			}
			
			if(!getline(file, line))
				break;			
		}
		file.close();

		std::cout << "Input file accepted. Generating minimum spanning trees...\n\n";
		std::cout << "Original graph:\n";
		printArr(arrSize, dfsMST);

		// Use A DFS
		CycleHelper cycle;

		// Operate until the graph is a minimum spanning tree
		while(true) {
			// Reset the visited array
			resetArr(vertices, visited);

			// Reset our cycle helper
			cycle.cycleVertex = -1;
			cycle.maxEdge1 = -1;
			cycle.maxEdge2 = -1;
			cycle.maxEdgeSoFar = 0;
			cycle.cycleComplete = false;

			// Complete a depth first search on the graph
			dfs(vertices, 1, 0, visited, dfsMST, &cycle);

			// If the there's a cycleVertex, there's a cycle
			if(cycle.cycleVertex != -1) {
				// Get the index of the edge to remove
				index = graphIndex(vertices, cycle.maxEdge1, cycle.maxEdge2);

				// Remove the edge
				dfsMST[index] = 0;
			}
			else
				break;
		}

		// Print out the array of the graph
		std::cout << "\nMinimum spanning tree (DFS):\n";
		printArr(arrSize, dfsMST);
		printMST(arrSize, vertices, dfsMST);
		std::cout << "\n";

		// Use Prim's algorithm (visited array == known array)
		int known[vertices], dv[vertices], pv[vertices];
		resetArr(vertices, known);
		resetArr(vertices, dv);
		resetArr(vertices, pv);

		// Show the costs to each vertex after the first as impossible
		for(int i = 1; i < vertices; i++)
			dv[i] = 100000;

		int currIndex = 0, lowestSoFar = 100000, lowestVertexPath = 0;

		while(unknownVertex(vertices, known) != -1) {
			known[currIndex] = 1;

			// Update dv and pv arrays with current vertex's connections
			for(int i = 0; i < vertices; i++) {
				if(i != currIndex && !known[i]) {
					// Get the correct index to check in the array
					index = graphIndex(vertices, i + 1, currIndex + 1);

					temp = primsMST[index];

					// If there's an edge
					if(temp > 0) {
						// If this edge has less weight than another, replace it
						if(temp < dv[i]) {
							dv[i] = temp;
							pv[i] = currIndex + 1;
						}
					}
				}
			}

			// Find the lowest cost path to an unknown vertex
			for(int i = 1; i < vertices; i++) {
				if(!known[i] && dv[i] < lowestSoFar) {
					lowestSoFar = dv[i];
					lowestVertexPath = i;
				}
			}

			if(lowestSoFar == 100000)
				break;

			// Make the connection and move on
			index = graphIndex(vertices, pv[lowestVertexPath], lowestVertexPath + 1);
			primsMST2[index] = lowestSoFar;

			currIndex = lowestVertexPath;
			lowestSoFar = 100000;
		}

		std::cout << "\nMinimum spanning tree (Prim's Algorithm):\n";
		printArr(arrSize, primsMST2);
		printMST(arrSize, vertices, primsMST2);
		std::cout << "\n";
	}
	else {
		std::cout << "The input file was unabled to be opened...\n\n";
		return 1;
	}

	std::cout << "\nExiting program...\n\n";
	// Exit the program
	return 0;
}

/**
 * Determines if there's a cycle in the graph using a DFS method
 * @param  vertices   - the number of vertices in the graph
 * @param  vertex     - the current vertex to be searched
 * @param  prevVertex - the previous vertex that's currently being searched
 * @param  visited    - the array holding visited vertices information
 * @param  graph      - the array holding the undirected graph information
 * @param  cycle      - the cycle helper object to track the largest path/vertices that hold it
 * @return            - true if there's a cycle in this graph
 */
void dfs(int vertices, int vertex, int prevVertex, int* visited, int* graph, CycleHelper *cycle) {
	// Set this vertex as visited
	visited[vertex - 1] = true;
	int index;

	// Check all of the vertices
	for(int i = 1; i <= vertices; i++) {
		if(i != vertex && prevVertex != i) {
			// Get the correct index to check in the array
			index = graphIndex(vertices, i, vertex);

			// If there's an edge and we've visited that node already, store necessary data
			if(graph[index] != 0 && visited[i - 1]) {
				cycle->cycleVertex = i;
				cycle->maxEdgeSoFar = graph[index];
				cycle->maxEdge1 = vertex;
				cycle->maxEdge2 = i;
			}
			else if(graph[index] != 0) {
				dfs(vertices, i, vertex, visited, graph, cycle);

				if(cycle->cycleComplete)
					return;

				// Lower deck found a cycle, check for a higher edge here
				if(cycle->cycleVertex != -1) {
					// Compare this edge with the max
					if(graph[index] > cycle->maxEdgeSoFar) {
						cycle->maxEdgeSoFar = graph[index];
						cycle->maxEdge1 = vertex;
						cycle->maxEdge2 = i;
					}

					if(cycle->cycleVertex == vertex)
						cycle->cycleComplete = true;

					return;
				}
			}
		}
	}
}

/**
 * Prints out the one dimensional array
 * @param size - the size of the input array
 * @param arr  - the input array to print
 */
void printArr(int size, int* arr) {
	std::cout << "[";
	for(int i = 0; i < size; i++) {
		std::cout << arr[i];
		if(i != size - 1)
			std::cout << ", ";
	}
	std::cout << "]\n";
}

/**
 * Prints out the minimum spanning tree
 * @param size     - the size of the input array
 * @param vertices - the number of vertices in the graph
 * @param arr      - the input array to print
 */
void printMST(int size, int vertices, int* arr) {
	int index = 0;
	int cost = 0;

	for(int r = 0; r < vertices; r++) {
		for(int c = 0; c < vertices; c++) {
			while(r + 1 - c > 0)
				c++;

			if(arr[index++] != 0 && index <= size) {
				std::cout << "(" << r + 1 << "," << c + 1 << ") ";
				cost += arr[index - 1];
			}
		}
	}

	std::cout << "\n\nTotal spanning tree cost: " << cost << "\n";
}

/**
 * Resets the input array to all 0s
 * @param size - the size of the input array
 * @param arr  - the input array to reset
 */
void resetArr(int size, int* arr) {
	for(int i = 0; i < size; i++)
		arr[i] = 0;
}

/**
 * Calculates the reverse connection/forward connection given the two coordinates
 * @param  vertices - the number of vertices in the graph
 * @param  i        - the first coordinate
 * @param  j        - the second coordinate
 * @return          - the integer location of the index (0-based)
 */
int connectionLoc(int vertices, int i, int j) {
	int sum = 0;
	for(int k = 1; k < i; k++)
		sum += vertices - k;

	return sum + j - i - 1;
}

/**
 * Determines whether or not a node has not been visited in the graph
 * @param  vertices - the number of vertices in the graph
 * @param  known    - the array of known vertices
 * @return          - the integer location of the index (0-based)
 */
int unknownVertex(int vertices, int* known) {
	for(int i = 0; i < vertices; i++) {
		if(known[i] != 1)
			return i;
	}

	return -1;
}

/**
 * Returns the index (0-based) on the graph given the # of vertices and two coordinates
 * @param  vertices - the number of vertices in the graph
 * @param  i        - the first coordinate
 * @param  j        - the second coordinate
 * @return          - the integer location of the index (0-based)
 */
int graphIndex(int vertices, int i, int j) {
	if(i < j)
		return connectionLoc(vertices, i, j);
	else
		return connectionLoc(vertices, j, i);
}