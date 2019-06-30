#include "BasicGUI.h"
#include "MainEvent.h"
#include "SubEvents.h"


BasicGUI::BasicGUI()
{
	needToClose = false;
}


BasicGUI::~BasicGUI()
{
}

void BasicGUI::cycle()
{
	if (enablerEv != NO_EV)
	{
		GUIEnabler::cycle(enablerEv);
		enablerEv = NO_EV;									// Clearing event used.
	}
	
	if (checkForEvents())
	{
		parseEvent();
	}
}

void BasicGUI::parseEvent()
{
	switch (GUIEv)
	{
	case GUI_TIMER:
	{
		for (auto controller : controllers)
		{
			GUIEnablerEvent temp = controller.second->parseTimerEvent();
			if (temp != NO_EV)													// It is assumed that only one parser will generate a new event.
			{																	// Also, every new enablerEv will be used right away.
				enablerEv = temp;												// Therefore, an eventQueue is unnecessary.
			}
		}
	}
	break;
	case GUI_MOUSE_DOWN:
	{
		for (auto controller : controllers)
		{
			GUIEnablerEvent temp = controller.second->parseMouseDownEvent(mouseCoordinates.first, mouseCoordinates.second);
			if (temp != NO_EV)													// It is assumed that only one parser will generate a new event.
			{																	// Also, every new enablerEv will be used right away.
				enablerEv = temp;												// Therefore, an eventQueue is unnecessary.
			}
		}
	}
		break;
	case GUI_MOUSE_UP:
	{
		for (auto controller : controllers)
		{
			GUIEnablerEvent temp = controller.second->parseMouseUpEvent(mouseCoordinates.first, mouseCoordinates.second);
			if (temp != NO_EV)													// It is assumed that only one parser will generate a new event.
			{																	// Also, every new enablerEv will be used right away.
				enablerEv = temp;												// Therefore, an eventQueue is unnecessary.
			}
		}
	}
	break;
	case GUI_CLOSE_DISPLAY: 
	{	//needToClose = true;
		for (auto controller : controllers)
		{
			controller.second->parseCloseWindow();
		}
	}

	break;
	default: break;
	}
}

bool BasicGUI::displayWasClosed()
{
	return needToClose;
}

void BasicGUI::attachController(string name, BasicController * newController)
{
	controllers[name] = newController;
}

BasicController::BasicController()
{
}

BasicController::BasicController(EventsHandler * handler_)
{
	evGen = new EventGenerator(handler_);
}

BasicController::~BasicController()
{
	delete evGen;
}

void BasicController::enable()
{
	enableMouseDown();
	enableMouseUp();
	enableTimer();
}

void BasicController::disable()
{
	disableMouseDown();
	disableMouseUp();
	disableTimer();
}

void BasicController::enableMouseDown()
{
	mouseDownActivated = true;
}

void BasicController::disableMouseDown()
{
	mouseDownActivated = false;
}

void BasicController::enableMouseUp()
{
	mouseUpActivated = true;
}

void BasicController::disableMouseUp()
{
	mouseUpActivated = false;
}

void BasicController::enableTimer()
{
	timerActivated = true;
}

void BasicController::disableTimer()
{
	timerActivated = false;
}

bool BasicController::isMouseDownActive()
{
	return mouseDownActivated;
}

bool BasicController::isMouseUpActive()
{
	return mouseUpActivated;
}

bool BasicController::isTimerActive()
{
	return timerActivated;
}

void BasicController::emitEvent(EventTypes type, int priority)
{
	GenericEvent* ev = new MainEvents(type);
	evGen->emitEvent(ev, priority);
}

void BasicController::emitSubEvent(EventTypes type, EventSubtypes subtype, package * pkg, int priority)
{
	GenericEvent* ev = new SubEvents(type, subtype, pkg);
	evGen->emitEvent(ev, priority);
}
