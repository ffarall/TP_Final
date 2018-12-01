#include "LocalPlayerEnabler.h"
#include "SubEvents.h"
#include "MainEvent.h"
#include "NewEventHandling.h"

#define TX(x) (static_cast<void (Enabler::* )(SubtypeEvent *)>(&LocalPlayerEnabler::x))

LocalPlayerEnabler::LocalPlayerEnabler()
{
	init();
}

LocalPlayerEnabler::LocalPlayerEnabler(Networking * pkgSender_, PlayerEnabler* remoteEnabler_)
{
	init();
	setPkgSender(pkgSender_);
	setRemoteEnabler(remoteEnabler_);
}


LocalPlayerEnabler::~LocalPlayerEnabler()
{
}

void LocalPlayerEnabler::setRemoteEnabler(PlayerEnabler * remoteEnabler_)
{
	remoteEnabler = remoteEnabler_;
}

void LocalPlayerEnabler::init()
{
	setDefaultRoutine(TX(noAct));
	localPlayer = nullptr;
	remotePlayer = nullptr;
	board = nullptr;
	pkgSender = nullptr;
	remoteEnabler = nullptr;
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

void LocalPlayerEnabler::localStarts(string nameLocal, string nameRemote)
{
	remoteEnabler->setLocalPlayer(localPlayer = new Player(nameLocal));					// Sets both localPlayer for local enabler and remote enabler.
	remoteEnabler->setRemotePlayer(remotePlayer = new Player(nameRemote));				// Same for remotePlayer.
	remoteEnabler->setBoard(board = new Board);											// Same for board.
	setWaitingMessage(string("Listo para empezar, jugador ") + localPlayer->getName() + " seleccione donde colocar su primer SETTLEMENT.");

	disableAll();
	enable(PLA_SETTLEMENT, { TX(firstSettlement) });
	setDefaultRoutine(TX(genericDefault));
}

void LocalPlayerEnabler::noAct(SubtypeEvent * ev)
{
}

void LocalPlayerEnabler::firstSettlement(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new SettlementPkg(*pkg));
	
	addSettlementToLocal(position);

	disable(PLA_SETTLEMENT);
	enable(PLA_ROAD, { TX(firstRoad) });

	notifyAllObservers();
}

void LocalPlayerEnabler::firstRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new RoadPkg(*pkg));
	
	addRoadToLocal(position);

	disable(PLA_ROAD);
	enable(PLA_SETTLEMENT, { TX(secondSettlement) });				// Leaving everything ready for next turn.

	emitEvent(TURN_FINISHED);										// Emitting event that turn is finished.

	notifyAllObservers();
}

void LocalPlayerEnabler::secondSettlement(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new SettlementPkg(*pkg));

	addSettlementToLocal(position);

	disable(PLA_SETTLEMENT);
	enable(PLA_ROAD, { TX(secondRoad) });
}

void LocalPlayerEnabler::secondRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new RoadPkg(*pkg));

	addRoadToLocal(position);
	getResourceFromSettlement(position, localPlayer);

	disable(PLA_ROAD);
	setUpForTurn();

	notifyAllObservers();
}

void LocalPlayerEnabler::checkDices(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	DicePkg* pkg = static_cast<DicePkg*>(auxEv->getPackage());

	pkgSender->pushPackage(new DicePkg(*pkg));

	int rolled = pkg->getValue(false);
	rolled += pkg->getValue(true);

	board->assignResourcesForNum(rolled);
	
	disable(PLA_DICES_ARE);
	if (rolled == 7)
	{
		if (remotePlayer->totalResourcesAmount() >= 7)
		{
			enable(NET_ROBBER_CARDS, { TX(remoteSendsRobberCards), TX(checkLocalResources) });
		}
		else
		{
			enable(NET_ACK, { TX(checkLocalResources) });
		}
	}
	else
	{
		enable(NET_ACK, { TX(enablePlayerActions) });
	}

	notifyAllObservers();
}

void LocalPlayerEnabler::remoteSendsRobberCards(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = static_cast<RobberCardsPkg*>(auxEv->getPackage());

	for (auto res : pkg->getCards())
	{
		remotePlayer->useResource(res, 1);										// For every card, a resource is eliminated.
	}
}

