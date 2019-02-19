#include "RemotePlayerEnabler.h"
#include "SubEvents.h"
#include "MainEvent.h"
#include "NewEventHandling.h"
#include <random>

#define TX(x) (static_cast<void (Enabler::* )(SubtypeEvent *)>(&RemotePlayerEnabler::x))

RemotePlayerEnabler::RemotePlayerEnabler()
{
}

RemotePlayerEnabler::RemotePlayerEnabler(Networking * pkgSender_,EventsHandler * handler_)
{
	init();
	setPkgSender(pkgSender_);
	setHandler(handler_);
}


RemotePlayerEnabler::~RemotePlayerEnabler()
{
}

void RemotePlayerEnabler::localStarts()
{
	setWaitingMessage(string("Listo para empezar, jugador ") + localPlayer->getName() + " seleccione donde colocar su primer SETTLEMENT.");

	disableAll();
	enable(NET_SETTLEMENT, { TX(firstSettlementLocalStarts) });
	setDefaultRoutine(TX(genericDefault));
}

void RemotePlayerEnabler::remoteStarts()
{
	string mensaje = "Listo para empezar, el jugador ";
	mensaje += remotePlayer->getName();
	mensaje += " debe colocar su primer SETTLEMENT.";
	setWaitingMessage( mensaje );

	disableAll();
	enable(NET_SETTLEMENT, { TX(firstSettlementRemoteStarts) });
	setDefaultRoutine(TX(genericDefault));

}

void RemotePlayerEnabler::setUpForTurn(SubtypeEvent* ev)
{
	disableAll();
	enable(NET_DICES_ARE, { TX(checkDices) });
}

bool RemotePlayerEnabler::deleteCards(vector<ResourceType> descarte, Player * player_)
{
	for (auto carta : descarte)
	{
		if (!player_->useResource(carta)) // si no tiene el recurso error
		{
			return false;
		}
	}
	return true;
}

void RemotePlayerEnabler::enableRemoteActions()
{
	disableAllBut({NET_YEARS_OF_PLENTY,NET_ROAD_BUILDING,NET_MONOPOLY,NET_KNIGHT});
	enable(NET_OFFER_TRADE, {TX(evaluateOffer)});
	enable(NET_SETTLEMENT, {TX(checkRemoteSettlement)});
	enable(NET_CITY, {TX(checkRemoteCity)});
	enable(NET_ROAD, {TX(checkRemoteRoad)});
	enable(NET_BANK_TRADE, {TX(checkRemoteBankTrade)});
	enable(NET_DEV_CARDS, {TX(checkDevCards)});
	enable(NET_PASS, {TX(endTurn)});
}

bool RemotePlayerEnabler::checkResourcesToGiveBackAndRespond(OfferTradePkg* pkg)
{
	vector< ResourceType > resourcesToGiveBack = pkg->getOpponentOnes();
	size_t lumberAmount = localPlayer->getResourceAmount(BOSQUE);
	size_t brickAmount = localPlayer->getResourceAmount(COLINAS);
	size_t oreAmount = localPlayer->getResourceAmount(MONTAÑAS);
	size_t grainAmount = localPlayer->getResourceAmount(CAMPOS);
	size_t woolAmount = localPlayer->getResourceAmount(PASTOS);

	for (ResourceType resource : resourcesToGiveBack)
	{
		switch (resource)
		{
		case BOSQUE:
		{
			if (!lumberAmount)
			{
				respondImposibleOfferTrade();
				return false;
			}
			lumberAmount--;
		}
			break;
		case COLINAS:
		{
			if (!brickAmount)
			{
				respondImposibleOfferTrade();
				return false;
			}
			brickAmount--;
		}
			break;
		case MONTAÑAS:
		{
			if (!oreAmount)
			{
				respondImposibleOfferTrade();
				return false;
			}
			oreAmount--;
		}
			break;
		case CAMPOS:
		{
			if (!grainAmount)
			{
				respondImposibleOfferTrade();
				return false;
			}
			grainAmount--;
		}
			break;
		case PASTOS:
		{
			if (!woolAmount)
			{
				respondImposibleOfferTrade();
				return false;
			}
			woolAmount--;
		}
			break;
		case DESIERTO:
			break;
		default:
			break;
		}
	}
	return true;
}

