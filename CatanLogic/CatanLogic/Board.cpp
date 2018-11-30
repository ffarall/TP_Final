#include "Board.h"



Board::Board()
{
}


Board::~Board()
{
}

bool Board::addSettlementToTokens(string position, Player* owner)
{
	bool ret = true;
	for (char c : position)					// For every token in coordinate...
	{
		ret &= board[c]->addSettlement(owner);		// Adds settlement.
	}
	return ret;
}

bool Board::addRoadToTokens(string position, Player * owner)
{
	bool ret = true;
	for (char c : position)						// For every token in coordinate...
	{
		ret &= board[c]->addRoad(owner);		// Adds road.
	}
	return ret;
}

bool Board::addCityToTokens(string position, Player * owner)
{
	bool ret = true;
	for (char c : position)						// For every token in coordinate...
	{
		ret &= board[c]->addCity(owner);		// Adds city.
	}
	return ret;
}
