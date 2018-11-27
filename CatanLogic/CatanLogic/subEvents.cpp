#include "subEvents.h"

subEvents::subEvents(mainTypes ppal, subType secnd):genericEvent(ppal)
{
	subTipo = secnd;
	paquete = nullptr;
}

subEvents::~subEvents()
{
}

void subEvents::addPackage(package * newPaket)
{
	if (paquete != nullptr)
	{
		delete paquete; // por las dudas
	}
	paquete = newPaket;
}
