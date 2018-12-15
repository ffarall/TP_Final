#include "BoardObsAndCon.h"
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

BoardObsAndCon::BoardObsAndCon()
{
	init();
	update();
}


BoardObsAndCon::~BoardObsAndCon()
{
	delete controller;
	delete decoder;
}

void BoardObsAndCon::init()
{
	controller = new BoardController;
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
