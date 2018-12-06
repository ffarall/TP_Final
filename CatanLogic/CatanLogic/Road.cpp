#include "Road.h"



Road::Road()
{
}

Road::Road(string coordinate_, vector< string > adjacentVertexes_)
{
	coordinate = coordinate_;
	adjacentVertexes = adjacentVertexes_;
}


Road::~Road()
{
}

string Road::getCoordinate()
{
	return coordinate;
}
