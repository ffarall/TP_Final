#include "LocalObserver.h"
#include "PosDef.h"

#define LADRILLO "ladrillo.png"
#define PASTO "pasto.png"
#define PIEDRA "piedra.png"
#define TRONCO "tronco.png"
#define LANA "lana.png"
#define ROAD "road.png"
#define CITY "city.png"
#define SETTLE "settlement.png"
#define ICONO "LocalPla.png"
#define FONT "catanFont.otf"
#define LROAD "LongestRoad.png"
#define LARMY "LargestArmy.png"

#define CANCEL "cruz.png"
#define ACCEPT "tick.png"
#define ROAD_BUILDING "RoadBuilding.png"
#define VICTORY_POINT "VictoryPoint.png"
#define Y_OF_PLENTY "YofP.png"
#define MONOPOLY "Monopoly.png"
#define KNIGHT "Knight.png"
#define ROBBER "robber.png"

#define FONT_SIZE 10 // ver 
#define BOARD_POS_X 310
#define BOARD_POS_Y 88

#define D_ALTO 700
#define D_ANCHO 1200

LocalObserver::LocalObserver(GutenbergsPressAllegro* printer, Player* local, LocalPlayerEnabler* playerEn, MainFSM* mainFSM_) : toDraw("mapaFinal.png")
{
	working = true;
	localPlayer = local;
	localEnabler = playerEn;
	impresora = printer;
	mainFSM = mainFSM_;

	dibujo[ICONO] = al_load_bitmap(ICONO);
	dibujo[ROAD] = al_load_bitmap(ROAD);
	dibujo[CITY] = al_load_bitmap(CITY);
	dibujo[SETTLE] = al_load_bitmap(SETTLE);
	dibujo[LROAD] = al_load_bitmap(LROAD);
	dibujo[LARMY] = al_load_bitmap(LARMY);
	dibujo[CANCEL] = al_load_bitmap(CANCEL);
	dibujo[ACCEPT] = al_load_bitmap(ACCEPT);
	dibujo[VICTORY_POINT] = al_load_bitmap(VICTORY_POINT);
	dibujo[ROAD_BUILDING] = al_load_bitmap(ROAD_BUILDING);
	dibujo[MONOPOLY] = al_load_bitmap(MONOPOLY);
	dibujo[Y_OF_PLENTY] = al_load_bitmap(Y_OF_PLENTY);
	dibujo[KNIGHT] = al_load_bitmap(KNIGHT);
	dibujo[ROBBER] = al_load_bitmap(ROBBER);

	for (auto each : dibujo) { if (each.second == NULL) { working = false; } }
	if (!working)
	{
		for (auto each : dibujo)
		{
			if (each.second != NULL)
			{
				al_destroy_bitmap(each.second);
				each.second = NULL;
			}
		}
	}

	fuente = al_load_font(FONT, FONT_SIZE, 0);

	if (fuente == NULL)
	{
		working = false;
		al_destroy_font(fuente);
	}

	cartasfotos[COLINAS] = al_load_bitmap(LADRILLO);
	cartasfotos[PASTOS] = al_load_bitmap(PASTO);
	cartasfotos[CAMPOS] = al_load_bitmap(LANA);
	cartasfotos[BOSQUE] = al_load_bitmap(TRONCO);
	cartasfotos[MONTAÑAS] = al_load_bitmap(PIEDRA);
	for (auto a : cartasfotos) { if (a.second == NULL) { working = false; } }
	if (!working)
	{
		for (auto a : cartasfotos)
		{
			if (a.second != NULL)
			{
				al_destroy_bitmap(a.second);
				a.second = NULL;
			}
		}
	}

	pair<int, MovableType*> temp(0, NULL);
	cartas[MONTAÑAS] = temp;
	cartas[PASTOS] = temp;
	cartas[COLINAS] = temp;
	cartas[BOSQUE] = temp;
	cartas[CAMPOS] = temp;
}


