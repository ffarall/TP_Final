#include <iostream>
#include <functional>
#include "NewGenericFSM.h"

//Forward declarations..

using namespace std;
using namespace std::placeholders;



void genericFSM::cycle(genericEvent * ev)
{
	if (ev != nullptr)
	{
		FsmCell temp;
		if ( fsmMap[state].acceptedEventsMap.count(ev->getType()) )
		{
			temp = fsmMap[state].acceptedEventsMap[(ev->getType())];
		}
		else
		{
			temp = fsmMap[state].defaultCell;
		}

		auto f = bind(temp.action, this, ev);

		f();
		state = temp.nextState;
		delete ev;
	}

	return;
}

genericFSM::genericFSM(FsmMap fsmMap_, StateTypes initState) : fsmMap(fsmMap_), state(initState)
{
}

genericEvent * genericFSM::getEvent()
{
	return fsmEvent;
}
