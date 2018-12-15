#include "BoardObserver.h"
#include "BoardController.h"


#define MAP_FILE "mapaFinal.png"
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

BoardObserver::BoardObserver()
{
	init();
	update();
}


BoardObserver::~BoardObserver()
{
	delete decoder;
}

void BoardObserver::update()
{
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
		pair<unsigned int, unsigned int> pos = decoder->getPositioningForToken(letra);
		al_draw_rotated_bitmap(temp,
			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
			pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
			ALLEGRO_PI*((((float)i) / 3) - 1), 0);
	}

	for (int i = 0; i < 19; i++) // dibujo los hex
	{
		ALLEGRO_BITMAP *  temp = NULL;
		switch (board->getResourceFromHex('A'+i))
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
		pair<unsigned int, unsigned int> pos = decoder->getPositioningForToken(letra);
		al_draw_rotated_bitmap(temp,
			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
			pos.first + BOARD_POS_X, pos.second + BOARD_POS_Y,
			0, 0);
	}
}

void BoardObserver::init()
{
	decoder = new MapDecoder(MAP_FILE);

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
	bitmaps[SETTLEMENT_FILE] = al_load_bitmap(SETTLEMENT_FILE);
	bitmaps[CITY_FILE] = al_load_bitmap(CITY_FILE);
	bitmaps[ROAD_FILE] = al_load_bitmap(ROAD_FILE);
	bitmaps[ROBBER_FILE] = al_load_bitmap(ROBBER_FILE);
}
