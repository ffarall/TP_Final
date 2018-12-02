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

bool RemotePlayerEnabler::deleteCards(vector<ResourceType> descarte, Player * player_)
{
	for (auto carta : descarte)
	{
		if (!player_->useResource(carta, 1)) // si no tiene el recurso error
		{
			return false;
		}
	}
	return true;
}

void RemotePlayerEnabler::enableRemoteActions()
{
	disableAllBut({});
	enable(NET_OFFER_TRADE, {TX(evaluateOffer)});
	enable(NET_SETTLEMENT, {TX(checkRemoteSettlement)});
	enable(NET_CITY, {TX(checkRemoteCity)});
	enable(NET_ROAD, {TX(checkRemoteRoad)});
	enable(NET_BANK_TRADE, {TX(checkRemoteBankTrade)});
	enable(NET_DEV_CARDS, {TX(checkDevCards)});
	enable(NET_PASS, {TX(endTurn)});
}

void RemotePlayerEnabler::checkRemoteDevCards()
{
	if (remotePlayer->getDevCardAmount(DevCards::KNIGHT))
	{
		enable(NET_KNIGHT,{TX(remUsedKnight)});
	}
	if (remotePlayer->getDevCardAmount(DevCards::MONOPOLY))
	{
		enable(NET_MONOPOLY, { TX(remUsedMonopoly) });
	}
	if (remotePlayer->getDevCardAmount(DevCards::YEARS_OF_PLENTY))
	{
		enable(NET_YEARS_OF_PLENTY, { TX(remUsedYoP) });
	}
	if (remotePlayer->getDevCardAmount(DevCards::ROAD_CONSTRUCTION))
	{
		enable(NET_ROAD_BUILDING, { TX(remUsedRoadBuilding) });
	}
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
	board->addSettlementToTokens(position, remotePlayer);

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
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	DicePkg* pkg = static_cast<DicePkg*>(auxEv->getPackage());

	int rolled = pkg->getValue(false);
	rolled += pkg->getValue(true);

	board->assignResourcesForNum(rolled);

	disable(NET_DICES_ARE);
	
	if (rolled == 7)
	{
		if (localPlayer->totalResourcesAmount() >= 7)
		{
			enable(PLA_ROBBER_CARDS, { TX(SendsRobberCards) });
		}
		else
		{
			pkgSender->pushPackage(new package(headers::ACK));
			if (remotePlayer->totalResourcesAmount() >= 7)
			{
				enable(NET_ROBBER_CARDS, {TX(remoteLoseCards)});
			}
			else
			{
				enable(NET_ROBBER_MOVE, { TX(remoteMoveRobber) , TX(checkRemoteDevCards() ) });
			}
		}
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ACK));
		checkRemoteDevCards();
		enableRemoteActions();
	}
}

void RemotePlayerEnabler::SendsRobberCards(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = new RobberCardsPkg(*static_cast<RobberCardsPkg*>(auxEv->getPackage()));

	if (!deleteCards(pkg->getCards(),localPlayer)) // si no puedo eliminar todas las cartas
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
	}
	else
	{
		pkgSender->pushPackage(pkg); // si uedo eliminarlas envio el paquete
		disable(PLA_ROBBER_CARDS); // deshabilito este evento

		if (remotePlayer->totalResourcesAmount() >= 7) // si el otro tiene mas de 7 habilito la espera de esas cartas
		{
			enable(NET_ROBBER_CARDS, { TX(remoteLoseCards) });
		}
		else
		{
			enable(NET_ROBBER_MOVE, { TX(remoteMoveRobber) });
		}
	}
}

void RemotePlayerEnabler::remoteLoseCards(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = static_cast<RobberCardsPkg*>(auxEv->getPackage()) ;

	if(!deleteCards(pkg->getCards(), remotePlayer)) // si no puedo eliminar todas las cartas
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ACK));
		disable(NET_ROBBER_CARDS);
		enable(NET_ROBBER_MOVE, { TX(remoteMoveRobber) });
	}
}

void RemotePlayerEnabler::remoteMoveRobber(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberMovePkg* pkg =new  RobberMovePkg(*static_cast<RobberMovePkg*>(auxEv->getPackage()));

	board->moveRobber(pkg->getPos());
	pkgSender->pushPackage(new package(headers::ACK));

	disable(NET_ROBBER_MOVE);
	enableRemoteActions();

}

