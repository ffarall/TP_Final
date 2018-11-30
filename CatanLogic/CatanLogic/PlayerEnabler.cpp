#include "PlayerEnabler.h"



PlayerEnabler::PlayerEnabler()
{
}


PlayerEnabler::~PlayerEnabler()
{
}

string PlayerEnabler::getErrMessage()
{
	return errMessageForUser;
}

string PlayerEnabler::getWaitingMessage()
{
	return waitingMessageForUser;
}

void PlayerEnabler::setLocalPlayer(Player * localPlayer_)
{
	localPlayer = localPlayer_;
}

void PlayerEnabler::setRemotePlayer(Player * remotePlayer_)
{
	remotePlayer = remotePlayer_;
}

void PlayerEnabler::setBoard(Board * board_)
{
	board = board_;
}

void PlayerEnabler::setPkgSender(Networking * pkgSender_)
{
	pkgSender = pkgSender_;
}

void PlayerEnabler::setErrMessage(string message)
{
	errMessageForUser = message;
}

void PlayerEnabler::setWaitingMessage(string message)
{
	waitingMessageForUser = message;
}
