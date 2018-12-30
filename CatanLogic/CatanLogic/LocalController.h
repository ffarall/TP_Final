#pragma once
#include "ObserverAndController.h"
#include "Player.h"
#include "LocalPlayerEnabler.h"
#include "Button.h"

#include "MapDecoder.h"
#include "CatanDefs.h"

#include "MovableType.h"
#include "GutenbergsPressAllegro.h"

#include <map>
#include <string>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

using namespace std;

class LocalController :
	public BasicController
{
public:
	LocalController(EventsHandler* handler_, GutenbergsPressAllegro * printer, Player * local, LocalPlayerEnabler * localEn);
	virtual ~LocalController();
	virtual void update();
	bool isOK();

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseMouseUpEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

private:
	bool working;

	Player * localPlayer;
	LocalPlayerEnabler * localEnabler;
	GutenbergsPressAllegro * impresora;
	
	MapDecoder toDraw;

	map< string, MovableType * > roads;
	map< string, MovableType * > sellos; // aca voy guardando los 
	
	
	map<ResourceType, pair<int, MovableType*>> cartas;

	ALLEGRO_FONT * fuente;
	map<string,ALLEGRO_BITMAP *> dibujo;
	map<ResourceType, ALLEGRO_BITMAP * > cartasfotos;

	map<string,MovableType*> botones;
	
	
};

