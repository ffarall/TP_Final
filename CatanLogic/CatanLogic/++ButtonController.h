#pragma once

#include "BasicGUI.h"
#include "Button.h"



class ButtonController :
	public BasicController
{
public:
	ButtonController(Button* toControl);
	virtual ~ButtonController();

	void addUtility(const Action& callback);

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

private:

	Action callback;
	Button * controlado;
};

