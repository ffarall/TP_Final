#pragma once
#include "EDAObserver.h"
#include "BasicGUI.h"

class ObserverAndController :
	public Observer
{
public:
	ObserverAndController();
	virtual ~ObserverAndController();
	BasicController* getController();

protected:
	// Controller to attach to GUI with getController().
	BasicController* controller;
};

