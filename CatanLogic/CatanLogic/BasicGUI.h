#pragma once
#include <list>
#include <map>
#include <cstdint>
#include "NewEventHandling.h"
#include "GUIEnabler.h"
#include "package.h"

using namespace std;

enum GUIEventTypes { GUI_TIMER, GUI_MOUSE_UP, GUI_MOUSE_DOWN, GUI_CLOSE_DISPLAY };

class BasicController :
	public Observer
{
public:
	BasicController();
	BasicController(EventsHandler* handler_);
	virtual  ~BasicController();
	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y) = 0;
	virtual GUIEnablerEvent parseMouseUpEvent(uint32_t x, uint32_t y) = 0;
	virtual GUIEnablerEvent parseTimerEvent() = 0;
	
	void enableMouseDown();
	void disableMouseDown();
	void enableMouseUp();
	void disableMouseUp();
	void enableTimer();
	void disableTimer();

	bool isMouseDownActive();
	bool isMouseUpActive();
	bool isTimerActive();

protected:
	// Determines whether this controller has to be paying attention to mouse down events.
	bool mouseDownActivated;
	// Determines whether this controller has to be paying attention to up down events.
	bool mouseUpActivated;
	// Determines whether this controller has to be paying attention to timer events.
	bool timerActivated;
	// For emitting events.
	EventGenerator* evGen;

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
