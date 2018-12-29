#pragma once
#include "ObserverAndController.h"
#include "MapDecoder.h"
#include "Board.h"
#include "Player.h"
#include "GutenbergsPressAllegro.h"

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
	BoardObsAndCon(GutenbergsPressAllegro * prnter_);
	virtual ~BoardObsAndCon();

	virtual void update();
	bool isOK();

private:
	void init();

	void drawMap();
	bool fondoListo;
	bool working;

	GutenbergsPressAllegro * printer;
	// Map with all of the Allegro bitmaps.
	map< string, ALLEGRO_BITMAP * > bitmaps;
	map< string, MovableType * > sellos; // robber y devCards por ahora
	ALLEGRO_FONT * font;

	// Board to observe.
	Board* board;
	// localPlayer to observe.
	Player* localPlayer;
	// remotePlayer to observe.
	Player* remotePlayer;
};

