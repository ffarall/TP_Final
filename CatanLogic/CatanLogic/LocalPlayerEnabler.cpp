#include "LocalPlayerEnabler.h"
#include "SubEvents.h"
#include "MainEvent.h"
#include "NewEventHandling.h"

#define TX(x) (static_cast<void (Enabler::* )(SubtypeEvent *)>(&LocalPlayerEnabler::x))

LocalPlayerEnabler::LocalPlayerEnabler()
{
	init();
}

LocalPlayerEnabler::LocalPlayerEnabler(Networking * pkgSender_, PlayerEnabler* remoteEnabler_, EventsHandler* handler_, BasicGUI* GUI_) : PlayerEnabler(handler_, GUI_)
{
	init();
	setPkgSender(pkgSender_);
	setRemoteEnabler(remoteEnabler_);
}


LocalPlayerEnabler::~LocalPlayerEnabler()
{
	end();
}

void LocalPlayerEnabler::setRemoteEnabler(PlayerEnabler * remoteEnabler_)
{
	remoteEnabler = remoteEnabler_;
}

string LocalPlayerEnabler::whoWon()
{
	if (localPlayer->hasWon())
	{
		return "local";
	}
	else if (remotePlayer->hasWon())
	{
		return "remote";
	}
	else
	{
		return "no one";
	}
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
}

void LocalPlayerEnabler::localStarts(string nameLocal, string nameRemote, Board* board_)
{
	end();																				// Clears possible previous Players and Board from previous games.

	remoteEnabler->setLocalPlayer(localPlayer = new Player(nameLocal, GUI));					// Sets both localPlayer for local enabler and remote enabler.
	remoteEnabler->setRemotePlayer(remotePlayer = new Player(nameRemote, GUI));				// Same for remotePlayer.
	remoteEnabler->setBoard(board = board_);											// Same for board.


	setWaitingMessage(string("Listo para empezar, jugador ") + localPlayer->getName() + " seleccione donde colocar su primer SETTLEMENT.");

	disableAll();
	enable(PLA_SETTLEMENT, { TX(firstSettlementLocalStarts) });
	setDefaultRoutine(TX(genericDefault));
}

void LocalPlayerEnabler::remoteStarts(string nameLocal, string nameRemote, Board* board_)
{
	end();																				// Clears possible previous Players and Board from previous games.

	remoteEnabler->setLocalPlayer(localPlayer = new Player(nameLocal, GUI));					// Sets both localPlayer for local enabler and remote enabler.
	remoteEnabler->setRemotePlayer(remotePlayer = new Player(nameRemote, GUI));				// Same for remotePlayer.
	remoteEnabler->setBoard(board = board_);											// Same for board.


	setWaitingMessage(string("Listo para empezar, el jugador ") + remotePlayer->getName() + " debe colocar su primer SETTLEMENT.");

	disableAll();
	enable(PLA_SETTLEMENT, { TX(firstSettlementRemoteStarts) });
	setDefaultRoutine(TX(genericDefault));
}

void LocalPlayerEnabler::noAct(SubtypeEvent * ev)
{
}

void LocalPlayerEnabler::firstSettlementLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new SettlementPkg(*pkg));
	
	addSettlementToLocal(position);

	disable(PLA_SETTLEMENT);
	enable(PLA_ROAD, { TX(firstRoadLocalStarts) });
}

void LocalPlayerEnabler::firstRoadLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new RoadPkg(*pkg));
	
	addRoadToLocal(position);

	disable(PLA_ROAD);
	enable(PLA_SETTLEMENT, { TX(secondSettlementLocalStarts) });				// Leaving everything ready for next turn.

	emitEvent(TURN_FINISHED);										// Emitting event that turn is finished.
}

void LocalPlayerEnabler::secondSettlementLocalStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new SettlementPkg(*pkg));

	addSettlementToLocal(position);

	disable(PLA_SETTLEMENT);
	enable(PLA_ROAD, { TX(secondRoadLocalStarts) });
}

void LocalPlayerEnabler::secondRoadLocalStarts(SubtypeEvent * ev)
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
}

void LocalPlayerEnabler::firstSettlementRemoteStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new SettlementPkg(*pkg));

	addSettlementToLocal(position);

	disable(PLA_SETTLEMENT);
	enable(PLA_ROAD, { TX(firstRoadRemoteStarts) });
}

void LocalPlayerEnabler::firstRoadRemoteStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new RoadPkg(*pkg));

	addRoadToLocal(position);

	disable(PLA_ROAD);
	enable(PLA_SETTLEMENT, { TX(secondSettlementRemoteStarts) });
}

void LocalPlayerEnabler::secondSettlementRemoteStarts(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	pkgSender->pushPackage(new SettlementPkg(*pkg));

	addSettlementToLocal(position);

	disable(PLA_SETTLEMENT);
	enable(PLA_ROAD, { TX(secondRoadRemoteStarts) });
}

