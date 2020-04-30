
#include "Path.h"

#include <iostream>

using namespace std;

Path::Path(int* innerCityIndexArray, int arraySize)
{
	pathIndexArray = new int [arraySize+2];

	pathIndexArray[0] = 0;
	pathIndexArray[arraySize-1] = 0;

	for(int i=0;i<arraySize;i++)
	{
		pathIndexArray[i+1] = innerCityIndexArray[i];
	}
	
}

Path::~Path()
{	
}

void Path::setCityIndexAt(int index, int cityIndex)
{
	pathIndexArray[index] = cityIndex;
}

int Path::getCityIndexAt(int index)
{
	return pathIndexArray[index];
}
