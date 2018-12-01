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

	void setResource(ResourceType resource_);
	void setDiceNum(int diceNum_);

	// Gives a resource to each of the Settlement and City owners.
	void assignResources();

protected:
	// Resource corresponding to this Hex.
	ResourceType resource;
	// This Hex assigns resources when this number is rolled.
	int diceNum;

	void init();
};

