#include "Enabler.h"
#include <functional>


Enabler::Enabler()
{
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
			for (auto action : enabledActions.enablerMap[ev->getSubtype()])
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
		delete ev;
	}
}

GenericEvent * Enabler::getEvent()
{
	return enablerEvent;
}

void Enabler::enable(EventSubtypes subtype, list< EnablerRoutine > routine)
{
	enabledActions.enablerMap[subtype] = routine;
}

void Enabler::disable(EventSubtypes subtype)
{
	enabledActions.enablerMap.erase(subtype);
}

void Enabler::disableAll()
{
	enabledActions.enablerMap.clear();
}

void Enabler::setDefaultRoutine(EnablerRoutine defaultRoutine_)
{
	enabledActions.defaultRoutine = defaultRoutine_;
}
