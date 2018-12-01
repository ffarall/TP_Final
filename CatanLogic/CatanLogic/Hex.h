#pragma once
#include "Token.h"

using namespace std;

class Hex :
	public Token
{
public:
	Hex();
	Hex(ResourceType resource_, int diceNum_); 
	virtual ~Hex();

	virtual string whatAmI();

	void setResource(ResourceType resource_);
	void setDiceNum(int diceNum_);

	int getDiceNum();

	// Gives a resource to each of the Settlement and City owners.
	void assignResources();
	// When Settlement adjacent to this Hex's coordinate asks for resources (to be used for first resources).
	ResourceType giveResource();

protected:
	// Resource corresponding to this Hex.
	ResourceType resource;
	// This Hex assigns resources when this number is rolled.
	int diceNum;

	void init();
};

