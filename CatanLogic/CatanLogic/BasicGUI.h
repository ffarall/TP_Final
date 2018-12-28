#pragma once
#include <list>
#include <map>
#include <cstdint>
#include "NewEventHandling.h"
#include "GUIEnabler.h"
#include "package.h"

using namespace std;

enum GUIEventTypes { GUI_TIMER, GUI_MOUSE };

class BasicController :
	public EventGenerator
{
public:
	BasicController();
	BasicController(EventsHandler* handler_);
	virtual  ~BasicController();
	virtual GUIEnablerEvent parseMouseEvent(uint32_t x, uint32_t y) = 0;
	virtual GUIEnablerEvent parseTimerEvent() = 0;
	
	void enableMouse();
	void disableMouse();
	void enableTimer();
	void disableTimer();

	bool isMouseActive();
	bool isTimerActive();

protected:
	// Determines whether this controller has to be paying attention to mouse events.
	bool mouseActivated;
	// Determines whether this controller has to be paying attention to timer events.
	bool timerActivated;

	// Auxiliary functions for emitting event.
	void emitEvent(EventTypes type);
	void emitSubEvent(EventTypes type, EventSubtypes subtype, package * pkg);
};

class BasicGUI :
	public GUIEnabler
{
public:
	BasicGUI();
	virtual ~BasicGUI();
	// Returns true if there is an event and sets GUIEventTypes to the corresponding type.
	virtual bool checkForEvents() = 0;
	// If there's a new event for the GUIEnabler, it runs the GUIEnabler cycle, and then calls parseEvent().
	void virtual cycle();
	// Calls all of the controllers' parse function corresponding to the GUIEv type.
	void parseEvent();

	void attachController(BasicController* newController);

protected:
	list< BasicController* > controllers;
	GUIEnablerEvent enablerEv;
	GUIEventTypes GUIEv;
	pair< uint32_t, uint32_t > mouseCoordinates;
};
