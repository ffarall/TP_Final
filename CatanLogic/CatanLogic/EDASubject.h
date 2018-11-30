#pragma once
#include "EDAObserver.h"
#include <list>

using namespace std;

class EDASubject 
{
	 
public:
	EDASubject(){}
	virtual ~EDASubject(){}
	void attach( Observer * observerPtr);
	void detach( Observer * observerPtr);
	
protected:
	void notifyAllObservers(void);
	
private:
	list<Observer * > listOfObservers;

};
