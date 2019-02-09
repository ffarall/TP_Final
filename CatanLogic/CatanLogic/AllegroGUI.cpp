#include "AllegroGUI.h"
#include"allegro5/allegro_image.h"
#include"allegro5/allegro_primitives.h"
#include"allegro5/allegro_ttf.h"
#include"allegro5/allegro_font.h"
#include "BoardController.h"

#define DIS_WIDTH 1000
#define DIS_HEIGHT 600
#define TIMER_TIME 100

#define TX(x) (static_cast<void (GUIEnabler::* )()>(&AllegroGUI::x))

AllegroGUI::AllegroGUI():BasicGUI()
{
	allegroError = false;
	
	eventQueue = nullptr;
	display = nullptr;

	if (allegroInit())
	{
		if (initAddOn())
		{
			if (!initDisplay())
			{
				closeAdd();
			}
			else if (!initTimer())
			{
				closeDisplay();
				closeAdd();
			
			}
			else if (!initEventQueue())
			{
				closeDisplay();
				closeAdd();
				closeTimer();
			}
			
		}
	}

	if (allegroError)
	{
		cout << "No se pudo inicializar todo, vuelva a intentar mas tarde\n";
		cout << "presione una tecla para finalizar...\n";
		getchar();
	}
}

bool AllegroGUI::checkForEvents()
{
	if (al_event_queue_is_empty(eventQueue))
	{
		return false;
	}
	else
	{
		ALLEGRO_EVENT* ev = NULL;
		al_get_next_event(eventQueue, ev);
		switch (ev->type)
		{
		case ALLEGRO_EVENT_TIMER:
			GUIEv = GUI_TIMER;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			GUIEv = GUI_MOUSE_DOWN;
			mouseCoordinates =std::make_pair(ev->mouse.x,ev->mouse.y);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			GUIEv = GUI_MOUSE_UP;
			mouseCoordinates = std::make_pair(ev->mouse.x, ev->mouse.y);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			GUIEv = GUI_CLOSE_DISPLAY;
			break;
		default:
			return false;//error?
			break;
		}
	}
	return true;
}

bool AllegroGUI::allegroInit()
{
	if (al_init() == true)
	{
		return true;
	}
	allegroError = true;
	return false;
}

bool AllegroGUI::initAddOn()
{
	if (al_init_font_addon())
	{
		if (al_init_image_addon())
		{
			if (al_init_primitives_addon())
			{
				if (al_init_ttf_addon())
				{
					if (al_install_keyboard())
					{
						if (al_install_mouse())
						{
							return true;
						}
						al_uninstall_keyboard();
					}
					al_shutdown_ttf_addon();
				}
				al_shutdown_primitives_addon();				
				
			}
			al_shutdown_image_addon();
		}
		al_shutdown_font_addon();
	}
	allegroError = true;
	return false;
}




bool AllegroGUI::initEventQueue() // necesita , display, addons, menu
{
	
	eventQueue = al_create_event_queue();
	if (eventQueue != NULL)
	{
		al_register_event_source(eventQueue, al_get_display_event_source(display));
		al_register_event_source(eventQueue, al_get_mouse_event_source());
		al_register_event_source(eventQueue, al_get_timer_event_source(timer));
		al_start_timer(timer);
	
		return true;
	}	
	allegroError = true;
	return false;
}

bool AllegroGUI::initDisplay()
{
	display = al_create_display(DIS_WIDTH, DIS_HEIGHT);
		if (display == nullptr)
		{
			allegroError = true;
			return false;
		}
	return true;
}

bool AllegroGUI::initTimer()
{
	timer = al_create_timer(TIMER_TIME);
	if (timer == nullptr)
	{
		allegroError = true;
		return false;
	}
		return true;
}
	
void AllegroGUI::closeAdd()
{
	al_uninstall_keyboard();
	al_shutdown_ttf_addon();
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
}

void AllegroGUI::closeDisplay()
{
	al_destroy_display(display);
}

