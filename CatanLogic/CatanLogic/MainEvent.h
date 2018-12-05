#pragma once
#include "NewEventHandling.h"
#include "SubEvents.h"

enum MainTypes : EventTypes { NETWORK, PLA_PLAY_AGAIN, NET_PLAY_AGAIN, PLA_GAME_OVER, NET_GAME_OVER, START_GAME, PLAYER_ACTION, QUIT, TICKS, LOCAL_STARTS, REMOTE_START, TURN_FINISHED, I_WON, TIME_OUT, ERR_IN_COM };

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

