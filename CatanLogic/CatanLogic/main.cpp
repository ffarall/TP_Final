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
#include "LocalController.h"
#include "BoardController.h"
#include "GutenbergsPressAllegro.h"

void createButtons(GutenbergsPressAllegro* printer, std::vector<Button*>& buttonListn, EventsHandler * evH,Player * jugador, MainFSM* mainFSM);


int main(int argc, char* argv[])
{
	std::string localPlayerName(argv[1]);
	Player localPlayer(localPlayerName);
	Player remotePlayer;
	Networking network;
	EventsHandler handler;
	RemotePlayerEnabler remotePlayerEnabler(&network, &handler);
	LocalPlayerEnabler localPlayerEnabler(&network, &remotePlayerEnabler, &handler, &localPlayer, &remotePlayer);
	HandShakingFSM hsFSM(&network, localPlayerName);
	MainFSM mainFSM(&hsFSM, &network, &handler, &localPlayerEnabler, &remotePlayerEnabler);
	AllegroGUI GUI;

	GutenbergsPressAllegro printer(NULL);
	LocalController localCont(&handler, &printer, &localPlayer, &localPlayerEnabler);
	BoardController boarCont(&handler, &printer);

	std::vector<Button*> buttonList;
	
	createButtons(&printer,buttonList,&handler,&localPlayer,&mainFSM);

	//faltan observers


	while (!mainFSM.isQuit() && !GUI.displayWasClosed())
	{
		GenericEvent* ev = handler.getNextEvent();
		mainFSM.cycle(ev);
		GUI.cycle();
		network.workPlease();
	}
}


