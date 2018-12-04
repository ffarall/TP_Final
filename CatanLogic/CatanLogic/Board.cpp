#include "Board.h"
#include "Hex.h"


Board::Board()
{
}

Board::Board(map<char, Token*>& board_, char robber_) : board(board_), robber(robber_)
{
}

Board::Board(map<char, Token*>& board_, char robber_, map<Coordinate, PortType>& ports_) : board(board_), robber(robber_), ports(ports_)
{
}


Board::~Board()
{
	for (auto token : board)
	{
		delete token.second;
	}
}

void Board::setDevCards(stack<DevCards>& pileOfDevCards_)
{
	pileOfDevCards = pileOfDevCards_;
}

void Board::setCircularToken(char token, unsigned int circToken)
{
	((Hex*)board[token])->setDiceNum(circToken);
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

void Board::moveRobber(char position)
{
	robber = position;
}

DevCards Board::pickDevCard()
{
	DevCards card = pileOfDevCards.top();
	pileOfDevCards.pop();
	return card;
}

bool Board::checkIfIsPort(string position)
{
	return (ports.find(position) != ports.end());
}

PortType Board::getPortType(string position)
{
	return ports[position];
}

void Board::setPort(string position, PortType type)
{
	ports[position] = type;
}