void LocalPlayerEnabler::checkLocalResources(SubtypeEvent * ev)
{
	if (localPlayer->totalResourcesAmount() >= 7)					// If local has 7 or more resources...
	{
		disableAll();
		enable(PLA_ROBBER_CARDS, { TX(discardLocalResources) });
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ACK));

		disableAll();
		enable(PLA_ROBBER_MOVE, { TX(moveRobber) });
	}

	notifyAllObservers();
}

void LocalPlayerEnabler::enablePlayerActions(SubtypeEvent * ev)
{
	disableAll();
	checkDevCards();
	enable(PLA_OFFER_TRADE, { TX(checkOffer) });
	enable(PLA_SETTLEMENT, { TX(checkSettlement) });
	enable(PLA_ROAD, { TX(checkRoad) });
	enable(PLA_CITY, { TX(checkCity) });
	enable(PLA_BANK_TRADE, { TX(checkBankTrade) });
	enable(PLA_DEV_CARD, { TX(drawDevCard) });
	enable(PLA_PASS, { TX(checkOffer) });
}

void LocalPlayerEnabler::discardLocalResources(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = static_cast<RobberCardsPkg*>(auxEv->getPackage());

	for (auto res : pkg->getCards())
	{
		localPlayer->useResource(res, 1);										// For every card, a resource is eliminated.
	}

	pkgSender->pushPackage(new RobberCardsPkg(*pkg));

	disableAll();
	enable(PLA_ROBBER_MOVE, { TX(moveRobber) });

	notifyAllObservers();
}

void LocalPlayerEnabler::moveRobber(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberMovePkg* pkg = static_cast<RobberMovePkg*>(auxEv->getPackage());

	board->moveRobber(pkg->getPos());

	disableAll();
	enable(NET_ACK, { TX(enablePlayerActions) });

	notifyAllObservers();
}

void LocalPlayerEnabler::genericDefault(SubtypeEvent * ev)
{
	unsigned int type = ev->getType();
	unsigned int subtype = ev->getSubtype();
	setErrMessage(string("Se recibió un evento de tipo ") + to_string(type) + " y subtipo " + to_string(subtype) + " , el cual no está habilitado.");
}

void LocalPlayerEnabler::emitEvent(EventTypes type)
{
	GenericEvent* ev = new MainEvents(type);
	handler->enqueueEvent(ev);
}

void LocalPlayerEnabler::emitSubEvent(EventTypes type, EventSubtypes subtype, package * pkg)
{
	GenericEvent* ev = new SubEvents(type, subtype, pkg);
	handler->enqueueEvent(ev);
}

void LocalPlayerEnabler::getResourceFromSettlement(string position, Player* who)
{
	for (char c : position)
	{
		if (isalpha(c))												// If it's a Hex.
		{
			ResourceType resType = board->getResourceFromHex(c);
			who->addResource(resType, 1);							// Adds 1 resource because it's a Settlement.
		}
	}
}

void LocalPlayerEnabler::addSettlementToLocal(string position)
{
	if (localPlayer->checkSettlementAvailability(position))
	{
		localPlayer->addToMySettlements(position);
		remotePlayer->addToRivalsSettlements(position);
	}
	else
	{
		setErrMessage("La posición donde se quiere colocar el Settlement es inválida.");
		return;
	}

	if (!board->addSettlementToTokens(position, localPlayer))
	{
		setErrMessage("El casillero del tablero donde se quiere agregar el Settlement está lleno.");
		return;
	}
}

void LocalPlayerEnabler::addRoadToLocal(string position)
{
	if (localPlayer->checkRoadAvailability(position))
	{
		localPlayer->addToMyRoads(position);
		remotePlayer->addToRivalsRoads(position);
	}
	else
	{
		setErrMessage("La posición donde se quiere colocar el Road es inválida.");
		return;
	}

	if (!board->addRoadToTokens(position, localPlayer))
	{
		setErrMessage("El casillero del tablero donde se quiere agregar el Road está lleno.");
		return;
	}
}

void LocalPlayerEnabler::setUpForTurn()
{
	disableAll();
	enable(PLA_DICES_ARE, { TX(checkDices) });
}
