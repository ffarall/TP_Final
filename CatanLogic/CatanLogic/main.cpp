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
#include "SubEvents.h"
#include "TimerController.h"

void createButtons(GutenbergsPressAllegro* printer, EventsHandler * evH,Player * jugador, MainFSM* mainFSM, AllegroGUI* GUI, Board * tablero, std::vector<Button*> &buttonList, RemotePlayerEnabler * remEneb, LocalPlayerEnabler * locEneb);


int main(int argc, char* argv[])
{
	std::string localPlayerName(argv[1]);
	Player localPlayer(localPlayerName);
	Player remotePlayer;
	Board globalBoard;
	EventsHandler handler;
	Networking network(&handler, argv[2]);
	RemotePlayerEnabler remotePlayerEnabler(&network, &handler);
	LocalPlayerEnabler localPlayerEnabler(&network, &remotePlayerEnabler, &handler, &localPlayer, &remotePlayer);
	HandShakingFSM hsFSM(&network, localPlayerName, &globalBoard, &handler);
	MainFSM mainFSM(&hsFSM, &network, &handler, &localPlayerEnabler, &remotePlayerEnabler,&globalBoard);
	AllegroGUI GUI;
	GutenbergsPressAllegro printer(NULL);
	BoardController boardCont(&handler, &printer, &mainFSM, &globalBoard, &localPlayerEnabler);
	TimerController timerCont(&handler);
	
	std::vector<Button*> buttonList;
	createButtons(&printer, &handler, &localPlayer, &mainFSM, &GUI,&globalBoard, buttonList, &remotePlayerEnabler, &localPlayerEnabler);	// Also adds them to the GUI.
	GUI.attachController("BoardController", &boardCont);
	GUI.attachController("TimerController", &timerCont);
	GUI.initGUIEnabler();

	LocalObserver localObs(&printer, &localPlayer, &localPlayerEnabler, &mainFSM);

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

	mainFSM.notifyAllObservers();
	while (!mainFSM.isQuit() && !GUI.displayWasClosed())
	{
		GUI.cycle();
		network.workPlease();
		if (handler.isEvent())
		{
			GenericEvent* ev = handler.getNextEvent();
			mainFSM.cycle(ev);
			delete ev;
		}
	}
}


