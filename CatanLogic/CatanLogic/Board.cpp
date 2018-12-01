#include "Board.h"
#include "Hex.h"


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

ResourceType Board::getResourceFromHex(char tokenChar)
{
	Hex* hex = static_cast< Hex* >(board[tokenChar]);
	return hex->giveResource();
}

void Board::assignResourcesForNum(int num)
{
	for (auto token : board)
	{
		if (isalpha(token.first))							// If it's a Hex...
		{
			Hex* hex = static_cast<Hex*>(token.second);
			if (hex->getDiceNum() == num)					// If it's diceNum is the given...
			{
				hex->assignResources();
			}
		}
	}
}
