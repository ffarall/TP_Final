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

class LocalObsAndCont :
	public BasicController
{
public:
	LocalObsAndCont(EventsHandler* handler_, GutenbergsPressAllegro * printer, Player * local, LocalPlayerEnabler * localEn);
	virtual ~LocalObsAndCont();
	virtual void update();
	bool isOK();

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

