#include"HandShakingFSM.h"
#include<cstdlib>
#include<ctime>

void HandShakingFSM::validateDevCards(GenericEvent * ev)
{
}

void HandShakingFSM::validateCircularTokens(GenericEvent * ev)
{
}

void HandShakingFSM::validateMap(GenericEvent * ev)
{
}

void HandShakingFSM::tryToConnect(GenericEvent * ev)
{
	network->startConection();
}

void HandShakingFSM::sendName(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::NET_NAME)
	{
		remoteName = ((NameIsPkg*)((SubEvents*)ev)->getPackage())->getName();
	}
	network->pushPackage(new NameIsPkg(localName));
}

void HandShakingFSM::changeToServer(GenericEvent * ev)
{
	network->toggleStatus();
}

void HandShakingFSM::defaultClientS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::nonActRoutine(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingClientNameS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::defaultServerS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::defaultWaitingForNameS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::sendMap(GenericEvent * ev)
{
	board->shuffleBoard();	
	network->pushPackage(new MapIsPkg(board));
}

void HandShakingFSM::defaultSendingServerNameS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::sendCircTokens(GenericEvent * ev)
{
	network->pushPackage(new CircularTokensPkg(tokens));
}

void HandShakingFSM::defaultSendingMapS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::askPlayDevCards(GenericEvent * ev)
{
	network->pushPackage(new package(headers::PLAY_WITH_DEV));
}

void HandShakingFSM::defaultSendingCircTokensS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::sendDevCards(GenericEvent * ev)
{
	network->pushPackage(new DevCardsPkg(devCards));
}

void HandShakingFSM::emitWhoStarts(GenericEvent * ev)
{
	network->pushPackage(new package(rand()%2 ?  headers::I_START: headers::YOU_START));
}

void HandShakingFSM::defaultPlayWithDevCardsS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::defaultSendingDevCardsS(GenericEvent * ev)
{
	error(ev);
}

void HandShakingFSM::error(GenericEvent * ev)
{
}

HandShakingFSM::HandShakingFSM(Networking* network_, std::string name_, const char *tokns, const char *devcards, Board *board_) :GenericFsm(fsmMap,Client_S)
{
	network = network_;
	localName = name_;
	tokens = tokns;
	srand(time(NULL));
	board = board_;
}

void HandShakingFSM::setState(handShakingStates newState)
{
	state = newState;
}

std::string HandShakingFSM::getLocalName()
{
	return localName;
}

std::string HandShakingFSM::getRemoteName()
{
	return remoteName;
}
