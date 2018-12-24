#pragma once

#include "GutenbergsPress.h"
#include "MovableType.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <list>

using namespace std;

// This class simulates Gutenberg's press, by having a background and a list of MovableTypes, whenever one is changed, using Allegro, it prints the new	stamp on screen.
class GutenbergsPressAllegro :
	public GutenbergsPress
{
public:
	GutenbergsPressAllegro(ALLEGRO_BITMAP* background_);
	virtual ~GutenbergsPressAllegro();

	void virtual print();
	MovableType* createType(
		ALLEGRO_BITMAP* bitmap_,
		ALLEGRO_COLOR tint_ = al_map_rgb(255, 255, 255),
		double coordinateX_ = 0,
		double coordinateY_ = 0,
		double difX_ = 0,
		double difY_ = 0,
		double scaleX_ = 1,
		double scaleY_ = 1,
		double angle_ = 0,
		int flags_ = NULL
	);

	void setBackgorund(ALLEGRO_BITMAP* background_);
	void addType(MovableType* newType);
	void delType(MovableType* type);

private:
	ALLEGRO_BITMAP* background;
	list< MovableType* > types;
};

