#include "Sea.h"



Sea::Sea()
{
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
