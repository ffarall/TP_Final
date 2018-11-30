#pragma once

//UNTOUCHED
#include <list>
#include <vector>
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

class SubtypeEvent : public GenericEvent
{
public:
	virtual EventSubtypes getSubtype() = 0;
	bool operator==(SubtypeEvent& ev) { return ((this->getType() == ev.getType()) && (this->getSubtype() == ev.getSubtype())); }
};

class EventsHandler
{
public:
	EventsHandler();
	virtual ~EventsHandler();
	GenericEvent * getNextEvent();
	virtual bool enqueueEvent(GenericEvent* ev, int priority = 0);			// By default, events go to first queue. Returns false when event priority > eventQueues.size() (Event couldn't be added)

private:
	std::vector< std::queue<GenericEvent *> >  eventQueues;
};

class EventGenerator
{
public:
	EventGenerator(EventsHandler * MainEventHandler = nullptr) { handler = MainEventHandler; }
	virtual ~EventGenerator() {}
	void attachHandler(EventsHandler * MainEventHandler) { handler = MainEventHandler; }
protected:
	EventsHandler* handler;
};