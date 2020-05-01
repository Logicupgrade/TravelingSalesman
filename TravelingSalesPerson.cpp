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

	// int adjacencyMatrix[numVertices][numVertices]
	// {
	//     {99999,518,218,439,704},        //Reno 		0
	//     {518,99999,99999,421,840},      //SLC  		1
	//     {218,99999,99999,569,808},      //SF   		2
	//     {439,421,569,99999,1125},       //Vegas		3
	//     {704,840,808,1125,99999}        //Seattle	4
	// };
	

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

	int traversePath(Path currentPath)
	{
		int sum = 0;

		for(int i=0;i<vertexCount+1;i++)
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


/*Graph*/GraphPlaceholder ReadGraphFromFile(string filename);
stack<Path> generatePaths(int numVertices);
void displayPaths( stack<Path> pathsToDisplay, int numVertices );

int main()
{
	string inputFile = "input.txt";

	//important to most of generation
	int vertexCount = 5;

	stack<Path> flapjacks;

	flapjacks = generatePaths(vertexCount);
	displayPaths( flapjacks, vertexCount );

	ReadGraphFromFile(inputFile).displayMatrix();


	int lowestPathCost = 1000000;
	Path* lowestPath;

	int pathCount = 1;
	while( !flapjacks.empty() )
	{	
		int pathCost;
		cout<<"Path "<<pathCount<<": [";
		for(int i=0;i<vertexCount+1;i++)
		{
			cout<<flapjacks.top().getCityIndexAt(i);
			if(i != vertexCount)
			{
				cout<<",";
			}
			else
			{
				cout<<"]"<<endl;
			}
		}
		pathCost = ReadGraphFromFile(inputFile).traversePath( flapjacks.top() );
		cout<<"Path Cost: "<<pathCost<<endl;

		if(pathCost<lowestPathCost)
		{
			lowestPathCost = pathCost;
			//lowestPath = flapjacks.top(); //**** need to write Path copy constructor and possibly =operator overload 
		}
		flapjacks.pop();
		pathCount++;
	}

	cout<<"Lowest Path Cost!: "<<lowestPathCost<<endl;
	

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

	// cout<<"countVertices: "<<countVertices<<endl;

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

	// cout<<"row: "<<row<<", col: "<<column<<endl;

	
	//check vertices Array
	// cout<<"Vertex: ";
	// for(int i=0;i<countVertices;i++)
	// {
	// 	 cout<<vertices[i];
	// 	 if(i != (countVertices-1))
	// 	 {
	// 	 	cout<<",";
	// 	 } 
	// }
	// cout<<endl;
	// cout<<"}"<<endl;   //*******cout is fked when using "}" or "]"
		 
	
	// check 2d matrix
	// for(int i=0; i<countVertices; i++)
	// {
	// 	for(int j=0; j<countVertices; j++)
	// 	{
	// 		cout<<"Matrix["<<i<<"]["<<j<<"]="<<inMatrix[i][j]<<" , ";
	// 	}
	// 	cout<<endl;
	// }

	GraphPlaceholder inGraph(countVertices, vertices, inMatrix);

	return inGraph;
}

//**********notes for automating exclusion, though seems unnecessary *********************
//can automate exclusion: need array of vertex pair indices that are unconnected 
//ie: noEdgePairArray[x][2] = {{0,1},{2,6}}
//for this project we will use the array {{1,2}}
//use int** noEdgePairArray as parameter
//put ifs in forloop iterating though all noEdgePair
stack<Path> generatePaths(int numVertices)
{
	int permArraySize = numVertices-1;
	stack<Path> pathStack;

	//array of individual permutation 
	int permArray[permArraySize];
	

	for(int i=0;i<numVertices;i++)
	{
		permArray[i] = i+1;
	}

	//sanitycheck prints permArray
	// for(int i=0;i<numVertices-1;i++)
	// {
	// 	cout<<"permArray["<<i<<"]"<<permArray[i]<<endl;
	// }

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
    		//creates path with current permutation excluding nonedgeVertices
    		Path tempPushPath(permArray,numVertices-1);
    		//pushes path to stack
    		pathStack.push(tempPushPath);
    	}
        
    } 
    while ( std::next_permutation(permArray,permArray+permArraySize) );

    return pathStack;
}

void displayPaths( stack<Path> pathsToDisplay, int numVertices )
{
	while(!pathsToDisplay.empty())
	{
		cout<<"Path: ";
		for(int i=0;i<numVertices+1;i++)
		{
			cout<<pathsToDisplay.top().getCityIndexAt(i);
		}
		cout<<endl;
		pathsToDisplay.pop();
	}
}