void RemotePlayerEnabler::respondImposibleOfferTrade()
{
	setWaitingMessage(getWaitingMessage() + " No se cuenta con tales recursos, seleccione Cancelar.");
	disableAll();
	enable(PLA_NO, { TX(rejectOffer), TX(enableRemoteActions) });
}

void RemotePlayerEnabler::checkLongestRoad()
{
	if (remotePlayer->getLongestRoad() >= 5)											// Minimum requisite for having the longestRoadCard
	{
		if (localPlayer->hasLongestRoad())											// If remote has it...
		{
			if (remotePlayer->getLongestRoad() > localPlayer->getLongestRoad())		// Must check who has it longer.
			{
				remotePlayer->setLongestRoadCard(true);
				localPlayer->setLongestRoadCard(false);
			}
		}
		else
		{
			remotePlayer->setLongestRoadCard(true);
		}
	}
}

void RemotePlayerEnabler::checkRemoteDevCards(SubtypeEvent * ev)
{
	if (playingWithDev)
	{
		if (remotePlayer->getDevCardAmount(DevCards::KNIGHT))
		{
			enable(NET_KNIGHT, { TX(remUsedKnight) });
		}
		else
		{
			disable(NET_KNIGHT);
		}

		if (remotePlayer->getDevCardAmount(DevCards::MONOPOLY))
		{
			enable(NET_MONOPOLY, { TX(remUsedMonopoly) });
		}
		else
		{
			disable(NET_MONOPOLY);
		}

		if (remotePlayer->getDevCardAmount(DevCards::YEARS_OF_PLENTY))
		{
			enable(NET_YEARS_OF_PLENTY, { TX(remUsedYoP) });
		}
		else
		{
			disable(NET_YEARS_OF_PLENTY);
		}

		if (remotePlayer->getDevCardAmount(DevCards::ROAD_BUILDING))
		{
			enable(NET_ROAD_BUILDING, { TX(remUsedRoadBuilding) });
		}
		else
		{
			disable(NET_ROAD_BUILDING);
		}

		if (remotePlayer->isThereDevCard(VICTORY_POINTS))
		{
			remotePlayer->useDevCard(VICTORY_POINTS);
			if (remotePlayer->hasWon(playingWithDev))
				enable(NET_I_WON, { TX(finDelJuego) });
		}
	}
}

