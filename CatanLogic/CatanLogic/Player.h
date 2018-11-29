#pragma once
#include <cstdint>
#include <map>
#include <list>
#include <string>
#include "Settlement.h"
#include "Road.h"

using namespace std;

class Player
{
public:
	Player();
	virtual ~Player();

	void init();

	size_t getVictoryPoints();
	string getName();

	// Asks if player has won.
	bool hasWon();

private:
	// True when player has won.
	bool iWon;
	// Counter of victory points.
	size_t victoryPoints;
	// Name of the player.
	string name;
	// Map of this player's settlements (some can be cities).
	map< string, Settlement* > mySettlements;
	// Map of this player's roads.
	map< string, Road* > myRoads;
	// Map of rivals' settlements (some can be cities).
	map< string, Settlement* > rivalsSettlements;
	// Map of rivals' roads.
	map< string, Road* > rivalsRoads;
	// List of coordinates available for putting roads.
	list< string > availableForRoad;
	// List of coordinates available for putting settlements.
	list< string > availableForSettlements;

	// Sets all corners of board available for building Settlements.
	void allJunctionsAvailable();
};

