#pragma once

#include "GutenbergsPress.h"
#include "MovableType.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <list>

using namespace std;

// This class simulates Gutenberg's press, by having a background and a list of MovableTypes, whenever one is changed, using Allegro, it prints the new	stamp on screen.
class GuntenbergsPressAllegro :
	public GutenbergsPress
{
public:
	GuntenbergsPressAllegro(ALLEGRO_BITMAP* background_);
	virtual ~GuntenbergsPressAllegro();

	void virtual print();

	void setBackgorund(ALLEGRO_BITMAP* background_);
	void addType(MovableType* newType);
	void delType(MovableType* type);

private:
	ALLEGRO_BITMAP* background;
	list< MovableType* > types;
};

