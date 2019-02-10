#pragma once
#include"NewGenericFSM.h"
#include"SubEvents.h"
#include"Networking.h"
#include<iostream>

enum handShakingStates : StateTypes { WaitingConnection_S,Client_S, SendingClientName_S, Server_S, WaitingForName_S, SendingServerName_S, SendingMap_S, SendingCircTokens_S, PlayWithDevCards_S, SendingDevCards_S, WaitingEnd_S};

class HandShakingFSM : public GenericFsm
{

private:
	Networking *network;
	std::string localName;
	std::string remoteName;
	Board *board;
	bool devCardsOn;
	

#define TX(x) (static_cast<void (GenericFsm::* )(GenericEvent *)>(&HandShakingFSM::x))

	const FsmMap fsmMap = {
		{WaitingConnection_S,{{
				{SubType::TICK,{WaitingConnection_S,TX(tryToConnect)}},
				{SubType::TIME_OUT,{Server_S,TX(changeToServer)}},
				{SubType::NET_CONNECTED,{Client_S,TX(nonActRoutine)}},
				
			},
			{Client_S,TX(defaultClientS)}}},
		{Client_S,{{
				{SubType::NET_NAME,{SendingClientName_S,TX(sendName)}},
				{SubType::NET_NAME_IS,{Client_S,TX(saveName)}},
				{SubType::NET_MAP_IS,{Client_S,TX(saveMap)}},
				{SubType::NET_CIRCULAR_TOKENS,{Client_S,TX(saveCircularTokens)}},
				{SubType::NET_DEV_CARDS,{Client_S,TX(saveDevCards)}},
				{SubType::TICK,{Client_S,TX(nonActRoutine)}},
				{SubType::NET_PLAY_WITH_DEV,{Client_S,TX(answerPlayWithDev)}}
				
			},
			{Client_S,TX(defaultClientS)}}},

		{SendingClientName_S,{{
				{SubType::NET_ACK,{Client_S,TX(askName)}},
				{SubType::TICK,{SendingClientName_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultSendingClientNameS)}}},

		{Server_S,{{
				{SubType::NET_CONNECTED,{WaitingForName_S,TX(askName)}},
				{SubType::TICK,{Server_S,TX(tryToConnect)}},
			},
			{Client_S,TX(defaultServerS)}}},

		{WaitingForName_S,{{
				{SubType::NET_NAME_IS,{SendingServerName_S,TX(saveName)}},
				{SubType::TICK,{WaitingForName_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultWaitingForNameS)}} },

		{SendingServerName_S,{{
				{SubType::NET_NAME,{SendingServerName_S,TX(sendName)}},
				{SubType::NET_ACK,{SendingMap_S,TX(sendMap)}},
				{SubType::TICK,{SendingServerName_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultSendingServerNameS)}} },

		{SendingMap_S,{{
				{SubType::NET_ACK,{SendingCircTokens_S,TX(sendCircTokens)}},
				{SubType::TICK,{SendingMap_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultSendingMapS)}} },

		{SendingCircTokens_S,{{
				{SubType::NET_ACK,{PlayWithDevCards_S,TX(askPlayDevCards)}},
				{SubType::TICK,{SendingCircTokens_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultSendingCircTokensS)}} },

		{PlayWithDevCards_S,{{
				{SubType::NET_YES,{SendingDevCards_S,TX(sendDevCards)}},
				{SubType::NET_NO,{PlayWithDevCards_S,TX(emitWhoStarts)}},
				{SubType::TICK,{PlayWithDevCards_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultPlayWithDevCardsS)}}},
		{SendingDevCards_S,{{
				{SubType::NET_ACK,{WaitingEnd_S,TX(emitWhoStarts)}},
				{SubType::TICK,{SendingDevCards_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultSendingDevCardsS)}} },
		{WaitingEnd_S,{{
				{SubType::NET_ACK,{WaitingEnd_S,TX(finish)}},
				{SubType::TICK,{WaitingEnd_S,TX(nonActRoutine)}},
			},
			{Client_S,TX(defaultSendingDevCardsS)}} }
	};
	
	void finish(GenericEvent *ev);

	void saveDevCards(GenericEvent *ev);

	void answerPlayWithDev(GenericEvent *ev);
	
	void saveCircularTokens(GenericEvent *ev);
	
	void saveMap(GenericEvent *ev);
	
	void tryToConnect(GenericEvent *ev);
	
	void sendName(GenericEvent *ev);

	void saveName(GenericEvent *ev);
	
	void askName(GenericEvent *ev);
	
	void changeToServer(GenericEvent *ev);
	
	void defaultClientS(GenericEvent *ev);
	
	void nonActRoutine(GenericEvent *ev);
	
	void defaultSendingClientNameS(GenericEvent *ev);
	
	void defaultServerS(GenericEvent *ev);
	
	void defaultWaitingForNameS(GenericEvent *ev);

	void sendMap(GenericEvent *ev);
	
	void defaultSendingServerNameS(GenericEvent *ev);

	void sendCircTokens(GenericEvent *ev);
		
	void defaultSendingMapS(GenericEvent *ev);
	
	void askPlayDevCards(GenericEvent *ev);
	
	void defaultSendingCircTokensS(GenericEvent *ev);
	
	void sendDevCards(GenericEvent *ev);
	
	void emitWhoStarts(GenericEvent *ev);
	
	void defaultPlayWithDevCardsS(GenericEvent *ev);
	
	void defaultSendingDevCardsS(GenericEvent *ev);

	void error(GenericEvent *ev);
	
public:
	HandShakingFSM(Networking* network_,std::string name_, Board* board_, EventsHandler* handler_);
	void setState(handShakingStates newState);
	std::string getLocalName();
	std::string getRemoteName();
	void setBoard(Board* board_);
	bool playingWithDev();
	virtual void cycle(GenericEvent* ev);
};