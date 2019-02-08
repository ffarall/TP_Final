#include<iostream>
#include<vector>
#include"Board.h"
#include"Player.h"
#include"RemotePlayerEnabler.h"
#include"LocalPlayerEnabler.h"
#include"BasicGUI.h"
#include"Networking.h"
#include"MainFSM.h"
#include"HandShakingFSM.h"
#include"Button.h"
#include"NewEventHandling.h"
#include"AllegroGUI.h"
#include "PosDef.h"
#include "LocalObserver.h"
#include "BoardController.h"
#include "GutenbergsPressAllegro.h"

void createButtons(GutenbergsPressAllegro* printer, EventsHandler * evH,Player * jugador, MainFSM* mainFSM, AllegroGUI* GUI, Board * tablero);


int main(int argc, char* argv[])
{
	std::string localPlayerName(argv[1]);
	Player localPlayer(localPlayerName);
	Player remotePlayer;
	Board globalBoard;
	Networking network;
	EventsHandler handler;
	RemotePlayerEnabler remotePlayerEnabler(&network, &handler);
	LocalPlayerEnabler localPlayerEnabler(&network, &remotePlayerEnabler, &handler, &localPlayer, &remotePlayer);
	HandShakingFSM hsFSM(&network, localPlayerName);
	MainFSM mainFSM(&hsFSM, &network, &handler, &localPlayerEnabler, &remotePlayerEnabler);
	AllegroGUI GUI;

	GutenbergsPressAllegro printer(NULL);
	BoardController boardCont(&handler, &printer);
	createButtons(&printer, &handler, &localPlayer, &mainFSM, &GUI,&globalBoard);	// Also adds them to the GUI.
	GUI.attachController("BoarController", &boardCont);
	GUI.initGUIEnabler();

	LocalObserver localObs(&handler, &printer, &localPlayer, &localPlayerEnabler);
	localPlayer.attach(&localObs);
	localPlayer.attach(&boardCont);													// localObs and boardCont are observers of localPlayer.
	remotePlayer.attach(&localObs);
	remotePlayer.attach(&boardCont);												// localObs and boardCont are observers of remotePlayer.
	globalBoard.attach(&localObs);
	globalBoard.attach(&boardCont);													// localObs and boardCont are observers of globalBoard.
	remotePlayerEnabler.attach(&localObs);
	remotePlayerEnabler.attach(&boardCont);											// localObs and boardCont are observers of remotePlayerEnabler.
	localPlayerEnabler.attach(&localObs);
	localPlayerEnabler.attach(&boardCont);											// localObs and boardCont are observers of localPlayerEnabler.
	mainFSM.attach(&localObs);
	mainFSM.attach(&boardCont);														// localObs and boardCont are observers of mainFSM.

	while (!mainFSM.isQuit() && !GUI.displayWasClosed())
	{
		GenericEvent* ev = handler.getNextEvent();
		mainFSM.cycle(ev);
		GUI.cycle();
		network.workPlease();
	}
}


