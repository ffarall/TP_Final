#pragma once

//UNTOUCHED
#include <list>
#include <queue>

//enunm Forward Declaration
//it is feasible as long as the type is defined in the code.
using EventTypes = unsigned int;
using EventSubtypes = unsigned int;

class GenericEvent
{
public:
	virtual EventTypes getType() = 0;
	bool operator==(EventTypes ev) { return (this->getType() == ev); }		//Easy Compare an Event With its types.
	virtual bool const operator!() const { return  false; } 		        //This operator can be used to understand if the event is present or not. ie: No Event.
};

class SubtypeEvent : GenericEvent
{
	virtual EventSubtypes getSubtype() = 0;
	bool operator==(SubtypeEvent& ev) { return ((this->getType() == ev.getType()) && (this->getSubtype() == ev.getSubtype())); }
};

class EventGenerator
{
public:
	virtual GenericEvent * getEvent(void) = 0;					// Returns NULL if there's no new Event or a pointer to a concrete instance in the heap of a GenericEvent if there's a new event
																// User must then free this isntance.
};

class mainEventGenerator
{
public:
	GenericEvent * getNextEvent(void);
	void attach(EventGenerator * evg);
	void detach(EventGenerator * evg);

private:
	std::queue<GenericEvent *>  eventQueue; //It can also be a priority_queue if events have got some sort of priority
	std::list<EventGenerator *> generators; //It will contain all EventGenerators attached to the mainEventGenerator
};
