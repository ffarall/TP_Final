#pragma once
#include <array>
#include "Player.h"

using namespace std;

class Token
{
public:
	Token();
	virtual ~Token();

	// Returns true if owner could be added, false otherwise.
	bool addSettlement(Player* owner);
	// Returns true if owner could be added, false otherwise.
	bool addCity(Player* owner);
	// Returns true if owner could be added, false otherwise.
	bool addRoad(Player* owner);

protected:
	array< Player*, 6 > settlementOwners;
	array< Player*, 6 > cityOwners;
	array< Player*, 6 > roadOwners;
};

