#include "BoardObsAndCon.h"
#include "BoardController.h"

#define MAP_FILE ""

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
