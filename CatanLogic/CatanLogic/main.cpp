#include<iostream>
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

void createButtons(std::list<Button*>& buttonList);


int main(int argc, char* argv[])
{
	std::string localPlayerName(argv[1]);
	Player localPlayer(localPlayerName);
	Player remotePlayer;
	Networking network;
	EventsHandler handler;
	RemotePlayerEnabler remotePlayerEnabler(&network, &handler);
	LocalPlayerEnabler localPlayerEnabler(&network, &remotePlayerEnabler, &handler, &localPlayer, &remotePlayer);
	HandShakingFSM hsFSM(&network,localPlayerName);
	MainFSM mainFSM (&hsFSM,&network,&handler,&localPlayerEnabler,&remotePlayerEnabler);
	AllegroGUI GUI;


	std::list<Button*> buttonList;
	createButtons(buttonList);

	//faltan observers


	while (!mainFSM.isQuit() && !GUI.displayWasClosed())
	{
		GenericEvent* ev = handler.getNextEvent();
		mainFSM.cycle(ev);
		GUI.cycle();
		network.workPlease();
	}
}


void createButtons(std::list<Button*>& buttonList)
{
	buttonList.push_back(new Button startPlayingButton());
	buttonList.push_back(new Button quitButton());
	buttonList.push_back(new Button newSettlementButton());
	buttonList.push_back(new Button newCityButton()); 
	buttonList.push_back(new Button newRoadButton());
	buttonList.push_back(new Button getDevCardButton());
	buttonList.push_back(new Button endTurnButton());
	buttonList.push_back(new Button bankTradeButton());
	buttonList.push_back(new Button offerTradeButton());
	buttonList.push_back(new Button throwDicesButton());
	buttonList.push_back(new Button useKnightButtton());
	buttonList.push_back(new Button useRoadBuildingButton());
	buttonList.push_back(new Button useMonopolyButton());
	buttonList.push_back(new Button useYearsOfPlentyButton());
	buttonList.push_back(new Button port4x1Button());
	buttonList.push_back(new Button port2x1Button());
	buttonList.push_back(new Button port3x1Button());
	buttonList.push_back(new Button brickButton());
	buttonList.push_back(new Button lumberButton());
	buttonList.push_back(new Button oreButton());
	buttonList.push_back(new Button grainButton());
	buttonList.push_back(new Button woolButtton());
	buttonList.push_back(new Button confirmButton());
	buttonList.push_back(new Button cancelButton());
	buttonList.push_back(new Button playAgainButton());
	buttonList.push_back(new Button stopPlayinButton());


}