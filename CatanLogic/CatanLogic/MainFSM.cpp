#include "MainFSM.h"

void MainFSM::endProgram(GenericEvent * ev)
{
}

void MainFSM::initHandShakingFSM(GenericEvent * ev)
{
}

void MainFSM::defaultStartMenuS(GenericEvent * ev)
{
}

void MainFSM::handShakingFSMRun(GenericEvent * ev)
{
}

void MainFSM::decAndRun(GenericEvent * ev)
{
}

void MainFSM::defaultHandShakingS(GenericEvent * ev)
{
}

void MainFSM::localFSMRun(GenericEvent * ev)
{
}

void MainFSM::defaultLocalPlayerS(GenericEvent * ev)
{
}

void MainFSM::remoteFSMRun(GenericEvent * ev)
{
}

void MainFSM::defaultRemotePlayerS(GenericEvent * ev)
{
}

void MainFSM::defaultGameOverS(GenericEvent * ev)
{
}

void MainFSM::continuePlaying(GenericEvent * ev)
{
}

void MainFSM::defaultPlayAgainS(GenericEvent * ev)
{
}

void MainFSM::nonActRoutine(GenericEvent * ev)
{
}

void MainFSM::decTimeCounter(GenericEvent * ev)
{
}

MainFSM::MainFSM():GenericFsm(mainFsmMap,StartMenu_S)
{
}
