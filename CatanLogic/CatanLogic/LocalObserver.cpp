#include "LocalObserver.h"
#include "PosDef.h"
#include "allegro5/allegro_primitives.h"

#define ROBBER "robber.png"
#define LADRILLO "ladrillo.png"
#define PASTO "pasto.png"
#define PIEDRA "piedra.png"
#define TRONCO "tronco.png"
#define LANA "lana.png"
#define ROAD "road.png"
#define CITY "city.png"
#define SETTLE "settlement.png"
#define ICONO "LocalPla.png"
#define ICONOR "RemotePla.png"
#define FONT "catanFont.otf"
#define LROAD "LongestRoad.png"
#define LARMY "LargestArmy.png"
#define COSTOS "BuildingCost.png"

#define CANCEL "cruz.png"
#define ACCEPT "tick.png"
#define ROAD_BUILDING "RoadBuilding.png"
#define VICTORY_POINT "VictoryPoint.png"
#define Y_OF_PLENTY "YofP.png"
#define MONOPOLY "Monopoly.png"
#define KNIGHT "Knight.png"
#define ROBBER "robber.png"
#define CARTEL "calrtel"
#define FONT_SIZE 10 // ver 
#define BOARD_POS_X 310
#define BOARD_POS_Y 88
#define ROBBER_POS 20

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
	dibujo[ICONOR] = al_load_bitmap(ICONOR);
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
	dibujo[COSTOS] = al_load_bitmap(COSTOS);
	dibujo[ROBBER] = al_load_bitmap(ROBBER);
	dibujo[CARTEL] = al_create_bitmap(475, 35);

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
	if (working)
	{
		ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		al_set_target_bitmap(dibujo[CARTEL]);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_rectangle(0, 0, 450, 35, al_map_rgb(0, 0, 0), 1);
		al_draw_text(fuente, al_map_rgb(0,0,0), al_get_bitmap_width(dibujo[CARTEL]) / 2, al_get_bitmap_height(dibujo[CARTEL])*0.4, ALLEGRO_ALIGN_CENTRE, "");
		al_set_target_backbuffer(tempDisplay);
		sellos[CARTEL] = impresora->createType(dibujo[CARTEL], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.35, D_ALTO * 0.065
		);

		sellos[ICONO] = impresora->createType(dibujo[ICONO], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.05, D_ALTO * 0.05
		);
		sellos[ICONOR] = impresora->createType(dibujo[ICONOR], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.95 - al_get_bitmap_width(dibujo[ICONOR]), D_ALTO*0.05
		);
		sellos[COSTOS] = impresora->createType(dibujo[COSTOS], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.95 - al_get_bitmap_width(dibujo[COSTOS]), D_ALTO*0.45
		);
		sellos[LARMY] = impresora->createType(dibujo[LARMY], al_map_rgba(0,0,0,0), D_ANCHO * 0.2, D_ALTO * 0.15);
		sellos[LROAD] = impresora->createType(dibujo[LROAD], al_map_rgba(0, 0, 0, 0), D_ANCHO * 0.25, D_ALTO * 0.15);


	}
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
	if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
	{
		bool anyChange = false;
		map<string, bool> buildings;

		if (sellos[ROBBER] == NULL)
		{
			sellos[ROBBER] = impresora->createType(dibujo[ROBBER], al_map_rgba(0, 0, 0, 0),
				0, 0, al_get_bitmap_width(dibujo[ROBBER]) / 2, al_get_bitmap_height(dibujo[ROBBER]) / 2,
				1, 1, 0, 0);
		}
		string foo;
		foo += localEnabler->getRobberPos();
		pair<unsigned int, unsigned int > pos = toDraw.getPositioningForToken(foo);
		//pos.first += ROBBER_POS + BOARD_POS_X;
		//pos.second += BOARD_POS_Y;
		sellos[ROBBER]->setTint(al_map_rgba(255, 255, 255, 255));
		sellos[ROBBER]->setDX(pos.first);
		sellos[ROBBER]->setDY(pos.second);

		ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		string temp = localEnabler->getWaitingMessage();
		al_set_target_bitmap(dibujo[CARTEL]);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_rectangle(1, 1, 449, 34, al_map_rgb(0, 0, 0), 1);
		al_draw_text(fuente, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo[CARTEL]) / 2, al_get_bitmap_height(dibujo[CARTEL])*0.4, ALLEGRO_ALIGN_CENTRE, temp.c_str());
		al_set_target_backbuffer(tempDisplay);
		sellos[CARTEL]->setTint(al_map_rgba(255, 255, 255, 255));

		sellos[ICONO]->setTint(al_map_rgba(255, 255, 255, 255));
		
		sellos[ICONOR]->setTint(al_map_rgba(120, 120, 120, 120));

		sellos[COSTOS]->setTint(al_map_rgba(255, 255, 255, 255));
		
		if (drawBuildings(true))
		{
			anyChange = true;
		}
		if (drawBuildings(false))
		{
			anyChange = true;
		}
		
		if (localPlayer->hasLargestArmy())
		{
			sellos[LARMY]->setDX(D_ANCHO * 0.2);
			sellos[LARMY]->setDY(D_ALTO * 0.15);
			sellos[LARMY]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		else
		{
			sellos[LARMY]->setTint(al_map_rgba(0, 0, 0, 0));
		}
		
		if (localPlayer->hasLongestRoad())
		{
			sellos[LROAD]->setDX(D_ANCHO * 0.25);
			sellos[LROAD]->setDY(D_ALTO * 0.15);
			sellos[LROAD]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		else
		{
			sellos[LROAD]->setTint(al_map_rgba(0, 0, 0, 0));
		}
		
		if (anyChange)
		{
			sellos.begin()->second->redraw();
		}
	}
	else if (mainFSM->getCurrState() == mainStates::RemotePlayer_S)
	{
		if (sellos[ROBBER] == NULL)
		{
			sellos[ROBBER] = impresora->createType(dibujo[ROBBER], al_map_rgba(0, 0, 0, 0),
				0, 0, al_get_bitmap_width(dibujo[ROBBER]) / 2, al_get_bitmap_height(dibujo[ROBBER]) / 2,
				1, 1, 0, 0);
		}

		string foo;
		foo += localEnabler->getRobberPos();
		pair<unsigned int, unsigned int > pos = toDraw.getPositioningForToken(foo);
		pos.first += ROBBER_POS + BOARD_POS_X;
		pos.second += BOARD_POS_Y;
		sellos[ROBBER]->setTint(al_map_rgba(255, 255, 255, 255));
		sellos[ROBBER]->setDX(pos.first);
		sellos[ROBBER]->setDY(pos.second);

		ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		string temp = localEnabler->getWaitingMessage();
		al_set_target_bitmap(dibujo[CARTEL]);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_rectangle(1, 1, 449, 34, al_map_rgb(0, 0, 0), 1);
		al_draw_text(fuente, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo[CARTEL]) / 2, al_get_bitmap_height(dibujo[CARTEL])*0.4, ALLEGRO_ALIGN_CENTRE, temp.c_str());
		al_set_target_backbuffer(tempDisplay);
		sellos[CARTEL]->setTint(al_map_rgba(255, 255, 255, 255));

		sellos[ICONO]->setTint(al_map_rgba(120, 120, 120, 120));

		sellos[ICONOR]->setTint(al_map_rgba(255, 255, 255, 255));

		sellos[COSTOS]->setTint(al_map_rgba(255, 255, 255, 255));

		drawBuildings(true);
		drawBuildings(false);
	
		sellos.begin()->second->redraw();

	}
	else
	{
		for (auto cada : sellos)
		{
			if (cada.second != NULL)
			{
				cada.second->setTint(al_map_rgba(0, 0, 0, 0));// los hago trasparentes
			}
		}
		for (auto cada : roads)
		{
			if (cada.second != NULL)
			{
				cada.second->setTint(al_map_rgba(0, 0, 0, 0));// los hago trasparentes
			}
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