void createButtons(GutenbergsPressAllegro* printer, std::vector<Button*>& buttonList, EventsHandler * handler,Player * localPlayer, MainFSM* mainFSM)
{
	buttonList.push_back(new Button(printer, handler, START_PLAYING_X, START_PLAYING_Y, START_PLAYING_H, START_PLAYING_W, "Start Playing", "", "", 14)); //startPlayingButton()
	buttonList.push_back(new Button(printer, handler, QUIT_X, QUIT_Y, QUIT_H, QUIT_W, "QUIT", "", "", 14));//quitButton()
	buttonList.push_back(new Button(printer, handler, NEW_SETTLEMENT_X, NEW_SETTLEMENT_Y, NEW_SETTLEMENT_H, NEW_SETTLEMENT_W, "", "settlement.png", "", 0));//newSettlementButton
	buttonList.push_back(new Button(printer, handler, NEW_CITY_X, NEW_CITY_Y, NEW_CITY_H, NEW_CITY_W, "", "CITY.png", "", 0));//newCityButton
	buttonList.push_back(new Button(printer, handler, NEW_ROAD_X, NEW_ROAD_Y, NEW_ROAD_H, NEW_ROAD_W, "", "ROAD.png", "", 0));//newRoadButton
	buttonList.push_back(new Button(printer, handler, BUY_DEV_CARD_X, BUY_DEV_CARD_Y, BUY_DEV_CARD_H, BUY_DEV_CARD_W, "", "BUY_DEV_CARD.png", "", 0));//getDevCardButton
	buttonList.push_back(new Button(printer, handler, PASS_X, PASS_Y, PASS_H, PASS_W, "", "PASS.png", "", 0));//endTurnButton
	buttonList.push_back(new Button(printer, handler, NEW_BANK_TRADE_X, NEW_BANK_TRADE_Y, NEW_BANK_TRADE_H, NEW_BANK_TRADE_W, "Bank Trade", "", "catanFont.otf", 14));//bankTradeButton
	buttonList.push_back(new Button(printer, handler, NEW_OFFER_TRADE_X, NEW_OFFER_TRADE_Y, NEW_OFFER_TRADE_H, NEW_OFFER_TRADE_W, "Offer Trade", "", "catanFont.otf", 14));//offerTradeButton
	buttonList.push_back(new Button(printer, handler, THROW_DICE_X, THROW_DICE_Y, THROW_DICE_H, THROW_DICE_W, "Dice", "dice.png", "catanFont.otf", 14));//throwDicesButton
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//useKnightButtton
	buttonList.push_back(new Button(printer, handler, USE_ROAD_BUILDING_X, USE_ROAD_BUILDING_Y, USE_ROAD_BUILDING_H, USE_ROAD_BUILDING_W, "", "ROAD_BUILDING.png", "catanFont.otf", 14));//useRoadBuildingButton
	buttonList.push_back(new Button(printer, handler, USE_MONOPOLY_X, USE_MONOPOLY_Y, USE_MONOPOLY_H, USE_MONOPOLY_W, "", "MONOPOLY.png", "catanFont.otf", 14));//useMonopolyButton
	buttonList.push_back(new Button(printer, handler, USE_YEARS_OF_PLENTY_X, USE_YEARS_OF_PLENTY_Y, USE_YEARS_OF_PLENTY_H, USE_YEARS_OF_PLENTY_W, "", "YEARS_OF_PLENTY.png", "catanFont.otf", 14));//useYearsOfPlentyButton
	buttonList.push_back(new Button(printer, handler, SELECT_4x1_X, SELECT_4x1_Y, SELECT_4x1_H, SELECT_4x1_W, "", "SELECT_4x1.png", "", 14));//port4x1Button
	buttonList.push_back(new Button(printer, handler, SELECT_3x1_X, SELECT_3x1_Y, SELECT_3x1_H, SELECT_3x1_W, "", "SELECT_3x1.png", "", 14));//port3x1Button
	buttonList.push_back(new Button(printer, handler, SELECT_2Mx1_X, SELECT_2Mx1_Y, SELECT_2Mx1_H, SELECT_2Mx1_W, "", "SELECT_2Mx1.png", "", 14));//port2Mx1Button
	buttonList.push_back(new Button(printer, handler, SELECT_2Tx1_X, SELECT_2Tx1_Y, SELECT_2Tx1_H, SELECT_2Tx1_W, "", "SELECT_2Tx1.png", "", 14));//port2Tx1Button
	buttonList.push_back(new Button(printer, handler, SELECT_2Lx1_X, SELECT_2Lx1_Y, SELECT_2Lx1_H, SELECT_2Lx1_W, "", "SELECT_2Lx1.png", "", 14));//port2Lx1Button
	buttonList.push_back(new Button(printer, handler, SELECT_2Ox1_X, SELECT_2Ox1_Y, SELECT_2Ox1_H, SELECT_2Ox1_W, "", "SELECT_2Ox1.png", "", 14));//port2Ox1Button
	buttonList.push_back(new Button(printer, handler, SELECT_2Px1_X, SELECT_2Px1_Y, SELECT_2Px1_H, SELECT_2Px1_W, "", "SELECT_2Px1.png", "", 14));//port2Px1Button
	buttonList.push_back(new Button(printer, handler, SELECT_BRICK_X, SELECT_BRICK_Y, SELECT_BRICK_H, SELECT_BRICK_W, "", "SELECT_BRICK.png", "catanFont.otf", 14));//brickButton
	buttonList.push_back(new Button(printer, handler, SELECT_LUMBER_X, SELECT_LUMBER_Y, SELECT_LUMBER_H, SELECT_LUMBER_W, "", " SELECT_LUMBER.png", "catanFont.otf", 14));//lumberButton
	buttonList.push_back(new Button(printer, handler, SELECT_ORE_X, SELECT_ORE_Y, SELECT_ORE_H, SELECT_ORE_W, "", "SELECT_ORE.png", "catanFont.otf", 14));//oreButton
	buttonList.push_back(new Button(printer, handler, SELECT_GRAIN_X, SELECT_GRAIN_Y, SELECT_GRAIN_H, SELECT_GRAIN_W, "", "SELECT_GRAIN.png", "catanFont.otf", 14));//grainButton
	buttonList.push_back(new Button(printer, handler, SELECT_WOOL_X, SELECT_WOOL_Y, SELECT_WOOL_H, SELECT_WOOL_W, "", "SELECT_WOOL.png", "catanFont.otf", 14));//woolButtton
	buttonList.push_back(new Button(printer, handler, ACCEPT_X, ACCEPT_Y, ACCEPT_H, ACCEPT_W, "", "tick.png", "", 0));//confirmButton
	buttonList.push_back(new Button(printer, handler, CANCEL_X, CANCEL_Y, CANCEL_H, CANCEL_W, "", "cruz.png", "", 0));//cancelButton
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//playAgainButton
	buttonList.push_back(new Button(printer, handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14));//stopPlayinButton
	
	//ahora le tengo que poner las funciones a cada boton
	for (auto a : buttonList)
	{
		a->disableMouseDown(); // por las dudas deshabilito todo
		a->disableMouseUp();
		a->disableTimer();
	}

	buttonList[0]->addUtility([]() {
		return GUIEnablerEvent::NO_EV;
		//emitir evento start
	});

	buttonList[1]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::QUIT;
			//emitir evento quit
		}
	);
	buttonList[2]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->checkCityResources())
			{
				return GUIEnablerEvent::NEW_CITY; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	buttonList[3]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->checkSettlementResources())
			{
				return GUIEnablerEvent::NEW_SETTLEMENT; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[4]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->checkRoadResources())
			{
				return GUIEnablerEvent::NEW_ROAD; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[5]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->checkResourcesForDevCard())
			{
				return GUIEnablerEvent::BUY_DEV_CARD; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);
	buttonList[6]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::PASS; 
		}
	);
	
	buttonList[7]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::BANK_TRADE; 
		}
	);

	buttonList[8]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::OFFER_TRADE; 
		}
	);

	buttonList[9]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::TRHOW_DICE; 
		}
	);

	buttonList[10]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getDevCardAmount(DevCards::KNIGHT))
			{
				return GUIEnablerEvent::USE_KNIGHT; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[11]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getDevCardAmount(DevCards::ROAD_BUILDING))
			{
				return GUIEnablerEvent::USE_ROAD_BUILDING; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[12]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getDevCardAmount(DevCards::MONOPOLY))
			{
				return GUIEnablerEvent::USE_MONOPOLY;
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[13]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getDevCardAmount(DevCards::YEARS_OF_PLENTY))
			{
				return GUIEnablerEvent::USE_YOP; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[14]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_4X1; 
		}
	);

	buttonList[15]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_3X1;
		}
	);

	buttonList[16]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_2MX1; 
		}
	);

	buttonList[17]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_2TX1; 
		}
	);

	buttonList[18]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_2LX1;
		}
	);

	buttonList[19]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_2OX1;
		}
	);

	buttonList[20]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::_2PX1; 
		}
	);

	buttonList[21]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getResourceAmount(ResourceType::COLINAS))
			{
				return GUIEnablerEvent::BRICK; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[22]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getResourceAmount(ResourceType::BOSQUE))
			{
				return GUIEnablerEvent::LUMBER; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[23]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getResourceAmount(ResourceType::MONTAÑAS))
			{
				return GUIEnablerEvent::ORE; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[24]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getResourceAmount(ResourceType::CAMPOS))
			{
				return GUIEnablerEvent::GRAIN; 
			}
			return GUIEnablerEvent::NO_EV;
		}
	);

	buttonList[25]->addUtility(
		[&localPlayer]()
		{
			if (localPlayer->getResourceAmount(ResourceType::PASTOS))
			{
				return GUIEnablerEvent::WOOL; 
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
		[&localPlayer]()
		{
			return GUIEnablerEvent::PLAY_AGAING; 
		}
	);

	buttonList[29]->addUtility(
		[&localPlayer]()
		{
			return GUIEnablerEvent::STOP_PLAYING; 
	);
}