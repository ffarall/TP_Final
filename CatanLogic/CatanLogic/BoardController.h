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

	// Functions that determine whether controller is active for clicking, and therefore must me shown as such.
	void toggleSettlement();
	void toggleRoad();
	void toggleCity();
	bool getPuttingCity();
	bool getPuttingSettlement();
	bool getPuttingRoad();

private:
	void init();

	// Reads the MapCode to determine what the player is touching in the board and also it specifies where to put the bitmaps of Roads and Settlements or Cities.
	MapDecoder* decoder;

	// Variables that determine whether controller is active.
	bool puttingSettlement;
	bool puttingCity;
	bool puttingRoad;
};

