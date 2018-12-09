#pragma once
#include "BasicGUI.h"
class BoardController :
	public BasicController
{
public:
	BoardController();
	virtual ~BoardController();

	virtual void parseMouseEvent(uint32_t x, uint32_t y);
	virtual void parseTimerEvent();
};

