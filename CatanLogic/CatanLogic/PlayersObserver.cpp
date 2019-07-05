#include "PlayersObserver.h"
#include "PosDef.h"
#include "allegro5/allegro_primitives.h"

#define ROBBER "Imagenes/robber.png"
#define LADRILLO "Imagenes/ladrillo.png"
#define PASTO "Imagenes/pasto.png"
#define PIEDRA "Imagenes/piedra.png"
#define TRONCO "Imagenes/tronco.png"
#define LANA "Imagenes/lana.png"
#define ROAD "Imagenes/road.png"
#define CITY "Imagenes/city.png"
#define SETTLE "Imagenes/settlement.png"
#define ICONO "Imagenes/LocalPla.png"
#define ICONOR "Imagenes/RemotePla.png"
#define FONT "catanFont.otf"
#define LROAD "Imagenes/LongestRoad.png"
#define LARMY "Imagenes/LargestArmy.png"
#define COSTOS "Imagenes/BuildingCost.png"

#define CANCEL "Imagenes/cruz.png"
#define ACCEPT "Imagenes/tick.png"
#define ROAD_BUILDING "Imagenes/RoadBuilding.png"
#define VICTORY_POINT "Imagenes/VictoryPoint.png"
#define Y_OF_PLENTY "Imagenes/YofP.png"
#define MONOPOLY "Imagenes/Monopoly.png"
#define KNIGHT "Imagenes/Knight.png"
#define ROBBER "Imagenes/robber.png"
#define CARTEL "calrtel"
#define FONT_SIZE 10 // ver
#define NAME_SIZE 17
#define BOARD_POS_X 310
#define BOARD_POS_Y 88
#define ROBBER_POS 20

#define D_ALTO 700
#define D_ANCHO 1200

PlayersObserver::PlayersObserver(GutenbergsPressAllegro* printer, Player* local, Player * remote, LocalPlayerEnabler* playerEn, RemotePlayerEnabler * remoteEnab, MainFSM* mainFSM_) : toDraw("Imagenes/mapaFinal.png")
{
	working = true;
	localPlayer = local;
	remotePlayer = remote;
	localEnabler = playerEn;
	remoteEnabler = remoteEnab;
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
	dibujo[CARTEL] = al_create_bitmap(550, 35);
	dibujo["pla1"] = al_create_bitmap(150, 225);
	dibujo["pla2"] = al_create_bitmap(150, 225);

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
	playerName = al_load_font(FONT, NAME_SIZE, 0);
	if (fuente == NULL || playerName == NULL)
	{
		working = false;
		if (fuente != NULL)
		{
			al_destroy_font(fuente);
		}
		else
		{
			al_destroy_font(playerName);
		}
	}
	if (working)
	{
		ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		al_set_target_bitmap(dibujo[CARTEL]);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_rectangle(1, 1, 549, 34, al_map_rgb(0, 0, 0), 1);
		al_draw_text(fuente, al_map_rgb(0,0,0), al_get_bitmap_width(dibujo[CARTEL]) / 2, al_get_bitmap_height(dibujo[CARTEL])*0.4, ALLEGRO_ALIGN_CENTRE, "");
		al_set_target_backbuffer(tempDisplay);
		sellos[CARTEL] = impresora->createType(dibujo[CARTEL], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.35, D_ALTO * 0.065
		);

		sellos[ICONO] = impresora->createType(dibujo["pla1"], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.05, D_ALTO * 0.05-35
		);
		sellos[ICONOR] = impresora->createType(dibujo["pla2"], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.95 - al_get_bitmap_width(dibujo["pla2"]), D_ALTO*0.05-35
		);

		sellos[COSTOS] = impresora->createType(dibujo[COSTOS], al_map_rgba(0, 0, 0, 0),
			D_ANCHO * 0.95 - al_get_bitmap_width(dibujo[COSTOS]), D_ALTO*0.45
		);
		sellos[LARMY] = impresora->createType(dibujo[LARMY], al_map_rgba(0,0,0,0), D_ANCHO * 0.2, D_ALTO * 0.15);
		sellos[LROAD] = impresora->createType(dibujo[LROAD], al_map_rgba(0, 0, 0, 0), D_ANCHO * 0.25, D_ALTO * 0.15);

	}
}


PlayersObserver::~PlayersObserver()
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

