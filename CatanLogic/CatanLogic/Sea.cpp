#include "Sea.h"



Sea::Sea()
{
	settlementOwners.fill(nullptr);
	cityOwners.fill(nullptr);
	roadOwners.fill(nullptr);
}


Sea::~Sea()
{
}

void Sea::setPortType(PortType type_)
{
	port = type_;
}

PortType Sea::getPortType()
{
	return port;
}

string Sea::whatAmI()
{
	return "Sea";
}
