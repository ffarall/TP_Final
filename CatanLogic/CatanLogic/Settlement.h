#pragma once
#include <string>

using namespace std;

class Settlement
{
public:
	Settlement();
	Settlement(string coordinate_);
	virtual ~Settlement();

	string getCoordinate();
	virtual string whatAmI();

protected:
	string coordinate;
};

