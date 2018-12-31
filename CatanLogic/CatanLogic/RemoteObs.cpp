#include "RemoteObs.h"

#define ROAD "road.png"
#define CITY "city.png"
#define SETTLE "setllement.png"
#define ICONO "RemotePla.png"
#define FONT "catanFont.otf"
#define LROAD "LongestRoad.png"
#define LARMY "LargestArmy.png"

#define FONT_SIZE 10 // ver 
#define BOARD_POS_X 310
#define BOARD_POS_Y 88

#define D_ALTO 700
#define D_ANCHO 1200


RemoteObs::RemoteObs(GutenbergsPressAllegro * printer, Player * remote, RemotePlayerEnabler * remoteEn)
{
	working = true;
	remotePlayer = remote;
	remoteEnabler = remoteEn;
	impresora = printer;

	bitmaps[ICONO] = al_load_bitmap(ICONO);
	bitmaps[ROAD] = al_load_bitmap(ROAD);
	bitmaps[CITY] = al_load_bitmap(CITY);
	bitmaps[SETTLE] = al_load_bitmap(SETTLE);
	bitmaps[LROAD] = al_load_bitmap(LROAD);
	bitmaps[LARMY] = al_load_bitmap(LARMY);

	for (auto each : bitmaps) { if (each.second == NULL) { working = false; } }
	if (!working)
	{
		for (auto each : bitmaps)
		{
			if (each.second != NULL)
			{
				al_destroy_bitmap(each.second);
			}
		}
	}

	fuente = al_load_font(FONT, FONT_SIZE, 0);

	if (fuente == NULL)
	{
		working = false;
		al_destroy_font(fuente);
	}

}


RemoteObs::~RemoteObs()
{
	if (working)
	{
		for (auto each : bitmaps)
		{
			if (each.second != NULL) { al_destroy_bitmap(each.second); }
		}
		if (fuente != NULL) { al_destroy_font(fuente); }
	}
}

void RemoteObs::update()
{
	bool anyChange = false;
	map<string, bool> buildings;
	// D_ANCHO * 0.95 - al_get_bitmap_width(visitante), D_ALTO*0.05
	if (sellos[ICONO] == NULL)
	{
		sellos[ICONO] = impresora->createType(bitmaps[ICONO], al_map_rgb(255, 255, 255),
			D_ANCHO * 0.95 - al_get_bitmap_width(bitmaps[ICONO]), D_ALTO*0.05
		);
		impresora->addType(sellos[ICONO]);
	}

	for (auto ciudad : remotePlayer->getMyCities())
	{
		buildings[ciudad] = true;
	}

	for (auto settlement : remotePlayer->getMySettlements())
	{
		buildings[settlement] = false;
	}

	for (auto a : buildings) // primero me fijo que esten bien todos los MovabeType de city o settlements
	{
		ALLEGRO_BITMAP *  temp = a.second ? bitmaps[CITY] : bitmaps[SETTLE];
		auto itr = sellos.find(a.first);
		if (itr == sellos.end())
		{
			ALLEGRO_BITMAP *  temp = a.second ? bitmaps[CITY] : bitmaps[SETTLE];
			pair<unsigned int, unsigned int> pos = toDraw.getPositioningForVertex(a.first);
			sellos[a.first] = impresora->createType(temp,
				al_map_rgba_f(0.0, 0.0, 1.0, 1.0), pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
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

	for (auto edge : remotePlayer->getMyRoads())
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

			roads[edge] = impresora->createType(bitmaps[ROAD], al_map_rgba_f(0.0, 0.0, 1.0, 1.0),
				pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
				al_get_bitmap_width(bitmaps[ROAD]) / 2, al_get_bitmap_height(bitmaps[ROAD]) / 2,
				1, 1, angle_rot
			);
		}
		anyChange = true;
	}//listo los roads

	if (remotePlayer->hasLargestArmy())
	{
		if (sellos[LARMY] == NULL)
		{
			sellos[LARMY] = impresora->createType(bitmaps[LARMY], al_map_rgb(255, 255, 255), D_ANCHO * 0.72, D_ALTO * 0.15);
		}
	}
	else if (sellos[LARMY] != NULL)
	{
		impresora->delType(sellos[LARMY]);
		delete sellos[LARMY];
	}

	if (remotePlayer->hasLongestRoad())
	{
		if (sellos[LROAD] == NULL)
		{
			sellos[LROAD] = impresora->createType(bitmaps[LROAD], al_map_rgb(255, 255, 255), D_ANCHO * 0.77, D_ALTO * 0.15);
		}
	}
	else if (sellos[LROAD] != NULL)
	{
		impresora->delType(sellos[LROAD]);
		delete sellos[LROAD];
	}
}

bool RemoteObs::isOK()
{
	return working;
}
