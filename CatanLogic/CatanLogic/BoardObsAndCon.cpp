#include "BoardObsAndCon.h"
#include "BoardController.h"

#define MAP_FILE "mapBest3.png"

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
