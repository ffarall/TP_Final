#pragma once
#include "EDAObserver.h"
#include "Player.h"
#include "MapDecoder.h"
#include "MovableType.h"
#include "RemotePlayerEnabler.h"
#include "GutenbergsPressAllegro.h"

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

	Player * localPlayer;
	LocalPlayerEnabler * localEnabler;
	GutenbergsPressAllegro * impresora;

	MapDecoder toDraw;

	map< string, MovableType * > roads;
	map< string, MovableType * > buildngs; 
};

