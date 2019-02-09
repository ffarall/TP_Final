#include "GutenbergsPressAllegro.h"
#include <functional>


GutenbergsPressAllegro::GutenbergsPressAllegro(ALLEGRO_BITMAP * background_)
{
	setBackgorund(al_load_bitmap("Backround.jpg"));
}

GutenbergsPressAllegro::~GutenbergsPressAllegro()
{
	al_destroy_bitmap(background);
	for (auto type : types)
	{
		delete type;
	}
}

void GutenbergsPressAllegro::print()
{
	al_draw_bitmap(background, 0, 0, NULL);				// Draws background.
	for (auto type : types)								// Then draws every type on top of the background.
	{
		type->printType();
	}
}

MovableType * GutenbergsPressAllegro::createType(ALLEGRO_BITMAP * bitmap_, ALLEGRO_COLOR tint_, double coordinateX_, double coordinateY_, double difX_, double difY_, double scaleX_, double scaleY_, double angle_, int flags_)
{
	MovableType* newType = new MovableType(this, bitmap_, tint_, coordinateX_, coordinateY_, difX_, difY_, scaleX_, scaleY_, angle_, flags_);
	addType(newType);
	return newType;
}

void GutenbergsPressAllegro::setBackgorund(ALLEGRO_BITMAP * background_)
{
	if (background != nullptr)
	{
		al_destroy_bitmap(background);
	}
	background = background_;
}

void GutenbergsPressAllegro::addType(MovableType * newType)
{
	types.push_back(newType);
}

void GutenbergsPressAllegro::delType(MovableType * type)
{
	types.erase(find(types.begin(), types.end(), type));
}