void LocalPlayerEnabler::secondRoadRemoteStarts(SubtypeEvent * ev)
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

	emitEvent(TURN_FINISHED);										// Emitting event that turn is finished.
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
		enable(NET_ACK, { TX(enablePlayerActions), TX(checkDevCards) });
	}
}

void LocalPlayerEnabler::remoteSendsRobberCards(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = static_cast<RobberCardsPkg*>(auxEv->getPackage());

	for (auto res : pkg->getCards())
	{
		remotePlayer->useResource(res);										// For every card, a resource is eliminated.
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
}

void LocalPlayerEnabler::enablePlayerActions(SubtypeEvent * ev)
{
	list<EventSubtypes> devCardsEvs = { PLA_KNIGHT, PLA_MONOPOLY, PLA_YEARS_OF_PLENTY, PLA_ROAD_BUILDING };

	disableAllBut(devCardsEvs);
	if (localPlayer->totalResourcesAmount())
	{
		enable(PLA_OFFER_TRADE, { TX(checkOffer) });
	}
	if (localPlayer->checkSettlementResources())
	{
		enable(PLA_SETTLEMENT, { TX(checkSettlement) });
	}
	if (localPlayer->checkRoadResources())
	{
		enable(PLA_ROAD, { TX(checkRoad) });
	}
	if (localPlayer->checkCityResources())
	{
		enable(PLA_CITY, { TX(checkCity) });
	}
	if (localPlayer->totalResourcesAmount())
	{
		enable(PLA_BANK_TRADE, { TX(checkBankTrade) });
	}
	if (localPlayer->checkResourcesForDevCard())
	{
		enable(PLA_DEV_CARD, { TX(drawDevCard) });
	}
	enable(PLA_PASS, { TX(endTurn) });
}

void LocalPlayerEnabler::checkDevCards(SubtypeEvent * ev)
{
	if (areWePlayingWithDev())
	{
		if (localPlayer->isThereDevCard(KNIGHT))
		{
			enable(PLA_KNIGHT, { TX(useKnight) });
		}
		else
		{
			disable(PLA_KNIGHT);
		}
		if (localPlayer->isThereDevCard(VICTORY_POINTS))
		{
			localPlayer->useDevCard(VICTORY_POINTS);
		}
		if (localPlayer->isThereDevCard(MONOPOLY))
		{
			enable(PLA_MONOPOLY, { TX(useMonopoly) });
		}
		else
		{
			disable(PLA_MONOPOLY);
		}
		if (localPlayer->isThereDevCard(YEARS_OF_PLENTY))
		{
			enable(PLA_YEARS_OF_PLENTY, { TX(useYearsOfPlenty) });
		}
		else
		{
			disable(PLA_YEARS_OF_PLENTY);
		}
		if (localPlayer->isThereDevCard(ROAD_BUILDING))
		{
			enable(PLA_ROAD_BUILDING, { TX(useRoadBuilding) });
		}
		else
		{
			disable(PLA_ROAD_BUILDING);
		}
	}
}

void LocalPlayerEnabler::discardLocalResources(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberCardsPkg* pkg = static_cast<RobberCardsPkg*>(auxEv->getPackage());

	for (auto res : pkg->getCards())
	{
		localPlayer->useResource(res);										// For every card, a resource is eliminated.
	}

	pkgSender->pushPackage(new RobberCardsPkg(*pkg));

	disableAll();
	enable(PLA_ROBBER_MOVE, { TX(moveRobber) });
}

void LocalPlayerEnabler::moveRobber(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RobberMovePkg* pkg = static_cast<RobberMovePkg*>(auxEv->getPackage());

	board->moveRobber(pkg->getPos());

	enable(NET_ACK, { TX(enablePlayerActions), TX(checkDevCards) });
}

void LocalPlayerEnabler::checkOffer(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	OfferTradePkg* pkg = static_cast<OfferTradePkg*>(auxEv->getPackage());

	if (validateOffer(pkg))
	{
		pendingOffer = *pkg;													// Saving offer for response.

		enable(NET_YES, { TX(exchangeResources), TX(enablePlayerActions) });
		enable(NET_NO, { TX(enablePlayerActions) });
	}
	else
	{
		setErrMessage("La oferta de trade ingresada es inválida. La misma debe constar de entre 1 y 9 recursos ofrecidos, y entre 1 y 9 pedidos.");
	}
}

void LocalPlayerEnabler::checkSettlement(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	SettlementPkg* pkg = static_cast<SettlementPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkSettlementAvailability(position))
	{
		localPlayer->addToMySettlements(position);
		remotePlayer->addToRivalsSettlements(position);
		board->addSettlementToTokens(position, localPlayer);
		pkgSender->pushPackage(new SettlementPkg(*pkg));
		enable(NET_ACK, { TX(enablePlayerActions) });
	}
	else
	{
		setErrMessage("La coordenada donde se quiso ubicar el nuevo Settlement no está disponible.");
	}

	checkIfLocalWon();
}

