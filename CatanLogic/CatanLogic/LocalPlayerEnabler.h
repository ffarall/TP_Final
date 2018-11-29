#pragma once
#include "PlayerEnabler.h"
#include <string>
#include <cstdint>
#include "Player.h"
#include "Board.h"

using namespace std;

class LocalPlayerEnabler :
	public PlayerEnabler
{
public:
	LocalPlayerEnabler();
	virtual ~LocalPlayerEnabler();

	void init();
	void end();

	// Enables events for the user to select when local starts.
	void localStarts(string nameLocal, string nameRemote);
	// Enables events when remote starts.
	void remoteStarts();
	// Enables events for beginning of turn.
	void setUpForTurn();

private:
	// To be used to set a common board, localPlayer and remotePlayer.
	PlayerEnabler* remoteEnabler;

	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(SubtypeEvent* ev);
	void firstSettlement(SubtypeEvent* ev);

	/* DEFAULT ROUTINES */
	void genericDefault(SubtypeEvent* ev);

	/* AUXILIARY METHODS */
	void addSettlementToLocal(string position);
};

