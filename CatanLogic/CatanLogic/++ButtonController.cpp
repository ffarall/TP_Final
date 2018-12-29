#include "ButtonController.h"

ButtonController::ButtonController(Button * toControl)
{
	controlado = toControl;
}

ButtonController::~ButtonController()
{
}

void ButtonController::addUtility(const Action & callback_)
{
	callback = callback_;
}

GUIEnablerEvent ButtonController::parseMouseDownEvent(uint32_t x, uint32_t y)
{
	if (controlado->isAvailable())
	{
		if (controlado->clickIn(x, y))
		{
			controlado->toggleButton();
			return callback();
		}
	}
	
	return GUIEnablerEvent::NO_EV;
	
}

GUIEnablerEvent ButtonController::parseTimerEvent()
{
	return GUIEnablerEvent::NO_EV; // ver
}
