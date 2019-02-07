#include "AllegroGUI.h"
#include"allegro5/allegro_image.h"
#include"allegro5/allegro_primitives.h"
#include"allegro5/allegro_ttf.h"
#include"allegro5/allegro_font.h"

#define DIS_WIDTH 1000
#define DIS_HEIGHT 600
#define TIMER_TIME 100

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
			else if (!initTimer)
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
		ALLEGRO_EVENT* ev;
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

void AllegroGUI::noAct(GUIEnablerEvent ev)
{
}

AllegroGUI::~AllegroGUI()
{
}
