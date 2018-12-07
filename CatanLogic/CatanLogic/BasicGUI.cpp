#include "BasicGUI.h"



BasicGUI::BasicGUI()
{
}


BasicGUI::~BasicGUI()
{
}

void BasicGUI::parseEvent()
{
	switch (GUIEv)
	{
	case GUI_TIMER:
	{
		for (auto controller : controllers)
		{
			controller->parseTimerEvent();
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