void AllegroGUI::closeEvents()
{
 	al_destroy_event_queue(eventQueue);
}

void AllegroGUI::closeTimer()
{
	al_destroy_timer(timer);
}

void AllegroGUI::disableAll()
{
	for (auto controller : controllers)
	{
		controller.second->disable();
	}
}

void AllegroGUI::enableAll()
{
	for (auto controller : controllers)
	{
		controller.second->enable();
	}
}

void AllegroGUI::noAct()
{
}

void AllegroGUI::nowSelectRoad()
{
	BoardController* boardCon = static_cast<BoardController*>(controllers["BoardController"]);
	if (!(boardCon->getPuttingRoad()))			// if puttingRoad is not set (NewRoad hasn't been clicked before
	{
		boardCon->toggleRoad();
		enable(POSITION_SELECTED, { TX(backToNormal) });
		enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
	}
}

void AllegroGUI::nowSelectSettlement()
{
	BoardController* boardCon = static_cast<BoardController*>(controllers["BoardController"]);
	if (!(boardCon->getPuttingSettlement()))			// if puttingRoad is not set (NewRoad hasn't been clicked before
	{
		boardCon->toggleSettlement();
		enable(POSITION_SELECTED, { TX(backToNormal) });
		enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
	}
}

void AllegroGUI::nowSelectCity()
{
	BoardController* boardCon = static_cast<BoardController*>(controllers["BoardController"]);
	if (!(boardCon->getPuttingCity()))			// if puttingRoad is not set (NewRoad hasn't been clicked before
	{
		boardCon->toggleCity();
		enable(POSITION_SELECTED, { TX(backToNormal) });
		enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
	}
}

void AllegroGUI::nowSelectRobberPos()
{
	BoardController* boardCon = static_cast<BoardController*>(controllers["BoardController"]);
	if (!(boardCon->getMovingRobber()))			// if puttingRoad is not set (NewRoad hasn't been clicked before
	{
		boardCon->toggleRobber();
		enable(POSITION_SELECTED, { TX(backToNormal) });
		enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
	}
}

void AllegroGUI::nowSelectPortType()
{
	controllers["Port4x1"]->enable();
	controllers["Port3x1"]->enable();
	controllers["Port2Mx1"]->enable();
	controllers["Port2Tx1"]->enable();
	controllers["Port2Lx1"]->enable();
	controllers["Port2Ox1"]->enable();
	controllers["Port2Px1"]->enable();

	GUIEnabler::disableAll();
	enable(GUIEnablerEvent::_2LX1, { TX(nowSelectResourcesToReceive) });
	enable(GUIEnablerEvent::_2MX1, { TX(nowSelectResourcesToReceive) });
	enable(GUIEnablerEvent::_2TX1, { TX(nowSelectResourcesToReceive) });
	enable(GUIEnablerEvent::_2OX1, { TX(nowSelectResourcesToReceive) });
	enable(GUIEnablerEvent::_2PX1, { TX(nowSelectResourcesToReceive) });
	enable(GUIEnablerEvent::_3X1, { TX(nowSelectResourcesToGive) });
	enable(GUIEnablerEvent::_4X1, { TX(nowSelectResourcesToGive) });
	enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
}

void AllegroGUI::nowSelectResourcesToGive()
{
	backToNormal();					// Disable previous unwanted buttons.
	GUIEnabler::disableAll();		// Disable all GUIEnablerEvents.
	
	controllers["Brick"]->enable();
	controllers["Lumber"]->enable();
	controllers["Ore"]->enable();
	controllers["Grain"]->enable();
	controllers["Wool"]->enable();

	enable(GUIEnablerEvent::RESOURCE, { TX(nowUserCanConfirmResourcesToGive) });
	enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
}

void AllegroGUI::nowUserCanConfirmResourcesToGive()
{
	enable(GUIEnablerEvent::ACCEPT, { TX(nowSelectResourcesToReceive) });
}