void createButtons(GutenbergsPressAllegro* printer, EventsHandler * handler,Player * localPlayer, MainFSM* mainFSM, AllegroGUI* GUI, Board * tablero)
{
	std::vector<Button*> buttonList;

	buttonList.push_back(new Button(printer, handler, START_PLAYING_X, START_PLAYING_Y, START_PLAYING_H, START_PLAYING_W, "Start Playing", "", "", 14)); //startPlayingButton()
	GUI->attachController("StartPlaying", buttonList[0]);
	buttonList.push_back(new Button(printer, handler, QUIT_X, QUIT_Y, QUIT_H, QUIT_W, "QUIT", "", "", 14));//quitButton()
	GUI->attachController("Quit", buttonList[1]);
	buttonList.push_back(new Button(printer, handler, NEW_SETTLEMENT_X, NEW_SETTLEMENT_Y, NEW_SETTLEMENT_H, NEW_SETTLEMENT_W, "", "settlement.png", "", 0));//newSettlementButton
	GUI->attachController("NewSettlement", buttonList[2]);
	buttonList.push_back(new Button(printer, handler, NEW_CITY_X, NEW_CITY_Y, NEW_CITY_H, NEW_CITY_W, "", "CITY.png", "", 0));//newCityButton
	GUI->attachController("NewCity", buttonList[3]);
	buttonList.push_back(new Button(printer, handler, NEW_ROAD_X, NEW_ROAD_Y, NEW_ROAD_H, NEW_ROAD_W, "", "ROAD.png", "", 0));//newRoadButton
	GUI->attachController("NewRoad", buttonList[4]);
	buttonList.push_back(new Button(printer, handler, BUY_DEV_CARD_X, BUY_DEV_CARD_Y, BUY_DEV_CARD_H, BUY_DEV_CARD_W, "", "BUY_DEV_CARD.png", "", 0));//getDevCardButton
	GUI->attachController("GetDevCard", buttonList[5]);
	buttonList.push_back(new Button(printer, handler, PASS_X, PASS_Y, PASS_H, PASS_W, "", "PASS.png", "", 0));//endTurnButton
	GUI->attachController("EndTurn", buttonList[6]);
	buttonList.push_back(new Button(printer, handler, NEW_BANK_TRADE_X, NEW_BANK_TRADE_Y, NEW_BANK_TRADE_H, NEW_BANK_TRADE_W, "Bank Trade", "", "catanFont.otf", 14));//bankTradeButton
	GUI->attachController("BankTrade", buttonList[7]);
	buttonList.push_back(new Button(printer, handler, NEW_OFFER_TRADE_X, NEW_OFFER_TRADE_Y, NEW_OFFER_TRADE_H, NEW_OFFER_TRADE_W, "Offer Trade", "", "catanFont.otf", 14));//offerTradeButton
	GUI->attachController("OfferTrade", buttonList[8]);
	buttonList.push_back(new Button(printer, handler, THROW_DICE_X, THROW_DICE_Y, THROW_DICE_H, THROW_DICE_W, "Dice", "dice.png", "catanFont.otf", 14));//throwDicesButton
	GUI->attachController("ThrowDices", buttonList[9]);
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//useKnightButtton
	GUI->attachController("UseKnight", buttonList[10]);
	buttonList.push_back(new Button(printer, handler, USE_ROAD_BUILDING_X, USE_ROAD_BUILDING_Y, USE_ROAD_BUILDING_H, USE_ROAD_BUILDING_W, "", "ROAD_BUILDING.png", "catanFont.otf", 14));//useRoadBuildingButton
	GUI->attachController("UseRoadBuilding", buttonList[11]);
	buttonList.push_back(new Button(printer, handler, USE_MONOPOLY_X, USE_MONOPOLY_Y, USE_MONOPOLY_H, USE_MONOPOLY_W, "", "MONOPOLY.png", "catanFont.otf", 14));//useMonopolyButton
	GUI->attachController("UseMonopoly", buttonList[12]);
	buttonList.push_back(new Button(printer, handler, USE_YEARS_OF_PLENTY_X, USE_YEARS_OF_PLENTY_Y, USE_YEARS_OF_PLENTY_H, USE_YEARS_OF_PLENTY_W, "", "YEARS_OF_PLENTY.png", "catanFont.otf", 14));//useYearsOfPlentyButton
	GUI->attachController("UseYearsOfPlenty", buttonList[13]);
	buttonList.push_back(new Button(printer, handler, SELECT_4x1_X, SELECT_4x1_Y, SELECT_4x1_H, SELECT_4x1_W, "", "SELECT_4x1.png", "", 14));//port4x1Button
	GUI->attachController("Port4x1", buttonList[14]);
	buttonList.push_back(new Button(printer, handler, SELECT_3x1_X, SELECT_3x1_Y, SELECT_3x1_H, SELECT_3x1_W, "", "SELECT_3x1.png", "", 14));//port3x1Button
	GUI->attachController("Port3x1", buttonList[15]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Mx1_X, SELECT_2Mx1_Y, SELECT_2Mx1_H, SELECT_2Mx1_W, "", "SELECT_2Mx1.png", "", 14));//port2Mx1Button
	GUI->attachController("Port2Mx1", buttonList[16]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Tx1_X, SELECT_2Tx1_Y, SELECT_2Tx1_H, SELECT_2Tx1_W, "", "SELECT_2Tx1.png", "", 14));//port2Tx1Button
	GUI->attachController("Port2Tx1", buttonList[17]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Lx1_X, SELECT_2Lx1_Y, SELECT_2Lx1_H, SELECT_2Lx1_W, "", "SELECT_2Lx1.png", "", 14));//port2Lx1Button
	GUI->attachController("Port2Lx1", buttonList[18]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Ox1_X, SELECT_2Ox1_Y, SELECT_2Ox1_H, SELECT_2Ox1_W, "", "SELECT_2Ox1.png", "", 14));//port2Ox1Button
	GUI->attachController("Port2Ox1", buttonList[19]);
	buttonList.push_back(new Button(printer, handler, SELECT_2Px1_X, SELECT_2Px1_Y, SELECT_2Px1_H, SELECT_2Px1_W, "", "SELECT_2Px1.png", "", 14));//port2Px1Button
	GUI->attachController("Port2Px1", buttonList[20]);
	buttonList.push_back(new Button(printer, handler, SELECT_BRICK_X, SELECT_BRICK_Y, SELECT_BRICK_H, SELECT_BRICK_W, "", "SELECT_BRICK.png", "catanFont.otf", 14));//brickButton
	GUI->attachController("Brick", buttonList[21]);
	buttonList.push_back(new Button(printer, handler, SELECT_LUMBER_X, SELECT_LUMBER_Y, SELECT_LUMBER_H, SELECT_LUMBER_W, "", " SELECT_LUMBER.png", "catanFont.otf", 14));//lumberButton
	GUI->attachController("Lumber", buttonList[22]);
	buttonList.push_back(new Button(printer, handler, SELECT_ORE_X, SELECT_ORE_Y, SELECT_ORE_H, SELECT_ORE_W, "", "SELECT_ORE.png", "catanFont.otf", 14));//oreButton
	GUI->attachController("Ore", buttonList[23]);
	buttonList.push_back(new Button(printer, handler, SELECT_GRAIN_X, SELECT_GRAIN_Y, SELECT_GRAIN_H, SELECT_GRAIN_W, "", "SELECT_GRAIN.png", "catanFont.otf", 14));//grainButton
	GUI->attachController("Grain", buttonList[24]);
	buttonList.push_back(new Button(printer, handler, SELECT_WOOL_X, SELECT_WOOL_Y, SELECT_WOOL_H, SELECT_WOOL_W, "", "SELECT_WOOL.png", "catanFont.otf", 14));//woolButtton
	GUI->attachController("Wool", buttonList[25]);
	buttonList.push_back(new Button(printer, handler, ACCEPT_X, ACCEPT_Y, ACCEPT_H, ACCEPT_W, "", "tick.png", "", 0));//confirmButton
	GUI->attachController("Confirm", buttonList[26]);
	buttonList.push_back(new Button(printer, handler, CANCEL_X, CANCEL_Y, CANCEL_H, CANCEL_W, "", "cruz.png", "", 0));//cancelButton
	GUI->attachController("Cancel", buttonList[27]);
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//playAgainButton
	GUI->attachController("PlayAgain", buttonList[28]);
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//stopPlayinButton
	GUI->attachController("StopPlaying", buttonList[29]);

	//ahora le tengo que poner las funciones a cada botón
	for (auto a : buttonList)
	{
		a->disableMouseDown(); // por las dudas deshabilito todo
		a->disableMouseUp();
		a->disableTimer();
	}
	/****** attach to each button its routine to executte when is pressed *******/
	/******* verifiying if the main FSM is in an appropiate state and the button might be avaliable*********/
	buttonList[0]->addUtility(
		[&mainFSM,&handler]() 
		{
			if (mainFSM->getCurrState() == mainStates::StartMenu_S)
			{
				//emitir evento start
				//handler->enqueueEvent(new MainEvents(MainTypes::START_GAME));
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[1]->addUtility(
		[&mainFSM, &handler]()
		{
			if (mainFSM->getCurrState() == mainStates::StartMenu_S)
			{
				//emitir evento de quit
				//handler->enqueueEvent(new MainEvents(MainTypes::QUIT));
				return GUIEnablerEvent::QUIT;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	buttonList[2]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (localPlayer->checkCityResources() && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::NEW_CITY; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	buttonList[3]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (localPlayer->checkSettlementResources() && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::NEW_SETTLEMENT; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[4]->addUtility(
		[&localPlayer , &mainFSM ]()
		{
			if (localPlayer->checkRoadResources() && (mainFSM->getCurrState() == mainStates::LocalPlayer_S) )
			{
				return GUIEnablerEvent::NEW_ROAD; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[5]->addUtility(
		[&localPlayer , &mainFSM ]()
		{
			if (localPlayer->checkResourcesForDevCard() && (mainFSM->getCurrState() == mainStates::LocalPlayer_S) )
			{
				return GUIEnablerEvent::BUY_DEV_CARD; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	buttonList[6]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
			{
				return GUIEnablerEvent::PASS;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	
	buttonList[7]->addUtility(
		[&localPlayer, &mainFSM]()
		{
			if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
			{
				return GUIEnablerEvent::BANK_TRADE;
			}
			return GUIEnablerEvent::NO_EV; 
		}
	);

	buttonList[8]->addUtility(
		[&localPlayer, &mainFSM]()
		{
			if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
			{
				return GUIEnablerEvent::OFFER_TRADE;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[9]->addUtility(
		[&localPlayer , &mainFSM ]()
		{
			if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
			{
				return GUIEnablerEvent::TRHOW_DICE;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[10]->addUtility(
		[&localPlayer ,&mainFSM]()
		{
			if (localPlayer->getDevCardAmount(DevCards::KNIGHT) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S) )
			{
				return GUIEnablerEvent::USE_KNIGHT; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[11]->addUtility(
		[&localPlayer, &mainFSM]()
		{
			if (localPlayer->getDevCardAmount(DevCards::ROAD_BUILDING) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S) )
			{
				return GUIEnablerEvent::USE_ROAD_BUILDING; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[12]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (localPlayer->getDevCardAmount(DevCards::MONOPOLY) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S) )
			{
				return GUIEnablerEvent::USE_MONOPOLY;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[13]->addUtility(
		[&localPlayer , &mainFSM ]()
		{
			if (localPlayer->getDevCardAmount(DevCards::YEARS_OF_PLENTY) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::USE_YOP; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[14]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() > 3) )
			{
				return GUIEnablerEvent::_4X1;
			}
			return GUIEnablerEvent::NO_EV; 
		}
	);

	buttonList[15]->addUtility(
		[&mainFSM, &localPlayer , &tablero]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 3) && (localPlayer->checkForAnyPort(tablero,PortType::_3x1)) )
			{
				return GUIEnablerEvent::_3X1;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[16]->addUtility(
		[&mainFSM, &localPlayer, &tablero]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Mx1)))
			{
				return GUIEnablerEvent::_2MX1;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[17]->addUtility(
		[&localPlayer, &mainFSM,&tablero]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Tx1)))
			{
				return GUIEnablerEvent::_2TX1;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[18]->addUtility(
		[&localPlayer, &mainFSM, &tablero]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Lx1)))
			{
				return GUIEnablerEvent::_2LX1;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[19]->addUtility(
		[&localPlayer , &mainFSM , &tablero]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Ox1)))
			{
				return GUIEnablerEvent::_2OX1;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[20]->addUtility(
		[&localPlayer, &mainFSM , &tablero ]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalPlayer_S) && (localPlayer->totalResourcesAmount() >= 2) && (localPlayer->checkForAnyPort(tablero, PortType::_2Px1)))
			{
				return GUIEnablerEvent::_2PX1;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[21]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (localPlayer->getResourceAmount(ResourceType::COLINAS) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::RESOURCE; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[22]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (localPlayer->getResourceAmount(ResourceType::BOSQUE) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::RESOURCE;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[23]->addUtility(
		[&localPlayer , &mainFSM]()
		{
			if (localPlayer->getResourceAmount(ResourceType::MONTAÑAS) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::RESOURCE;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[24]->addUtility(
		[&localPlayer, &mainFSM]()
		{
			if (localPlayer->getResourceAmount(ResourceType::CAMPOS) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::RESOURCE;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[25]->addUtility(
		[&localPlayer, &mainFSM]()
		{
			if (localPlayer->getResourceAmount(ResourceType::PASTOS) && (mainFSM->getCurrState() == mainStates::LocalPlayer_S))
			{
				return GUIEnablerEvent::RESOURCE;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	
	buttonList[26]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::ACCEPT;
		}
	);

	buttonList[27]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::CANCEL; 
		}
	);

	buttonList[28]->addUtility(
		[&mainFSM]()
		{
		 //revisar si es en estos estados que aparecen estos botones
			if ((mainFSM->getCurrState() == mainStates::LocalGameOver_S) || (mainFSM->getCurrState() == mainStates::RemoteGameOver_S))
			{
				return GUIEnablerEvent::PLAY_AGAIN;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[29]->addUtility(
		[&mainFSM]()
		{
			if ((mainFSM->getCurrState() == mainStates::LocalGameOver_S) || (mainFSM->getCurrState() == mainStates::RemoteGameOver_S))
			{
				return GUIEnablerEvent::STOP_PLAYING;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	// all the action routines added 

	// Specifying how every button should update its movable type.

	buttonList[0]->addUpdate(

	);

	buttonList[1]->addUpdate(

	);

	buttonList[2]->addUpdate(

	);

	buttonList[3]->addUpdate(

	);

	buttonList[4]->addUpdate(

	);

	buttonList[5]->addUpdate(

	);

	buttonList[6]->addUpdate(

	);

	buttonList[7]->addUpdate(

	);

	buttonList[8]->addUpdate(

	);

	buttonList[9]->addUpdate(

	);

	buttonList[10]->addUpdate(

	);

	buttonList[11]->addUpdate(

	);

	buttonList[12]->addUpdate(

	);

	buttonList[13]->addUpdate(

	);

	buttonList[14]->addUpdate(

	);

	buttonList[15]->addUpdate(

	);

	buttonList[16]->addUpdate(

	);

	buttonList[17]->addUpdate(

	);

	buttonList[18]->addUpdate(

	);

	buttonList[19]->addUpdate(

	);

	buttonList[20]->addUpdate(

	);

	buttonList[21]->addUpdate(

	);

	buttonList[22]->addUpdate(

	);

	buttonList[23]->addUpdate(

	);

	buttonList[24]->addUpdate(

	);

	buttonList[25]->addUpdate(

	);

	buttonList[26]->addUpdate(

	);

	buttonList[27]->addUpdate(

	);

	buttonList[28]->addUpdate(

	);

	buttonList[29]->addUpdate(

	);
}