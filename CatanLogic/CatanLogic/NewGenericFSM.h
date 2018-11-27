#pragma once
#include "NewEventHandling.h"
#include<map>

class genericFSM;
using StateTypes = unsigned int;

struct FsmCell
{
	StateTypes nextState;
	void (genericFSM::*action)(genericEvent *);
};

struct StateMap
{
	std::map< eventTypes, FsmCell > acceptedEventsMap;		// Every state has a map of accepted events with their corresponding FsmCells.
	FsmCell defaultCell;									// And a cell that contains the information of what to do when the event that arrived is not in the current state's map.
};

using FsmMap = std::map< StateTypes, StateMap >;





class genericFSM : public eventGenerator
{
public:

	genericFSM( const FsmMap fsmMap_, StateTypes initState);
	genericEvent * getEvent();
	void cycle(genericEvent * ev);

private:
	StateTypes state;
	genericEvent * fsmEvent = nullptr;

	
	FsmMap fsmMap;
};
