#include "BoardController.h"
#include "SubEvents.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"
#include <string>

#define MAP_FILE "mapaFinal.png"

#define HILLS_HEX_FILE "colinas.png"
#define WOODS_HEX_FILE "bosque.png"
#define MOUNTAINS_HEX_FILE "montana.png"
#define FIELDS_HEX_FILE "campo.png"
#define PASTURES_HEX_FILE "pastura.png"
#define DESERT_HEX_FILE "desierto.png"
#define SEA_3X1_FILE "sea3x1.png"
#define SEA_2TX1_FILE "sea2Tx1.png"
#define SEA_2OX1_FILE "sea2Ox1.png"
#define SEA_2LX1_FILE "sea2Lx1.png"
#define SEA_2PX1_FILE "sea2Px1.png"
#define SEA_2MX1_FILE "sea2Mx1.png"
#define ROBBER_FILE "robber.png"
#define FONDO "fondo.jpg"
#define BACKGROUND "Backround.jpg"
#define BOARD_POS_X 310
#define BOARD_POS_Y 88
#define ROBBER_POS 20
#define CT_RAD 10
#define FONT_SIZE 14
#define D_ALTO 700
#define D_ANCHO 1200

using namespace std;

BoardController::BoardController()
{
}

BoardController::BoardController(EventsHandler * handler_, GutenbergsPressAllegro * prnter_, MainFSM* mainFSM_, Board* board_, PlayerEnabler* locEnab_) : BasicController(handler_)
{
	printer = prnter_;
	mainFSM = mainFSM_;
	board = board_;
	locEnab = locEnab_;
	init();
}


BoardController::~BoardController()
{
	delete decoder;
}

void BoardController::update()
{
	if (mainFSM->getCurrState() == mainStates::LocalPlayer_S || mainFSM->getCurrState() == mainStates::RemotePlayer_S)
	{
		if (!fondoListo)
		{
			fondoListo = true;
			fondoPpal = false;
			drawMap();
		}

		string foo;
		foo += board->getRobberPos();
		pair<unsigned int, unsigned int > pos = getDecoder()->getPositioningForToken(foo);
		pos.first += ROBBER_POS + BOARD_POS_X;
		pos.second += BOARD_POS_Y;
		sellos[ROBBER_FILE]->setCX(pos.first);
		sellos[ROBBER_FILE]->setCY(pos.second);
		sellos[ROBBER_FILE]->setTint(al_map_rgba(255, 255, 255, 255));
		sellos[ROBBER_FILE]->redraw();

	
	}
	else
	{
		if (!fondoPpal)
		{
			printer->setBackgorund(bitmaps[BACKGROUND]);
			fondoPpal = true;
			fondoListo = false;
		}
		sellos[ROBBER_FILE]->setTint(al_map_rgba(0, 0, 0, 0));
	}
}

bool BoardController::isOK()
{
	return working;
}

GUIEnablerEvent BoardController::parseMouseDownEvent(uint32_t x, uint32_t y)
{
	if (isMouseDownActive())
	{
		unsigned char temp = decoder->getPixelType(x - BOARD_POS_X , y - BOARD_POS_Y);
		if (temp == VERTEX || temp == EDGE || temp == TOKEN)
		{
			enableMouseUp();
			return NO_EV;
		}
	}

	return NO_EV;
}

