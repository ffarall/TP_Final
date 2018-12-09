#pragma once
#include "ObserverAndController.h"
#include "MapDecoder.h"

class BoardObsAndCon :
	public ObserverAndController
{
public:
	BoardObsAndCon();
	virtual ~BoardObsAndCon();

private:
	void init();

	// Reads the MapCode to determine what the player is touching in the board and also it specifies where to put the bitmaps of Roads and Settlements or Cities.
	MapDecoder* decoder;
};

