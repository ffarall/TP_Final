#pragma once
#include "EDAObserver.h"
#include "Player.h"
#include "MapDecoder.h"
#include "MovableType.h"
#include "RemotePlayerEnabler.h"
#include "GutenbergsPressAllegro.h"

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

#include <map>
#include <string>

class RemoteObs :
	public Observer
{
public:
	RemoteObs(GutenbergsPressAllegro * printer, Player * remote, RemotePlayerEnabler * remoteEn);
	virtual ~RemoteObs();

	virtual void update();
	bool isOK();

private:
	bool working;

	Player * remotePlayer;
	RemotePlayerEnabler * remoteEnabler;
	GutenbergsPressAllegro * impresora;

	MapDecoder toDraw;

	map< string, MovableType * > roads;
	map< string, MovableType * > sellos; 
	map< string, ALLEGRO_BITMAP * > bitmaps;
	ALLEGRO_FONT * fuente;
};

