#pragma once
#include <array>
#include "Player.h"

using namespace std;

enum ResourceType : char { M='M', L='L', P='P', T='T', O='O', N='N' };

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

	// Gives a resource of this token's type

protected:


	array< Player*, 6 > settlementOwners;
	array< Player*, 6 > cityOwners;
	array< Player*, 6 > roadOwners;
};

