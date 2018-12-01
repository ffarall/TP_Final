#pragma once
#include "NewEventHandling.h"
#include "package.h"

enum MainTypes : EventTypes { NETWORK, PLAY_AGAIN, GAME_OVER, START_GAME, PLAYER_ACTION, QUIT, TICKS, LOCAL_STARTS, REMOTE_START, TURN_FINISHED, I_WON, TIME_OUT, ERR_IN_COM, NET_QUIT };

enum SubType : EventSubtypes {
	/* Subtipos de NETWORKING */
	NET_CONNECTED, 
	NET_ACK, NET_NAME ,
	NET_NAME_IS, NET_MAP_IS, NET_CIRCULAR_TOKENS, NET_PLAY_WITH_DEV, NET_DEV_CARDS, NET_YOU_START, NET_I_START, NET_CARD_IS,
	NET_YES, NET_NO ,
	NET_ROBBER_CARDS, NET_DICES_ARE, NET_ROBBER_MOVE, NET_OFFER_TRADE, NET_SETTLEMENT, NET_ROAD, NET_CITY, NET_BANK_TRADE, NET_DEV_CARD, NET_PASS,
	NET_KNIGHT, NET_MONOPOLY, NET_YEARS_OF_PLENTY, NET_ROAD_BUILDING,
	NET_I_WON,
	/******************/
	/* Subtipos de PLAYER_ACTION */
	PLA_CONNECTED,
	PLA_ACK, PLA_NAME,
	PLA_NAME_IS, PLA_MAP_IS, PLA_CIRCULAR_TOKENS, PLA_PLAY_WITH_DEV, PLA_DEV_CARDS, PLA_YOU_START, PLA_I_START, PLA_CARD_IS,
	PLA_YES, PLA_NO,
	PLA_ROBBER_CARDS, PLA_DICES_ARE, PLA_ROBBER_MOVE, PLA_OFFER_TRADE, PLA_SETTLEMENT, PLA_ROAD, PLA_CITY, PLA_BANK_TRADE, PLA_DEV_CARD, PLA_PASS,
	PLA_KNIGHT, PLA_MONOPOLY, PLA_YEARS_OF_PLENTY, PLA_ROAD_BUILDING,
	/******************/
	TIME_OUT, TICK 
};

class SubEvents :
	public SubtypeEvent
{
public:
	SubEvents() { paquete = nullptr; }
	SubEvents(EventTypes mainEvent_, EventSubtypes subTipo_, package * paquete_=nullptr) { setEvent(mainEvent_); setSubtype(subTipo_); paquete = paquete_; }
	~SubEvents() 
	{ 
		if(paquete != nullptr)
			delete paquete; 
	}
	
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

