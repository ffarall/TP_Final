#include "BasicGUI.h"
#include "MainEvent.h"
#include "SubEvents.h"


BasicGUI::BasicGUI()
{
}


BasicGUI::~BasicGUI()
{
}

void BasicGUI::cycle()
{
	if (enablerEv != NO_EV)
	{
		((GUIEnabler*)this)->cycle(enablerEv);
	}
	enablerEv = NO_EV;									// Clearing event used.
	
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
			GUIEnablerEvent temp = controller->parseTimerEvent();
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
			controller->parseMouseDownEvent(mouseCoordinates.first, mouseCoordinates.second);
		}
	}
		break;
	case GUI_MOUSE_UP:
	{
		for (auto controller : controllers)
		{
			controller->parseMouseUpEvent(mouseCoordinates.first, mouseCoordinates.second);
		}
	}
	break;
	case GUI_CLOSE_DISPLAY:
	//que  hacemo?
	break;
	default:
		break;
	}
}

void BasicGUI::attachController(BasicController * newController)
{
	controllers.push_back(newController);
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

bool BasicController::isMouseActive()
{
	return mouseDownActivated;
}

bool BasicController::isTimerActive()
{
	return timerActivated;
}

void BasicController::emitEvent(EventTypes type)
{
	GenericEvent* ev = new MainEvents(type);
	evGen->emitEvent(ev);
}

void BasicController::emitSubEvent(EventTypes type, EventSubtypes subtype, package * pkg)
{
	GenericEvent* ev = new SubEvents(type, subtype, pkg);
	evGen->emitEvent(ev);
}
