#pragma once
#include "BasicGUI.h"
#include "MapDecoder.h"
#include "Board.h"
#include "Player.h"
#include "GutenbergsPressAllegro.h"
#include "MainFSM.h"
#include "PlayerEnabler.h"

#include <string>
#include <map>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"

class BoardController :
	public BasicController
{
public:
	BoardController();
	BoardController(EventsHandler* handler_, GutenbergsPressAllegro * prnter_, MainFSM* mainFSM_, Board* board_, PlayerEnabler* locEnab);
	virtual ~BoardController();

	virtual void update();
	bool isOK();

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseMouseUpEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();
	virtual GUIEnablerEvent parseCloseWindow();

	virtual void disable();

	MapDecoder* getDecoder();

	// Functions that determine whether controller is active for clicking, and therefore must me shown as such.
	void toggleSettlement();
	void toggleRoad();
	void toggleCity();
	void toggleRobber();
	bool getPuttingCity();
	bool getPuttingSettlement();
	bool getPuttingRoad();
	bool getMovingRobber();

private:
	void init();

	void drawMap();

	bool fondoListo;
	bool fondoPpal;
	bool working;

	GutenbergsPressAllegro * printer;
	// Map with all of the Allegro bitmaps.
	map< string, ALLEGRO_BITMAP * > bitmaps;
	map< string, MovableType * > sellos; // robber y devCards por ahora
	ALLEGRO_FONT * font;

	// MainFSM to observe.
	MainFSM* mainFSM;
	// Board to observe.
	Board* board;
	// localPlayer to observe.
	Player* localPlayer;
	// remotePlayer to observe.
	Player* remotePlayer;
	// localPlayerEnabler to observe.
	PlayerEnabler* locEnab;

	// Reads the MapCode to determine what the player is touching in the board and also it specifies where to put the bitmaps of Roads and Settlements or Cities.
	MapDecoder* decoder;

	// Variables that determine whether controller is active.
	bool puttingSettlement;
	bool puttingCity;
	bool puttingRoad;
	bool movingRobber;
};

