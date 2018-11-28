#pragma once
#include "Enabler.h"
#include <string>
#include <cstdint>

using namespace std;

class LocalPlayerEnabler :
	public Enabler
{
public:
	LocalPlayerEnabler();
	virtual ~LocalPlayerEnabler();

	// Enables events for the user to select 
	void setUpForGame();
	// Enables events for beginning of turn.
	void setUpForTurn();

	string getErrMessage();
	string getWaitingMessage();
	size_t getVictoryPoints();
	// Asks if player has won.
	bool hasWon();

private:
	// Message to display error.
	string errMessageForUser;
	// Message to display when waiting.
	string waitingMessageForUser;
	// True when player has won.
	bool iWon;
	// Counter of victory points.
	size_t victoryPoints;

	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(SubtypeEvent* ev);
};

