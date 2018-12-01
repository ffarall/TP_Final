#pragma once
#include "Token.h"
#include "Player.h"
#include <iostream>
#include <map>

using namespace std;

class Board
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

private:
	map< char, Token* > board;
};