void RemotePlayerEnabler::road1(SubtypeEvent * ev)
{
	setErrMessage("");
	
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();
	setWaitingMessage("El jugador coloco su primer road");

	if (remotePlayer->checkRoadAvailability(position))
	{
		addRoadToRemote(position);
		disable(NET_ROAD);
		enable(NET_ROAD, { TX(road2) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rivala intenteto poner un road en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::road2(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("El jugador coloco su segundo road");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkRoadAvailability(position))
	{
		addRoadToRemote(position);
		disable(NET_ROAD);
		enableRemoteActions();
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rivala intenteto poner un road en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::finDelJuego(SubtypeEvent * ev)
{
	disableAll();
	emitEvent(I_WON);
}

void RemotePlayerEnabler::firstTurn(SubtypeEvent * ev)
{
	setUpForTurn();
	emitEvent(TURN_FINISHED);
}

void RemotePlayerEnabler::init()
{
	setDefaultRoutine(TX(noAct));
	localPlayer = nullptr;
	remotePlayer = nullptr;
	board = nullptr;
	pkgSender = nullptr;
	
}

void RemotePlayerEnabler::end()
{
}

void RemotePlayerEnabler::noAct(SubtypeEvent * ev)
{
}

void RemotePlayerEnabler::firstSettlementLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su primer Settlement");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkSettlementAvailability(position))
	{
		addSettlementToRemote(position);
		disable(NET_SETTLEMENT);
		enable(NET_ROAD, { TX(firstRoadLocalStarts) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su primer Settlement en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::firstSettlementRemoteStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkSettlementAvailability(position))
	{
		addSettlementToRemote(position);
		disable(NET_SETTLEMENT);
		enable(NET_ROAD, { TX(firstRoadRemoteStarts) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su segundo Settlement en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::firstRoadRemoteStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su primer Settlement");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkRoadAvailability(position))
	{
		addRoadToRemote(position);
		disable(NET_ROAD);
		enable(NET_PASS, { TX(primeraParte) });
	}
	else
	{
  		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su segundo Road en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::firstRoadLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su primer Road");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	
	if (remotePlayer->checkRoadAvailability(position))
	{
		addRoadToRemote(position);
		disable(NET_ROAD);
		enable(NET_SETTLEMENT, { TX(secondSettlementLocalStarts) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su primer road en una posicion incorrecta");
	}

}

void RemotePlayerEnabler::primeraParte(SubtypeEvent * ev)
{
	disable(NET_PASS);
	emitEvent(TURN_FINISHED);
	enable(NET_SETTLEMENT, { TX(secondSettlementRemoteStarts) });				// Leaving everything ready for next turn.
}

void RemotePlayerEnabler::secondSettlementLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su segundo Settlement");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkSettlementAvailability(position))
	{
		addSettlementToRemote(position);
		disable(NET_SETTLEMENT);
		enable(NET_ROAD, { TX(secondRoadLocalStarts) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su segundo Settlement en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::secondRoadLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su segundo road");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if(remotePlayer->checkRoadAvailability(position))
	{
		addRoadToRemote(position);
		getResourceFromSettlement(remotePlayer->getLastSettlement(), remotePlayer);
		disable(NET_ROAD);
		enable(NET_PASS, { TX(firstTurn) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su segundo Road en una posicion incorrecta");
	}
	
}

void RemotePlayerEnabler::secondSettlementRemoteStarts(SubtypeEvent* ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su segundo Settlement");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkSettlementAvailability(position))
	{
		addSettlementToRemote(position);
		disable(NET_SETTLEMENT);
		enable(NET_ROAD, { TX(secondRoadRemoteStarts) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su segundo Settlement en una posicion incorrecta");
	}
}

void RemotePlayerEnabler::secondRoadRemoteStarts(SubtypeEvent* ev)
{
	setErrMessage("");
	setWaitingMessage("El oponente coloco su segundo Road");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkRoadAvailability(position))
	{
		addRoadToRemote(position);
		getResourceFromSettlement(remotePlayer->getLastSettlement(), remotePlayer);
		disable(NET_ROAD);
		enable(NET_DICES_ARE, { TX(checkDices) });
	}
	else
	{
		disableAll();
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("El rival intenteto poner su segundo Road en una posicion incorrecta");
	}
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
			setWaitingMessage("El oponente tiro 7, hay que eliminar cartas");
			enable(PLA_ROBBER_CARDS, { TX(SendsRobberCards) });
		}
		else
		{

			pkgSender->pushPackage(new package(headers::ACK));
			if (remotePlayer->totalResourcesAmount() >= 7)
			{
				setWaitingMessage("El oponente tiro 7, debe descartar cartas");
				enable(NET_ROBBER_CARDS, {TX(remoteLoseCards)});
			}
			else
			{
				setWaitingMessage("El oponente tiro 7 y essta moviendo el robber");
				enable(NET_ROBBER_MOVE, { TX(remoteMoveRobber) , TX(checkRemoteDevCards) });
			}
		}
	}
	else
	{
		setWaitingMessage("El oponente tiro " + to_string(rolled));
		pkgSender->pushPackage(new package(headers::ACK));
		checkRemoteDevCards(ev);
		enableRemoteActions();
	}
}

void RemotePlayerEnabler::SendsRobberCards(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("Descartando cartas");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = new RobberCardsPkg(*static_cast<RobberCardsPkg*>(auxEv->getPackage()));

	if (!deleteCards(pkg->getCards(),localPlayer)) // si no puedo eliminar todas las cartas
	{
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
		setErrMessage("Error al eliminar las cartas al mover el robber");
	}
	else
	{
		pkgSender->pushPackage(pkg); // si uedo eliminarlas envio el paquete
		disable(PLA_ROBBER_CARDS); // deshabilito este evento

		if (remotePlayer->totalResourcesAmount() >= 7) // si el otro tiene mas de 7 habilito la espera de esas cartas
		{
			setWaitingMessage("El oponente tiro 7, debe descartar cartas");
			enable(NET_ROBBER_CARDS, { TX(remoteLoseCards) });
		}
		else
		{
			setWaitingMessage("El oponente tiro 7 y essta moviendo el robber");
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
		setErrMessage("Error al eliminar las cartas del rival al mover el robber");
	}
	else
	{
		setWaitingMessage("El oponente tiro 7 y esta moviendo el robber");
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

	setWaitingMessage("El oponente pensando la jugada maestra...");

	enableRemoteActions();

}

void RemotePlayerEnabler::evaluateOffer(SubtypeEvent * ev)
{
	disableAllBut({ NET_KNIGHT,NET_YEARS_OF_PLENTY,NET_MONOPOLY,NET_ROAD_BUILDING });
	setErrMessage("");
	setWaitingMessage(""); 

	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	OfferTradePkg* pkg = static_cast<OfferTradePkg*>(auxEv->getPackage());

	pendingOffer = *pkg;													// Saving offer for response.
	map< ResourceType, char> oferta, pedido;								//armando el mensaje para mostrarle al jugador
	for (auto recurso : pendingOffer.getMyOnes())
	{
		oferta[recurso] += 1; // armo una lista con los recursos y cantidades
	}
	for (auto recurso : pendingOffer.getOpponentOnes())
	{
		pedido[recurso] += 1; // armo una lista con los recursos y cantidades
	}
	string mensaje("Acepta la oferta de: ");
	for (auto par : oferta)
	{
		mensaje += to_string(par.second);
		switch (par.first)
		{
		case BOSQUE:
			mensaje += " de madera - ";
			break;
		case COLINAS:
			mensaje += " de ladrillo - ";
			break;
		case MONTAÑAS:
			mensaje += " de piedra - ";
			break;
		case CAMPOS:
			mensaje += " de trigo - ";
			break;
		case PASTOS:
			mensaje += " de oveja - ";
			break;
		default:break;
		}
	}
	mensaje += " Por: ";
	for (auto par : pedido)
	{
		mensaje += to_string(par.second);
		switch (par.first)
		{
		case BOSQUE:
			mensaje += " de madera - ";
			break;
		case COLINAS:
			mensaje += " de ladrillo - ";
			break;
		case MONTAÑAS:
			mensaje += " de piedra - ";
			break;
		case CAMPOS:
			mensaje += " de trigo - ";
			break;
		case PASTOS:
			mensaje += " de oveja - ";
			break;
		default:break;
		}
	}
	setWaitingMessage(mensaje); // cargo el mensaje con la oferta

	if (validateOffer(pkg))
	{
		if (checkResourcesToGiveBackAndRespond(pkg))
		{
			enable(PLA_YES, { TX(exchangeResources), TX(enableRemoteActions) });
			enable(PLA_NO, { TX(rejectOffer),TX(enableRemoteActions) });
		}
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

	if (remotePlayer->checkSettlementAvailability(position))
	{
		setWaitingMessage("El oponente coloco un nuevo SETTLEMENT !!!");

		remotePlayer->addToMySettlements(position);
		localPlayer->addToRivalsSettlements(position);
		pkgSender->pushPackage(new package(headers::ACK));
		if (remotePlayer->hasWon(playingWithDev))
			enable(NET_I_WON, {TX(finDelJuego)});
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

	if (remotePlayer->checkRoadAvailability(position))
	{
		setWaitingMessage("El oponente coloco un nuevo ROAD !!!");

		remotePlayer->addToMyRoads(position);
		localPlayer->addToRivalsRoads(position);
		board->addRoadToTokens(position, remotePlayer);
		pkgSender->pushPackage(new package(headers::ACK));
		checkLongestRoad();
		if (remotePlayer->hasWon(playingWithDev))
			enable(NET_I_WON, { TX(finDelJuego) });
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
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	CityPkg* pkg = static_cast<CityPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (remotePlayer->checkPromotionOfCity(position))
	{
		setWaitingMessage("El oponente coloco una nueva CITY !!!");

		remotePlayer->promoteToMyCity(position);
		localPlayer->promoteToRivalsCity(position);
		board->addCityToTokens(position, remotePlayer);
		pkgSender->pushPackage(new package(headers::ACK));
		if (remotePlayer->hasWon(playingWithDev))
			enable(NET_I_WON, { TX(finDelJuego) });
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
	BankTradePkg* pkg = static_cast<BankTradePkg*>(auxEv->getPackage());
	int amountOfResourcesPaid = pkg->getLength();
	bool isOk = false;

	switch (amountOfResourcesPaid)
	{
	case 4:
		isOk = true;
		break;
	case 3:
		if (remotePlayer->checkForAnyPort(board, PortType::_3x1)) { isOk = true; }
		break;
	case 2:
		switch (pkg->getResoucesPaid()[0])
		{
		case PortType::_2Lx1:
			if (remotePlayer->checkForAnyPort(board, PortType::_2Lx1)) { isOk = true; }
			break;
		case PortType::_2Ox1:
			if (remotePlayer->checkForAnyPort(board, PortType::_2Ox1)) { isOk = true; }
			break;
		case PortType::_2Mx1:
			if (remotePlayer->checkForAnyPort(board, PortType::_2Mx1)) { isOk = true; }
			break;
		case PortType::_2Px1:
			if (remotePlayer->checkForAnyPort(board, PortType::_2Px1)) { isOk = true; }
			break;
		case PortType::_2Tx1:
			if (remotePlayer->checkForAnyPort(board, PortType::_2Tx1)) { isOk = true; }
			break;
		}
		break;
	default:
		isOk = false; // hay algun error en el paquete
		break;
	}
	/* despues de fijarme si es posible la cuestien de los puertos, me fijo si tiene los recursos suficientes*/
	if (isOk)
	{
		for (ResourceType a : pkg->getResoucesPaid())
		{
			if (!(remotePlayer->useResource(a)))
			{
				isOk = false;
			}
		}
	}

	if (isOk)
	{
		remotePlayer->addResource(pkg->getResouceBougth(),1);
		pkgSender->pushPackage(new package(headers::ACK));
	}
	else
	{
		emitEvent(ERR_IN_COM);
		pkgSender->pushPackage(new package(headers::ERROR_));
		setErrMessage("Error al intentar concretar el Banck trade del rival");
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
		setErrMessage("Error, el rival no tinene suficientes recursos para comprar una Dev Card"); //ver de cambiar esto, le da al oponente info de los recursos
		pkgSender->pushPackage(new package(headers::ERROR_));
		emitEvent(ERR_IN_COM);
	}
}

void RemotePlayerEnabler::endTurn(SubtypeEvent * ev)
{
	disableAll();
	enable(NET_DICES_ARE, { TX(checkDices) });
	setWaitingMessage("");
	setErrMessage("");
	emitEvent(TURN_FINISHED);
}

void RemotePlayerEnabler::remUsedKnight(SubtypeEvent * ev)
{
	disableAll();
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberMovePkg* pkg = static_cast<RobberMovePkg*>(auxEv->getPackage());
	
	random_device rd;
	mt19937_64 generator{ rd() };
	uniform_int_distribution<> dist{ 0,4}; // para tener un numero bien aleatorio (mejor que rand()%)
	ResourceType randCard;

	board->moveRobber(pkg->getPos());
	if (localPlayer->isThereSetOrCity(pkg->getPos()))
	{
		do{
			switch (dist(generator))
			{
			case 0: randCard = ResourceType::BOSQUE; break;
			case 1:randCard = ResourceType::CAMPOS; break;
			case 2:randCard = ResourceType::COLINAS; break;
			case 3:randCard = ResourceType::MONTAÑAS; break;
			case 4:randCard = ResourceType::PASTOS; break;
			default:randCard = ResourceType::DESIERTO; break; // para que se sortee otro nuevo
			}
		} while (localPlayer->getResourceAmount(randCard) == 0);
		localPlayer->useResource(randCard);
		remotePlayer->addResource(randCard);
		pkgSender->pushPackage(new CardIsPkg(static_cast<char>(randCard)));
	}
	else
	{
		pkgSender->pushPackage(new package(headers::ACK));
	}
	enableRemoteActions();
}

void RemotePlayerEnabler::remUsedMonopoly(SubtypeEvent * ev)
{
	disableAll();
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	MonopolyPkg* pkg = static_cast<MonopolyPkg*>(auxEv->getPackage());

	pkgSender->pushPackage(new package(headers::ACK)); // respondo el pauqete
	ResourceType recurso = pkg->getResource();
	size_t amount = localPlayer->getResourceAmount(recurso); // busco la cantidad de recursos que el local tiene para agregarle al remoto
	
	remotePlayer->addResource(recurso, amount); // transfiero los recursos al oponenete
	localPlayer->useResource(recurso, amount); // saco los recuros
	remotePlayer->useDevCard(DevCards::MONOPOLY); // uso la carta
	enableRemoteActions();
}

void RemotePlayerEnabler::remUsedYoP(SubtypeEvent * ev)
{
	disableAll();
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	YearsOfPlentyPkg* pkg = static_cast<YearsOfPlentyPkg*>(auxEv->getPackage());

	pkgSender->pushPackage(new package(headers::ACK)); // respondo el pauqete
	ResourceType recurso = pkg->getResource(true);
	size_t amount = localPlayer->getResourceAmount(recurso); // busco la cantidad de recursos que el local tiene para agregarle al remoto

	remotePlayer->addResource(recurso, amount); // transfiero los recursos al oponenete
	localPlayer->useResource(recurso, amount); // saco los recuros

	recurso = pkg->getResource(false);
	amount = localPlayer->getResourceAmount(recurso); // busco la cantidad de recursos que el local tiene para agregarle al remoto

	remotePlayer->addResource(recurso, amount); // transfiero los recursos al oponenete
	localPlayer->useResource(recurso, amount); // saco los recuros

	remotePlayer->useDevCard(DevCards::YEARS_OF_PLENTY); // uso la carta
	enableRemoteActions();
}

void RemotePlayerEnabler::remUsedRoadBuilding(SubtypeEvent * ev)
{
	disableAll();
	pkgSender->pushPackage(new package(headers::ACK));
	enable(NET_ROAD, { TX(firstRoadLocalStarts) });
}

void RemotePlayerEnabler::enableRemoteActions(SubtypeEvent * ev)
{
	disableAllBut({ NET_KNIGHT,NET_YEARS_OF_PLENTY,NET_MONOPOLY,NET_ROAD_BUILDING }); 
	if (remotePlayer->totalResourcesAmount())
	{
		enable(NET_OFFER_TRADE, { TX(evaluateOffer) });
		enable(NET_BANK_TRADE, { TX(checkRemoteBankTrade) });
	}
	if (remotePlayer->checkSettlementResources())
	{
		enable(NET_SETTLEMENT, { TX(checkRemoteSettlement) });
	}
	if (remotePlayer->checkCityResources())
	{
		enable(NET_CITY, { TX(checkRemoteCity) });
	}
	if (remotePlayer->checkRoadResources())
	{
		enable(NET_ROAD, { TX(checkRemoteRoad) });
	}
	if (remotePlayer->checkResourcesForDevCard())
	{
		enable(NET_DEV_CARDS, { TX(checkDevCards) });
	}
	enable(NET_PASS, { TX(endTurn) });
}

void RemotePlayerEnabler::rejectOffer(SubtypeEvent * ev)
{
	pkgSender->pushPackage(new package(headers::NO));
}

void RemotePlayerEnabler::exchangeResources(SubtypeEvent * ev)
{
	pkgSender->pushPackage(new package(headers::YES));
	for (auto resource : pendingOffer.getMyOnes())
	{
		localPlayer->addResource(resource);					// Adding the resources coming from opponent.
		remotePlayer->useResource(resource);
	}
	for (auto resource : pendingOffer.getOpponentOnes())
	{
		remotePlayer->addResource(resource);					// Giving resources to opponent.
		localPlayer->useResource(resource);
	}
}

void RemotePlayerEnabler::genericDefault(SubtypeEvent * ev)
{
	emitEvent(ERR_IN_COM);
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
