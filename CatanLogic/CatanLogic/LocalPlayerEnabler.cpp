#include "LocalPlayerEnabler.h"

#define TX(x) (static_cast<void (Enabler::* )(SubtypeEvent *)>(&LocalPlayerEnabler::x))

LocalPlayerEnabler::LocalPlayerEnabler()
{
	iWon = false;
	setDefaultRoutine(TX(noAct));
}


LocalPlayerEnabler::~LocalPlayerEnabler()
{
}

void LocalPlayerEnabler::setUpForGame()
{

}

void LocalPlayerEnabler::noAct(SubtypeEvent * ev)
{
}
