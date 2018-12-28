#include "BoardController.h"
#include "SubEvents.h"
#include <string>

#define MAP_FILE "mapaFinal.png"

using namespace std;

BoardController::BoardController()
{
}

BoardController::BoardController(EventsHandler * handler_) : BasicController(handler_)
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
			if (decoder->getPixelType(x, y) == VERTEX)
			{
				string vertex = decoder->getCoordinateFromPixel(x, y);
				SettlementPkg* setPkg = new SettlementPkg(vertex);
				emitSubEvent(PLAYER_ACTION, PLA_SETTLEMENT, setPkg);

				return POSITION_SELECTED;
			}
		}
		else if (getPuttingRoad())												// When user has to select where to put Road.
		{
			if (decoder->getPixelType(x, y) == EDGE)
			{
				string edge = decoder->getCoordinateFromPixel(x, y);
				RoadPkg* roadPkg = new RoadPkg(edge);
				emitSubEvent(PLAYER_ACTION, PLA_ROAD, roadPkg);

				return POSITION_SELECTED;
			}
		}
		else if (getPuttingCity())												// When user has to select where to put City.
		{
			if (decoder->getPixelType(x, y) == VERTEX)
			{
				string vertex = decoder->getCoordinateFromPixel(x, y);
				CityPkg* cityPkg = new CityPkg(vertex);
				emitSubEvent(PLAYER_ACTION, PLA_CITY, cityPkg);

				return POSITION_SELECTED;
			}
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


