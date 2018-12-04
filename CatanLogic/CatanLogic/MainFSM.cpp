#include "MainFSM.h"
#include<random>

void MainFSM::endProgram(GenericEvent * ev)
{
	receivedQuit = true;
}

void MainFSM::initHandShakingFSM(GenericEvent * ev)
{
	random_device rd;
	mt19937_64 generator{ rd() };
	uniform_int_distribution<> dist{ 2000, 5000 };	
	timerCount = dist(generator)/TICK_TIME;; //cambiar este valor por el random
	handShaking->setBoard(board);
	handShaking->setState(handShakingStates::Client_S);//la fsm de handshaking siempre comienza como client
}

void MainFSM::defaultStartMenuS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::handShakingFSMRun(GenericEvent * ev)
{
	handShaking->cycle(ev);
	if (timerCount == 0)
	{
		timerCount = MAX_TICK_TIME;
	}
}

void MainFSM::decAndRun(GenericEvent * ev)
{
	timerCount--;
	if (timerCount != 0)
	{
		handShaking->cycle(ev);
	}
	else
	{
		emitSubEvent(MainTypes::TIME_OUT, SubType::TIME_OUT);
	}
}

void MainFSM::localStartsRoutine(GenericEvent * ev)
{
	localEnabler->localStarts(handShaking->getLocalName(),handShaking->getRemoteName(),board);
	remoteEnabler->localStarts();
}

void MainFSM::remoteStartsRoutine(GenericEvent * ev)
{
	localEnabler->remoteStarts(handShaking->getLocalName(), handShaking->getRemoteName(),board);
	remoteEnabler->remoteStarts();
}

void MainFSM::defaultHandShakingS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::localFSMRun(GenericEvent * ev)
{
	localEnabler->cycle((SubtypeEvent*)ev);
}

void MainFSM::defaultLocalPlayerS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::remoteFSMRun(GenericEvent * ev)
{
	remoteEnabler->cycle((SubtypeEvent*)ev);
}

void MainFSM::defaultRemotePlayerS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::defaultGameOverS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::continuePlaying(GenericEvent * ev)
{
	if (localEnabler->whoWon() == "remote")
	{
		handShaking->setState(handShakingStates::Client_S);
	}
	else if(localEnabler->whoWon() == "local")
	{
		handShaking->setState(handShakingStates::SendingServerName_S);
		emitSubEvent(MainTypes::NETWORK, SubType::NET_ACK);
	}
	else
	{
		error(ev);
	}//la fsm de handshaking siempre comienza como client
	//en principio no deberiamos vover a conectarnos con el otro, nada mas deberiamos hacer un nuevo board y comoenzar a jugar de vuelta, suponiendo que el que es server sigue siendo server
}


void MainFSM::defaultPlayAgainS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::nonActRoutine(GenericEvent * ev)
{
	//done
}

void MainFSM::decTimeCounter(GenericEvent * ev)
{
	timerCount--;
	if (timerCount == 0)
	{
		emitSubEvent(MainTypes::TIME_OUT, SubType::TIME_OUT);
	}
}

void MainFSM::resetTimer(GenericEvent * ev)
{
	timerCount = MAX_TICK_TIME;
}

void MainFSM::emitSubEvent(EventTypes type, EventSubtypes subtype)
{
	handler->enqueueEvent(new SubEvents(type, subtype));
}

void MainFSM::error(GenericEvent * ev)
{
	//do error stuff
}

MainFSM::MainFSM(HandShakingFSM* handshaking, Networking *network_, EventsHandler *handler_, LocalPlayerEnabler *enablerLocal, RemotePlayerEnabler *enablerRemote):GenericFsm(mainFsmMap,StartMenu_S)
{
	handShaking = handshaking;
	network = network_;
	handler = handler_;
	localEnabler = enablerLocal;
	remoteEnabler = enablerRemote;
	receivedQuit = false;
	timerCount = MAX_TICK_TIME;
	board = new Board;
}

mainStates MainFSM::getCurrState()
{
	return (mainStates)state;
}

bool MainFSM::isQuit()
{
	return receivedQuit;
}
