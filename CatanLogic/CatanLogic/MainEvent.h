#pragma once
#include "NewEventHandling.h"
#include "SubEvents.h"

class MainEvents : 
	public GenericEvent
{
public:
	MainEvents() {}
	MainEvents(EventTypes tipo_) { setEvent(tipo_); }
	~MainEvents() {}
	EventTypes getType() { return type; }
	void setEvent(EventTypes tipo_) { type = static_cast<MainTypes>(tipo_); }
protected:
	MainTypes type;
};

