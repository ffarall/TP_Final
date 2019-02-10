#include"HandShakingFSM.h"
#include<cstdlib>
#include<ctime>

void HandShakingFSM::saveDevCards(GenericEvent * ev)
{
	devCardsOn = true;
	board->setDevCards(((DevCardsPkg*)((SubEvents*)ev)->getPackage())->getDeck());
	network->pushPackage(new package(headers::ACK));
}

void HandShakingFSM::saveCircularTokens(GenericEvent * ev)
{
	for (int i = 0; i < 19; i++)
	{
		char circ = (((CircularTokensPkg*)((SubEvents*)ev)->getPackage())->getTokenList())[i];
		board->setCircularToken('A' + i, circ);
	}
	network->pushPackage(new package(headers::ACK));
}

void HandShakingFSM::saveMap(GenericEvent * ev)
{
	board->copyBoard(((MapIsPkg*)((SubEvents*)ev)->getPackage())->getBoard());
	network->pushPackage(new package(headers::ACK));
}

void HandShakingFSM::tryToConnect(GenericEvent * ev)
{
	network->startConection();
}

void HandShakingFSM::sendName(GenericEvent * ev)
{
	/*if (((SubEvents*)ev)->getType() == SubType::NET_NAME)
	{
		remoteName = ((NameIsPkg*)((SubEvents*)ev)->getPackage())->getName();
	}*/
	network->pushPackage(new NameIsPkg(localName));
}

void HandShakingFSM::saveName(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::NET_NAME)
	{
		remoteName = ((NameIsPkg*)((SubEvents*)ev)->getPackage())->getName();
	}
	network->pushPackage(new package(headers::ACK));
}

void HandShakingFSM::askName(GenericEvent * ev)
{
		network->pushPackage(new package(headers::NAME));
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
	//DONE
}

void HandShakingFSM::defaultSendingClientNameS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::defaultServerS(GenericEvent * ev)
{
	//error(ev);
}

void HandShakingFSM::defaultWaitingForNameS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::sendMap(GenericEvent * ev)
{
	board->shuffleBoard();	
	network->pushPackage(new MapIsPkg(board));
}

void HandShakingFSM::defaultSendingServerNameS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::sendCircTokens(GenericEvent * ev)
{
	network->pushPackage(new CircularTokensPkg(board));
}

void HandShakingFSM::defaultSendingMapS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::askPlayDevCards(GenericEvent * ev)
{
	network->pushPackage(new package(headers::PLAY_WITH_DEV));
}

void HandShakingFSM::defaultSendingCircTokensS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::sendDevCards(GenericEvent * ev)
{
	network->pushPackage(new DevCardsPkg(board->getDevCards()));
}

void HandShakingFSM::emitWhoStarts(GenericEvent * ev)
{
	if (state == handShakingStates::PlayWithDevCards_S)
	{
		devCardsOn = false;
	}
	else
	{
		devCardsOn = true;
	}
	network->pushPackage(new package(rand()%2 ?  headers::I_START: headers::YOU_START));
}

void HandShakingFSM::defaultPlayWithDevCardsS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::defaultSendingDevCardsS(GenericEvent * ev)
{
	if (((SubEvents*)ev)->getType() == SubType::TIME_OUT)
	{
		error(ev);
	}
}

void HandShakingFSM::error(GenericEvent * ev)
{ // aca esta lo de time out, para pushear denuevo
	network->pushPackage(new package(headers::ERROR_));//do error stuff
	network->closeConection();
	handler->enqueueEvent(new SubEvents(MainTypes::ERR_IN_COM, SubType::TIME_OUT));// revisar si esta bien, asumo error en la comunicacion
}

HandShakingFSM::HandShakingFSM(Networking* network_, std::string name_, Board* board_, EventsHandler* handler_) : GenericFsm(&fsmMap,Client_S, handler_)
{
	board = board_;
	network = network_;
	localName = name_;
	srand(time(NULL));	
	devCardsOn = false;
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

void HandShakingFSM::setBoard(Board * board_)
{
	if (board_ != nullptr)
	{
		board = board_;
	}
}

bool HandShakingFSM::playingWithDev()
{
	return devCardsOn;
}

void HandShakingFSM::cycle(GenericEvent* ev)
{
	SubEvents* auxEvP = static_cast<SubEvents*>(ev);
	auxEvP->setEvent(auxEvP->getSubtype());

	GenericFsm::cycle(auxEvP);
}
