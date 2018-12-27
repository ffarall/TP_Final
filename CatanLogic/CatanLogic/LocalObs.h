#pragma once
#include "EDAObserver.h"
#include "Player.h"
#include "MapDecoder.h"

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
	LocalObs(GutenbergsPress * printer, Player * local);
	virtual ~LocalObs();
	virtual void update();
	bool isOK();
private:

	bool working;

	Player * localPlayer;
	MapDecoder toDraw;

	map< string, MovableType * > buildings;
	map< string, MovableType * > roads;

	GutenbergsPressAllegro * impresora;
	map<string, MovableType *> sellos;
	
	ALLEGRO_FONT * fuente;
	map<string,ALLEGRO_BITMAP *> dibujo;
	
};

