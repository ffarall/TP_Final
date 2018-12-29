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
	

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	bool allegroError;



};
