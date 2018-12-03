#pragma once
#include "Token.h"
#include "Player.h"
#include "EDASubject.h"
#include <iostream>
#include <map>
#include <stack>
#include "CatanDefs.h"

using namespace std;
using Coordinate = string;

class Board :
	public EDASubject
{
public:
	Board();
	Board(map< char, Token* >& board_, char robber_);
	Board(map< char, Token* >& board_, char robber_, map< Coordinate, PortType >& ports_);
	virtual ~Board();

	// Creates new board randomly and according to game rules.
	void shuffleBoard();

	// Sets new pile of devCards.
	void setDevCards(stack< DevCards >& pileOfDevCards_);
	// Sets Circular Token for the given Token.
	void setCircularToken(char token, unsigned int circToken);

	// Returns false if one of the Tokens is already full of settlements.
	bool addSettlementToTokens(string position, Player* owner);
	// Returns false if one of the Tokens is already full of roads.
	bool addRoadToTokens(string position, Player* owner);
	// Returns false if one of the Tokens is already full of cities.
	bool addCityToTokens(string position, Player* owner);

	// Returns ResourceType from Hex. Validation that the char given is alpha must be done before calling.
	ResourceType getResourceFromHex(char tokenChar);
	// Assigns resources from all of the Hex that have a diceNum like the given.
	void assignResourcesForNum(int num);

	// Moves Robber to position given.
	void moveRobber(char position);

	// Returns DevCard at the top of the pile.
	DevCards pickDevCard();

	// Checks if position given has a port.
	bool checkIfIsPort(string position);
	// Returns type of port in given position.
	PortType getPortType(string position);
	// Sets port in position given to type given.
	void setPort(string position, PortType type);

private:
	// Actual board containing the identifier of every Token (which can be a Sea or a Hex).
	map< char, Token* > board;
	// Position of Robber.
	char robber;
	// DevCards pile.
	stack< DevCards > pileOfDevCards;
	// Vertexes with ports.
	map< Coordinate, PortType > ports;
};

