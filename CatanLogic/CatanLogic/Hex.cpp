#include "Hex.h"



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

void Hex::setResource(ResourceType resource_)
{
	resource = resource_;
}

void Hex::setDiceNum(int diceNum_)
{
	diceNum = diceNum_;
}

void Hex::assignResources()
{
	for (auto owner : settlementOwners)
	{

	}
}

void Hex::init()
{
	settlementOwners.fill(nullptr);
	cityOwners.fill(nullptr);
	roadOwners.fill(nullptr);
}
