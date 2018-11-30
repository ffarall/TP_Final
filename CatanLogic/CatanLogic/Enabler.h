#pragma once
#include <iostream>
#include <map>
#include <list>
#include "NewEventHandling.h"
#include "EDASubject.h"

class Enabler;
using namespace std;
using EventTypes = unsigned int;
using EventSubtypes = unsigned int;
using EnablerRoutine = void (Enabler::*)(SubtypeEvent*);
struct EnablerLogic
{
	map< EventSubtypes, list< EnablerRoutine > > enablerMap;
	EnablerRoutine defaultRoutine;
};

// Framework
class Enabler :
	public EDASubject
{
public:
	Enabler();
	Enabler(EventsHandler* handler_);
	virtual ~Enabler();

	// To be called when new event arrives.
	void cycle(SubtypeEvent* ev);
	// Event getter.
	GenericEvent * getEvent();
	// Sets new handler.
	void setHandler(EventsHandler* handler_);

protected:
	// Map containing all enabled events and its actions.
	EnablerLogic enabledActions;
	// Current event.
	GenericEvent * enablerEvent = nullptr;

	// To enable an event and its action.
	void enable(EventSubtypes subtype, list< EnablerRoutine > routine);
	// To disable an event.
	void disable(EventSubtypes subtype);
	// Disables all events.
	void disableAll();
	// Sets default routine.
	void setDefaultRoutine(EnablerRoutine defaultRoutine_);

	EventsHandler* handler;
};

