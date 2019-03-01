#pragma once
#include "BasicGUI.h"
#include "NewEventHandling.h"


class TimerController :
	public BasicController
{
public:
	TimerController();
	TimerController(EventsHandler* handler_);
	virtual ~TimerController();

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseMouseUpEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();
	virtual GUIEnablerEvent parseCloseWindow();

	virtual void update();
};

