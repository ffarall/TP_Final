#include "ObserverAndController.h"



ObserverAndController::ObserverAndController()
{
}


ObserverAndController::~ObserverAndController()
{
	delete controller;
}

BasicController * ObserverAndController::getController()
{
	return controller;
}