GUIEnablerEvent BoardController::parseMouseUpEvent(uint32_t x, uint32_t y)
{
	x -= BOARD_POS_X;
	y -= BOARD_POS_Y;
	if (isMouseUpActive())
	{
		disableMouseUp();
		if (getPuttingSettlement())												// When user has to select where to put Settlement.
		{
			if (decoder->getPixelType(x, y) == VERTEX)
			{
				string vertex = decoder->getCoordinateFromPixel(x, y);
				SettlementPkg* setPkg = new SettlementPkg(vertex);
				emitSubEvent(PLAYER_ACTION, PLA_SETTLEMENT, setPkg);
			}
		}
		else if (getPuttingRoad())												// When user has to select where to put Road.
		{
			if (decoder->getPixelType(x, y) == EDGE)
			{
				string edge = decoder->getCoordinateFromPixel(x, y);
				RoadPkg* roadPkg = new RoadPkg(edge);
				emitSubEvent(PLAYER_ACTION, PLA_ROAD, roadPkg);
			}
		}
		else if (getPuttingCity())												// When user has to select where to put City.
		{
			if (decoder->getPixelType(x, y) == VERTEX)
			{
				string vertex = decoder->getCoordinateFromPixel(x, y);
				CityPkg* cityPkg = new CityPkg(vertex);
				emitSubEvent(PLAYER_ACTION, PLA_CITY, cityPkg);
			}
		}
		else if (getMovingRobber())												// When user has to select where to move the robber using Knight card
		{
			if (decoder->getPixelType(x, y) == TOKEN)
			{
				string token = decoder->getCoordinateFromPixel(x, y);
				string robberpos;
				robberpos.push_back(board->getRobberPos());
				if (token.compare(robberpos))
				{
					KnightPkg* robberPkg = new KnightPkg(token[0]);
					emitSubEvent(PLAYER_ACTION, PLA_KNIGHT, robberPkg);
					movingRobber = false;
				}
			}
		}
		else if (locEnab->waitingForThisSubtype(new SubEvents(MainTypes::PLAYER_ACTION, SubType::PLA_ROBBER_MOVE)) || getMovingRobber())
		{
			if (decoder->getPixelType(x, y) == TOKEN)
			{
				string token = decoder->getCoordinateFromPixel(x, y);
				string robberpos;
				robberpos.push_back(board->getRobberPos());
				if (token.compare(robberpos))
				{
					RobberMovePkg* robberPkg = new RobberMovePkg(token[0]);
					emitSubEvent(PLAYER_ACTION, PLA_ROBBER_MOVE, robberPkg);
				}
			}
		}

		return POSITION_SELECTED;
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

GUIEnablerEvent BoardController::parseCloseWindow()
{
	return NO_EV;
}

void BoardController::disable()
{
	BasicController::disable();
	puttingSettlement = puttingCity = puttingRoad = movingRobber = false;
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

void BoardController::toggleRobber()
{
	movingRobber = !movingRobber;
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

bool BoardController::getMovingRobber()
{
	return movingRobber;
}

void BoardController::init()
{
	decoder = new MapDecoder(MAP_FILE); 
	font = NULL;
	fondoListo = false;
	fondoPpal = false;
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
	bitmaps[ROBBER_FILE] = al_load_bitmap(ROBBER_FILE);
	bitmaps[BACKGROUND] = al_load_bitmap(BACKGROUND);

	for (auto imagen : bitmaps) // me fijo si esta todo inicializado
	{
		if (imagen.second == NULL) { working = false; }
	}

	if (!working) // si hubo algún problema limpio
	{
		for (auto imagen : bitmaps)
		{
			if (imagen.second != NULL) { al_destroy_bitmap(imagen.second); }
		}
	}

	if (!working || (font = al_load_font("catanFont.otf", FONT_SIZE, 0)) == NULL)
	{
		working = false;
	}

	if (working)
	{
		printer->setBackgorund(bitmaps[BACKGROUND]);
		fondoPpal = true;
	}

	sellos[ROBBER_FILE] = printer->createType(bitmaps[ROBBER_FILE], al_map_rgba(0, 0, 0, 0),
		0, 0, al_get_bitmap_width(bitmaps[ROBBER_FILE]) / 2, al_get_bitmap_height(bitmaps[ROBBER_FILE]) / 2,
		1, 1, 0, 0);

}

void BoardController::drawMap()
{
	ALLEGRO_BITMAP * fondo = al_create_bitmap(580, 524);
	ALLEGRO_BITMAP * disp = al_create_bitmap(D_ANCHO, D_ALTO);
	ALLEGRO_BITMAP * tempFondo = al_load_bitmap(FONDO);
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
		pair<unsigned int, unsigned int> pos = getDecoder()->getPositioningForToken(letra);
		al_draw_rotated_bitmap(temp,
			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
			pos.first, pos.second,
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
		pair<unsigned int, unsigned int> pos = getDecoder()->getPositioningForToken(letra);
		al_draw_rotated_bitmap(temp,
			al_get_bitmap_width(temp) / 2, al_get_bitmap_height(temp) / 2,
			pos.first, pos.second,
			0, 0);
		if ((board->getResourceFromHex('A' + i)) != DESIERTO)
		{
			al_draw_filled_circle(pos.first, pos.second, CT_RAD, al_map_rgb(255, 255, 255));
			al_draw_circle(pos.first, pos.second, CT_RAD, al_map_rgb(0, 0, 0), 1);//revisar
			string ctoken = to_string(board->getCircToken(letra[0])).c_str();
			al_draw_text(font, al_map_rgb(0, 0, 0), pos.first, pos.second - CT_RAD / 2, ALLEGRO_ALIGN_CENTRE, ctoken.c_str());
		}
	}
	// hasta aca dibujo el mapa en un bitmap
	al_set_target_bitmap(disp);
	if (tempFondo != NULL)
	{
		al_draw_scaled_bitmap(tempFondo, 0, 0,
			al_get_bitmap_width(tempFondo), al_get_bitmap_height(tempFondo),
			0, 0, D_ANCHO, D_ALTO, 0);
	}
	al_draw_bitmap(fondo, BOARD_POS_X, BOARD_POS_Y, 0);
	printer->setBackgorund(disp);
	al_destroy_bitmap(tempFondo);
	al_destroy_bitmap(fondo); // el bitmap del display hay que destruirlo despues
	al_set_target_backbuffer(tempDisplay);
	}


