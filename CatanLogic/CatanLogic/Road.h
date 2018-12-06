#pragma once
#include <string>
#include <vector>

using namespace std;

class Road
{
public:
	Road();
	Road(string coordinate_, vector< string > adjacentVertexes_);
	~Road();

	string getCoordinate();

private:
	string coordinate;
	vector< string > adjacentVertexes;
};

