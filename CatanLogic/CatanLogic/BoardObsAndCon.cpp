#include "BoardObsAndCon.h"
#include "BoardController.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#define HILLS_HEX_FILE "colinas.png"
#define WOODS_HEX_FILE "bosque.png"
#define MOUNTAINS_HEX_FILE "montaña.png"
#define FIELDS_HEX_FILE "campo.png"
#define PASTURES_HEX_FILE "pastura.png"
#define DESERT_HEX_FILE "desierto.png"
#define SEA_3X1_FILE "sea3x1.png"
#define SEA_2TX1_FILE "sea2Tx1.png"
#define SEA_2OX1_FILE "sea2Ox1.png"
#define SEA_2LX1_FILE "sea2Lx1.png"
#define SEA_2PX1_FILE "sea2Px1.png"
#define SEA_2MX1_FILE "sea2Mx1.png"
#define SETTLEMENT_FILE "settlement.png"
#define CITY_FILE "city.png"
#define ROAD_FILE "road.png"
#define ROBBER_FILE "robber.png"

#define BOARD_POS_X 310
#define BOARD_POS_Y 88
#define ROBBER_POS 20
#define CT_RAD 10
#define FONT_SIZE 14
#define D_ALTO 700
#define D_ANCHO 1200

BoardObsAndCon::BoardObsAndCon(GutenbergsPressAllegro * prnter_)
{
	printer = prnter_;
	init();
	update();
}


BoardObsAndCon::~BoardObsAndCon()
{
	delete controller;
}

void BoardObsAndCon::update()
{
	drawMap();
	for (auto edge : localPlayer->getMyRoads()) { drawRoad(edge, true); }
	for (auto edge : remotePlayer->getMyRoads()) { drawRoad(edge, false); }

	for (auto vertex : localPlayer->getMySettlements()) { drawBuilding(vertex, true, true); }
	for (auto vertex : remotePlayer->getMySettlements()) { drawBuilding(vertex, true, false); }

	for (auto vertex : localPlayer->getMyCities()) { drawBuilding(vertex, false, true); }
	for (auto vertex : remotePlayer->getMyCities()) { drawBuilding(vertex, false, false); }
}

void BoardObsAndCon::toggleSettlement()
{
	puttingSettlement = !puttingSettlement;
}

void BoardObsAndCon::toggleRoad()
{
	puttingRoad = !puttingRoad;
}

void BoardObsAndCon::toggleCity()
{
	puttingCity = !puttingCity;
}

bool BoardObsAndCon::getPuttingCity()
{
	return puttingCity;
}

bool BoardObsAndCon::getPuttingSettlement()
{
	return puttingSettlement;
}

bool BoardObsAndCon::getPuttingRoad()
{
	return puttingRoad;
}

void BoardObsAndCon::init()
{
	controller = new BoardController;
	font = NULL;

	bitmaps[HILLS_HEX_FILE] = al_load_bitmap(HILLS_HEX_FILE);
	bitmaps[WOODS_HEX_FILE] = al_load_bitmap(WOODS_HEX_FILE);
	bitmaps[MOUNTAINS_HEX_FILE] = al_load_bitmap(MOUNTAINS_HEX_FILE);
	bitmaps[FIELDS_HEX_FILE] = al_load_bitmap(FIELDS_HEX_FILE);
	bitmaps[PASTURES_HEX_FILE] = al_load_bitmap(PASTURES_HEX_FILE);
	bitmaps[DESERT_HEX_FILE] = al_load_bitmap(DESERT_HEX_FILE);
	bitmaps[SEA_3X1_FILE] = al_load_bitmap(SEA_3X1_FILE);
	bitmaps[SEA_2TX1_FILE] = al_load_bitmap(SEA_2TX1_FILE);
	bitmaps[SEA_2OX1_FILE] = al_load_bitmap(SEA_2OX1_FILE);
	bitmaps[SEA_2LX1_FILE] = al_load_bitmap(SEA_2LX1_FILE);
	bitmaps[SEA_2PX1_FILE] = al_load_bitmap(SEA_2PX1_FILE);
	bitmaps[SEA_2MX1_FILE] = al_load_bitmap(SEA_2MX1_FILE);
	bitmaps[CITY_FILE] = al_load_bitmap(CITY_FILE);
	bitmaps[ROAD_FILE] = al_load_bitmap(ROAD_FILE);
	bitmaps[SETTLEMENT_FILE] = al_load_bitmap(SETTLEMENT_FILE);
	bitmaps[ROBBER_FILE] = al_load_bitmap(ROBBER_FILE);
	bool allegOk = true;

	for (auto imagen : bitmaps) // me fijo si esta todo inicializado
	{
		if (imagen.second == NULL) { allegOk = false; }
	}

	if (!allegOk) // si hubo algún problema limpio
	{
		for (auto imagen : bitmaps)
		{
			if (imagen.second != NULL) { al_destroy_bitmap(imagen.second); }
		}
		// ver de agregar algo de error o nose
	}

	//if (!al_init_font_addon() || !al_init_primitives_addon() || !al_init_ttf_addon())
	//{
	//	allegOk = false;
	//}

	if (!allegOk || (font = al_load_font("catanFont.otf", FONT_SIZE, 0))== NULL)
	{
		allegOk = false;
	}

	puttingCity = false;
	puttingRoad = false;
	puttingSettlement = false;
}

