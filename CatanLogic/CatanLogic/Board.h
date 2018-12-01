#pragma once
#include "Token.h"
#include "Player.h"
#include "EDASubject.h"
#include <iostream>
#include <map>

using namespace std;

class Board :
	public EDASubject
{
public:
	Board();
	virtual ~Board();

	// Creates new board randomly and according to game rules.
	void shuffleBoard();

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

private:
	// Actual board containing the identifier of every Token (which can be a Sea or a Hex).
	map< char, Token* > board;
	// Position of Robber.
	char robber;
};

