#include "Hex.h"



Hex::Hex(ResourceType resource_)
{
	settlementOwners.fill(nullptr);
	cityOwners.fill(nullptr);
	roadOwners.fill(nullptr);
	setResource(resource_);
}


Hex::~Hex()
{
}

void Hex::setResource(ResourceType resource_)
{
	resource = resource_;
}
