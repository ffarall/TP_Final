#include "Settlement.h"



Settlement::Settlement()
{
}

Settlement::Settlement(string coordinate_)
{
	coordinate = coordinate_;
}


Settlement::~Settlement()
{
}

string Settlement::getCoordinate()
{
	return coordinate;
}

string Settlement::whatAmI()
{
	return "Settlement";
}
