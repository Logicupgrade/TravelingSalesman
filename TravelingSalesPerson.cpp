#include "Path.cpp"
// #include "GraphPlaceholder.cpp"
#include "Graph.cpp"

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Graph ReadGraphFromFile(string filename);
stack<Path> generatePaths(int numVertices, Graph aGraph);
Path findShortestPath(Graph aGraph, stack<Path> pathStack);
void displayPaths( stack<Path> pathsToDisplay, int numVertices );
bool writePathsToFile(stack<Path> pathsToDisplay, int numVertices, Path shortPath, string filename);


int main()
{
	//important to most of generation
	int vertexCount = 5;

	//file I/O names
	string inputFile = "input.txt";
	string outputFile = "output.txt";

	//initializing objects: Path,Stack<Paths>,Graph
	Path shortestPath;
	stack<Path> pathStack;
	Graph theGraph = ReadGraphFromFile(inputFile);
	pathStack = generatePaths(vertexCount,theGraph);

	//Finding shortestPath
	shortestPath = findShortestPath(theGraph, pathStack);

	//display all of the Paths
	displayPaths( pathStack, vertexCount );

	//Write all of the Paths, Shortest Path, and Shortest Path Cost to file
	writePathsToFile( pathStack, vertexCount, shortestPath, outputFile );
	
	return 0;
}

Graph ReadGraphFromFile(string filename)
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

	//OLD// GraphPlaceholder inGraph(countVertices, vertices, inMatrix);
	Graph inGraph(countVertices, vertices, inMatrix);

	return inGraph;
}

//**********notes for automating exclusion, though seems unnecessary *********************
//can automate exclusion: need array of vertex pair indices that are unconnected 
//ie: noEdgePairArray[x][2] = {{0,1},{2,6}}
//for this project we will use the array {{1,2}}
//use int** noEdgePairArray as parameter
//put ifs in forloop iterating though all noEdgePair
stack<Path> generatePaths(int numVertices, Graph aGraph)
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
    		//aGraph.traversePath(tempPushPath)
    		//traverse sets cost in path (redundant, but would like to choose to not update path cost with graph)
    		
    		//set city name array using graph as reference
    		for( int i=0;i<tempPushPath.getPathArraySize();i++ )
    		{
	   			tempPushPath.setCityNameAt( aGraph.getVertex( tempPushPath.getCityIndexAt(i) ) , i);
	   										//OLD//aGraph.getVertexName( tempPushPath.getCityIndexAt(i) )
    		}

    		//pushes path to stack
    		lameStack.push(tempPushPath);///**OLD Isssue resolved, but keeping as reminder to research dynamic allocation for multiple arrays in stack and Object Scope

    	}
        
    } 
    while ( next_permutation(permArray,permArray+permArraySize) );

    return lameStack;
}

Path findShortestPath(Graph aGraph, stack<Path> pathStack)
{
	int vertexCount = pathStack.top().getPathArraySize();

	int shortestPathCost = 1000000;
	int tempPath[vertexCount+1];
	int currentPathCost;

	for(int i=0;i<vertexCount;i++)
	{
		tempPath[i]=0;
	}

	Path shortestPath(tempPath,vertexCount);

	while( !pathStack.empty() )
	{	
		currentPathCost = aGraph.traversePath( pathStack.top() );

		if( currentPathCost < shortestPathCost )
		{
			shortestPathCost = currentPathCost;
			shortestPath = pathStack.top();
		}
		pathStack.pop();
	}

	
	cout<<"Shortest Path!: [";
	for( int i=0; i<shortestPath.getPathArraySize();i++ )
	{
		cout<<shortestPath.getCityIndexAt(i);
		if(i != shortestPath.getPathArraySize()-1)
		{
			cout<<",";
		}
		else
		{
			cout<<"]"<<endl;
		}
	}
	
	cout<<"Shortest Path Cost!: "<<shortestPathCost<<endl;

	return shortestPath;
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

bool writePathsToFile(stack<Path> pathsToDisplay, int numVertices, Path shortPath, string filename)
{
	bool wroteToFile = false;
	ofstream theFile (filename);

	if(theFile.is_open())
	{
		//write all paths to file
		while(!pathsToDisplay.empty())
		{
			theFile<<"Path: [";
			for(int i=0;i<numVertices+1;i++)
			{
				theFile<<pathsToDisplay.top().getCityIndexAt(i);
				if(i != numVertices)
				{
					theFile<<",";
				}
			}
			theFile<<"]"<<endl;
			theFile<<"Cost: "<<pathsToDisplay.top().getTraversalCost()<<endl;
			pathsToDisplay.pop();
		}

		theFile<<endl;
		theFile<<"Shortest Path!: [";
		for( int i=0; i<shortPath.getPathArraySize();i++ )
		{
			theFile<<shortPath.getCityIndexAt(i);
			if(i != shortPath.getPathArraySize()-1)
			{
				theFile<<",";
			}
			else
			{
				theFile<<"]"<<endl;
			}
		}
		theFile<<"Shortest Path Cost!: "<<shortPath.getTraversalCost()<<endl;
		theFile.close();
		wroteToFile = true;
	}

	else
	{
		cout<<"Unable to open File"<<endl;
	}

	return wroteToFile;
}