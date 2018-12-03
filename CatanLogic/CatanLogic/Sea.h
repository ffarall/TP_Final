#pragma once
#include "Token.h"
#include "CatanDefs.h"

class Sea :
	public Token
{
public:
	Sea();
	virtual ~Sea();

	void setPortType(PortType type_);
	PortType getPortType();

	virtual string whatAmI();
private:
	// Port corresponding to this Sea.
	PortType port;
};

