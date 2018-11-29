#include "NewEventHandling.h"

using namespace std;

GenericEvent * EventsHandler::getNextEvent()
{
	GenericEvent* ret = eventQueue.front();
	eventQueue.pop();
	return ret;
}

void EventsHandler::enqueueEvent(GenericEvent* ev)
{
	eventQueue.push(ev);
}
