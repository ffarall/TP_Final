#pragma once
#include "ObserverAndController.h"
#include "MapDecoder.h"
#include "Board.h"
#include "Player.h"
#include <string>
#include <map>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"


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

	void drawMap();
	void drawRoad(string edge, bool player); //true red, false blue
	void drawBuilding(string edge, bool type, bool player); // false city, true settlement, true red , false blue

	// Reads the MapCode to determine what the player is touching in the board and also it specifies where to put the bitmaps of Roads and Settlements or Cities.
	MapDecoder* decoder;
	// Map with all of the Allegro bitmaps.
	map< string, ALLEGRO_BITMAP* > bitmaps;
	ALLEGRO_FONT * font;
	/* As observer, this object will make use of public functions of both Board and Players to check for changes and represent them on screen. */
	// Board to observe.
	Board* board;
	// localPlayer to observe.
	Player* localPlayer;
	// remotePlayer to observe.
	Player* remotePlayer;
};

