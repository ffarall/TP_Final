#pragma once
#include "EDAObserver.h"
#include "Player.h"
#include "LocalPlayerEnabler.h"
#include "Button.h"
#include "MainFSM.h"

#include "MapDecoder.h"
#include "CatanDefs.h"

#include "MovableType.h"
#include "GutenbergsPressAllegro.h"

#include <map>
#include <string>
#include <vector>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

using namespace std;

class LocalObserver :
	public Observer
{
public:
	LocalObserver(GutenbergsPressAllegro * printer, Player * local, LocalPlayerEnabler * localEn, MainFSM* mainFSM_);
	virtual ~LocalObserver();
	virtual void update();
	bool isOK();

private:
	bool working;

	bool drawBuildings(bool locOrRemote);

	Player * localPlayer;
	LocalPlayerEnabler * localEnabler;
	GutenbergsPressAllegro * impresora;
	MainFSM* mainFSM;

	MapDecoder toDraw;

	map< string, MovableType * > roads;
	map< string, MovableType * > sellos; // aca voy guardando los 
	
	
	map<ResourceType, pair<int, MovableType*>> cartas;

	ALLEGRO_FONT * fuente;
	map<string,ALLEGRO_BITMAP *> dibujo;
	map<ResourceType, ALLEGRO_BITMAP * > cartasfotos;
};

