#pragma once
#include"allegro5/allegro.h"
#include "BasicGUI.h"

class AllegroGUI :
	public BasicGUI
{
public:
	AllegroGUI();
	virtual bool checkForEvents();
	virtual ~AllegroGUI();

	// To be called after attaching all controllers.
	void initGUIEnabler();

private:
	bool allegroInit();
	bool initAddOn();
	bool initEventQueue();
	bool initDisplay();
	bool initTimer();
	void closeAdd();
	void closeDisplay();
	void closeEvents();
	void closeTimer();
	
	// Disables all controllers
	void disableAll();
	// Enables all controllers
	void enableAll();

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	bool allegroError;


	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct();
	// Enables Road selection for the BoardController after NewRoad has been clicked.
	void nowSelectRoad();
	// Enables Settlement selection for the BoardController after NewSettlement has been clicked.
	void nowSelectSettlement();
	// Enables City selection for the BoardController after NewCity has been clicked.
	void nowSelectCity();
	// Enables Robber movement selection for the BoardController after UseKnight has been clicked.
	void nowSelectRobberPos();

	// Gets called after user clicks on NewTrade.
	void nowSelectPortType();
	//
	void nowSelectResources();
	// Goes back to the way initGUIEnabler leaves everything.
	void backToNormal();
};