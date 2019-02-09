#include "PlayerEnabler.h"



PlayerEnabler::PlayerEnabler()
{
}

PlayerEnabler::PlayerEnabler(EventsHandler * handler_) : Enabler(handler_)
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

bool PlayerEnabler::waitingForThisSubtype(SubtypeEvent * ev)
{
	bool ret = false;

	if (enabledActions.enablerMap.find(ev->getSubtype()) != enabledActions.enablerMap.end())
	{
		ret = true;
	}
	delete ev;
	return ret;
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

void PlayerEnabler::setPlayingWithDev(bool playing)
{
	playingWithDev = playing;
}

bool PlayerEnabler::areWePlayingWithDev()
{
	return playingWithDev;
}

void PlayerEnabler::setErrMessage(string message)
{
	errMessageForUser = message;
}

void PlayerEnabler::setWaitingMessage(string message)
{
	waitingMessageForUser = message;
}

bool PlayerEnabler::validateOffer(OfferTradePkg * pkg)
{
	size_t bidder = pkg->getMyOnes().size();
	size_t receiver = pkg->getOpponentOnes().size();

	if (bidder > 0 && bidder <= 9 && receiver > 0 && receiver >= 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}