void PlayersObserver::update()
{
	if (mainFSM->getCurrState() == mainStates::LocalPlayer_S || mainFSM->getCurrState() == mainStates::RemotePlayer_S)
	{
		// primero dibujo las cosas que son comunes y no cambian con que jugadore este jugando
		
		ALLEGRO_DISPLAY* tempDisplay = al_get_current_display();
		string temp = localEnabler->getErrMessage();
		if (temp.compare("") == 0)
		{
			temp = remoteEnabler->getErrMessage();
			if (temp.compare("") == 0)
			{
				temp = localEnabler->getWaitingMessage();
				if (temp.compare("") == 0)
				{
					temp = remoteEnabler->getWaitingMessage();
				}
			}
		}
		al_set_target_bitmap(dibujo[CARTEL]);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_rectangle(1, 1, 549, 34, al_map_rgb(0, 0, 0), 1);
		al_draw_text(fuente, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo[CARTEL]) / 2, al_get_bitmap_height(dibujo[CARTEL])*0.4, ALLEGRO_ALIGN_CENTRE, temp.c_str());
		sellos[CARTEL]->setTint(al_map_rgba(255, 255, 255, 255));

		drawBuildings(true);
		drawBuildings(false);
		
		if (localPlayer->hasLargestArmy())
		{
			sellos[LARMY]->setCX(D_ANCHO * 0.2);
			sellos[LARMY]->setCY(D_ALTO * 0.15);
			sellos[LARMY]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		else if (remotePlayer->hasLargestArmy())
		{
			sellos[LARMY]->setCX(D_ANCHO * 0.72);
			sellos[LARMY]->setCY(D_ALTO * 0.15);
			sellos[LARMY]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		else
		{
			sellos[LARMY]->setTint(al_map_rgba(0, 0, 0, 0));
		}

		if (localPlayer->hasLongestRoad())
		{
			sellos[LROAD]->setCX(D_ANCHO * 0.25);
			sellos[LROAD]->setCY(D_ALTO * 0.15);
			sellos[LROAD]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		else if (remotePlayer->hasLongestRoad())
		{
			sellos[LROAD]->setCX(D_ANCHO * 0.77);
			sellos[LROAD]->setCY(D_ALTO * 0.15);
			sellos[LROAD]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		else
		{
			sellos[LROAD]->setTint(al_map_rgba(0, 0, 0, 0));
		}

		sellos[COSTOS]->setTint(al_map_rgba(255, 255, 255, 255));

		al_set_target_bitmap(sellos[ICONO]->getBitmap());
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_bitmap(dibujo[ICONO], 0, 25, 0);
		string name = localPlayer->getName();
		if (name.size() > 10)
		{
			name = name.substr(0, 10);
			name += "...";
		}
		al_draw_text(playerName, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo["pla1"])*0.1, al_get_bitmap_height(dibujo["pla1"])*0.05, ALLEGRO_ALIGN_LEFT, name.c_str());
		name.clear();
		name = "Victory Points: " + to_string(localPlayer->getVictoryPoints());
		al_draw_text(playerName, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo["pla1"])*0.1, al_get_bitmap_height(dibujo["pla1"])*0.8, ALLEGRO_ALIGN_LEFT, name.c_str());
		
		if (localEnabler->areWePlayingWithDev())
		{
			name.clear();
			name = "Army size: " + to_string(localPlayer->getArmySize());
			al_draw_text(playerName, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo["pla1"])*0.1, al_get_bitmap_height(dibujo["pla1"])*0.9, ALLEGRO_ALIGN_LEFT, name.c_str());
		}
		name.clear();

		al_set_target_bitmap(sellos[ICONOR]->getBitmap());
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_bitmap(dibujo[ICONOR], 0, 25, 0);
		name = remotePlayer->getName();
		if (name.size() > 10)
		{
			name = name.substr(0, 10);
			name += "...";
		}
		al_draw_text(playerName, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo["pla2"])*0.9, al_get_bitmap_height(dibujo["pla2"])*0.05, ALLEGRO_ALIGN_RIGHT, name.c_str());
		name.clear();
		name = "Victory Points: " + to_string(remotePlayer->getVictoryPoints());
		al_draw_text(playerName, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo["pla1"])*0.9, al_get_bitmap_height(dibujo["pla1"])*0.8, ALLEGRO_ALIGN_RIGHT, name.c_str());

		if (localEnabler->areWePlayingWithDev())
		{
			name.clear();
			name = "Army size: " + to_string(remotePlayer->getArmySize());
			al_draw_text(playerName, al_map_rgb(0, 0, 0), al_get_bitmap_width(dibujo["pla1"])*0.9, al_get_bitmap_height(dibujo["pla1"])*0.9, ALLEGRO_ALIGN_RIGHT, name.c_str());
		}
		
		if (mainFSM->getCurrState() == mainStates::LocalPlayer_S)
		{
			sellos[ICONO]->setTint(al_map_rgba(255, 255, 255, 255));

			sellos[ICONOR]->setTint(al_map_rgba(120, 120, 120, 120));
		}
		else
		{
			sellos[ICONO]->setTint(al_map_rgba(120, 120, 120, 120));

			sellos[ICONOR]->setTint(al_map_rgba(255, 255, 255, 255));
		}
		
		al_set_target_backbuffer(tempDisplay);

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
		for (auto cada : roads) // elimino todos los roads para la proxima partida
		{
			if (cada.second != NULL)
			{
				impresora->delType(cada.second);
			}
		}
		roads.clear();
		for (auto cada : estructuras) // elimino settlement y city para la proxima partida
		{
			if (cada.second != NULL)
			{
				impresora->delType(cada.second);
			}
		}
		estructuras.clear();
	}
}

bool PlayersObserver::isOK()
{
	return working;
}

bool PlayersObserver::drawBuildings(bool locOrRemote) // true es local, false es remote
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
		auto itr = estructuras.find(a.first);
		if (itr == estructuras.end())
		{
			ALLEGRO_BITMAP* temp = a.second ? dibujo[SETTLE] : dibujo[CITY];
			pair<unsigned int, unsigned int> pos = toDraw.getPositioningForVertex(a.first);
			estructuras[a.first] = impresora->createType(temp,
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
