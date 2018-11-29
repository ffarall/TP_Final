#include"HandShakingFSM.h"

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
}

void HandShakingFSM::changeToServer(GenericEvent * ev)
{
	network->toggleStatus();
}

void HandShakingFSM::defaultClientS(GenericEvent * ev)
{
}

void HandShakingFSM::nonActRoutine(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingClientNameS(GenericEvent * ev)
{
}

void HandShakingFSM::defaultServerS(GenericEvent * ev)
{
}

void HandShakingFSM::defaultWaitingForNameS(GenericEvent * ev)
{
}

void HandShakingFSM::sendMap(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingServerNameS(GenericEvent * ev)
{
}

void HandShakingFSM::sendCircTokens(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingMapS(GenericEvent * ev)
{
}

void HandShakingFSM::askPlayDevCards(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingCircTokensS(GenericEvent * ev)
{
}

void HandShakingFSM::sendDevCards(GenericEvent * ev)
{
}

void HandShakingFSM::emitWhoStarts(GenericEvent * ev)
{
}

void HandShakingFSM::defaultPlayWithDevCardsS(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingDevCardsS(GenericEvent * ev)
{
}

HandShakingFSM::HandShakingFSM(Networking * network_):GenericFsm(fsmMap,Client_S)
{
	network = network_;
}
