#pragma once
#include "Enabler.h"
#include <cstdint>
#include "Player.h"
#include "Board.h"
#include "Networking.h"

class PlayerEnabler :
	public Enabler
{
public:
	PlayerEnabler();
	virtual ~PlayerEnabler();

	string getErrMessage();
	string getWaitingMessage();

	// Allows other PlayerEnabler to create common new Player objects for localPlayer.
	void setLocalPlayer(Player* localPlayer_);
	// Allows other PlayerEnabler to create common new Player objects for remotePlayer.
	void setRemotePlayer(Player* remotePlayer_);
	// Allows other PlayerEnabler to create common new Board objects for board.
	void setBoard(Board* board_);
	// Sets package sender.
	void setPkgSender(Networking* pkgSender_);


protected:
	// Message to display error.
	string errMessageForUser;
	// Message to display when waiting.
	string waitingMessageForUser;
	// Local player.
	Player* localPlayer;
	// Remote player.
	Player* remotePlayer;
	// Board.
	Board* board;
	// For sending packages.
	Networking * pkgSender;

	void setErrMessage(string message);
	void setWaitingMessage(string message);
};

