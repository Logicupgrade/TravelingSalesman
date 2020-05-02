
#include "Path.h"

#include <iostream>

using namespace std;

Path::Path(int* innerCityIndexArray, int arraySize)
{
	pathArraySize = arraySize+2;
	// pathIndexArray = new int [pathArraySize];
	// vertexNames = new string [pathArraySize];

	pathIndexArray[0] = 0;
	pathIndexArray[pathArraySize-1] = 0;

	for(int i=0;i<arraySize;i++)
	{
		pathIndexArray[i+1] = innerCityIndexArray[i];
	}
	
}

Path::Path(const Path& aPath)
{
	pathArraySize = aPath.pathArraySize;
	traversalCost = aPath.traversalCost;
	

	for(int i=0;i<pathArraySize;i++)
	{
		pathIndexArray[i] = aPath.pathIndexArray[i];
		// vertexNames[i] = aPath.vertexNames[i];
	}
}

Path::~Path()
{		
}

int Path::getPathArraySize()
{
	return pathArraySize;
}

void Path::setCityIndexAt(int index, int cityIndex)
{
	pathIndexArray[index] = cityIndex;
}

int Path::getCityIndexAt(int index)
{
	return pathIndexArray[index];
}

void Path::operator=(const Path& aPath)
{
	pathArraySize = aPath.pathArraySize;
	traversalCost = aPath.traversalCost;
	

	for(int i=0;i<pathArraySize;i++)
	{
		pathIndexArray[i] = aPath.pathIndexArray[i];
		vertexNames[i] = aPath.vertexNames[i];
	}
	
}

void Path::setTraversalCost(int tCost)
{
	traversalCost = tCost;
}

int Path::getTraversalCost()
{
	return traversalCost;
}

void Path::setCityNameAt(string cityName, int index)
{
	vertexNames[index] = cityName;	
}
	
string Path::getCityNameAt(int index)
{
	return vertexNames[index];
}
