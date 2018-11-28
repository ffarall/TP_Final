#include<iostream>
#include"NewGenericFSM.h"


enum eventTypes { DEV_CARDS, CIRCULAR_TOKENS, MAP_IS, TICK, NAME, ACK,TIME_OUT, CONNECTED, YES_DEV, NO_DEV  };
enum implStates : StateTypes {Client_S, SendingClientName_S, Server_S, WaitingForName_S, SendingServerName_S, SendingMap_S, SendingCircTokens_S, PlayWithDevCards_S, SendingDevCards_S};

class HandShakingFSM : public GenericFsm
{
public:

private:
#define TX(x) (static_cast<void (GenericFsm::* )(GenericEvent *)>(&HandShakingFSM::x))

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

	void validateDevCards(GenericEvent *ev)
	{
	}
	void validateCircularTokens(GenericEvent *ev)
	{}

};