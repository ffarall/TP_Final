#pragma once
#include "EDAObserver.h"
#include "Player.h"
#include "LocalPlayerEnabler.h"

#include "MapDecoder.h"
#include "CatanDefs.h"

#include "MovableType.h"
#include "GutenbergsPressAllegro.h"

#include <map>
#include <string>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

using namespace std;

class LocalObs :
	public Observer
{
public:
	LocalObs(GutenbergsPressAllegro * printer, Player * local, LocalPlayerEnabler * localEn);
	virtual ~LocalObs();
	virtual void update();
	bool isOK();
private:

	bool working;

	Player * localPlayer;
	LocalPlayerEnabler * localEnabler;
	
	MapDecoder toDraw;

	map< string, MovableType * > buildings;
	map< string, MovableType * > roads;

	GutenbergsPressAllegro * impresora;
	map<string, MovableType *> sellos;
	map<ResourceType, pair<int, MovableType*>> cartas;

	ALLEGRO_FONT * fuente;
	map<string,ALLEGRO_BITMAP *> dibujo;
	map<ResourceType, ALLEGRO_BITMAP * > cartasfotos;
	
	
};

