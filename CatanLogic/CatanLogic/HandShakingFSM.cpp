#include<iostream>
#include"NewGenericFSM.h"
#include"subEvents.h"
enum implStates : StateTypes {Client_S, SendingClientName_S, Server_S, WaitingForName_S, SendingServerName_S, SendingMap_S, SendingCircTokens_S, PlayWithDevCards_S, SendingDevCards_S};

class HandShakingFSM : public GenericFsm
{
public:

private:
#define TX(x) (static_cast<void (GenericFsm::* )(GenericEvent *)>(&HandShakingFSM::x))

	const FsmMap testFsmMap = {
		{Client_S,{{
				{subType::DEV_CARDS,{Client_S,TX(validateDevCards)}},
				{subType::CIRCULAR_TOKENS,{Client_S,TX(validateCircularTokens)}},
				{subType::MAP_IS,{Client_S,TX(validateMap)}},
				{subType::TICK,{Client_S,TX(tryToConnect)}},
				{subType::NAME,{SendingClientName_S,TX(sendName)}},
				{subType::TIME_OUT,{Server_S,TX(changeToServer)}}
			},
			{Client_S,TX(defaultClientS)}}},

		{SendingClientName_S,{{
				{subType::ACK,{Client_S,TX(nonActRoutine)}}
			},
			{SendingClientName_S,TX(defaultSendingClientNameS)}}},

		{Server_S,{{
				{subType::CONNECTED,{WaitingForName_S,TX(nonActRoutine)}}
			},
			{Server_S,TX(defaultServerS)}}},

		{WaitingForName_S,{{
				{subType::NAME,{SendingServerName_S,TX(sendName)}}
			},
			{WaitingForName_S,TX(defaultWaitingForNameS)}} },

		{SendingServerName_S,{{
				{subType::ACK,{SendingMap_S,TX(sendMap)}}
			},
			{SendingServerName_S,TX(defaultSendingServerNameS)}} },
		{SendingServerName_S,{{
				{subType::ACK,{SendingMap_S,TX(sendMap)}}
			},
			{SendingServerName_S,TX(defaultSendingServerNameS)}} },
		{},
		{},
		{},
	};

	void validateDevCards(GenericEvent *ev)
	{
	}
	void validateCircularTokens(GenericEvent *ev)
	{}
	void validateMap(GenericEvent *ev)
	{}
	void tryToConnect(GenericEvent *ev)
	{}
	void sendName(GenericEvent *ev)
	{}
	void changeToServer(GenericEvent *ev)
	{}
	void defaultClientS(GenericEvent *ev)
	{}
	void nonActRoutine(GenericEvent *ev)
	{}
	void defaultSendingClientNameS(GenericEvent *ev)
	{}
	void defaultServerS(GenericEvent *ev)
	{}
	void defaultWaitingForNameS(GenericEvent *ev)
	{}
	void sendMap(GenericEvent *ev)
	{}
	void defaultSendingServerNameS(GenericEvent *ev)
	{}
};