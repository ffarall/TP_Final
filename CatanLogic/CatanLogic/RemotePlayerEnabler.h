#pragma once
#include "PlayerEnabler.h"
#include <string>
#include <cstdint>
#include "Player.h"
#include "Board.h"
#include "package.h"

using namespace std;

class RemotePlayerEnabler :
	public PlayerEnabler
{
public:
	RemotePlayerEnabler();
	RemotePlayerEnabler(Networking* pkgSender_, PlayerEnabler* localEnabler_);
	virtual ~RemotePlayerEnabler();


	// Enables events for when local starts.
	void localStarts();
	// Enables events when remote starts.
	void remoteStarts();
	// Enables events for beginning of turn.
	void setUpForTurn();

	void setLocalEnabler(PlayerEnabler* localEnabler_);
private:
	void init();
	void end();

	// To be used to set a common board, localPlayer and remotePlayer.
	PlayerEnabler* localEnabler;

	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(SubtypeEvent* ev);
	void firstSettlement(SubtypeEvent* ev);
	void firstRoad(SubtypeEvent* ev);
	void secondSettlement(SubtypeEvent* ev);
	void secondRoad(SubtypeEvent* ev);
	void checkDices(SubtypeEvent* ev);
	void SendsRobberCards(SubtypeEvent* ev);

	/* DEFAULT ROUTINES */
	void genericDefault(SubtypeEvent* ev);

	/* AUXILIARY METHODS */
	void emitEvent(EventTypes type);
	void emitSubEvent(EventTypes type, EventSubtypes subtype, package* pkg = nullptr);

	// Adds settlement to remotePlayer and board from both Enablers
	void addSettlementToRemote(string position);
	// Adds road to localPlayer and board from both Enablers
	void addRoadToRemote(string position);
	// Enables events for beginning of turn.
	void setUpForTurn();
	// Eliminates Robbers cards
	bool deleteCards(vector<ResourceType> descarte);
	
};

