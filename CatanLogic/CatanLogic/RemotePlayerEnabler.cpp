#include "RemotePlayerEnabler.h"
#include "SubEvents.h"
#include "MainEvent.h"
#include "NewEventHandling.h"


#define TX(x) (static_cast<void (Enabler::* )(SubtypeEvent *)>(&RemotePlayerEnabler::x))

RemotePlayerEnabler::RemotePlayerEnabler()
{
}

RemotePlayerEnabler::RemotePlayerEnabler(Networking * pkgSender_, PlayerEnabler* localEnabler_)
{
	init();
	setPkgSender(pkgSender_);
	setLocalEnabler(localEnabler_);
}


RemotePlayerEnabler::~RemotePlayerEnabler()
{
}

void RemotePlayerEnabler::localStarts()
{
	setWaitingMessage(string("Listo para empezar, jugador ") + localPlayer->getName() + " seleccione donde colocar su primer SETTLEMENT.");

	enable(NET_SETTLEMENT, { TX(firstSettlement) });
	setDefaultRoutine(TX(genericDefault));
}

void RemotePlayerEnabler::remoteStarts()
{
}

void RemotePlayerEnabler::setUpForTurn()
{
	disableAll();
	enable(NET_DICES_ARE, { TX(checkDices) });
}

void RemotePlayerEnabler::setLocalEnabler(PlayerEnabler * localEnabler_)
{
	localEnabler = localEnabler_;
}

void RemotePlayerEnabler::init()
{
	setDefaultRoutine(TX(noAct));
	localPlayer = nullptr;
	remotePlayer = nullptr;
	board = nullptr;
	pkgSender = nullptr;
	localEnabler = nullptr;
}

void RemotePlayerEnabler::end()
{
}

void RemotePlayerEnabler::noAct(SubtypeEvent * ev)
{
}

void RemotePlayerEnabler::firstSettlement(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	addSettlementToRemote(position);

	disable(NET_SETTLEMENT);
	enable(NET_ROAD, { TX(firstRoad) });
}

void RemotePlayerEnabler::firstRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	addRoadToRemote(position);

	disable(NET_ROAD);
	enable(NET_SETTLEMENT, { TX(secondSettlement) });				// Leaving everything ready for next turn.
}

void RemotePlayerEnabler::secondSettlement(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	addSettlementToRemote(position);

	disable(NET_SETTLEMENT);
	enable(NET_ROAD, { TX(secondRoad) });
}

void RemotePlayerEnabler::secondRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	addRoadToRemote(position);

	disable(NET_ROAD);
	setUpForTurn();
	emitEvent(TURN_FINISHED);
}

void RemotePlayerEnabler::checkDices(SubtypeEvent * ev)
{
	
}

void RemotePlayerEnabler::genericDefault(SubtypeEvent * ev)
{
}

void RemotePlayerEnabler::emitEvent(EventTypes type)
{
	GenericEvent* ev = new MainEvents(type);
	handler->enqueueEvent(ev);
}

void RemotePlayerEnabler::emitSubEvent(EventTypes type, EventSubtypes subtype, package * pkg)
{
	GenericEvent* ev = new SubEvents(type, subtype, pkg);
	handler->enqueueEvent(ev);
}

void RemotePlayerEnabler::addSettlementToRemote(string position)
{
	if (remotePlayer->checkSettlementAvailability(position))
	{
		remotePlayer->addToMySettlements(position);
		localPlayer->addToRivalsSettlements(position);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("La posición donde se quiere colocar el Settlement es inválida.");
		return;
	}

	if (!board->addSettlementToTokens(position, remotePlayer))
	{
		setErrMessage("El casillero del tablero donde se quiere agregar el Settlement está lleno.");
		return;
	}
}

void RemotePlayerEnabler::addRoadToRemote(string position)
{
	if (remotePlayer->checkRoadAvailability(position))
	{
		remotePlayer->addToMyRoads(position);
		localPlayer->addToRivalsRoads(position);
	}
	else
	{
		setErrMessage("La posición donde se quiere colocar el Road es inválida.");
		return;
	}

	if (!board->addRoadToTokens(position, remotePlayer))
	{
		setErrMessage("El casillero del tablero donde se quiere agregar el Road está lleno.");
		return;
	}
}
