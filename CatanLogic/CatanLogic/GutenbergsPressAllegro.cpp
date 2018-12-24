#include "GutenbergsPressAllegro.h"
#include <functional>


GutenbergsPressAllegro::GutenbergsPressAllegro(ALLEGRO_BITMAP * background_)
{
	setBackgorund(background_);
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
