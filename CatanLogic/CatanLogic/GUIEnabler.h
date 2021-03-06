#pragma once
#include <iostream>
#include <map>
#include <list>


enum GUIEnablerEvent {
	NO_EV, POSITION_SELECTED, NEW_ROAD, NEW_CITY, NEW_SETTLEMENT, QUIT, BUY_DEV_CARD, PASS, BANK_TRADE,
	OFFER_TRADE, TRHOW_DICE, USE_KNIGHT, USE_ROAD_BUILDING, USE_MONOPOLY, USE_YOP,
	_4X1, _3X1, _2MX1, _2TX1, _2LX1, _2OX1, _2PX1,ROBBER_CARDS,
	RESOURCE,
	ACCEPT,CANCEL,PLAY_AGAIN,STOP_PLAYING
};

class GUIEnabler;
using namespace std;
using EventTypes = unsigned int;
using EventSubtypes = unsigned int;
using GUIEnablerRoutine = void (GUIEnabler::*)();
struct GUIEnablerLogic
{
	map< GUIEnablerEvent, list< GUIEnablerRoutine > > enablerMap;
	GUIEnablerRoutine defaultRoutine;
};


// This Enabler implementation will ease emitting events that require more than one action from the user,
// like making a trade, requires clicking the New Trade button as well as selecting which trade type to request
// and selecting the resources.
class GUIEnabler
{
public:
	GUIEnabler();
	virtual ~GUIEnabler();

	// To be called when new event arrives.
	void virtual cycle(GUIEnablerEvent ev);

protected:
	// Map containing all enabled events and its actions.
	GUIEnablerLogic enabledActions;

	// To enable an event and its action.
	void enable(GUIEnablerEvent type, list< GUIEnablerRoutine > routine);
	// To disable an event.
	void disable(GUIEnablerEvent type);
	// Disables all events.
	void disableAll();
	// Disables all events but the ones passed through the list;
	void disableAllBut(list<GUIEnablerEvent> theseEvents);
	// Sets default routine.
	void setDefaultRoutine(GUIEnablerRoutine defaultRoutine_);

};