void RemotePlayerEnabler::evaluateOffer(SubtypeEvent * ev)
{
	disableAllBut({ NET_KNIGHT,NET_YEARS_OF_PLENTY,NET_MONOPOLY,NET_ROAD_BUILDING });
	setErrMessage("");
	setWaitingMessage("");

	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	OfferTradePkg* pkg = static_cast<OfferTradePkg*>(auxEv->getPackage());

	if (validateOffer(pkg))
	{
		pendingOffer = *pkg;													// Saving offer for response.

		enable(NET_YES, { TX(exchangeResources), TX(enableRemoteActions) });
		enable(NET_NO, { TX(enableRemoteActions) });
	}
	else
	{
		setErrMessage("La oferta de trade ingresada es inválida. La misma debe constar de entre 1 y 9 recursos ofrecidos, y entre 1 y 9 pedidos.");
	}
}

void RemotePlayerEnabler::checkRemoteSettlement(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkSettlementAvailability(position))
	{
		remotePlayer->addToMySettlements(position);
		localPlayer->addToRivalsSettlements(position);
		board->addSettlementToTokens(position, remotePlayer);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		emitEvent(ERR_IN_COM);
		setErrMessage("La coordenada donde se quiso ubicar el nuevo Settlement no está disponible.");
	}
}

void RemotePlayerEnabler::checkRemoteRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkRoadAvailability(position))
	{
		remotePlayer->addToMyRoads(position);
		localPlayer->addToRivalsRoads(position);
		board->addRoadToTokens(position, remotePlayer);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		emitEvent(ERR_IN_COM);
		pkgSender->pushPackage(new package(headers::ERROR_));
		setErrMessage("La coordenada donde se quiso ubicar el nuevo Road no está disponible.");
	}
}

void RemotePlayerEnabler::checkRemoteCity(SubtypeEvent * ev)
{
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	CityPkg* pkg = static_cast<CityPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkPromotionOfCity(position))
	{
		remotePlayer->promoteToMyCity(position);
		localPlayer->promoteToRivalsCity(position);
		board->addCityToTokens(position, remotePlayer);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("La coordenada donde se quiso promover la nueva City no es aceptada.");
	}
}

void RemotePlayerEnabler::checkRemoteBankTrade(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	BanckTradePkg* pkg = static_cast<BanckTradePkg*>(auxEv->getPackage());
	
	bool isOK = true;
	for (ResourceType a : pkg->getResoucesPaid())
	{
		if (!(remotePlayer->useResource(a, 1)))
		{
			isOK = false;
		}
	}

	if (isOK)
	{
		remotePlayer->addResource(pkg->getResouceBougth(),1);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		emitEvent(ERR_IN_COM);
		pkgSender->pushPackage(new package(headers::ERROR_));
	}
}

void RemotePlayerEnabler::checkDevCards(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");

	if (remotePlayer->checkResourcesForDevCard())
	{
		remotePlayer->getNewDevCard(board);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
	}
}

void RemotePlayerEnabler::endTurn(SubtypeEvent * ev)
{
	disableAll();
	enable(NET_DICES_ARE, { TX(checkDices) });
	emitEvent(TURN_FINISHED);
}

void RemotePlayerEnabler::enableRemoteActions(SubtypeEvent * ev)
{
	disableAllBut({ NET_KNIGHT,NET_YEARS_OF_PLENTY,NET_MONOPOLY,NET_ROAD_BUILDING }); 
	enable(NET_OFFER_TRADE, { TX(evaluateOffer) });
	enable(NET_SETTLEMENT, { TX(checkRemoteSettlement) });
	enable(NET_CITY, { TX(checkRemoteCity) });
	enable(NET_ROAD, { TX(checkRemoteRoad) });
	enable(NET_BANK_TRADE, { TX(checkRemoteBankTrade) });
	enable(NET_DEV_CARDS, { TX(checkDevCards) });
	enable(NET_PASS, { TX(endTurn) });
}

void RemotePlayerEnabler::exchangeResources(SubtypeEvent * ev)
{
	for (auto resource : pendingOffer.getMyOnes())
	{
		localPlayer->addResource(resource, 1);					// Adding the resources coming from opponent.
		remotePlayer->useResource(resource, 1);
	}
	for (auto resource : pendingOffer.getOpponentOnes())
	{
		remotePlayer->addResource(resource, 1);					// Giving resources to opponent.
		localPlayer->useResource(resource, 1);
	}
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
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("La posición donde se quiere colocar el Road es inválida.");
		return;
	}

	if (!board->addRoadToTokens(position, remotePlayer))
	{
		setErrMessage("El casillero del tablero donde se quiere agregar el Road está lleno.");
		return;
	}
}
