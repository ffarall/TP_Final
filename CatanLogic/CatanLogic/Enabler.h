#pragma once
#include <iostream>
#include <map>
#include <list>
#include "NewEventHandling.h"

class Enabler;
using namespace std;
using EventTypes = unsigned int;
using EventSubtypes = unsigned int;
using EnablerRoutine = void (Enabler::*)(GenericEvent*);
using EnablerMap = map< EventTypes, map< EventSubtypes, list< EnablerRoutine > > >;

class Enabler
{
public:
	Enabler();
	virtual ~Enabler();

	// To be called when new event arrives.
	void cycle(GenericEvent* ev);
	// Event getter.
	GenericEvent * getEvent();

private:
	// Map containing all enabled events and its actions.
	EnablerMap enabledActions;
	// Current event.
	GenericEvent * enablerEvent = nullptr;
	
	// To enable an event and its action.
	void enable(EventTypes type, EventSubtypes subtype, EnablerRoutine routine);
	// To disable an event.
	void disable(EventTypes type, EventSubtypes subtype);
};

