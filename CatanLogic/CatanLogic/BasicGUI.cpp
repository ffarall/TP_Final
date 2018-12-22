#include "BasicGUI.h"



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
	case GUI_MOUSE:
	{
		for (auto controller : controllers)
		{
			controller->parseMouseEvent(mouseCoordinates.first, mouseCoordinates.second);
		}
	}
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

BasicController::~BasicController()
{
}
