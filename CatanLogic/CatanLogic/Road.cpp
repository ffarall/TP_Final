#include "Road.h"



Road::Road()
{
}

Road::Road(string coordinate_)
{
	coordinate = coordinate_;
}


Road::~Road()
{
}

string Road::getCoordinate()
{
	return coordinate;
}
