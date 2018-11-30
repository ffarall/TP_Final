#include "EDASubject.h"

void
EDASubject::attach(Observer * observerPtr)
{
	listOfObservers.push_back(observerPtr);
}

void
EDASubject::detach(Observer * observerPtr)
{
	listOfObservers.remove(observerPtr);
}

void
EDASubject::notifyAllObservers(void)
{
	list<Observer * >::iterator it;
	for(it= listOfObservers.begin(); it != listOfObservers.end(); it++)
		(*it)->update();
}
