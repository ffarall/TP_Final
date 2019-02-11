#include "Enabler.h"
#include <functional>
#include <algorithm>


Enabler::Enabler()
{
}

Enabler::Enabler(EventsHandler * handler_)
{
	setHandler(handler_);
}


Enabler::~Enabler()
{
}

void Enabler::cycle(SubtypeEvent * ev)
{
	if (ev != nullptr)
	{
		if (enabledActions.enablerMap.count(ev->getSubtype()))
		{
			list< EnablerRoutine > copyList = enabledActions.enablerMap[ev->getSubtype()];
			for (auto action : copyList)
			{
				auto f = bind(action, this, ev);
				f();
			}
		}
		else
		{
			auto f = bind(enabledActions.defaultRoutine, this, ev);
			f();
		}

		notifyAllObservers();
		delete ev;
	}
}

GenericEvent * Enabler::getEvent()
{
	return enablerEvent;
}

void Enabler::setHandler(EventsHandler * handler_)
{
	handler = handler_;
}

void Enabler::enable(EventSubtypes subtype, list< EnablerRoutine > routine)
{
	enabledActions.enablerMap[subtype] = routine;
}

void Enabler::disable(EventSubtypes subtype)
{
	if (enabledActions.enablerMap.find(subtype) != enabledActions.enablerMap.end())
	{
		enabledActions.enablerMap.erase(subtype);
	}
}

void Enabler::disableAll()
{
	enabledActions.enablerMap.clear();
}

void Enabler::disableAllBut(list<EventSubtypes> theseEvents)
{
	for (auto ev : enabledActions.enablerMap)
	{
		if (find(theseEvents.begin(), theseEvents.end(), ev.first) == theseEvents.end())		// If it's not in the but list.
		{
			disable(ev.first);
		}
	}
}

void Enabler::setDefaultRoutine(EnablerRoutine defaultRoutine_)
{
	enabledActions.defaultRoutine = defaultRoutine_;
}
