#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "RemotePlayerEnabler.h"
#include "LocalPlayerEnabler.h"
#include "MainFSM.h"
#include "Button.h"
#include "NewEventHandling.h"
#include "AllegroGUI.h"
#include "PosDef.h"
#include "GutenbergsPressAllegro.h"
#include "SubEvents.h"


#define TINT_CORR(r, g, b, a) (r*255), (g*255), (b*255), (a*255)
GUIEnablerEvent ResourceButton(Button * bankbutton, Button * offerbutton, Button * Yop, Button * monopoly, MainFSM * mainFSM, Player * localPlayer, ResourceType recurso);

void createButtons(GutenbergsPressAllegro* printer, EventsHandler * handler, Player * localPlayer, MainFSM* mainFSM, AllegroGUI* GUI, Board * tablero, std::vector<Button*> &buttonList, RemotePlayerEnabler * remEnab, LocalPlayerEnabler * locEnab)
{

	buttonList.push_back(new Button(printer, handler, START_PLAYING_X, START_PLAYING_Y, START_PLAYING_H, START_PLAYING_W, "", "start.png", "", 14)); //startPlayingButton()
	GUI->attachController("StartPlaying", buttonList[0]);
	buttonList.push_back(new Button(printer, handler, QUIT_X, QUIT_Y, QUIT_H, QUIT_W, "", "quit.png", "", 14));//quitButton()
	GUI->attachController("Quit", buttonList[1]);
	buttonList.push_back(new Button(printer, handler, NEW_SETTLEMENT_X, NEW_SETTLEMENT_Y, NEW_SETTLEMENT_H, NEW_SETTLEMENT_W, "", "settlement.png", "", 0));//newSettlementButton
	GUI->attachController("NewSettlement", buttonList[2]);
	buttonList.push_back(new Button(printer, handler, NEW_CITY_X, NEW_CITY_Y, NEW_CITY_H, NEW_CITY_W, "", "city.png", "", 0));//newCityButton
	GUI->attachController("NewCity", buttonList[3]);
	buttonList.push_back(new Button(printer, handler, NEW_ROAD_X, NEW_ROAD_Y, NEW_ROAD_H, NEW_ROAD_W, "", "road.png", "", 0));//newRoadButton
	GUI->attachController("NewRoad", buttonList[4]);
	buttonList.push_back(new Button(printer, handler, BUY_DEV_CARD_X, BUY_DEV_CARD_Y, BUY_DEV_CARD_H, BUY_DEV_CARD_W, "", "DevBack2.PNG", "", 0));//getDevCardButton
	GUI->attachController("GetDevCard", buttonList[5]);
	buttonList.push_back(new Button(printer, handler, PASS_X, PASS_Y, PASS_H, PASS_W, "", "pass.png", "", 0));//endTurnButton
	GUI->attachController("EndTurn", buttonList[6]);
	buttonList.push_back(new Button(printer, handler, NEW_BANK_TRADE_X, NEW_BANK_TRADE_Y, NEW_BANK_TRADE_H, NEW_BANK_TRADE_W, "Bank Trade", "bankTrade.png", "catanFont.otf", 14));//bankTradeButton
	GUI->attachController("BankTrade", buttonList[7]);
	buttonList.push_back(new Button(printer, handler, NEW_OFFER_TRADE_X, NEW_OFFER_TRADE_Y, NEW_OFFER_TRADE_H, NEW_OFFER_TRADE_W, "Offer Trade", "offerTrade.png", "catanFont.otf", 14));//offerTradeButton
	GUI->attachController("OfferTrade", buttonList[8]);
	buttonList.push_back(new Button(printer, handler, THROW_DICE_X, THROW_DICE_Y, THROW_DICE_H, THROW_DICE_W, "Dice", "dice.png", "catanFont.otf", 14));//throwDicesButton
	GUI->attachController("ThrowDices", buttonList[9]);
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//useKnightButtton
	GUI->attachController("UseKnight", buttonList[10]);
	buttonList.push_back(new Button(printer, handler, USE_ROAD_BUILDING_X, USE_ROAD_BUILDING_Y, USE_ROAD_BUILDING_H, USE_ROAD_BUILDING_W, "", "RoadBuilding.PNG", "catanFont.otf", 14));//useRoadBuildingButton
	GUI->attachController("UseRoadBuilding", buttonList[11]);
	buttonList.push_back(new Button(printer, handler, USE_MONOPOLY_X, USE_MONOPOLY_Y, USE_MONOPOLY_H, USE_MONOPOLY_W, "", "Monopoly.PNG", "catanFont.otf", 14));//useMonopolyButton
	GUI->attachController("UseMonopoly", buttonList[12]);
	buttonList.push_back(new Button(printer, handler, USE_YEARS_OF_PLENTY_X, USE_YEARS_OF_PLENTY_Y, USE_YEARS_OF_PLENTY_H, USE_YEARS_OF_PLENTY_W, "", "YofP.PNG", "catanFont.otf", 14));//useYearsOfPlentyButton
	GUI->attachController("UseYearsOfPlenty", buttonList[13]);
	buttonList.push_back(new Button(printer, handler, SELECT_4x1_X, SELECT_4x1_Y, SELECT_4x1_H, SELECT_4x1_W, "", "4por1.png", "", 14));//port4x1Button
	GUI->attachController("Port4x1", buttonList[14]);
	buttonList.push_back(new Button(printer, handler, SELECT_3x1_X, SELECT_3x1_Y, SELECT_3x1_H, SELECT_3x1_W, "", "3por1.png", "", 14));//port3x1Button
	GUI->attachController("Port3x1", buttonList[15]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Mx1_X, SELECT_2Mx1_Y, SELECT_2Mx1_H, SELECT_2Mx1_W, "", "2Mpor1.png", "", 14));//port2Mx1Button
	GUI->attachController("Port2Mx1", buttonList[16]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Tx1_X, SELECT_2Tx1_Y, SELECT_2Tx1_H, SELECT_2Tx1_W, "", "2Gpor1.png", "", 14));//port2Tx1Button
	GUI->attachController("Port2Tx1", buttonList[17]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Lx1_X, SELECT_2Lx1_Y, SELECT_2Lx1_H, SELECT_2Lx1_W, "", "2Lpor1.png", "", 14));//port2Lx1Button
	GUI->attachController("Port2Lx1", buttonList[18]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Ox1_X, SELECT_2Ox1_Y, SELECT_2Ox1_H, SELECT_2Ox1_W, "", "2Opor1.png", "", 14));//port2Ox1Button
	GUI->attachController("Port2Ox1", buttonList[19]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Px1_X, SELECT_2Px1_Y, SELECT_2Px1_H, SELECT_2Px1_W, "", "2Ppor1.png", "", 14));//port2Px1Button
	GUI->attachController("Port2Px1", buttonList[20]);
	buttonList.push_back(new Button(printer, handler, SELECT_BRICK_X, SELECT_BRICK_Y, SELECT_BRICK_H, SELECT_BRICK_W, "", "ladrillo.png", "", 14));//brickButton
	GUI->attachController("Brick", buttonList[21]);
	buttonList.push_back(new Button(printer, handler, SELECT_LUMBER_X, SELECT_LUMBER_Y, SELECT_LUMBER_H, SELECT_LUMBER_W, "", "tronco.png", "", 14));//lumberButton
	GUI->attachController("Lumber", buttonList[22]);
	buttonList.push_back(new Button(printer, handler, SELECT_ORE_X, SELECT_ORE_Y, SELECT_ORE_H, SELECT_ORE_W, "", "piedra.png", "", 14));//oreButton
	GUI->attachController("Ore", buttonList[23]);
	buttonList.push_back(new Button(printer, handler, SELECT_GRAIN_X, SELECT_GRAIN_Y, SELECT_GRAIN_H, SELECT_GRAIN_W, "", "pasto.png", "", 14));//grainButton
	GUI->attachController("Grain", buttonList[24]);
	buttonList.push_back(new Button(printer, handler, SELECT_WOOL_X, SELECT_WOOL_Y, SELECT_WOOL_H, SELECT_WOOL_W, "", "lana.png", "", 14));//woolButtton
	GUI->attachController("Wool", buttonList[25]);
	buttonList.push_back(new Button(printer, handler, ACCEPT_X, ACCEPT_Y, ACCEPT_H, ACCEPT_W, "", "tick.png", "", 0));//confirmButton
	GUI->attachController("Confirm", buttonList[26]);
	buttonList.push_back(new Button(printer, handler, CANCEL_X, CANCEL_Y, CANCEL_H, CANCEL_W, "", "cruz.png", "", 0));//cancelButton
	GUI->attachController("Cancel", buttonList[27]);
	buttonList.push_back(new Button(printer, handler, PLAY_AGAIN_X, PLAY_AGAIN_Y, PLAY_AGAIN_H, PLAY_AGAIN_W, "", "playAgain.png", "", 14));//playAgainButton
	GUI->attachController("PlayAgain", buttonList[28]);
	buttonList.push_back(new Button(printer, handler, GAME_OVER_X, GAME_OVER_Y, GAME_OVER_H, GAME_OVER_W, "", "gameOver.png", "", 14));//stopPlayinButton
	GUI->attachController("StopPlaying", buttonList[29]);
	buttonList.push_back(new Button(printer, handler, VICTORY_POINT_X, VICTORY_POINT_Y, VICTORY_POINT_H, VICTORY_POINT_W, "", "VictoryPoint.png", "", 14));//stopPlayinButton
	GUI->attachController("VictoryPoint", buttonList[30]);

	// attach de los bot�nes a los modelos de los que son observers
	mainFSM->attach(buttonList[0]);
	mainFSM->attach(buttonList[1]);
	mainFSM->attach(buttonList[2]);
	mainFSM->attach(buttonList[3]);
	mainFSM->attach(buttonList[4]);
	mainFSM->attach(buttonList[5]);
	mainFSM->attach(buttonList[6]);
	mainFSM->attach(buttonList[7]);
	mainFSM->attach(buttonList[8]);
	mainFSM->attach(buttonList[9]);
	mainFSM->attach(buttonList[10]);
	mainFSM->attach(buttonList[11]);
	mainFSM->attach(buttonList[12]);
	mainFSM->attach(buttonList[13]);
	mainFSM->attach(buttonList[14]);
	mainFSM->attach(buttonList[15]);
	mainFSM->attach(buttonList[16]);
	mainFSM->attach(buttonList[17]);
	mainFSM->attach(buttonList[18]);
	mainFSM->attach(buttonList[19]);
	mainFSM->attach(buttonList[20]);
	mainFSM->attach(buttonList[21]);
	mainFSM->attach(buttonList[22]);
	mainFSM->attach(buttonList[23]);
	mainFSM->attach(buttonList[24]);
	mainFSM->attach(buttonList[25]);
	mainFSM->attach(buttonList[26]);
	mainFSM->attach(buttonList[27]);
	mainFSM->attach(buttonList[28]);
	mainFSM->attach(buttonList[29]);
	mainFSM->attach(buttonList[30]);

	localPlayer->attach(buttonList[2]);
	localPlayer->attach(buttonList[3]);
	localPlayer->attach(buttonList[4]);
	localPlayer->attach(buttonList[5]);
	localPlayer->attach(buttonList[6]);
	localPlayer->attach(buttonList[7]);
	localPlayer->attach(buttonList[8]);
	localPlayer->attach(buttonList[9]);
	localPlayer->attach(buttonList[10]);
	localPlayer->attach(buttonList[11]);
	localPlayer->attach(buttonList[12]);
	localPlayer->attach(buttonList[13]);
	localPlayer->attach(buttonList[14]);
	localPlayer->attach(buttonList[15]);
	localPlayer->attach(buttonList[16]);
	localPlayer->attach(buttonList[17]);
	localPlayer->attach(buttonList[18]);
	localPlayer->attach(buttonList[19]);
	localPlayer->attach(buttonList[20]);
	localPlayer->attach(buttonList[21]);
	localPlayer->attach(buttonList[22]);
	localPlayer->attach(buttonList[23]);
	localPlayer->attach(buttonList[24]);
	localPlayer->attach(buttonList[25]);
	localPlayer->attach(buttonList[26]);
	localPlayer->attach(buttonList[27]);
	localPlayer->attach(buttonList[30]);

	//ahora le tengo que poner las funciones a cada bot�n
	for (auto a : buttonList)
	{
		a->disableMouseDown(); // por las dudas deshabilito todo
		a->disableMouseUp();
		a->disableTimer();
	}
	/****** attach to each button its routine to executte when is pressed *******/
	/******* verifiying if the main FSM is in an appropiate state and the button might be avaliable*********/
	buttonList[0]->addUtility(
		[mainFSM, handler]()
	{
		if (mainFSM->getCurrState() == mainStates::StartMenu_S)
		{
			//emitir evento start
			handler->enqueueEvent(new MainEvents(MainTypes::START_GAME));
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[1]->addUtility(
		[mainFSM, handler]()
	{
		if (mainFSM->getCurrState() == mainStates::StartMenu_S)
		{
			//emitir evento de quit
			handler->enqueueEvent(new MainEvents(MainTypes::QUIT_MT));
			return GUIEnablerEvent::QUIT;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);
	buttonList[2]->addUtility(
		[locEnab]()
		{
			if (locEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_SETTLEMENT)))
			{
				return GUIEnablerEvent::NEW_SETTLEMENT;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	buttonList[3]->addUtility(
		[locEnab]()
		{
			if (locEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_CITY)))
			{
				return GUIEnablerEvent::NEW_CITY;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[4]->addUtility(
		[localPlayer, mainFSM]()
	{
		if (localPlayer->checkRoadResources() && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
		{
			return GUIEnablerEvent::NEW_ROAD;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[5]->addUtility(
		[localPlayer, mainFSM, tablero, handler]()
	{
		if (localPlayer->checkResourcesForDevCard() && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
		{
			handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_DEV_CARD, new package(headers::DEV_CARD)));
			return GUIEnablerEvent::BUY_DEV_CARD;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);
	buttonList[6]->addUtility(
		[localPlayer, mainFSM, handler]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
		{
			//ver si esta bien el mainType ?
			handler->enqueueEvent(new SubEvents(MainTypes::TURN_FINISHED, SubType::PLA_PASS, new package(headers::PASS)));
			return GUIEnablerEvent::PASS;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	Button * bankbutton = buttonList[7];
	buttonList[7]->addUtility(
		[localPlayer, mainFSM, bankbutton]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
		{
			bankbutton->setPackage(new BankTradePkg()); // creo el paquete vacio
			return GUIEnablerEvent::BANK_TRADE;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	Button * offerbutton = buttonList[7];
	buttonList[8]->addUtility(
		[localPlayer, mainFSM, offerbutton]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
		{
			offerbutton->setPackage(new OfferTradePkg()); // crep el paquete vacio para empezar a completarlo
			return GUIEnablerEvent::OFFER_TRADE;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[9]->addUtility(
		[localPlayer, mainFSM, handler, locEnab]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && locEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_DICES_ARE)))
		{
			srand(time(NULL));
			char dado1, dado2;
			dado1 = rand() % 6 + 1;
			dado2 = rand() % 6 + 1;
			handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_DICES_ARE, new DicePkg(dado1, dado2)));
			return GUIEnablerEvent::TRHOW_DICE;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[10]->addUtility(
		[localPlayer, mainFSM]()
	{
		if (localPlayer->getDevCardAmount(DevCards::KNIGHT) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
		{
			return GUIEnablerEvent::USE_KNIGHT; // no hace nada mas
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[11]->addUtility(
		[localPlayer, mainFSM]()
	{
		if (localPlayer->getDevCardAmount(DevCards::ROAD_BUILDING) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
		{
			return GUIEnablerEvent::USE_ROAD_BUILDING; //no hace nada mas
		}
		return GUIEnablerEvent::NO_EV;
	}
	);
	Button * monopoly = buttonList[12];
	buttonList[12]->addUtility(
		[localPlayer, mainFSM, monopoly]()
	{
		if (localPlayer->getDevCardAmount(DevCards::MONOPOLY) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
		{
			monopoly->setPackage(new MonopolyPkg());
			return GUIEnablerEvent::USE_MONOPOLY; // crear paquete 
		}
		return GUIEnablerEvent::NO_EV;
	}
	);
	Button * Yop = buttonList[13];
	buttonList[13]->addUtility(
		[localPlayer, mainFSM, Yop]()
	{
		if (localPlayer->getDevCardAmount(DevCards::YEARS_OF_PLENTY) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
		{
			Yop->setPackage(new YearsOfPlentyPkg());
			return GUIEnablerEvent::USE_YOP;  // crear paquete
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[14]->addUtility(
		[localPlayer, mainFSM, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() > 3))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(4);
				return GUIEnablerEvent::_4X1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[15]->addUtility(
		[mainFSM, localPlayer, tablero, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 3) && (localPlayer->checkForAnyPort(tablero, PortType::_3x1)))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(3);
				return GUIEnablerEvent::_3X1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[16]->addUtility(
		[mainFSM, localPlayer, tablero, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Mx1)))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(2);
				std::vector<ResourceType> mandar;
				mandar.emplace_back(ResourceType::BOSQUE);
				mandar.emplace_back(ResourceType::BOSQUE);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setPaid(mandar);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->closeOffer();
				return GUIEnablerEvent::_2MX1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[17]->addUtility(
		[localPlayer, mainFSM, tablero, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Tx1)))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(2);
				std::vector<ResourceType> mandar;
				mandar.emplace_back(ResourceType::CAMPOS);
				mandar.emplace_back(ResourceType::CAMPOS);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setPaid(mandar);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->closeOffer();
				return GUIEnablerEvent::_2TX1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[18]->addUtility(
		[localPlayer, mainFSM, tablero, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Lx1)))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(2);
				std::vector<ResourceType> mandar;
				mandar.emplace_back(ResourceType::COLINAS);
				mandar.emplace_back(ResourceType::COLINAS);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setPaid(mandar);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->closeOffer();
				return GUIEnablerEvent::_2LX1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[19]->addUtility(
		[localPlayer, mainFSM, tablero, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Ox1)))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(2);
				std::vector<ResourceType> mandar;
				mandar.emplace_back(ResourceType::PASTOS);
				mandar.emplace_back(ResourceType::PASTOS);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setPaid(mandar);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->closeOffer();
				return GUIEnablerEvent::_2OX1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[20]->addUtility(
		[localPlayer, mainFSM, tablero, bankbutton]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Px1)))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo que este creado el paquete
			{
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setType(2);
				std::vector<ResourceType> mandar;
				mandar.emplace_back(ResourceType::MONTA�AS);
				mandar.emplace_back(ResourceType::MONTA�AS);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->setPaid(mandar);
				static_cast<BankTradePkg *>(bankbutton->getPackage())->closeOffer();
				return GUIEnablerEvent::_2PX1;
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[21]->addUtility(
		[&localPlayer, &mainFSM, bankbutton, offerbutton, Yop, monopoly]()
	{
		return ResourceButton(bankbutton, offerbutton, Yop, monopoly, mainFSM, localPlayer, ResourceType::COLINAS);
	}
	);

	buttonList[22]->addUtility(
		[&localPlayer, &mainFSM, bankbutton, offerbutton, Yop, monopoly]()
	{
		return ResourceButton(bankbutton, offerbutton, Yop, monopoly, mainFSM, localPlayer, ResourceType::BOSQUE);
	}
	);

	buttonList[23]->addUtility(
		[&localPlayer, &mainFSM, bankbutton, offerbutton, Yop, monopoly]()
	{
		return ResourceButton(bankbutton, offerbutton, Yop, monopoly, mainFSM, localPlayer, ResourceType::MONTA�AS);
	}
	);

	buttonList[24]->addUtility(
		[&localPlayer, &mainFSM, bankbutton, offerbutton, Yop, monopoly]()
	{
		return ResourceButton(bankbutton, offerbutton, Yop, monopoly, mainFSM, localPlayer, ResourceType::CAMPOS);
	}
	);

	buttonList[25]->addUtility(
		[&localPlayer, &mainFSM, bankbutton, offerbutton, Yop, monopoly]()
	{
		return ResourceButton(bankbutton, offerbutton, Yop, monopoly, mainFSM, localPlayer, ResourceType::PASTOS);
	}
	);

	buttonList[26]->addUtility(
		[localPlayer, mainFSM, handler, bankbutton, offerbutton, Yop, monopoly, remEnab]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (mainFSM->getCurrState() == mainStates::RemotePlayer_S))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo si hay BankTrade
			{
				BankTradePkg * paquete = static_cast<BankTradePkg *>(bankbutton->getPackage());
				if (!paquete->offerclosed())
				{
					paquete->closeOffer();
					return GUIEnablerEvent::ACCEPT;
				}
				else if (paquete->isComplete())
				{
					handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_BANK_TRADE, new BankTradePkg(paquete))); // emito evento de bank trade
					delete paquete;
					bankbutton->setPackage(nullptr);
					return GUIEnablerEvent::ACCEPT;
				}
			}
			else if (offerbutton->getPackage() != nullptr) // Me fijo el OfferTrade
			{
				OfferTradePkg * paquete = static_cast<OfferTradePkg *>(bankbutton->getPackage());
				if (!paquete->offerclosed())
				{
					paquete->closeOffer();
					return GUIEnablerEvent::ACCEPT;
				}
				else if (paquete->isComplete())
				{
					handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_OFFER_TRADE, new OfferTradePkg(paquete))); // emito evento de offertrade
					delete paquete;
					offerbutton->setPackage(nullptr);
					return GUIEnablerEvent::ACCEPT;
				}
			}
			else if (Yop->getPackage() != nullptr)
			{
				YearsOfPlentyPkg * paquete = static_cast<YearsOfPlentyPkg *>(Yop->getPackage());
				if (paquete->getResource(false) != ResourceType::DESIERTO) // si ya se eligieron los dos, confirmo el paquete 
				{
					handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_YEARS_OF_PLENTY, new YearsOfPlentyPkg(paquete->getResource(true), paquete->getResource(false)))); // ver quien elimina el paquete
					delete paquete;
					Yop->setPackage(nullptr);
					return GUIEnablerEvent::ACCEPT;
				}
			}
			else if (monopoly->getPackage() != nullptr)
			{
				MonopolyPkg * paquete = static_cast<MonopolyPkg *>(monopoly->getPackage());
				if (paquete->getResource() != ResourceType::DESIERTO)
				{
					handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_MONOPOLY, new MonopolyPkg(paquete->getResource())));
					delete paquete;
					monopoly->setPackage(nullptr);
					return GUIEnablerEvent::ACCEPT;
				}
			}
			else if (remEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_YES))) // contesto la oferta que me manda el otro player
			{
				handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_YES, new package(headers::YES)));
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[27]->addUtility(
		[localPlayer, mainFSM, handler, bankbutton, offerbutton, Yop, monopoly, remEnab]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) || (mainFSM->getCurrState() == mainStates::RemotePlayer_S))
		{
			if (bankbutton->getPackage() != nullptr) // me fijo si hay BankTrade
			{
				BankTradePkg * paquete = static_cast<BankTradePkg *>(bankbutton->getPackage());
				delete paquete;
				bankbutton->setPackage(nullptr);
				return GUIEnablerEvent::CANCEL;
			}
			else if (offerbutton->getPackage() != nullptr) // Me fijo el OfferTrade
			{
				OfferTradePkg * paquete = static_cast<OfferTradePkg *>(bankbutton->getPackage());
				delete paquete;
				offerbutton->setPackage(nullptr);
				return GUIEnablerEvent::CANCEL;
			}
			else if (Yop->getPackage() != nullptr)
			{
				YearsOfPlentyPkg * paquete = static_cast<YearsOfPlentyPkg *>(Yop->getPackage());
				delete paquete;
				offerbutton->setPackage(nullptr);
				return GUIEnablerEvent::CANCEL;
			}
			else if (monopoly->getPackage() != nullptr)
			{
				MonopolyPkg * paquete = static_cast<MonopolyPkg *>(monopoly->getPackage());
				delete paquete;
				offerbutton->setPackage(nullptr);
				return GUIEnablerEvent::CANCEL;
			}
			else if (remEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_NO))) // contesto la oferta que me manda el otro player
			{
				handler->enqueueEvent(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_NO, new package(headers::NO)));
			}
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[28]->addUtility(
		[mainFSM, handler]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayAgain_S) || (mainFSM->getCurrState() == mainStates::RemoteGameOver_S))
		{
			handler->enqueueEvent(new MainEvents(MainTypes::PLAY_AGAIN_MT));
			return GUIEnablerEvent::PLAY_AGAIN;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[29]->addUtility(
		[mainFSM, handler]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayAgain_S) || (mainFSM->getCurrState() == mainStates::RemoteGameOver_S))
		{
			handler->enqueueEvent(new MainEvents(MainTypes::GAME_OVER));
			return GUIEnablerEvent::STOP_PLAYING;
		}
		return GUIEnablerEvent::NO_EV;
	}
	);

	buttonList[30]->addUtility(
		[mainFSM, handler]()
	{
		if ((mainFSM->getCurrState() == mainStates::LocalPlayAgain_S) || (mainFSM->getCurrState() == mainStates::RemoteGameOver_S))
		{
			//algo de victory point o nada 
		}
		return GUIEnablerEvent::NO_EV;
	}
	);
	// all the action routines added 

	// Specifying how every button should update its movable type.


	buttonList[0]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::StartMenu_S)
		{
			if (buttonList[0]->isEnabled())
			{
				if (!buttonList[0]->isPressed())
				{
					buttonList[0]->setTypeTint(TINT_CORR(1, 1, 1, 1));
				}
				else
				{
					buttonList[0]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
				}
			}
			else
			{
				buttonList[0]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
			}
		}
		else
		{
			buttonList[0]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);

	buttonList[1]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::StartMenu_S)
		{
			if (!buttonList[1]->isPressed() && buttonList[1]->isEnabled())
			{
				buttonList[1]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[1]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else //si no estoy en el menu de inicio el bot�n es invisible y esta desactivado
		{
			buttonList[1]->setTypeTint(TINT_CORR(0, 0, 0, 0));
		}

	}
	);

	buttonList[2]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->checkSettlementResources() && buttonList[2]->isEnabled())
		{
			if (!buttonList[2]->isPressed())
			{
				buttonList[2]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[2]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && (!localPlayer->checkSettlementResources() || !buttonList[2]->isEnabled())) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[2]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[2]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[2]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);
	buttonList[3]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->checkCityResources() && buttonList[3]->isEnabled())
		{
			if (!buttonList[3]->isPressed())
			{
				buttonList[3]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[3]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && (!localPlayer->checkCityResources() || !buttonList[3]->isEnabled())) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[3]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[3]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[3]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[4]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->checkRoadResources() && buttonList[4]->isEnabled())
		{
			if (!buttonList[4]->isPressed())
			{
				buttonList[4]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[4]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && (!localPlayer->checkRoadResources() || !buttonList[4]->isEnabled())) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[4]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[4]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[4]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[5]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->checkResourcesForDevCard() && buttonList[5]->isEnabled())
		{
			if (!buttonList[5]->isPressed())
			{
				buttonList[5]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[5]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && (!localPlayer->checkResourcesForDevCard() || !buttonList[5]->isEnabled())) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[5]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[5]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[5]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}


	);

	buttonList[6]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
		{
			if (!buttonList[6]->isPressed() && buttonList[6]->isEnabled())
			{
				buttonList[6]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[6]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !buttonList[6]->isEnabled()) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[6]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[6]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[6]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}



	);

	buttonList[7]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->totalResourcesAmount() && buttonList[7]->isEnabled())
		{
			if (!buttonList[7]->isPressed())
			{
				buttonList[7]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[7]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && (!localPlayer->totalResourcesAmount() || !buttonList[4]->isEnabled())) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[7]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[7]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[7]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}
	);

	buttonList[8]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->totalResourcesAmount() && buttonList[8]->isEnabled())
		{
			if (!buttonList[8]->isPressed())
			{
				buttonList[8]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[8]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && (!localPlayer->totalResourcesAmount() || !buttonList[8]->isEnabled())) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[8]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[8]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[8]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[9]->addUpdate(
		[mainFSM, locEnab, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && locEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_DICES_ARE)))
		{
			if (!buttonList[9]->isPressed())
			{
				buttonList[9]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[9]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !locEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_DICES_ARE))) //si no tengo recursos, bot�n semitransparente para mostrarlo
		{
			buttonList[9]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[9]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[9]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[10]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->isThereDevCard(KNIGHT))
		{
			if (!buttonList[10]->isPressed())
			{
				buttonList[10]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[10]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->isThereDevCard(KNIGHT))
		{
			buttonList[10]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[10]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[10]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);
	buttonList[11]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->isThereDevCard(ROAD_BUILDING))
		{
			if (!buttonList[11]->isPressed())
			{
				buttonList[11]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[11]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->isThereDevCard(ROAD_BUILDING))
		{
			buttonList[11]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[11]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[11]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[12]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->isThereDevCard(MONOPOLY))
		{
			if (!buttonList[12]->isPressed())
			{
				buttonList[12]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[12]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->isThereDevCard(MONOPOLY))
		{
			buttonList[12]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[12]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[12]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}


	);

	buttonList[13]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->isThereDevCard(YEARS_OF_PLENTY))
		{
			if (!buttonList[13]->isPressed())
			{
				buttonList[13]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[13]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->isThereDevCard(YEARS_OF_PLENTY))
		{
			buttonList[13]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[13]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[13]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[14]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[14]->isEnabled())
		{
			if (!buttonList[14]->isPressed())
			{
				buttonList[14]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[14]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}


		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[14]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[14]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}


	);

	buttonList[15]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[15]->isEnabled())
		{
			if (!buttonList[15]->isPressed())
			{
				buttonList[15]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[15]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}


		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[15]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[15]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}

	);

	buttonList[16]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[16]->isEnabled())
		{
			if (!buttonList[16]->isPressed())
			{
				buttonList[16]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[16]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}


		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[16]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[16]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}

	);

	buttonList[17]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[17]->isEnabled())
		{
			if (!buttonList[17]->isPressed())
			{
				buttonList[17]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[17]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}


		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[17]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[17]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}

	);

	buttonList[18]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[18]->isEnabled())
		{
			if (!buttonList[18]->isPressed())
			{
				buttonList[18]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[18]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}


		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[18]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[18]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}

	);

	buttonList[19]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[19]->isEnabled())
		{
			if (!buttonList[19]->isPressed())
			{
				buttonList[19]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[19]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}


		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[19]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[19]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}

	);

	buttonList[20]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && buttonList[20]->isEnabled())
		{
			if (!buttonList[20]->isPressed())
			{
				buttonList[20]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[20]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}

		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, boton desactivado
		{
			buttonList[20]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[20]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el boton es invisible y esta desactivado
		}


	}

	);

	buttonList[21]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->getResourceAmount(COLINAS))
		{
			if (!buttonList[21]->isPressed())
			{
				buttonList[21]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[21]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->getResourceAmount(COLINAS))
		{
			buttonList[21]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[21]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[21]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}



	);

	buttonList[22]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->getResourceAmount(BOSQUE))
		{
			if (!buttonList[22]->isPressed())
			{
				buttonList[22]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[22]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->getResourceAmount(BOSQUE))
		{
			buttonList[22]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[22]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[22]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}

	);

	buttonList[23]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->getResourceAmount(MONTA�AS))
		{
			if (!buttonList[23]->isPressed())
			{
				buttonList[23]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[23]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->getResourceAmount(MONTA�AS))
		{
			buttonList[23]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[23]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[23]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}
	);

	buttonList[24]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->getResourceAmount(CAMPOS))
		{
			if (!buttonList[24]->isPressed())
			{
				buttonList[24]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[24]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->getResourceAmount(CAMPOS))
		{
			buttonList[24]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[24]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[24]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}
	);

	buttonList[25]->addUpdate(
		[mainFSM, localPlayer, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && localPlayer->getResourceAmount(PASTOS))
		{
			if (!buttonList[25]->isPressed())
			{
				buttonList[25]->setTypeTint(TINT_CORR(1, 1, 1, 1));
			}
			else
			{
				buttonList[25]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
			}
		}
		else if (mainFSM->getCurrState() == mainStates::LocalPlayer_S && !localPlayer->getResourceAmount(PASTOS))
		{
			buttonList[25]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S) // si estoy en juego pero no es mi turno, bot�n desactivado
		{
			buttonList[25]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
		}
		else
		{
			buttonList[25]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}


	}
	);

	buttonList[26]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S || mainFSM->getCurrState() == mainStates::RemotePlayer_S)
		{
			if (buttonList[26]->isEnabled())
			{
				if (!buttonList[26]->isPressed())
				{
					buttonList[26]->setTypeTint(TINT_CORR(1, 1, 1, 1));
				}
				else
				{
					buttonList[26]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
				}
			}
			else
			{
				buttonList[26]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
			}
		}
		else
		{
			buttonList[26]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);

	buttonList[27]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S || mainFSM->getCurrState() == mainStates::RemotePlayer_S)
		{
			if (buttonList[27]->isEnabled())
			{
				if (!buttonList[27]->isPressed())
				{
					buttonList[27]->setTypeTint(TINT_CORR(1, 1, 1, 1));
				}
				else
				{
					buttonList[27]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
				}
			}
			else
			{
				buttonList[27]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
			}
		}
		else
		{
			buttonList[27]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);

	buttonList[28]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayAgain_S || mainFSM->getCurrState() == mainStates::RemoteGameOver_S)
		{
			if (buttonList[28]->isEnabled())
			{
				if (!buttonList[28]->isPressed())
				{
					buttonList[28]->setTypeTint(TINT_CORR(1, 1, 1, 1));
				}
				else
				{
					buttonList[28]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
				}
			}
			else
			{
				buttonList[28]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
			}
		}
		else
		{
			buttonList[28]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);

	buttonList[29]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayAgain_S || mainFSM->getCurrState() == mainStates::RemoteGameOver_S)
		{
			if (buttonList[29]->isEnabled())
			{
				if (!buttonList[29]->isPressed())
				{
					buttonList[29]->setTypeTint(TINT_CORR(1, 1, 1, 1));
				}
				else
				{
					buttonList[29]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
				}
			}
			else
			{
				buttonList[29]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
			}
		}
		else
		{
			buttonList[29]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);

	buttonList[30]->addUpdate(
		[mainFSM, buttonList]()
	{
		if (mainFSM->getCurrState() == mainStates::LocalPlayAgain_S || mainFSM->getCurrState() == mainStates::RemoteGameOver_S)
		{
			if (buttonList[30]->isEnabled())
			{
				if (!buttonList[30]->isPressed())
				{
					buttonList[30]->setTypeTint(TINT_CORR(1, 1, 1, 1));
				}
				else
				{
					buttonList[30]->setTypeTint(TINT_CORR(1, 0.5, 0.5, 1));
				}
			}
			else
			{
				buttonList[30]->setTypeTint(TINT_CORR(0.5, 0.5, 0.5, 0.5));
			}
		}
		else
		{
			buttonList[30]->setTypeTint(TINT_CORR(0, 0, 0, 0));//si no estoy en el juego el bot�n es invisible y esta desactivado
		}
	}
	);
}