void AllegroGUI::nowSelectResourcesToReceive()
{
	backToNormal();					// Disable previous unwanted buttons.
	GUIEnabler::disableAll();		// Disable all GUIEnablerEvents.

	controllers["Brick"]->enable();
	controllers["Lumber"]->enable();
	controllers["Ore"]->enable();
	controllers["Grain"]->enable();
	controllers["Wool"]->enable();

	enable(GUIEnablerEvent::RESOURCE, { TX(nowUserCanConfirmResourcesToReceive) });
	enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
}

void AllegroGUI::nowUserCanConfirmResourcesToReceive()
{
	enable(GUIEnablerEvent::ACCEPT, { TX(backToNormal) });
}

void AllegroGUI::nowSelectFirstRoad()
{
	BoardController* boardCon = static_cast<BoardController*>(controllers["BoardController"]);
	if (!(boardCon->getPuttingRoad()))			// if puttingRoad is not set (NewRoad hasn't been clicked before
	{
		boardCon->toggleRoad();
		enable(POSITION_SELECTED, { TX(nowSelectRoad) });
		enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
	}
}

void AllegroGUI::nowSelectMonopolyResource()
{
	backToNormal();					// Disable previous unwanted buttons.
	GUIEnabler::disableAll();		// Disable all GUIEnablerEvents.

	controllers["Brick"]->enable();
	controllers["Lumber"]->enable();
	controllers["Ore"]->enable();
	controllers["Grain"]->enable();
	controllers["Wool"]->enable();

	enable(GUIEnablerEvent::RESOURCE, { TX(backToNormal) });
	enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
}

void AllegroGUI::nowSelectFirstResource()
{
	backToNormal();					// Disable previous unwanted buttons.
	GUIEnabler::disableAll();		// Disable all GUIEnablerEvents.

	controllers["Brick"]->enable();
	controllers["Lumber"]->enable();
	controllers["Ore"]->enable();
	controllers["Grain"]->enable();
	controllers["Wool"]->enable();

	enable(GUIEnablerEvent::RESOURCE, { TX(nowSelectSecondResource) });
	enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
}

void AllegroGUI::nowSelectSecondResource()
{
	backToNormal();					// Disable previous unwanted buttons.
	GUIEnabler::disableAll();		// Disable all GUIEnablerEvents.

	controllers["Brick"]->enable();
	controllers["Lumber"]->enable();
	controllers["Ore"]->enable();
	controllers["Grain"]->enable();
	controllers["Wool"]->enable();

	enable(GUIEnablerEvent::RESOURCE, { TX(backToNormal) });
	enable(GUIEnablerEvent::CANCEL, { TX(backToNormal) });
}

void AllegroGUI::backToNormal()
{
	initGUIEnabler();
}

AllegroGUI::~AllegroGUI()
{
}

void AllegroGUI::initGUIEnabler()
{
	enableAll();
	controllers["BoardController"]->disable();
	controllers["Port4x1"]->disable();
	controllers["Port3x1"]->disable();
	controllers["Port2Mx1"]->disable();
	controllers["Port2Tx1"]->disable();
	controllers["Port2Lx1"]->disable();
	controllers["Port2Ox1"]->disable();
	controllers["Port2Px1"]->disable();
	controllers["Brick"]->disable();
	controllers["Lumber"]->disable();
	controllers["Ore"]->disable();
	controllers["Grain"]->disable();
	controllers["Wool"]->disable();

	setDefaultRoutine(TX(noAct));
	enable(GUIEnablerEvent::BANK_TRADE, { TX(nowSelectPortType) });
	enable(GUIEnablerEvent::OFFER_TRADE, { TX(nowSelectResourcesToGive) });
	enable(GUIEnablerEvent::NEW_ROAD, { TX(nowSelectRoad) });
	enable(GUIEnablerEvent::NEW_SETTLEMENT, { TX(nowSelectSettlement) });
	enable(GUIEnablerEvent::NEW_CITY, { TX(nowSelectCity) });
	enable(GUIEnablerEvent::USE_KNIGHT, { TX(nowSelectRobberPos) });
}
