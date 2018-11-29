#include<iostream>
#include"NewGenericFSM.h"
#include"SubEvents.h"
enum implStates : StateTypes {Client_S, SendingClientName_S, Server_S, WaitingForName_S, SendingServerName_S, SendingMap_S, SendingCircTokens_S, PlayWithDevCards_S, SendingDevCards_S};

class HandShakingFSM : public GenericFsm
{

private:

#define TX(x) (static_cast<void (GenericFsm::* )(GenericEvent *)>(&HandShakingFSM::x))

	const FsmMap fsmMap = {
		{Client_S,{{
				{SubType::DEV_CARDS,{Client_S,TX(validateDevCards)}},
				{SubType::CIRCULAR_TOKENS,{Client_S,TX(validateCircularTokens)}},
				{SubType::MAP_IS,{Client_S,TX(validateMap)}},
				{SubType::TICK,{Client_S,TX(tryToConnect)}},
				{SubType::NAME,{SendingClientName_S,TX(sendName)}},
				{SubType::TIME_OUT,{Server_S,TX(changeToServer)}}
			},
			{Client_S,TX(defaultClientS)}}},

		{SendingClientName_S,{{
				{SubType::ACK,{Client_S,TX(nonActRoutine)}}
			},
			{SendingClientName_S,TX(defaultSendingClientNameS)}}},

		{Server_S,{{
				{SubType::CONNECTED,{WaitingForName_S,TX(nonActRoutine)}}
			},
			{Server_S,TX(defaultServerS)}}},

		{WaitingForName_S,{{
				{SubType::NAME,{SendingServerName_S,TX(sendName)}}
			},
			{WaitingForName_S,TX(defaultWaitingForNameS)}} },

		{SendingServerName_S,{{
				{SubType::ACK,{SendingMap_S,TX(sendMap)}}
			},
			{SendingServerName_S,TX(defaultSendingServerNameS)}} },

		{SendingMap_S,{{
				{SubType::ACK,{SendingCircTokens_S,TX(sendCircTokens)}}
			},
			{SendingMap_S,TX(defaultSendingMapS)}} },

		{SendingCircTokens_S,{{
				{SubType::ACK,{PlayWithDevCards_S,TX(askPlayDevCards)}}
			},
			{SendingCircTokens_S,TX(defaultSendingCircTokensS)}} },

		{PlayWithDevCards_S,{{
				{SubType::YES,{SendingDevCards_S,TX(sendDevCards)}},
				{SubType::NO,{PlayWithDevCards_S,TX(emitWhoStarts)}}				
			},
			{PlayWithDevCards_S,TX(defaultPlayWithDevCardsS)}}},
		{SendingDevCards_S,{{
				{SubType::ACK,{SendingDevCards_S,TX(emitWhoStarts)}}
			},
			{SendingDevCards_S,TX(defaultSendingDevCardsS)}} },
	};

	void validateDevCards(GenericEvent *ev)
	{
		//TODO
	}
	void validateCircularTokens(GenericEvent *ev)
	{
	}
	void validateMap(GenericEvent *ev)
	{
	}
	void tryToConnect(GenericEvent *ev)
	{
	}
	void sendName(GenericEvent *ev)
	{
	}
	void changeToServer(GenericEvent *ev)
	{
	}
	void defaultClientS(GenericEvent *ev)
	{
	}
	void nonActRoutine(GenericEvent *ev)
	{
	}
	void defaultSendingClientNameS(GenericEvent *ev)
	{
	}
	void defaultServerS(GenericEvent *ev)
	{
	}
	void defaultWaitingForNameS(GenericEvent *ev)
	{
	}
	void sendMap(GenericEvent *ev)
	{
	}
	void defaultSendingServerNameS(GenericEvent *ev)
	{
	}
	void sendCircTokens(GenericEvent *ev)
	{
	}
	void defaultSendingMapS(GenericEvent *ev)
	{
	}
	void askPlayDevCards(GenericEvent *ev)
	{
	}
	void defaultSendingCircTokensS(GenericEvent *ev)
	{
	}
	void sendDevCards(GenericEvent *ev)
	{
	}
	void emitWhoStarts(GenericEvent *ev)
	{
	}
	void defaultPlayWithDevCardsS(GenericEvent *ev)
	{
	}
	void defaultSendingDevCardsS(GenericEvent *ev)
	{
	}
	public:
		HandShakingFSM():GenericFsm(fsmMap,Client_S)
		{
		}

};