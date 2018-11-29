#include "City.h"



City::City()
{
}

City::City(string coordinate_)
{
	coordinate = coordinate_;
}


City::~City()
{
}

string City::whatAmI()
{
	return "City";
}
