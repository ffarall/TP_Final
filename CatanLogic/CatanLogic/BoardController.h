#pragma once
#include "BasicGUI.h"
#include "MapDecoder.h"

class BoardController :
	public BasicController
{
public:
	BoardController();
	virtual ~BoardController();

	virtual GUIEnablerEvent parseMouseEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

	MapDecoder* getDecoder();

private:
	void init();

	// Reads the MapCode to determine what the player is touching in the board and also it specifies where to put the bitmaps of Roads and Settlements or Cities.
	MapDecoder* decoder;
};

