#pragma once
#include "EDAObserver.h"
#include "Player.h"
#include "LocalPlayerEnabler.h"
#include "RemotePlayerEnabler.h"
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

class PlayersObserver :
	public Observer
{
public:
	PlayersObserver(GutenbergsPressAllegro * printer, Player * local, Player * remote, LocalPlayerEnabler * localEn, RemotePlayerEnabler * remoteEnab, MainFSM* mainFSM_);
	virtual ~PlayersObserver();
	virtual void update();
	bool isOK();

private:
	bool working;

	bool drawBuildings(bool locOrRemote);

	Player * localPlayer;
	Player * remotePlayer;
	LocalPlayerEnabler * localEnabler;
	RemotePlayerEnabler * remoteEnabler;
	GutenbergsPressAllegro * impresora;
	MainFSM* mainFSM;

	MapDecoder toDraw;

	map< string, MovableType * > roads;
	map< string, MovableType * > sellos; // aca voy guardando los 
	
	ALLEGRO_FONT * fuente;
	map<string,ALLEGRO_BITMAP *> dibujo;
	
};

