#pragma once

#include "BasicGUI.h"
#include "Button.h"



class ButtonController :
	public BasicController
{
public:
	ButtonController(Button * toControl, const Action& callback);
	virtual ~ButtonController();

	virtual GUIEnablerEvent parseMouseEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

private:

	Action callback;
	Button * controldo;
};

