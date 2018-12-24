#include "GuntenbergsPressAllegro.h"
#include <functional>


GuntenbergsPressAllegro::GuntenbergsPressAllegro(ALLEGRO_BITMAP * background_)
{
	setBackgorund(background_);
}

GuntenbergsPressAllegro::~GuntenbergsPressAllegro()
{
	al_destroy_bitmap(background);
	for (auto type : types)
	{
		delete type;
	}
}

void GuntenbergsPressAllegro::print()
{
	al_draw_bitmap(background, 0, 0, NULL);				// Draws background.
	for (auto type : types)								// Then draws every type on top of the background.
	{
		type->printType();
	}
}

void GuntenbergsPressAllegro::setBackgorund(ALLEGRO_BITMAP * background_)
{
	if (background != nullptr)
	{
		al_destroy_bitmap(background);
	}
	background = background_;
}

void GuntenbergsPressAllegro::addType(MovableType * newType)
{
	types.push_back(newType);
}

void GuntenbergsPressAllegro::delType(MovableType * type)
{
	types.erase(find(types.begin(), types.end(), type));
}
