#include "BoardObsAndCon.h"
#include "BoardController.h"

#define MAP_FILE "mapaFinal.png"
#define HILLS_HEX_FILE "arcillaOK.png"
#define WOODS_HEX_FILE "bosqueOK.png"
#define MOUNTAINS_HEX_FILE "montañaOK.png"
#define FIELDS_HEX_FILE "campoOK.png"
#define PASTURES_HEX_FILE "pastura.png"
#define DESERT_HEX_FILE "desiertoOK.png"
#define SEA_3X1_FILE "sea3x1.png"
#define SEA_2TX1_FILE "sea2Tx1.png"
#define SEA_2OX1_FILE "sea2Ox1.png"
#define SEA_2LX1_FILE "sea2Lx1.png"
#define SEA_2PX1_FILE "sea2Px1.png"
#define SEA_2MX1_FILE "sea2Mx1.png"

BoardObsAndCon::BoardObsAndCon()
{
	init();
}


BoardObsAndCon::~BoardObsAndCon()
{
	delete decoder;
}

void BoardObsAndCon::init()
{
	controller = new BoardController;
	decoder = new MapDecoder(MAP_FILE);
}
