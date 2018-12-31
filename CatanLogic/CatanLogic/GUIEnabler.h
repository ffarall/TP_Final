#pragma once
#include <iostream>
#include <map>
#include <list>


enum GUIEnablerEvent { NO_EV, POSITION_SELECTED };

class GUIEnabler;
using namespace std;
using EventTypes = unsigned int;
using EventSubtypes = unsigned int;
using EnablerRoutine = void (GUIEnabler::*)(GUIEnablerEvent);
struct EnablerLogic
{
	map< EventSubtypes, list< EnablerRoutine > > enablerMap;
	EnablerRoutine defaultRoutine;
};


class GUIEnabler
{
public:
	GUIEnabler();
	virtual ~GUIEnabler();

	// To be called when new event arrives.
	void virtual cycle(GUIEnablerEvent ev);

protected:
	// Map containing all enabled events and its actions.
	EnablerLogic enabledActions;

	// To enable an event and its action.
	void enable(EventSubtypes subtype, list< EnablerRoutine > routine);
	// To disable an event.
	void disable(EventSubtypes subtype);
	// Disables all events.
	void disableAll();
	// Disables all events but the ones passed through the list;
	void disableAllBut(list<EventSubtypes> thisEvents);
	// Sets default routine.
	void setDefaultRoutine(EnablerRoutine defaultRoutine_);
};

