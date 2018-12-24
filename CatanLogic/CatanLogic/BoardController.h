#pragma once
#include "BasicGUI.h"
class BoardController :
	public BasicController
{
public:
	BoardController();
	virtual ~BoardController();

	virtual GUIEnablerEvent parseMouseEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();
};

