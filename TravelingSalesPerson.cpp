#include "Path.cpp"

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>

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
	GraphPlaceholder(int numVertex, string* newVertices, int** adjMatrix):vertexCount(numVertex)
	{
		vertices = new string[numVertex];

		for(int i =0;i<numVertex;i++)
		{
			vertices[i] = newVertices[i]; 
		}

		setMatrix(numVertex, adjMatrix);
	}

	void setMatrix( int numVertices, int** adjMatrix )
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
	bool setVertexConnections(int vertexIndex, int* connections)
	{
		for(int i = 0;i<vertexCount;i++)
		{
			adjacencyMatrix[vertexIndex][i] = connections[i];
		}

		return true;
	}

	//returns edge cost given vertex index and connecting vertex index
	int getConnectionValue(int vertexIndex, int connectionIndex)
	{
		return adjacencyMatrix[vertexIndex][connectionIndex];
	}

	//returns name of vertex given the index
	string getVertexName(int vertexIndex)
	{
		return vertices[vertexIndex];
	}

	int traversePath(Path& currentPath)
	{
		int sum = 0;
		
		for(int i=0;i<currentPath.getPathArraySize()-1;i++)
		{
			sum += getConnectionValue( currentPath.getCityIndexAt(i),currentPath.getCityIndexAt(i+1) );
		}

		return sum;
	}

	void displayMatrix()
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
};


GraphPlaceholder ReadGraphFromFile(string filename);
stack<Path> generatePaths(int numVertices, GraphPlaceholder aGraph);
Path findShortestPath(GraphPlaceholder aGraph, stack<Path> pathStack);
void displayPaths( stack<Path> pathsToDisplay, int numVertices );
bool writePathsToFile(string filename);


int main()
{
	string inputFile = "input.txt";

	//important to most of generation
	int vertexCount = 5;

	stack<Path> flapjacks;
	GraphPlaceholder theGraph = ReadGraphFromFile(inputFile);

	// int testPath[4]= {1,2,3,4};
	// Path TestPath(testPath,4);
	// theGraph.displayMatrix();

	flapjacks = generatePaths(vertexCount,theGraph);

	displayPaths( flapjacks, vertexCount );

	

	findShortestPath(theGraph, flapjacks);
	

	return 0;
}

GraphPlaceholder ReadGraphFromFile(string filename)
{
	bool gotVertices = false;
	int countVertices = 0;
	int vertexIndex = 0;
	string* vertices;
	string lineIn;
	string lineParse;
	int** inMatrix;
	
	ifstream getGraph;
	getGraph.open(filename);

	getline(getGraph,lineIn,'\n');
	stringstream getVerticesCount(lineIn);

	//get vertices count
	while( getline(getVerticesCount,lineParse,',') )
	{
		countVertices++;
	}

	vertices = new string [countVertices];

	//setup empty 2D matrix of size (countVertices)^2
	inMatrix = new int*[countVertices];
	for(int i=0;i<countVertices;i++)
	{
		inMatrix[i] = new int[countVertices];
	}

	//accounting for vertex title row
	int row = -1;
	int column = -countVertices;

	//reset getline to beginning of file
	getGraph.seekg(0);

	if( getGraph.is_open() )
	{
		
		while( getline(getGraph,lineIn,'\n') )
		{
			stringstream lineStr(lineIn);

			//accounts for vertex title columns
			if(gotVertices)
			{
				column = 0;
			}

			while( getline(lineStr,lineParse,',') )
			{
				
				if(!gotVertices)
				{
					//set vertices[0-n]
					vertices[vertexIndex]=lineParse;
					vertexIndex++;
				}
				else
				{	
					inMatrix[row][column] = stoi(lineParse);
				}

				column++;
			}
			//should get vertices after first iteration
			gotVertices = true;
			
			row++;
		}			
	}

	getGraph.close();

	GraphPlaceholder inGraph(countVertices, vertices, inMatrix);

	return inGraph;
}

//**********notes for automating exclusion, though seems unnecessary *********************
//can automate exclusion: need array of vertex pair indices that are unconnected 
//ie: noEdgePairArray[x][2] = {{0,1},{2,6}}
//for this project we will use the array {{1,2}}
//use int** noEdgePairArray as parameter
//put ifs in forloop iterating though all noEdgePair
stack<Path> generatePaths(int numVertices, GraphPlaceholder aGraph)
{
	stack<Path> lameStack;

	int permArraySize = numVertices-1;

	//array of individual permutation 
	int permArray[permArraySize];
	

	for(int i=0;i<numVertices;i++)
	{
		permArray[i] = i+1;
	}

    do 
    {	
    	bool canDo = true;
    	for(int i=0;i<permArraySize-1;i++)
    	{
    		if ( (permArray[i] == 1) || (permArray[i] == 2) )
    		{
    			if( (permArray[i+1] == 1) || (permArray[i+1] == 2) )
    			{
    				canDo = false;
    				break;
    			}
    			
    		}
    	}
    	if(canDo)
    	{

    		//temporary Path used to turn permutation into Path and push stack
			Path tempPushPath(permArray,numVertices-1);

    		//set traveral time 
    		tempPushPath.setTraversalCost( aGraph.traversePath(tempPushPath) );

    		
    		//set city name array using graph as reference
    		for( int i=0;i<tempPushPath.getPathArraySize();i++ )
    		{
	   			tempPushPath.setCityNameAt( aGraph.getVertexName( tempPushPath.getCityIndexAt(i) ) , i);
    		}

    		//pushes path to stack
    		lameStack.push(tempPushPath);///**OLD Isssue resolved, but keeping as reminder to research dynamic allocation for multiple arrays in stack and Object Scope

    	}
        
    } 
    while ( next_permutation(permArray,permArray+permArraySize) );

    return lameStack;
}

Path findShortestPath(GraphPlaceholder aGraph, stack<Path> pathStack)
{
	int vertexCount = pathStack.top().getPathArraySize();

	int lowestPathCost = 1000000;
	int tempPath[vertexCount+1];
	int currentPathCost;

	for(int i=0;i<vertexCount;i++)
	{
		tempPath[i]=0;
	}

	Path lowestPath(tempPath,vertexCount);

	while( !pathStack.empty() )
	{	
		//Path Display function *******************************
		
		//*****************************************************

		currentPathCost = aGraph.traversePath( pathStack.top() );

		if( currentPathCost < lowestPathCost )
		{
			lowestPathCost = currentPathCost;
			lowestPath = pathStack.top();
		}
		pathStack.pop();
	}

	
	cout<<"Shortest Path!: [";
	for( int i=0; i<lowestPath.getPathArraySize();i++ )
	{
		cout<<lowestPath.getCityIndexAt(i);
		if(i != lowestPath.getPathArraySize()-1)
		{
			cout<<",";
		}
		else
		{
			cout<<"]"<<endl;
		}
	}
	
	cout<<"Shortest Path Cost!: "<<lowestPathCost<<endl;

	return lowestPath;
}

void displayPaths( stack<Path> pathsToDisplay, int numVertices )
{
	while(!pathsToDisplay.empty())
	{
		cout<<"Path: [";
		for(int i=0;i<numVertices+1;i++)
		{
			cout<<pathsToDisplay.top().getCityIndexAt(i);
			if(i != numVertices)
			{
				cout<<",";
			}
		}
		cout<<"]"<<endl;
		cout<<"Cost: "<<pathsToDisplay.top().getTraversalCost()<<endl;
		pathsToDisplay.pop();
	}
}

bool writePathsToFile(string filename)
{
	return true;
}