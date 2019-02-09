#pragma once
#include <array>
#include "EDASubject.h"
#include "CatanDefs.h"

using namespace std;

class Token
{
public:
	Token();
	virtual ~Token();

	virtual string whatAmI() = 0;

	// Returns true if owner could be added, false otherwise.
	bool addSettlement(EDASubject* owner_);
	// Returns true if owner could be added, false otherwise.
	bool addCity(EDASubject* owner_);
	// Returns true if owner could be added, false otherwise.
	bool addRoad(EDASubject* owner_);

	// Gives a resource of this token's type

protected:
	array< EDASubject*, 6 > settlementOwners;
	array< EDASubject*, 6 > cityOwners;
	array< EDASubject*, 6 > roadOwners;
};

