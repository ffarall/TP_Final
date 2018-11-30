#pragma once
#include "Token.h"
class Hex :
	public Token
{
public:
	Hex(ResourceType resource_);
	virtual ~Hex();
	void setResource(ResourceType resource_);

	// Gives a resource to each of the Settlement and City owners.


protected:
	ResourceType resource;
};

