#pragma once
#include"NewGenericFSM.h"
#include"MainEvent.h"
#include"HandShakingFSM.h"
#include"LocalPlayerEnabler.h"
#include"RemotePlayerEnabler.h"



#define MAX_TICK_TIME 12000
enum mainStates : StateTypes { StartMenu_S, HandShaking_S, LocalPlayer_S, RemotePlayer_S, GameOver_S, PlayAgain_S };
class MainFSM: public GenericFsm
{
private:
	HandShakingFSM *handShaking;
	Networking *network;
	EventsHandler *handler;
	LocalPlayerEnabler *localEnabler;
	RemotePlayerEnabler *remoteEnabler;

	unsigned long int timerCount;
	bool receivedQuit;
#define TX(x) (static_cast<void (GenericFsm::* )(GenericEvent *)>(&MainFSM::x))
	const FsmMap mainFsmMap = {
		{StartMenu_S,{{
				{MainTypes::QUIT,{StartMenu_S,TX(endProgram)}},
				{MainTypes::START_GAME,{HandShaking_S,TX(initHandShakingFSM)}},
			},
			{StartMenu_S,TX(defaultStartMenuS)}}},

		{HandShaking_S,{{
				{MainTypes::NETWORK,{HandShaking_S,TX(handShakingFSMRun)}},
				{MainTypes::TIME_OUT,{HandShaking_S,TX(handShakingFSMRun)}},
				{MainTypes::TICKS,{HandShaking_S,TX(decAndRun)}},
				{MainTypes::LOCAL_STARTS,{LocalPlayer_S,TX(localStartsRoutine)}},
				{MainTypes::REMOTE_START,{RemotePlayer_S,TX(remoteStartsRoutine)}}

			},
			{HandShaking_S,TX(defaultHandShakingS)}}},

		{LocalPlayer_S,{{
				{MainTypes::PLAYER_ACTION,{LocalPlayer_S,TX(localFSMRun)}},
				{MainTypes::NETWORK,{LocalPlayer_S,TX(localFSMRun)}},
				{MainTypes::TURN_FINISHED,{RemotePlayer_S,TX(nonActRoutine)}},
				{MainTypes::TICKS,{LocalPlayer_S,TX(decTimeCounter)}},
				{MainTypes::I_WON,{GameOver_S,TX(nonActRoutine)}}
			},
			{LocalPlayer_S,TX(defaultLocalPlayerS)}}},

		{RemotePlayer_S,{{
				{MainTypes::NETWORK,{RemotePlayer_S,TX(remoteFSMRun)}},
				{MainTypes::I_WON,{GameOver_S,TX(nonActRoutine)}},
				{MainTypes::TURN_FINISHED,{LocalPlayer_S,TX(nonActRoutine)}},
				{MainTypes::PLAYER_ACTION,{RemotePlayer_S,TX(remoteFSMRun)}},
				{MainTypes::TICKS,{RemotePlayer_S,TX(decTimeCounter)}}
			},
			{RemotePlayer_S,TX(defaultRemotePlayerS)}} },

		{GameOver_S,{{
				{MainTypes::TICKS,{GameOver_S,TX(decTimeCounter)}},
				{MainTypes::PLAY_AGAIN,{PlayAgain_S,TX(nonActRoutine)}},
				{MainTypes::GAME_OVER,{StartMenu_S,TX(nonActRoutine)}}
			},
			{GameOver_S,TX(defaultGameOverS)}} },

		{PlayAgain_S,{{
				{MainTypes::GAME_OVER,{StartMenu_S,TX(nonActRoutine)}},
				{MainTypes::TICKS,{PlayAgain_S,TX(decTimeCounter)}},
				{MainTypes::PLAY_AGAIN,{HandShaking_S,TX(continuePlaying)}}
			},
			{PlayAgain_S,TX(defaultPlayAgainS)}} },

		
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

	void defaultGameOverS(GenericEvent *ev);

	void continuePlaying(GenericEvent *ev);
	void defaultPlayAgainS(GenericEvent *ev);

	void nonActRoutine(GenericEvent *ev);
	void decTimeCounter(GenericEvent *ev);

	void emitSubEvent(EventTypes type, EventSubtypes subtype);
public:
	MainFSM(HandShakingFSM* handshaking, Networking *network_, EventsHandler *handler_ , LocalPlayerEnabler *enablerLocal, RemotePlayerEnabler *enablerRemote);
	bool isQuit();

};