void LocalPlayerEnabler::checkRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkRoadAvailability(position))
	{
		localPlayer->addToMyRoads(position);
		remotePlayer->addToRivalsRoads(position);
		board->addRoadToTokens(position, localPlayer);
		pkgSender->pushPackage(new RoadPkg(*pkg));
		enable(NET_ACK, { TX(enablePlayerActions) });
	}
	else
	{
		setErrMessage("La coordenada donde se quiso ubicar el nuevo Road no está disponible.");
	}
	
	checkLongestRoad();
	checkIfLocalWon();
}

void LocalPlayerEnabler::checkCity(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	CityPkg* pkg = static_cast<CityPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkPromotionOfCity(position))
	{
		localPlayer->promoteToMyCity(position);
		remotePlayer->promoteToRivalsCity(position);
		board->addCityToTokens(position, localPlayer);
		pkgSender->pushPackage(new CityPkg(*pkg));
		enable(NET_ACK, { TX(enablePlayerActions) });
	}
	else
	{
		setErrMessage("La coordenada donde se quiso promover la nueva City no es aceptada.");
	}

	checkIfLocalWon();
}

void LocalPlayerEnabler::checkBankTrade(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	BankTradePkg* pkg = static_cast<BankTradePkg*>(auxEv->getPackage());
	int amountOfResourcesPaid = pkg->getLength();
	ResourceType resourcesOffered = pkg->getResoucesPaid()[0];

	PortType tradeType;
	switch (amountOfResourcesPaid)
	{
	case 4: tradeType = _4x1;
		break;
	case 3: tradeType = _3x1;
		break;
	case 2:
	{
		switch (resourcesOffered)
		{
		case BOSQUE: tradeType = _2Mx1;
			break;
		case COLINAS: tradeType = _2Lx1;
			break;
		case MONTAÑAS: tradeType = _2Px1;
			break;
		case CAMPOS: tradeType = _2Tx1;
			break;
		case PASTOS: tradeType = _2Ox1;
			break;
		default:
			break;
		}
	}
	break;
	default:
	{
		setErrMessage("Condiciones inválidas ingresadas para BANK_TRADE.");
		return;
	}
		break;
	}

	if (localPlayer->checkResourcesForBankTrade(tradeType))
	{
		pkgSender->pushPackage(new BankTradePkg(*pkg));

		if (tradeType == _4x1)
		{
			localPlayer->makeBankTrade(tradeType, pkg->getResouceBougth(), pkg->getResoucesPaid[0]);
		}
		else
		{
			if (localPlayer->checkForAnyPort(board, tradeType))
			{
				localPlayer->makeBankTrade(tradeType, pkg->getResouceBougth(), pkg->getResoucesPaid[0]);
			}
			else
			{
				setErrMessage("El usuario no cuenta con un puerto capaz de hacer un tarde de este tipo.");
			}
		}
	}
	else
	{
		setErrMessage("El usuario no cuenta con los recursos necesarios para hacer el BANK_TRADE.");
	}
}

void LocalPlayerEnabler::drawDevCard(SubtypeEvent * ev)
{
	if (localPlayer->checkResourcesForDevCard())
	{
		localPlayer->getNewDevCard(board);
		enable(NET_ACK, { TX(enablePlayerActions) });
	}
	else
	{
		setErrMessage("El jugador no cuenta con suficientes recursos para tomar una Development Card.");
	}
}

void LocalPlayerEnabler::useKnight(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	KnightPkg* pkg = static_cast<KnightPkg*>(auxEv->getPackage());
	char movedTo = pkg->getPos();

	pkgSender->pushPackage(new KnightPkg(*pkg));

	localPlayer->useDevCard(KNIGHT);
	if (remotePlayer->isThereSetOrCity(movedTo))
	{
		disableAll();
		enable(NET_CARD_IS, { TX(takeRobberCard), TX(enablePlayerActions) });
	}
	else
	{
		disableAll();
		enable(NET_ACK, { TX(enablePlayerActions) });
	}

	checkLargestArmy();
	checkIfLocalWon();
}

void LocalPlayerEnabler::useMonopoly(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	MonopolyPkg* pkg = static_cast<MonopolyPkg*>(auxEv->getPackage());
	ResourceType res = pkg->getResource();

	pkgSender->pushPackage(new MonopolyPkg(*pkg));

	localPlayer->useDevCard(MONOPOLY);
	localPlayer->addResource(res, remotePlayer->getResourceAmount(res));
	remotePlayer->useResource(res, remotePlayer->getResourceAmount(res));

	disableAll();
	enable(NET_ACK, { TX(enablePlayerActions) });

	checkIfLocalWon();
}

