#include "Token.h"
#include "Player.h"


Token::Token()
{
	for (auto set : settlementOwners)
	{
		set = nullptr;
	}
	for (auto city : cityOwners)
	{
		city = nullptr;
	}
	for (auto road : roadOwners)
	{
		road = nullptr;
	}
}


Token::~Token()
{
}

bool Token::addSettlement(EDASubject * owner_)
{
	Player* owner = static_cast<Player*>(owner_);
	int i = 0;
	while ((i != settlementOwners.size()) && (settlementOwners[i]))
	{
		i++;
	}
	if (i == settlementOwners.size())
	{
		return false;
	}
	else
	{
		settlementOwners[i] = owner;
		return true;
	}
}

bool Token::addCity(EDASubject * owner_)
{
	Player* owner = static_cast<Player*>(owner_);
	int i = 0;
	bool ret = false;

	while ((i != cityOwners.size()) && (cityOwners[i]))
	{
		i++;
	}
	if (i != cityOwners.size())
	{
		cityOwners[i] = owner;										// Adds to cityOwners.
		ret = true;
	}

	i = 0;
	while ((i != settlementOwners.size()) && (settlementOwners[i] != owner))
	{
		i++;
	}
	if (i == settlementOwners.size())
	{
		return false;
	}
	else
	{
		settlementOwners[i] = nullptr;								// Deletes from settlementOwners.
		return ret;
	}
}

bool Token::addRoad(EDASubject * owner_)
{
	Player* owner = static_cast<Player*>(owner_);
	int i = 0;
	while ((i != roadOwners.size()) && (roadOwners[i]))
	{
		i++;
	}
	if (i == roadOwners.size())
	{
		return false;
	}
	else
	{
		roadOwners[i] = owner;
		return true;
	}
}