#include <iostream>
#include <functional>
#include "NewGenericFsm.h"

//Forward declarations..

using namespace std;
using namespace std::placeholders;



void GenericFsm::cycle(GenericEvent * ev)
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
	}

	return;
}

GenericFsm::~GenericFsm()
{
}

GenericFsm::GenericFsm(FsmMap fsmMap_, StateTypes initState) : fsmMap(fsmMap_), state(initState)
{
}

GenericFsm::GenericFsm(const FsmMap fsmMap_, StateTypes initState, EventsHandler * handler_) : fsmMap(fsmMap_), state(initState), handler(handler_)
{
}

GenericEvent * GenericFsm::getEvent()
{
	return fsmEvent;
}

void GenericFsm::setHandler(EventsHandler * handler_)
{
	handler = handler_;
}
