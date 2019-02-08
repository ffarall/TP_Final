b#pragma once
#include"NewGenericFSM.h"
#include"MainEvent.h"
#include"HandShakingFSM.h"
#include"LocalPlayerEnabler.h"
#include"RemotePlayerEnabler.h"


#define TICK_TIME 5//ms
#define MAX_TICK_TIME 12000//set to be 2 min 30 sec
enum mainStates : StateTypes { StartMenu_S, HandShaking_S, LocalPlayer_S, RemotePlayer_S, LocalGameOver_S, LocalPlayAgain_S, RemoteGameOver_S, RemotePlayAgain_S };
class MainFSM: public GenericFsm
{
private:
	HandShakingFSM *handShaking;
	Networking *network;
	EventsHandler *handler;
	LocalPlayerEnabler *localEnabler;
	RemotePlayerEnabler *remoteEnabler;
	Board *board;

	unsigned long int timerCount;
	bool receivedQuit;
#define TX(x) (static_cast<void (GenericFsm::* )(GenericEvent *)>(&MainFSM::x))
	const FsmMap mainFsmMap = {
		{StartMenu_S,{{
				{MainTypes::QUIT,{StartMenu_S,TX(endProgram)}},
				{MainTypes::START_GAME,{HandShaking_S,TX(initHandShakingFSM)}},
				{MainTypes::TICKS,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultStartMenuS)}}},

		{HandShaking_S,{{
				{MainTypes::NETWORK,{HandShaking_S,TX(handShakingFSMRun)}},
				{MainTypes::TIME_OUT,{HandShaking_S,TX(handShakingFSMRun)}},
				{MainTypes::TICKS,{HandShaking_S,TX(decAndRun)}},
				{MainTypes::LOCAL_STARTS,{LocalPlayer_S,TX(localStartsRoutine)}},
				{MainTypes::REMOTE_START,{RemotePlayer_S,TX(remoteStartsRoutine)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultHandShakingS)}}},

		{LocalPlayer_S,{{
				{MainTypes::PLAYER_ACTION,{LocalPlayer_S,TX(localFSMRun)}},
				{MainTypes::NETWORK,{LocalPlayer_S,TX(localFSMRun)}},
				{MainTypes::TURN_FINISHED,{RemotePlayer_S,TX(resetTimer)}},
				{MainTypes::TICKS,{LocalPlayer_S,TX(decTimeCounter)}},
				{MainTypes::I_WON,{LocalGameOver_S,TX(nonActRoutine)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultLocalPlayerS)}}},

		{RemotePlayer_S,{{
				{MainTypes::NETWORK,{RemotePlayer_S,TX(remoteFSMRun)}},
				{MainTypes::I_WON,{RemoteGameOver_S,TX(nonActRoutine)}},
				{MainTypes::TURN_FINISHED,{LocalPlayer_S,TX(resetTimer)}},
				{MainTypes::PLAYER_ACTION,{RemotePlayer_S,TX(remoteFSMRun)}},
				{MainTypes::TICKS,{RemotePlayer_S,TX(decTimeCounter)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultRemotePlayerS)}} },

		{LocalGameOver_S,{{
				{MainTypes::TICKS,{LocalGameOver_S,TX(decTimeCounter)}},
				{MainTypes::PLAY_AGAIN,{LocalPlayAgain_S,TX(nonActRoutine)}},
				{MainTypes::GAME_OVER,{StartMenu_S,TX(sendAck)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultGameOverS)}} },

		{LocalPlayAgain_S,{{
				{MainTypes::GAME_OVER,{StartMenu_S,TX(sendGameOver)}},
				{MainTypes::TICKS,{LocalPlayAgain_S,TX(decTimeCounter)}},
				{MainTypes::PLAY_AGAIN,{HandShaking_S,TX(continuePlaying)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultPlayAgainS)}} },

		{RemoteGameOver_S,{{
				{MainTypes::TICKS,{RemoteGameOver_S,TX(decTimeCounter)}},
				{MainTypes::PLAY_AGAIN,{RemotePlayAgain_S,TX(sendPlayAgain)}},
				{MainTypes::GAME_OVER,{StartMenu_S,TX(sendGameOver)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultGameOverS)}} },

		{RemotePlayAgain_S,{{
				{MainTypes::GAME_OVER,{StartMenu_S,TX(sendAck)}},
				{MainTypes::TICKS,{RemotePlayAgain_S,TX(decTimeCounter)}},
				{MainTypes::PLAY_AGAIN,{HandShaking_S,TX(ackAndcontinuePlaying)}},
				{MainTypes::ERR_IN_COM,{StartMenu_S,TX(error)}},
				{MainTypes::QUIT,{StartMenu_S,TX(nonActRoutine)}}
			},
			{StartMenu_S,TX(defaultPlayAgainS)}} }

		
	};

	void endProgram(GenericEvent *ev);
	void initHandShakingFSM(GenericEvent *ev);
	void defaultStartMenuS(GenericEvent *ev);

	void handShakingFSMRun(GenericEvent *ev);
	void decAndRun(GenericEvent *ev);	
	void localStartsRoutine(GenericEvent *ev);
	void remoteStartsRoutine(GenericEvent *ev);
	void defaultHandShakingS(GenericEvent *ev);

	void localFSMRun(GenericEvent *ev);
	void defaultLocalPlayerS(GenericEvent *ev);

	void remoteFSMRun(GenericEvent *ev);
	void defaultRemotePlayerS(GenericEvent *ev);

	void sendAck(GenericEvent *ev);
	void defaultGameOverS(GenericEvent *ev);

	void sendGameOver(GenericEvent *ev);
	void sendPlayAgain(GenericEvent *ev);

	void continuePlaying(GenericEvent *ev);
	void defaultPlayAgainS(GenericEvent *ev);
	void ackAndcontinuePlaying(GenericEvent *ev);
	
	void nonActRoutine(GenericEvent *ev);
	void decTimeCounter(GenericEvent *ev);
	void resetTimer(GenericEvent *ev);

	void emitSubEvent(EventTypes type, EventSubtypes subtype);
	void error(GenericEvent *ev);
public:
	MainFSM(HandShakingFSM* handshaking, Networking *network_, EventsHandler *handler_ , LocalPlayerEnabler *enablerLocal, RemotePlayerEnabler *enablerRemote);
	virtual ~MainFSM();
	mainStates getCurrState();
	bool isQuit();

};