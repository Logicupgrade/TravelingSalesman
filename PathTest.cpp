
#include "Path.cpp"

#include <iostream>

using namespace std;

int main()
{

	int destinationsIndices[4] = {2,3,4,5};

	Path travelDestinations(destinationsIndices, 4);

	for(int i=0;i<6;i++)
	{
		cout<<"City index: "<<travelDestinations.getCityIndexAt(i)<<" at Index"<< i <<endl;
	}
}