
#ifndef	_PATH
#define _PATH

#include <string>

using namespace std;

class Path
{

private:
	int pathIndexArray[6];
	int pathArraySize;
	int traversalCost;
	string vertexNames[6];
public:
	Path();
	Path(int* innerCityIndexArray, int arraySize);
	Path(const Path& aPath);
	~Path();
	int getPathArraySize();
	void setCityIndexAt(int index, int cityIndex);
	int getCityIndexAt(int index);
	void operator=(const Path& aPath);
	void setTraversalCost(int tCost);
	int getTraversalCost();
	void setCityNameAt(string cityName, int index);
	string getCityNameAt(int index);
};

#endif