void LocalPlayerEnabler::useYearsOfPlenty(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	YearsOfPlentyPkg* pkg = static_cast<YearsOfPlentyPkg*>(auxEv->getPackage());
	ResourceType resCard1 = pkg->getResource(true);
	ResourceType resCard2 = pkg->getResource(false);

	pkgSender->pushPackage(new YearsOfPlentyPkg(*pkg));

	localPlayer->useDevCard(YEARS_OF_PLENTY);
	localPlayer->addResource(resCard1);
	localPlayer->addResource(resCard2);

	disableAll();
	enable(NET_ACK, { TX(enablePlayerActions) });

	checkIfLocalWon();
}

void LocalPlayerEnabler::useRoadBuilding(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("Seleccione donde quiere colocar el primer Road.");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);

	pkgSender->pushPackage(new package(headers::ROAD_BUILDING));

	disableAll();
	enable(NET_ACK, { TX(enableFstRoad) });

	checkIfLocalWon();
}

void LocalPlayerEnabler::exchangeResources(SubtypeEvent * ev)
{
	for (auto resource : pendingOffer.getOpponentOnes())
	{
		localPlayer->addResource(resource);					// Adding the resources coming from opponent.
		remotePlayer->useResource(resource);
	}
	for (auto resource : pendingOffer.getMyOnes())
	{
		remotePlayer->addResource(resource);					// Giving resources to opponent.
		localPlayer->useResource(resource);
	}
}

void LocalPlayerEnabler::takeRobberCard(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	CardIsPkg* pkg = static_cast<CardIsPkg*>(auxEv->getPackage());
	ResourceType res = pkg->getResource();

	localPlayer->addResource(res);
	remotePlayer->useResource(res);
}

void LocalPlayerEnabler::enableFstRoad(SubtypeEvent * ev)
{
	disableAll();
	enable(PLA_ROAD, { TX(checkFstRoad) });
}

void LocalPlayerEnabler::checkFstRoad(SubtypeEvent * ev)
{
	setErrMessage("");
	setWaitingMessage("");
	SubEvents* auxEv = static_cast<SubEvents*>(ev);
	RoadPkg* pkg = static_cast<RoadPkg*>(auxEv->getPackage());
	string position = pkg->getPos();

	if (localPlayer->checkRoadAvailability(position))
	{
		localPlayer->addToMyRoads(position);
		remotePlayer->addToRivalsRoads(position);
		board->addRoadToTokens(position, localPlayer);
		pkgSender->pushPackage(new RoadPkg(*pkg));
		enable(NET_ACK, { TX(enableSndRoad) });
	}
	else
	{
		setErrMessage("La coordenada donde se quiso ubicar el nuevo Road no está disponible.");
	}

	checkIfLocalWon();
}

void LocalPlayerEnabler::enableSndRoad(SubtypeEvent * ev)
{
	disableAll();
	enable(PLA_ROAD, { TX(checkSndRoad) });
}

void LocalPlayerEnabler::checkSndRoad(SubtypeEvent * ev)
{
	checkRoad(ev);
}

void LocalPlayerEnabler::endTurn(SubtypeEvent * ev)
{
	emitEvent(TURN_FINISHED);
	disableAll();
	enable(PLA_DICES_ARE, { TX(checkDices) });

	checkIfLocalWon();
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
			who->addResource(resType);							// Adds 1 resource because it's a Settlement.
		}
	}
}

void LocalPlayerEnabler::checkIfLocalWon()
{
	if (localPlayer->hasWon())
	{
		emitEvent(I_WON);
	}
}

void LocalPlayerEnabler::checkLongestRoad()
{
	if (localPlayer->getLongestRoad() >= 5)											// Minimum requisite for having the longestRoadCard
	{
		if (remotePlayer->hasLongestRoad())											// If remote has it...
		{
			if (localPlayer->getLongestRoad() > remotePlayer->getLongestRoad())		// Must check who has it longer.
			{
				localPlayer->setLongestRoadCard(true);
			}
		}
		else
		{
			localPlayer->setLongestRoadCard(true);
		}
	}
}

void LocalPlayerEnabler::checkLargestArmy()
{
	if (localPlayer->getArmySize() >= 3)											// Minimum requisite for having the largestArmyCard
	{
		if (remotePlayer->hasLargestArmy())											// If remote has it...
		{
			if (localPlayer->getArmySize() > remotePlayer->getArmySize())			// Must check who has it larger.
			{
				localPlayer->setLargestArmyCard(true);
			}
		}
		else
		{
			localPlayer->setLargestArmyCard(true);
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
