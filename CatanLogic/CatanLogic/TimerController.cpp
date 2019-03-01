#include "TimerController.h"
#include "SubEvents.h"


TimerController::TimerController()
{
}

TimerController::TimerController(EventsHandler* handler_) : BasicController(handler_)
{
}


TimerController::~TimerController()
{
}

GUIEnablerEvent TimerController::parseMouseDownEvent(uint32_t x, uint32_t y)
{
	return NO_EV;
}

GUIEnablerEvent TimerController::parseMouseUpEvent(uint32_t x, uint32_t y)
{
	return NO_EV;
}

GUIEnablerEvent TimerController::parseTimerEvent()
{
	emitSubEvent(TICKS, TICK, NULL, 1);
	return NO_EV;
}

GUIEnablerEvent TimerController::parseCloseWindow()
{
	emitEvent(MainTypes::CLOSE_ALL);
	return NO_EV;
}

void TimerController::update()
{
}
