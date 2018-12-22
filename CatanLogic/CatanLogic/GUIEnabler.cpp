#include "GUIEnabler.h"
#include <functional>
#include <algorithm>


GUIEnabler::GUIEnabler()
{
}


GUIEnabler::~GUIEnabler()
{
}

void GUIEnabler::cycle(GUIEnablerEvent ev)
{
		if (enabledActions.enablerMap.count(ev))
		{
			for (auto action : enabledActions.enablerMap[ev])
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
}

void GUIEnabler::enable(EventSubtypes subtype, list<EnablerRoutine> routine)
{
	enabledActions.enablerMap[subtype] = routine;
}

void GUIEnabler::disable(EventSubtypes subtype)
{
	if (enabledActions.enablerMap.find(subtype) != enabledActions.enablerMap.end())
	{
		enabledActions.enablerMap.erase(subtype);
	}
}

void GUIEnabler::disableAll()
{
	enabledActions.enablerMap.clear();
}

void GUIEnabler::disableAllBut(list<EventSubtypes> thisEvents)
{
	for (auto ev : enabledActions.enablerMap)
	{
		if (find(thisEvents.begin(), thisEvents.end(), ev.first) == thisEvents.end())		// If it's not in the but list.
		{
			disable(ev.first);
		}
	}
}

void GUIEnabler::setDefaultRoutine(EnablerRoutine defaultRoutine_)
{
	enabledActions.defaultRoutine = defaultRoutine_;
}
