#include "Path.cpp"

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;


stack<Path> generatePaths(int numPaths);
void displayPaths( stack<Path> pathsToDisplay, int numVertices );

int main()
{
	// int adjacencyMatrix[numVertices][numVertices]
	// {
	//     {99999,518,218,439,704},        //Reno 		0
	//     {518,99999,99999,421,840},      //SLC  		1
	//     {218,99999,99999,569,808},      //SF   		2
	//     {439,421,569,99999,1125},       //Vegas		3
	//     {704,840,808,1125,99999}        //Seattle	4
	// };

	//int minPath;

	//important to most of generation
	int vertexCount = 5;

	stack<Path> flapjacks;

	flapjacks = generatePaths(vertexCount);
	displayPaths( flapjacks, vertexCount );

	return 0;
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