#include "LocalObs.h"

#define ROAD "road.png"
#define CITY "city.png"
#define SETTLE "setllement.png"
#define FONT ""
#define FONT_SIZE 10 // ver 
#define BOARD_POS_X 310
#define BOARD_POS_Y 88

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
	bool anyChange = false;
	map<string, bool> buildings;
	for (auto ciudad : localPlayer->getMyCities())
	{
		buildings[ciudad] = true;
	}
	for (auto settlement : localPlayer->getMySettlements)
	{
		buildings[settlement] = false;
	}
	
	for (auto a : buildings) // primero me fijo que esten bien todos los MovabeType de city o settlements
	{
		ALLEGRO_BITMAP *  temp = a.second ? dibujo[CITY] : dibujo[SETTLE];
		auto itr = sellos.find(a.first);
		if (itr == sellos.end())
		{
			ALLEGRO_BITMAP *  temp = a.second ? dibujo[CITY] : dibujo[SETTLE];
			pair<unsigned int, unsigned int> pos = toDraw.getPositioningForVertex(a.first);
			sellos[a.first] = impresora->createType(temp,
				al_map_rgba_f(1.0, 0.0, 0.0, 1.0), pos.first+BOARD_POS_X, pos.second+BOARD_POS_Y,
				al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2
			);
			impresora->addType(sellos[a.first]);
			anyChange = true;
		}
		else if (itr->second->getBitmap() != temp)
		{
			itr->second->setBitmap(temp); // el caso de que haya cambiado un settlement a city
			anyChange = true;
		}
	}

	for (auto edge : localPlayer->getMyRoads())
	{
		auto itr = roads.find(edge);
		if (itr == roads.end()) // si no esta lo tengo que crear
		{
			float angle_rot;
			if (edge.length() == 2)
			{
				if ((edge[1] - edge[0]) == 1)
				{
					angle_rot = 0;
				}
				else if (edge[0] <= '9' && edge[0] >= '0')
				{
					angle_rot = ALLEGRO_PI * (((float)(1 - 2 * (edge[0] - '0'))) / 3);
				}
				else
				{
					float sing = ((edge[1] - edge[0]) % 2 ? -1 : 1); // si la diferencia es par va inclinado para un lado
					if (edge[0] >= 'D' && edge[0] <= 'L') { sing = (sing * -1); }
					angle_rot = sing * ALLEGRO_PI / 3;
				}
			}
			else // aristas de 3 letras
			{
				float desv = 0;
				switch (edge[0] - '0')
				{
				case 0:desv = ((edge[1] - edge[2]) > 0 ? 1.0 / 3.0 : -1.0 / 3.0); break;
				case 1:desv = ((edge[1] - edge[2]) > 0 ? -1.0 / 3.0 : 0); break;
				case 2:desv = ((edge[1] - edge[2]) > 0 ? 0 : 1.0 / 3.0); break;
				case 3:desv = ((edge[1] - edge[2]) == 1 ? -1.0 / 3.0 : 1.0 / 3.0); break;
				case 4:desv = ((edge[1] - edge[2]) & 0xF0 ? -1.0 / 3.0 : 0); break;
				case 5:desv = ((edge[1] - edge[2]) & 0xF0 ? 0 : 1.0 / 3.0); break;
				}
				angle_rot = ALLEGRO_PI * desv;
			}

			pair<unsigned int, unsigned int> pos = toDraw.getPositioningForEdge(edge);

			roads[edge] = impresora->createType(dibujo[ROAD], al_map_rgba_f(1.0, 0, 0, 1.0),
				pos.first+BOARD_POS_X, pos.second+BOARD_POS_Y,
				al_get_bitmap_width(dibujo[ROAD]) / 2, al_get_bitmap_height(dibujo[ROAD]) / 2,
				1, 1, angle_rot
			);
		}
		anyChange = true;
	}//listo los roads
	

}

bool LocalObs::isOK()
{
	return working;
}
