#include "LocalPlayerEnabler.h"
#include "SubEvents.h"

#define TX(x) (static_cast<void (Enabler::* )(SubtypeEvent *)>(&LocalPlayerEnabler::x))

LocalPlayerEnabler::LocalPlayerEnabler()
{
	init();
}


LocalPlayerEnabler::~LocalPlayerEnabler()
{
}

void LocalPlayerEnabler::init()
{
	iWon = false;
	setDefaultRoutine(TX(noAct));
	localPlayer = nullptr;
	remotePlayer = nullptr;
}

void LocalPlayerEnabler::end()
{
	if (localPlayer != nullptr)
	{
		delete localPlayer;
	}
	if (remotePlayer != nullptr)
	{
		delete remotePlayer;
	}
}

void LocalPlayerEnabler::localStarts()
{
	localPlayer = new Player;
	enable(PLA_SETTLEMENT, { TX(firstSettlement) });
}

void LocalPlayerEnabler::noAct(SubtypeEvent * ev)
{
}
