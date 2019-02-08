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
	void enableAll();

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	bool allegroError;


	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(GUIEnablerEvent ev);
};
