#include "NewEventHandling.h"

using namespace std;

EventsHandler::EventsHandler()
{
	eventQueues.push_back(queue<GenericEvent *>({  }));			// Initialising at least one empty queue.

}

EventsHandler::~EventsHandler()
{
}

GenericEvent * EventsHandler::getNextEvent()
{
	int i = 0;
	while (eventQueues[i].empty() && (i < eventQueues.size()))				// Lower index queues have higher priority.
	{																		// Method returns first event in higher priority queue that is not empty.
		i++;
	}

	GenericEvent* ret = eventQueues[i].front();
	eventQueues[i].pop();
}

bool EventsHandler::enqueueEvent(GenericEvent* ev, int priority)
{
	if (priority < eventQueues.size())										// If this priority order exists already...
	{
		eventQueues[priority].push(ev);
		return true;
	}
	else if (priority == eventQueues.size())								// User can ask to add a priority this way.				
	{
		eventQueues.push_back(queue<GenericEvent *>({ ev }));
		return true;
	}
	else
	{
		return false;
	}
}
