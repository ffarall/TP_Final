#include "Hex.h"
#include "Player.h"


Hex::Hex()
{
	init();
}

Hex::Hex(ResourceType resource_, int diceNum_)
{
	init();
	setResource(resource_);
	setDiceNum(diceNum_);
}


Hex::~Hex()
{
}

string Hex::whatAmI()
{
	return "Hex";
}

void Hex::setResource(ResourceType resource_)
{
	resource = resource_;
}

void Hex::setDiceNum(int diceNum_)
{
	diceNum = diceNum_;
}

int Hex::getDiceNum()
{
	return diceNum;
}

void Hex::assignResources()
{
	for (auto owner : settlementOwners)
	{
		if (owner != NULL)
		{
			(static_cast<Player*>(owner))->addResource(resource);		// 1 resource per Settlement.
		}
	}
	for (auto owner : cityOwners)
	{
		if (owner != NULL)
		{
			(static_cast<Player*>(owner))->addResource(resource, 2);		// 2 per City.
		}
	}
}

ResourceType Hex::giveResource()
{
	return resource;
}

void Hex::init()
{
	settlementOwners.fill(nullptr);
	cityOwners.fill(nullptr);
	roadOwners.fill(nullptr);
}
