#pragma once
#include <chrono>
#include <map>
#include <array>

#include "EDAObserver.h"
#include "MainFSM.h"
#include "MovableType.h"
#include "GutenbergsPressAllegro.h"

#include "allegro5/allegro_image.h"

using namespace std;
class DetailsObserver :
	public Observer
{
public:
	DetailsObserver(MainFSM* fsm,GutenbergsPressAllegro * allegroPress);
	virtual ~DetailsObserver();
	
	virtual void update();
	bool isOK();
private:
	bool working;

	MainFSM * fsmToObserv;
	GutenbergsPressAllegro * printer;

	array< ALLEGRO_BITMAP*,4> imagenes;
	int contador;
	map<string, MovableType*> sellos;

	chrono::high_resolution_clock::time_point timer;
};

