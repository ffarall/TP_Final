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
	if (isMouseActive())
	{
		if (getPuttingSettlement())												// When user has to select where to put Settlement.
		{

		}
		else if (getPuttingRoad())												// When user has to select where to put Road.
		{
			
		}
		else if (getPuttingCity())												// When user has to select where to put City.
		{

		}
	}

	return NO_EV;
}

GUIEnablerEvent BoardController::parseTimerEvent()
{
	if (isTimerActive())
	{

	}

	return NO_EV;
}

MapDecoder * BoardController::getDecoder()
{
	return decoder;
}

void BoardController::toggleSettlement()
{
	puttingSettlement = !puttingSettlement;
}

void BoardController::toggleRoad()
{
	puttingRoad = !puttingRoad;
}

void BoardController::toggleCity()
{
	puttingCity = !puttingCity;
}

bool BoardController::getPuttingCity()
{
	return puttingCity;
}

bool BoardController::getPuttingSettlement()
{
	return puttingSettlement;
}

bool BoardController::getPuttingRoad()
{
	return puttingRoad;
}

void BoardController::init()
{
	decoder = new MapDecoder(MAP_FILE);
}


