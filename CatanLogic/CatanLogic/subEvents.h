#pragma once
#include "NewEventHandling.h"
#include "package.h"

enum mainTypes { NETWORK, PLAY_AGAIN, GAME_OVER, START_GAME, PLAYER_ACTION, QUIT, TICKS, LOCAL_STARTS, TURN_FINISHED, I_WON, TIME_OUT, ERR_IN_COM };
enum class subType {
	/* subtipos de networking */
	CONNECTED, 
	ACK , NAME ,
	NAME_IS , MAP_IS , CIRCULAR_TOKENS , PLAY_WITH_DEV , DEV_CARDS , YOU_START , I_START ,
	DICE_ARE , ROBBER_CARDS , CARD_IS , ROBBER_MOVE,
	SETTLMENT , ROAD , CITY , BANK_TRADE , OFFER_TRADE , PASS ,
	DEV_CARD , MONOPOLY , YEARS_OF_PLENTY , ROAD_BILDING , KNIGHT ,
	YES , NO ,
	I_WON , PLAY_AGAIN , GAME_OVER ,
	ERROR , QUIT ,
	/******************/
	TIME_OUT , TICK 
};

class subEvents :
	public GenericEvent
{
public:
	subEvents(mainTypes ppal, subType secnd);
	~subEvents();
	
	subType getSubType() { return subTipo; };

	void addPackage(package * newPaket);
	package * getPaket() { return paquete; };

private:
	subType subTipo;
	package * paquete;
};

