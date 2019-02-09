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
		if ( (*fsmMap_).at(state).acceptedEventsMap.count(ev->getType()) )
		{
			temp = (*fsmMap_).at(state).acceptedEventsMap.at(ev->getType());
		}
		else
		{
			temp = (*fsmMap_).at(state).defaultCell;
			
		}

		auto f = bind(temp.action, this, ev);

		f();
		state = temp.nextState;

		notifyAllObservers();
	}

	return;
}

GenericFsm::~GenericFsm()
{
}

GenericFsm::GenericFsm(const FsmMap * fsmMap_, StateTypes initState) : fsmMap_(fsmMap_), state(initState)
{
}

GenericFsm::GenericFsm( const FsmMap * fsmMap_, StateTypes initState, EventsHandler * handler_) : fsmMap_(fsmMap_), state(initState), handler(handler_)
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
