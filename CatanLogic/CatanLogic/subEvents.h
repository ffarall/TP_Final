#pragma once
#include "NewEventHandling.h"
#include "package.h"

enum MainTypes : EventTypes { NETWORK, PLAY_AGAIN, GAME_OVER, START_GAME, PLAYER_ACTION, QUIT, TICKS, LOCAL_STARTS, REMOTE_START, TURN_FINISHED, I_WON, TIME_OUT, ERR_IN_COM };

enum SubType : EventSubtypes {
	/* Subtipos de NETWORKING */
	CONNECTED, 
	ACK , NAME ,
	NAME_IS , MAP_IS , CIRCULAR_TOKENS , PLAY_WITH_DEV , DEV_CARDS , YOU_START , I_START ,
	YES , NO ,
	/******************/
	/* Subtipos de PLAYER_ACTION */
	CONNECTED,
	ACK, NAME,
	NAME_IS, MAP_IS, CIRCULAR_TOKENS, PLAY_WITH_DEV, DEV_CARDS, YOU_START, I_START,
	YES, NO,
	/******************/
	TIME_OUT , TICK 
};

class SubEvents :
	public SubtypeEvent
{
public:
	SubEvents() { paquete = nullptr; }
	SubEvents(EventTypes mainEvent_, EventSubtypes subTipo_) { setEvent(mainEvent_); setSubtype(subTipo_); paquete = nullptr; }
	SubEvents(EventTypes mainEvent_, EventSubtypes subTipo_, package * paquete_) { setEvent(mainEvent_); setSubtype(subTipo_); paquete = paquete_; }

	virtual EventSubtypes getSubtype() { return subTipo; }
	void setSubtype(EventSubtypes subType_) { subTipo = static_cast<SubType>(subType_); }

	EventTypes getType() { return mainEvent; }
	void setEvent(EventTypes tipo_) { mainEvent = static_cast<MainTypes>(tipo_); }
	
	void addPackage(package * newPacket) 
	{
		if (paquete != nullptr) { delete paquete; }
		paquete = newPacket;
	};
	package * getPackage() { return paquete; };

private:
	MainTypes mainEvent;
	SubType subTipo;
	package * paquete;
};