void BoardObsAndCon::drawMap()
{

	ALLEGRO_BITMAP * fondo = al_create_bitmap(580,524);
	ALLEGRO_BITMAP * disp = al_create_bitmap(D_ANCHO, D_ALTO);

	ALLEGRO_DISPLAY * tempDisplay = al_get_current_display();

	al_set_target_bitmap(fondo);

	for (int i = 0; i < 6; i++) // dibujo el agua
	{
		ALLEGRO_BITMAP *  temp = NULL;
		switch (board->getPortType('0' + i))
		{
		case PortType::_2Lx1: temp = bitmaps[SEA_2LX1_FILE]; break;
		case PortType::_2Mx1:temp = bitmaps[SEA_2MX1_FILE]; break;
		case PortType::_2Ox1:temp = bitmaps[SEA_2OX1_FILE]; break;
		case PortType::_2Px1:temp = bitmaps[SEA_2PX1_FILE]; break;
		case PortType::_2Tx1:temp = bitmaps[SEA_2TX1_FILE]; break;
		case PortType::_3x1:temp = bitmaps[SEA_3X1_FILE]; break;
		}
		string letra = "0";
		letra[0] += i;
		pair<unsigned int, unsigned int> pos = ((BoardController*)controller)->getDecoder()->getPositioningForToken(letra);
		al_draw_rotated_bitmap(temp,
			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
			pos.first, pos.second ,
			ALLEGRO_PI*((((float)i) / 3) - 1), 0);
	}

	for (int i = 0; i < 19; i++) // dibujo los hex
	{
		ALLEGRO_BITMAP *  temp = NULL;
		switch (board->getResourceFromHex('A' + i))
		{
		case BOSQUE: temp = bitmaps[WOODS_HEX_FILE]; break;
		case COLINAS:temp = bitmaps[HILLS_HEX_FILE]; break;
		case MONTAÑAS:temp = bitmaps[MOUNTAINS_HEX_FILE]; break;
		case CAMPOS:temp = bitmaps[FIELDS_HEX_FILE]; break;
		case PASTOS:temp = bitmaps[PASTURES_HEX_FILE]; break;
		case DESIERTO:temp = bitmaps[DESERT_HEX_FILE]; break;
		}

		string letra = "A";
		letra[0] += i;
		pair<unsigned int, unsigned int> pos = ((BoardController*)controller)->getDecoder()->getPositioningForToken(letra);
		al_draw_rotated_bitmap(temp,
			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
			pos.first , pos.second ,
			0, 0);
		if ((board->getResourceFromHex('A' + i)) != DESIERTO)
		{
			al_draw_filled_circle(pos.first , pos.second , CT_RAD, al_map_rgb(255, 255, 255));
			al_draw_circle(pos.first , pos.second , CT_RAD, al_map_rgb(0, 0, 0), 1);//revisar
			string ctoken = to_string(board->getCircToken(letra[0])).c_str();
			al_draw_text(font, al_map_rgb(0, 0, 0), pos.first, pos.second - CT_RAD / 2, ALLEGRO_ALIGN_CENTRE, ctoken.c_str());
		}
	}
	// hasta aca dibujo el mapa en un bitmap
	al_set_target_bitmap(disp);
	al_draw_bitmap(fondo, BOARD_POS_X, BOARD_POS_Y, 0);
	printer->setBackgorund(disp);

	al_set_target_backbuffer(tempDisplay);

	pair<unsigned int, unsigned int> robberPos = ((BoardController*)controller)->getDecoder()->getPositioningForToken(to_string(board->getRobberPos()));
	al_draw_bitmap(bitmaps[ROBBER_FILE],
		robberPos.first + BOARD_POS_X + ROBBER_POS, robberPos.second + BOARD_POS_Y + ROBBER_POS,
		0); // dibujo el robber0

}

void BoardObsAndCon::drawRoad(string edge, bool player)
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

	pair<unsigned int, unsigned int> pos = ((BoardController*)controller)->getDecoder()->getPositioningForEdge(edge);

	al_draw_tinted_rotated_bitmap(bitmaps[ROAD_FILE],
		player ? al_map_rgba_f(1, 0, 0, 1) : al_map_rgba_f(0, 0, 1, 1),
		al_get_bitmap_width(bitmaps[ROAD_FILE]) / 2, al_get_bitmap_height(bitmaps[ROAD_FILE]) / 2,
		pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
		angle_rot, 0
	);
}

void BoardObsAndCon::drawBuilding(string edge, bool type, bool player)
{
	ALLEGRO_BITMAP * temp = (type ? bitmaps[CITY_FILE] : bitmaps[SETTLEMENT_FILE]);
	pair<unsigned int, unsigned int> pos = ((BoardController*)controller)->getDecoder()->getPositioningForVertex(edge);
	al_draw_tinted_rotated_bitmap(temp,
		player ? al_map_rgba_f(1, 0, 0, 1) : al_map_rgba_f(0, 0, 1, 1),
		al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
		pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
		0, 0);
}
