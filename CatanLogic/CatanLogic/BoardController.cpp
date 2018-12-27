#include "BoardController.h"

#define MAP_FILE "mapaFinal.png"

BoardController::BoardController()
{
}


BoardController::~BoardController()
{
	delete decoder;
}

GUIEnablerEvent BoardController::parseMouseEvent(uint32_t x, uint32_t y)
{
	return GUIEnablerEvent();
}

GUIEnablerEvent BoardController::parseTimerEvent()
{
	return GUIEnablerEvent();
}

MapDecoder * BoardController::getDecoder()
{
	return decoder;
}

void BoardController::init()
{
	decoder = new MapDecoder(MAP_FILE);
}