LocalObserver::~LocalObserver()
{
	if (working)
	{
		for (auto each : dibujo)
		{
			if (each.second != NULL) 
			{ 
				al_destroy_bitmap(each.second);
				each.second = NULL;
			}
		}
		if (fuente != NULL) { al_destroy_font(fuente); }
	}
}

void LocalObserver::update()
{
	if (mainFSM->getCurrState() == mainStates::LocalPlayer_S || mainFSM->getCurrState() == mainStates::RemotePlayer_S)
	{
		bool anyChange = false;
		map<string, bool> buildings;

		if (sellos[ICONO] == NULL)
		{
			sellos[ICONO] = impresora->createType(dibujo[ICONO], al_map_rgba(255, 255, 255, 255),
				D_ANCHO * 0.05, D_ALTO * 0.05
			);
			anyChange = true;
		}
		if (drawBuildings(true))
		{
			anyChange = true;
		}
		if (drawBuildings(false))
		{
			anyChange = true;
		}
		///************ Para el local player ************/
		//for (auto ciudad : localPlayer->getMyCities())
		//{
		//	buildings[ciudad] = true;
		//}

		//for (auto settlement : localPlayer->getMySettlements())
		//{
		//	buildings[settlement] = false;
		//}

		//for (auto a : buildings) // primero me fijo que esten bien todos los MovabeType de city o settlements
		//{
		//	ALLEGRO_BITMAP* temp = a.second ?  dibujo[SETTLE]: dibujo[CITY] ;
		//	auto itr = sellos.find(a.first);
		//	if (itr == sellos.end())
		//	{
		//		ALLEGRO_BITMAP* temp = a.second ? dibujo[SETTLE] : dibujo[CITY];
		//		pair<unsigned int, unsigned int> pos = toDraw.getPositioningForVertex(a.first);
		//		sellos[a.first] = impresora->createType(temp,
		//			al_map_rgba_f(1.0, 0.0, 0.0, 1.0), pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
		//			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2
		//		);
		//		anyChange = true;
		//	}
		//	else if (itr->second->getBitmap() != temp)
		//	{
		//		itr->second->setBitmap(temp); // el caso de que haya cambiado un settlement a city
		//		anyChange = true;
		//	}
		//}

		//for (auto edge : localPlayer->getMyRoads())
		//{
		//	auto itr = roads.find(edge);
		//	if (itr == roads.end()) // si no esta lo tengo que crear
		//	{
		//		float angle_rot;
		//		if (edge.length() == 2)
		//		{
		//			if ((edge[1] - edge[0]) == 1)
		//			{
		//				angle_rot = 0;
		//			}
		//			else if (edge[0] <= '9' && edge[0] >= '0')
		//			{
		//				angle_rot = ALLEGRO_PI * (((float)(1 - 2 * (edge[0] - '0'))) / 3);
		//			}
		//			else
		//			{
		//				float sing = ((edge[1] - edge[0]) % 2 ? -1 : 1); // si la diferencia es par va inclinado para un lado
		//				if (edge[0] >= 'D' && edge[0] <= 'L') { sing = (sing * -1); }
		//				angle_rot = sing * ALLEGRO_PI / 3;
		//			}
		//		}
		//		else // aristas de 3 letras
		//		{
		//			float desv = 0;
		//			switch (edge[0] - '0')
		//			{
		//			case 0:desv = ((edge[1] - edge[2]) > 0 ? 1.0 / 3.0 : -1.0 / 3.0); break;
		//			case 1:desv = ((edge[1] - edge[2]) > 0 ? -1.0 / 3.0 : 0); break;
		//			case 2:desv = ((edge[1] - edge[2]) > 0 ? 0 : 1.0 / 3.0); break;
		//			case 3:desv = ((edge[1] - edge[2]) == 1 ? -1.0 / 3.0 : 1.0 / 3.0); break;
		//			case 4:desv = ((edge[1] - edge[2]) & 0xF0 ? -1.0 / 3.0 : 0); break;
		//			case 5:desv = ((edge[1] - edge[2]) & 0xF0 ? 0 : 1.0 / 3.0); break;
		//			}
		//			angle_rot = ALLEGRO_PI * desv;
		//		}

		//		pair<unsigned int, unsigned int> pos = toDraw.getPositioningForEdge(edge);

		//		roads[edge] = impresora->createType(dibujo[ROAD], al_map_rgba_f(1.0, 0, 0, 1.0),
		//			pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
		//			al_get_bitmap_width(dibujo[ROAD]) / 2, al_get_bitmap_height(dibujo[ROAD]) / 2,
		//			1, 1, angle_rot
		//		);
		//	}
		//	anyChange = true;
		//}//listo los roads
		///****** Termino local **********/

		/************ idem para el remote player ************/
		for (auto ciudad : localPlayer->getRivalCities())
		{
			buildings[ciudad] = true;
		}

		for (auto settlement : localPlayer->getRivalSettlements())
		{
			buildings[settlement] = false;
		}

		for (auto a : buildings) // primero me fijo que esten bien todos los MovabeType de city o settlements
		{
			ALLEGRO_BITMAP* temp = a.second ? dibujo[SETTLE] : dibujo[CITY];
			auto itr = sellos.find(a.first);
			if (itr == sellos.end())
			{
				ALLEGRO_BITMAP* temp = a.second ? dibujo[SETTLE] : dibujo[CITY];
				pair<unsigned int, unsigned int> pos = toDraw.getPositioningForVertex(a.first);
				sellos[a.first] = impresora->createType(temp,
					al_map_rgba_f(0.0, 0.0, 1.0, 1.0), pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
					al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2
				);
				anyChange = true;
			}
			else if (itr->second->getBitmap() != temp)
			{
				itr->second->setBitmap(temp); // el caso de que haya cambiado un settlement a city
				anyChange = true;
			}
		}

		for (auto edge : localPlayer->getRivalRoads())
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

				roads[edge] = impresora->createType(dibujo[ROAD], al_map_rgba_f(0, 0, 1.0, 1.0),
					pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
					al_get_bitmap_width(dibujo[ROAD]) / 2, al_get_bitmap_height(dibujo[ROAD]) / 2,
					1, 1, angle_rot
				);
			}
			anyChange = true;
		}
		/****** Termino remote **********/

		//list<ResourceType> util = { CAMPOS,MONTAÑAS,PASTOS,COLINAS,BOSQUE };
		//int i = 0;
		//for (auto a : util)
		//{
		//	if (localPlayer->getResourceAmount(a) == 0)
		//	{
		//		if (cartas[a].second != NULL) // si no tiene cartas de este tipo saco el sello que le corresponde
		//		{
		//			impresora->delType(cartas[a].second);
		//			delete cartas[a].second;
		//			cartas[a].second = NULL;
		//			cartas[a].first = 0;
		//			anyChange = true;
		//		}
		//	}
		//	else if (localPlayer->getResourceAmount(a) != cartas[a].first) // si cambio la cantidad de cartas tengo que hacer un nuevo bitmap
		//	{
		//		if (cartas[a].second != NULL) // si ya existe el sello sobreescribo el birtmap
		//		{
		//			ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		//			ALLEGRO_BITMAP * temp = cartas[a].second->getBitmap();
		//			al_set_target_bitmap(temp);
		//			al_clear_to_color(al_map_rgb(255, 255, 255));
		//			al_draw_bitmap(cartasfotos[a], 0, 0, 0);
		//			al_draw_text(fuente, al_map_rgb(0, 0, 0), al_get_bitmap_width(temp) / 2, 57, ALLEGRO_ALIGN_CENTRE, to_string(localPlayer->getResourceAmount(a)).c_str());
		//			al_set_target_backbuffer(tempDisplay);
		//			anyChange = true;
		//		}
		//		else // si no existe lo tengo que crear
		//		{
		//			ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		//			ALLEGRO_BITMAP* temp = al_create_bitmap(35, 65);// numeros magicos
		//			al_set_target_bitmap(temp);
		//			al_clear_to_color(al_map_rgb(255, 255, 255));
		//			al_draw_bitmap(cartasfotos[a], 0, 0, 0);
		//			al_draw_text(fuente, al_map_rgb(0, 0, 0), al_get_bitmap_width(temp) / 2, 57, ALLEGRO_ALIGN_CENTRE, to_string(localPlayer->getResourceAmount(a)).c_str());
		//			al_set_target_backbuffer(tempDisplay);

		//			cartas[a].second = impresora->createType(temp,
		//				al_map_rgb(255, 255, 255), D_ANCHO * 0.05 + al_get_bitmap_width(temp) * 1.05 * i, D_ALTO * 0.3
		//			);
		//			anyChange = true;
		//		}
		//	}
		//	//si son iguales no hago nada, ya se va a imprimir bien 
		//}

		if (localPlayer->hasLargestArmy())
		{
			if (sellos[LARMY] == NULL)
			{
				sellos[LARMY] = impresora->createType(dibujo[LARMY], al_map_rgb(255, 255, 255), D_ANCHO * 0.2, D_ALTO * 0.15);
			}
		}
		else if (sellos[LARMY] != NULL)
		{
			impresora->delType(sellos[LARMY]);
			delete sellos[LARMY];
		}

		if (localPlayer->hasLongestRoad())
		{
			if (sellos[LROAD] == NULL)
			{
				sellos[LROAD] = impresora->createType(dibujo[LROAD], al_map_rgb(255, 255, 255), D_ANCHO * 0.25, D_ALTO * 0.15);
			}
		}
		else if (sellos[LROAD] != NULL)
		{
			impresora->delType(sellos[LROAD]);
			delete sellos[LROAD];
		}

		if (anyChange)
		{
			sellos[ICONO]->redraw();
		}
	}
}

