
#ifndef	_PATH
#define _PATH

class Path
{

private:
	int* pathIndexArray;
public:
	Path(int* innerCityIndexArray, int arraySize);
	~Path();
	void setCityIndexAt(int index, int cityIndex);
	int getCityIndexAt(int index);
};

#endif