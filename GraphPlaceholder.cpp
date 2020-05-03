
#include "GraphPlaceholder.h"

GraphPlaceholder::GraphPlaceholder(int numVertex, string* newVertices, int** adjMatrix):vertexCount(numVertex)
{
	vertices = new string[numVertex];

	for(int i =0;i<numVertex;i++)
	{
		vertices[i] = newVertices[i]; 
	}

	setMatrix(numVertex, adjMatrix);
}

void GraphPlaceholder::setMatrix( int numVertices, int** adjMatrix )
{
	adjacencyMatrix = new int* [numVertices];
	for(int a=0;a<numVertices;a++)
	{
		adjacencyMatrix[a] = new int [numVertices]; 
	}
	
	for(int i=0; i<numVertices; i++)
	{
		for(int j=0; j<numVertices; j++)
		{
			adjacencyMatrix[i][j] = adjMatrix[i][j];
		}
	}
}

//sets vertex array in adj array given vertex index and connection list(array)
bool GraphPlaceholder::setVertexConnections(int vertexIndex, int* connections)
{
	for(int i = 0;i<vertexCount;i++)
	{
		adjacencyMatrix[vertexIndex][i] = connections[i];
	}

	return true;
}

//returns edge cost given vertex index and connecting vertex index
int GraphPlaceholder::getConnectionValue(int vertexIndex, int connectionIndex)
{
	return adjacencyMatrix[vertexIndex][connectionIndex];
}

//returns name of vertex given the index
string GraphPlaceholder::getVertexName(int vertexIndex)
{
	return vertices[vertexIndex];
}

int GraphPlaceholder::traversePath(Path& currentPath)
{
	int sum = 0;
	
	for(int i=0;i<currentPath.getPathArraySize()-1;i++)
	{
		sum += getConnectionValue( currentPath.getCityIndexAt(i),currentPath.getCityIndexAt(i+1) );
	}

	return sum;
}

void GraphPlaceholder::displayMatrix()
{

	for(int i=0; i<vertexCount; i++)
	{
		for(int j=0; j<vertexCount; j++)
		{
			cout<<"Matrix["<<i<<"]["<<j<<"]="<<adjacencyMatrix[i][j]<<" , ";
		}
		cout<<endl;
	}
}