bool LocalObserver::isOK()
{
	return working;
}

bool LocalObserver::drawBuildings(bool locOrRemote) // true es local, false es remote
{
	bool anyChange = false;
	map<string, bool> buildings;

	for (auto ciudad : (locOrRemote ? localPlayer->getMyCities(): localPlayer->getRivalCities()) )
	{
		buildings[ciudad] = true;
	}

	for (auto settlement :(locOrRemote? localPlayer->getMySettlements(): localPlayer->getRivalSettlements() ) )
	{
		buildings[settlement] = false;
	}

	for (auto a : buildings) // primero me fijo que esten bien todos los MovabeType de city o settlements
	{
		ALLEGRO_BITMAP* temp = a.second ? dibujo[SETTLE] : dibujo[CITY];
		auto itr = sellos.find(a.first);
		if (itr == sellos.end())
		{
			ALLEGRO_BITMAP* temp = a.second ? dibujo[SETTLE] : dibujo[CITY];
			pair<unsigned int, unsigned int> pos = toDraw.getPositioningForVertex(a.first);
			sellos[a.first] = impresora->createType(temp,
				locOrRemote?al_map_rgba_f(1.0, 0.0, 0.0, 1.0) : al_map_rgba_f(0, 0, 1.0, 1.0),
				pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
				al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2
			);
			anyChange = true;
		}
		else if (itr->second->getBitmap() != temp)
		{
			itr->second->setBitmap(temp); // el caso de que haya cambiado un settlement a city
			anyChange = true;
		}
	}

	for (auto edge : (locOrRemote ? localPlayer->getMyRoads() : localPlayer->getRivalRoads() ) )
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

			roads[edge] = impresora->createType(dibujo[ROAD], 
				locOrRemote? al_map_rgba_f(1.0, 0, 0, 1.0) : al_map_rgba_f(0, 0, 1.0, 1.0),
				pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
				al_get_bitmap_width(dibujo[ROAD]) / 2, al_get_bitmap_height(dibujo[ROAD]) / 2,
				1, 1, angle_rot
			);
		}
		anyChange = true;
	}//listo los roads

	return anyChange;
}
