#include<iostream>
#include"NewGenericFSM.h"


enum eventTypes { DEV_CARDS, CIRCULAR_TOKENS, MAP_IS, TICK, NAME, ACK,TIME_OUT, CONNECTED, YES_DEV, NO_DEV  };
enum implStates : StateTypes {Client_S, SendingClientName_S, Server_S, WaitingForName_S, SendingServerName_S, SendingMap_S, SendingCircTokens_S, PlayWithDevCards_S, SendingDevCards_S};

class HandShakingFSM : public genericFSM
{
public:

private:
#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&HandShakingFSM::x))

	const FsmMap testFsmMap = {
		{Client_S,{{
				{DEV_CARDS,{Client_S,TX(validateDevCards)}},
				{}}}},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
	};

	void validateDevCards(genericEvent *ev)
	{
	}
	void validateCircularTokens(genericEvent *ev)
	{}

};