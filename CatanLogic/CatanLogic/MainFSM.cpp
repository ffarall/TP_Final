#include "MainFSM.h"

void MainFSM::endProgram(GenericEvent * ev)
{
	receivedQuit = true;
}

void MainFSM::initHandShakingFSM(GenericEvent * ev)
{
	handShaking->setState(handShakingStates::Client_S);//la fsm de handshaking siempre comienza como client
}

void MainFSM::defaultStartMenuS(GenericEvent * ev)
{
	//TODO
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
	localEnabler->localStarts(handShaking->getLocalName(),handShaking->getRemoteName());
	remoteEnabler->localStarts();
}

void MainFSM::remoteStartsRoutine(GenericEvent * ev)
{
	localEnabler->remoteStarts(handShaking->getLocalName(), handShaking->getRemoteName());
	remoteEnabler->remoteStarts();
}

void MainFSM::defaultHandShakingS(GenericEvent * ev)
{
}

void MainFSM::localFSMRun(GenericEvent * ev)
{
	localEnabler->cycle((SubtypeEvent*)ev);
}

void MainFSM::defaultLocalPlayerS(GenericEvent * ev)
{
}

void MainFSM::remoteFSMRun(GenericEvent * ev)
{
	remoteEnabler->cycle((SubtypeEvent*)ev);
}

void MainFSM::defaultRemotePlayerS(GenericEvent * ev)
{
}

void MainFSM::defaultGameOverS(GenericEvent * ev)
{
}

void MainFSM::continuePlaying(GenericEvent * ev)
{
	handShaking->setState(handShakingStates::Client_S);//la fsm de handshaking siempre comienza como client
	//en principio no deberiamos vover a conectarnos con el otro, nada mas deberiamos hacer un nuevo board y comoenzar a jugar de vuelta, suponiendo que el que es server sigue siendo server
}


void MainFSM::defaultPlayAgainS(GenericEvent * ev)
{
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

void MainFSM::emitSubEvent(EventTypes type, EventSubtypes subtype)
{
	handler->enqueueEvent(new SubEvents(type, subtype));
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
}

bool MainFSM::isQuit()
{
	return receivedQuit;
}
