#include "Token.h"



Token::Token()
{
	settlementOwners.fill(nullptr);
	cityOwners.fill(nullptr);
	roadOwners.fill(nullptr);
}


Token::~Token()
{
}

bool Token::addSettlement(Player * owner)
{
	int i = 0;
	while ((settlementOwners[i] != nullptr) && (i != settlementOwners.size()))
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

bool Token::addCity(Player * owner)
{
	int i = 0;
	bool ret = false;

	while ((cityOwners[i] != nullptr) && (i != cityOwners.size()))
	{
		i++;
	}
	if (i != cityOwners.size())
	{
		cityOwners[i] = owner;										// Adds to cityOwners.
		ret = true;
	}

	i = 0;
	while ((settlementOwners[i] != owner) && (i != settlementOwners.size()))
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

bool Token::addRoad(Player * owner)
{
	int i = 0;
	while ((roadOwners[i] != nullptr) && (i != roadOwners.size()))
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