#pragma once
#include "BasicGUI.h"
class BoardController :
	public BasicController
{
public:
	BoardController();
	virtual ~BoardController();

	virtual GenericEvent parseMouseEvent(uint32_t x, uint32_t y);
	virtual GenericEvent parseTimerEvent();
};

