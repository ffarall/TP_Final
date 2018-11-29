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
	setDefaultRoutine(TX(noAct));
	localPlayer = nullptr;
	remotePlayer = nullptr;
	board = nullptr;
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
	if (board != nullptr)
	{
		delete board;
	}
}

void LocalPlayerEnabler::localStarts()
{
	setLocalPlayer(localPlayer = new Player);					// Sets both localPlayer for local enabler and remote enabler.
	setRemotePlayer(remotePlayer = new Player);					// Same for remotePlayer.
	setBoard(board = new Board);								// Same for board.
	setWaitingMessage(string("Listo para empezar, jugador ") + localPlayer->getName() + " seleccione donde colocar su primer SETTLEMENT.");

	enable(PLA_SETTLEMENT, { TX(firstSettlement) });
	setDefaultRoutine(TX(genericDefault));
}

void LocalPlayerEnabler::noAct(SubtypeEvent * ev)
{
}

void LocalPlayerEnabler::firstSettlement(SubtypeEvent * ev)
{

}

void LocalPlayerEnabler::genericDefault(SubtypeEvent * ev)
{
	unsigned int type = ev->getType();
	unsigned int subtype = ev->getSubtype();
	setErrMessage(string("Se recibió un evento de tipo ") + to_string(type) + " y subtipo " + to_string(subtype) + " , el cual no está habilitado.");
}
