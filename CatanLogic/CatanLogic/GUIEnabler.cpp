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
		if (enabledActions.enablerMap.count(ev))						// Checking there is an action enabled for ev.
		{
			list< GUIEnablerRoutine > auxToIterate = enabledActions.enablerMap[ev];
			for (auto action : auxToIterate)
			{
				auto f = bind(action, this);
				f();
			}
		}
		else
		{
			auto f = bind(enabledActions.defaultRoutine, this);
			f();
		}
}

void GUIEnabler::enable(GUIEnablerEvent type, list<GUIEnablerRoutine> routine)
{
	enabledActions.enablerMap[type] = routine;
}

void GUIEnabler::disable(GUIEnablerEvent type)
{
	if (enabledActions.enablerMap.find(type) != enabledActions.enablerMap.end())
	{
		enabledActions.enablerMap.erase(type);
	}
}

void GUIEnabler::disableAll()
{
	enabledActions.enablerMap.clear();
}

void GUIEnabler::disableAllBut(list<GUIEnablerEvent> theseEvents)
{
	for (auto ev : enabledActions.enablerMap)
	{
		if (find(theseEvents.begin(), theseEvents.end(), ev.first) == theseEvents.end())		// If it's not in the but list.
		{
			disable(ev.first);
		}
	}
}

void GUIEnabler::setDefaultRoutine(GUIEnablerRoutine defaultRoutine_)
{
	enabledActions.defaultRoutine = defaultRoutine_;
}
