

#ifndef	_GRAPH_PLACEHOLDER
#define _GRAPH_PLACEHOLDER

#include "Path.h"

#include <string>
#include <iostream>

using namespace std;

class GraphPlaceholder
{
private:
	string* vertices;
	int** 	adjacencyMatrix;
	int 	vertexCount;
	int 	minPathCost;
	Path* 	minPath;

public:
	GraphPlaceholder(int numVertex, string* newVertices, int** adjMatrix);

	void setMatrix( int numVertices, int** adjMatrix );
	
	//sets vertex array in adj array given vertex index and connection list(array)
	bool setVertexConnections(int vertexIndex, int* connections);
	
	//returns edge cost given vertex index and connecting vertex index
	int getConnectionValue(int vertexIndex, int connectionIndex);
	
	//returns name of vertex given the index
	string getVertexName(int vertexIndex);

	int traversePath(Path& currentPath);

	void displayMatrix();
};


#endif