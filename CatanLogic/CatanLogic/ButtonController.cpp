#include "ButtonController.h"

ButtonController::ButtonController(Button * toControl, const Action & callback_)
{
	callback = callback_;
	controldo = toControl;
}

ButtonController::~ButtonController()
{
}

GUIEnablerEvent ButtonController::parseMouseEvent(uint32_t x, uint32_t y)
{
	if ( /* esta tocando*/)
	{
		controldo->toggleButton();
		return callback();
	}
	else
	{
		return GUIEnablerEvent::NO_EV;
	}
}

GUIEnablerEvent ButtonController::parseTimerEvent()
{
	return GUIEnablerEvent::NO_EV; // ver
}
