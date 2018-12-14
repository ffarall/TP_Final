#pragma once
#include "ObserverAndController.h"
#include "MapDecoder.h"
#include "Board.h"
#include "Player.h"
#include <string>

using namespace std;

class BoardObsAndCon :
	public ObserverAndController
{
public:
	BoardObsAndCon();
	virtual ~BoardObsAndCon();

	virtual void update();

private:
	void init();

	// Reads the MapCode to determine what the player is touching in the board and also it specifies where to put the bitmaps of Roads and Settlements or Cities.
	MapDecoder* decoder;
	
	/* As observer, this object will make use of public functions of both Board and Players to check for changes and represent them on screen. */
	// Board to observe.
	Board* board;
	// localPlayer to observe.
	Player* localPlayer;
	// remotePlayer to observe.
	Player* remotePlayer;
};

