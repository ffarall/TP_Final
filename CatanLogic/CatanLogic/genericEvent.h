#pragma once

enum mainTypes { NETWORK, PLAY_AGAIN, GAME_OVER, START_GAME, PLAYER_ACTION, QUIT, TICKS, LOCAL_STARTS, TURN_FINISHED, I_WON, TIME_OUT, ERR_IN_COM };

class genericEvent
{
public:
	genericEvent(mainTypes type_) { type = type_ ; };
	~genericEvent() {};

	mainTypes getType() { return type; };

protected:
	mainTypes type;
};

