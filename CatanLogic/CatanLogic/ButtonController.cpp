#include "ButtonController.h"

ButtonController::ButtonController(Button * toControl)
{
	controldo = toControl;
}

ButtonController::~ButtonController()
{
}

void ButtonController::addUtility(const Action & callback_)
{
	callback = callback_;
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
