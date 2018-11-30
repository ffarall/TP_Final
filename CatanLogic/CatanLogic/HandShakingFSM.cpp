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
	network->pushPackage(new NameIsPkg(name));
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
	network->pushPackage(new MapIsPkg(gameMap));
}

void HandShakingFSM::defaultSendingServerNameS(GenericEvent * ev)
{
}

void HandShakingFSM::sendCircTokens(GenericEvent * ev)
{
	network->pushPackage(new CircularTokensPkg(tokens));
}

void HandShakingFSM::defaultSendingMapS(GenericEvent * ev)
{
}

void HandShakingFSM::askPlayDevCards(GenericEvent * ev)
{
	network->pushPackage(new package(headers::PLAY_WITH_DEV));
}

void HandShakingFSM::defaultSendingCircTokensS(GenericEvent * ev)
{
}

void HandShakingFSM::sendDevCards(GenericEvent * ev)
{
	network->pushPackage(new DevCardsPkg(devCards));
}

void HandShakingFSM::emitWhoStarts(GenericEvent * ev)
{
	network->pushPackage(new package(headers::I_START));
}

void HandShakingFSM::defaultPlayWithDevCardsS(GenericEvent * ev)
{
}

void HandShakingFSM::defaultSendingDevCardsS(GenericEvent * ev)
{
}

HandShakingFSM::HandShakingFSM(Networking* network_, std::string name_, const char *map, const char *tokns, const char *devcards) :GenericFsm(fsmMap,Client_S)
{
	network = network_;
	name = name_;
	gameMap = map;
	tokens = tokns;
}
