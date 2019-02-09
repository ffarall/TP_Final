#include "Token.h"
#include "Player.h"


Token::Token()
{
}


Token::~Token()
{
}

bool Token::addSettlement(EDASubject * owner_)
{
	Player* owner = static_cast<Player*>(owner_);
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

bool Token::addCity(EDASubject * owner_)
{
	Player* owner = static_cast<Player*>(owner_);
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

bool Token::addRoad(EDASubject * owner_)
{
	Player* owner = static_cast<Player*>(owner_);
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