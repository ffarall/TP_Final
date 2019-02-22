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

	handShaking->setState(handShakingStates::WaitingConnection_S);//la fsm de handshaking siempre comienza como client
}

void MainFSM::defaultStartMenuS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::handShakingFSMRun(GenericEvent * ev)
{
	handShaking->cycle(ev);
	timerCount = MAX_TICK_TIME;
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
		emitSubEvent(MainTypes::TIME_OUT_MT, SubType::TIME_OUT);
	}
}

void MainFSM::localStartsRoutine(GenericEvent* ev)
{
	localEnabler->localStarts(handShaking->getLocalName(), handShaking->getRemoteName(), board);
	remoteEnabler->localStarts();
	if (handShaking->playingWithDev())
	{
		localEnabler->setPlayingWithDev(true);
		remoteEnabler->setPlayingWithDev(true);
	}
	else
	{
		localEnabler->setPlayingWithDev(false);
		remoteEnabler->setPlayingWithDev(false);
	}
}

void MainFSM::remoteStartsRoutine(GenericEvent * ev)
{
	localEnabler->remoteStarts(handShaking->getLocalName(), handShaking->getRemoteName(),board);
	remoteEnabler->remoteStarts();
	if (handShaking->playingWithDev())
	{
		localEnabler->setPlayingWithDev(true);
		remoteEnabler->setPlayingWithDev(true);
	}
	else
	{
	localEnabler->setPlayingWithDev(false);
	remoteEnabler->setPlayingWithDev(false);
	}
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

void MainFSM::sendAck(GenericEvent * ev)
{
	network->pushPackage(new package(headers::ACK));
		
}

void MainFSM::defaultGameOverS(GenericEvent * ev)
{
	error(ev);
}

void MainFSM::sendGameOver(GenericEvent * ev)
{
	network->pushPackage(new package(headers::GAME_OVER_H));
}

void MainFSM::sendPlayAgain(GenericEvent * ev)
{
	network->pushPackage(new package(headers::PLAY_AGAIN_H));
}

void MainFSM::continuePlaying(GenericEvent * ev)
{
	if (localEnabler->whoWon() == "remote")
	{
		handShaking->setState(handShakingStates::Client_S);
	}
	else if(localEnabler->whoWon() == "local")
	{
		sendPlayAgain(ev);		
		handShaking->setState(handShakingStates::SendingServerName_S);
		//emitSubEvent(MainTypes::NETWORK, SubType::NET_ACK);
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

void MainFSM::ackAndcontinuePlaying(GenericEvent * ev)
{
	network->pushPackage(new package(headers::ACK));
	continuePlaying(ev);
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
		//emitSubEvent(MainTypes::TIME_OUT_MT, SubType::TIME_OUT);
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
	network->closeConection();
	
	//network->pushPackage(new package(headers::ERROR_));
	//cerrame la 12 nestor
}

MainFSM::MainFSM(HandShakingFSM* handshaking, Networking *network_, EventsHandler *handler_, LocalPlayerEnabler *enablerLocal, RemotePlayerEnabler *enablerRemote, Board *board_):GenericFsm(&mainFsmMap,StartMenu_S)
{
	handShaking = handshaking;
	network = network_;
	handler = handler_;
	localEnabler = enablerLocal;
	remoteEnabler = enablerRemote;
	receivedQuit = false;
	timerCount = MAX_TICK_TIME;
	board = board_;
}

MainFSM::~MainFSM()
{
	//delete board;
}

mainStates MainFSM::getCurrState()
{
	return (mainStates)state;
}

bool MainFSM::isQuit()
{
	return receivedQuit;
}
