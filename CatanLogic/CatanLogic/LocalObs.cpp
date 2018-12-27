#include "LocalObs.h"

#define ROAD "road.png"
#define CITY "city.png"
#define SETTLE "setllement.png"
#define FONT ""
#define FONT_SIZE 10 // ver 

LocalObs::LocalObs(GutenbergsPress * printer, Player * local) :toDraw("mapaFinal.png")
{
	working = true;
	localPlayer = local;
	impresora = printer;

	dibujo[ROAD] = al_load_bitmap(ROAD);
	dibujo[CITY] = al_load_bitmap(CITY);
	dibujo[SETTLE] = al_load_bitmap(SETTLE);
	fuente = al_load_font(FONT, FONT_SIZE, 0);

	if (dibujo[ROAD] == NULL || dibujo[SETTLE] == NULL || dibujo[CITY] == NULL || fuente == NULL)
	{
		working = false;
		for (auto each : dibujo)
		{
			if (each.second != NULL) {al_destroy_bitmap(each.second);}
		}
		if (fuente != NULL) { al_destroy_font(fuente); }
	}
}


LocalObs::~LocalObs()
{
	if (working)
	{
		for (auto each : dibujo)
		{
			if (each.second != NULL) { al_destroy_bitmap(each.second); }
		}
		if (fuente != NULL) { al_destroy_font(fuente); }
	}
}

void LocalObs::update()
{
	map<string, bool> buildings;
	for (auto ciudad : localPlayer->getMyCities())
	{
		buildings[ciudad] = true;
	}
	for (auto ciudad : localPlayer->getMySettlements)
	{
		buildings[ciudad] = true;
	}
	
	for (auto a : buildings)
	{
		auto itr = sellos.find(a.first);
		if (itr == sellos.end())
		{
			//sellos[a.first] = 
		}
	}

}

bool LocalObs::isOK()
{
	return working;
}
