#include "BoardObsAndCon.h"
#include "BoardController.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#define HILLS_HEX_FILE "colinas.png"
#define WOODS_HEX_FILE "bosque.png"
#define MOUNTAINS_HEX_FILE "monta�a.png"
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
#define DEV_FILE "DevBack2.png"

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
	if (!fondoListo)
	{
		fondoListo = true;
		drawMap();
	}
	
	if (sellos[ROBBER_FILE] == NULL)
	{
		string foo;
		foo += board->getRobberPos();
		pair<unsigned int, unsigned int > pos = ((BoardController*)controller)->getDecoder()->getPositioningForToken(foo);
		pos.first += ROBBER_POS + BOARD_POS_X;
		pos.second += BOARD_POS_Y;
		sellos[ROBBER_FILE] = printer->createType(bitmaps[ROBBER_FILE], al_map_rgb(255, 255, 255),
			pos.first, pos.second, al_get_bitmap_width(bitmaps[ROBBER_FILE]) / 2, al_get_bitmap_height(bitmaps[ROBBER_FILE]) / 2,
			1, 1, 0, 0);
		printer->addType(sellos[ROBBER_FILE]);
	}
	else
	{
		string foo;
		foo += board->getRobberPos();
		pair<unsigned int, unsigned int > pos = ((BoardController*)controller)->getDecoder()->getPositioningForToken(foo);
		pos.first += ROBBER_POS + BOARD_POS_X;
		pos.second += BOARD_POS_Y;
		sellos[ROBBER_FILE]->setDX(pos.first);
		sellos[ROBBER_FILE]->setDY(pos.first);
	}

	if (sellos[DEV_FILE] == NULL)
	{
		al_draw_text(font, al_map_rgb(0, 0, 0), D_ANCHO*0.65, D_ALTO*0.82, 0, "Pile of DevCards");
		al_draw_tinted_bitmap(bitmaps[DEV_FILE], al_map_rgb(255, 170, 10), D_ANCHO * 0.65, D_ALTO * 0.85, 0);
	}
}

bool BoardObsAndCon::isOK()
{
	return working;
}

void BoardObsAndCon::init()
{
	controller = new BoardController;
	font = NULL;
	fondoListo = false;
	working = true;

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
	bitmaps[DEV_FILE] = al_load_bitmap(DEV_FILE);

	for (auto imagen : bitmaps) // me fijo si esta todo inicializado
	{
		if (imagen.second == NULL) { working = false; }
	}

	if (working) // si hubo alg�n problema limpio
	{
		for (auto imagen : bitmaps)
		{
			if (imagen.second != NULL) { al_destroy_bitmap(imagen.second); }
		}
	}

	if (working || (font = al_load_font("catanFont.otf", FONT_SIZE, 0))== NULL)
	{
		working = false;
	}

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
		case MONTA�AS:temp = bitmaps[MOUNTAINS_HEX_FILE]; break;
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

	

}

