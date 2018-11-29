#pragma once
#include <string>

using namespace std;

class Road
{
public:
	Road();
	Road(string coordinate_);
	~Road();

	string getCoordinate();

private:
	string coordinate;
};