GUIEnablerEvent ResourceButton(Button * bankbutton, Button * offerbutton, Button * Yop, Button * monopoly, MainFSM * mainFSM, Player * localPlayer, ResourceType recurso)
{
	if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
	{
		if (localPlayer->getResourceAmount(recurso) && bankbutton->getPackage() != nullptr)
		{
			BankTradePkg * paquete = static_cast<BankTradePkg *>(bankbutton->getPackage());
			if (!paquete->offerclosed())
			{
				char i = paquete->getLength();
				if (localPlayer->getResourceAmount(recurso) >= i) // me fijo si tiene los recursos necesarios
				{
					std::vector<ResourceType> payment;
					for (i; i > 0; i--)
					{
						payment.emplace_back(recurso);
					}
					paquete->setPaid(payment);
					return GUIEnablerEvent::RESOURCE;
				}
			}
			else if (!paquete->isComplete())
			{
				paquete->setBougth(ResourceType::COLINAS);
				return GUIEnablerEvent::RESOURCE;
			}
		}
		else if (localPlayer->getResourceAmount(recurso) && offerbutton->getPackage() != nullptr)
		{
			OfferTradePkg * paquete = static_cast<OfferTradePkg *>(bankbutton->getPackage());
			if (!paquete->offerclosed())
			{
				int amount = 0;
				for (auto rec : paquete->getMyOnes())
				{
					amount += (rec == recurso ? 1 : 0);
				}
				if (localPlayer->getResourceAmount(recurso) > amount) // me fijo que tenga los recursos que esta ofreciendo
				{
					paquete->addToMyOffer(recurso);
					return GUIEnablerEvent::RESOURCE;
				}
			}
			else if (!paquete->isComplete())
			{
				paquete->addToMyRequest(recurso);
				return GUIEnablerEvent::RESOURCE;
			}
		}
		else if (Yop->getPackage() != nullptr)
		{
			YearsOfPlentyPkg * paquete = static_cast<YearsOfPlentyPkg *>(bankbutton->getPackage());
			if (paquete->getResource(true) == ResourceType::DESIERTO) // me fijo si esta completo el primer recurso
			{
				paquete->setResource(true, recurso);
				return GUIEnablerEvent::RESOURCE;
			}
			else if (paquete->getResource(false) == ResourceType::DESIERTO) // ahora me fijo el segundo
			{
				paquete->setResource(false, recurso);
				return GUIEnablerEvent::RESOURCE;
			}
			else
			{
				paquete->setResource(true, paquete->getResource(false)); // paso el segundo al primero
				paquete->setResource(false, recurso); // el nuevo lo pongo en el segundo
				return GUIEnablerEvent::RESOURCE;
			}
		}
		else if (monopoly->getPackage() != nullptr)
		{
			MonopolyPkg * paquete = static_cast<MonopolyPkg *>(bankbutton->getPackage());
			paquete->setResource(recurso);
			return GUIEnablerEvent::RESOURCE;
		}
	}
	return GUIEnablerEvent::NO_EV;
}