#include "DetailsObserver.h"

#define W1 "Imagenes/waiting1.png"
#define W2 "Imagenes/waiting2.png"
#define W3 "Imagenes/waiting3.png"
#define W4 "Imagenes/waiting4.png"

#define W_X 500
#define W_Y 300
#define CHANGE_TIME 0.75

DetailsObserver::DetailsObserver(MainFSM* fsm, GutenbergsPressAllegro * allegroPress)
{
	fsmToObserv = fsm;
	printer = allegroPress;
	contador = 3;
	working = true;
	imagenes[0] = al_load_bitmap(W1);
	imagenes[1] = al_load_bitmap(W2);
	imagenes[2] = al_load_bitmap(W3);
	imagenes[3] = al_load_bitmap(W4);
	for (auto each : imagenes) { if (each == NULL) { working = false; } }
	if (!working)
	{
		for (auto each : imagenes)
		{
			if (each != NULL)
			{
				al_destroy_bitmap(each);
				each = NULL;
			}
		}
	}
	if (working)
	{
		sellos[W1] = printer->createType(imagenes[contador], al_map_rgba(0, 0, 0, 0), W_X, W_Y);
	}
	timer = chrono::high_resolution_clock::now();


}


DetailsObserver::~DetailsObserver()
{
}

void DetailsObserver::update()
{
	if (fsmToObserv->getCurrState() == mainStates::HandShaking_S)
	{
		chrono::high_resolution_clock::time_point timeout = chrono::high_resolution_clock::now();
		chrono::duration<double> difftime = chrono::duration_cast<std::chrono::duration<double>>(timeout-timer); //tengo la diferencia de tiempo en segundos 
		if (difftime.count() > CHANGE_TIME) 
		{
			timer = chrono::high_resolution_clock::now();
			contador++;
			if (contador == 4) { contador = 0; } // si llega al limite lo reseteo
			sellos[W1]->setTint(al_map_rgba(255, 255, 255, 255));
			sellos[W1]->setBitmap(imagenes[contador]);
			sellos[W1]->redraw();
		}
	}
	else
	{
		for (auto type : sellos)
		{
			type.second->setTint(al_map_rgba(0, 0, 0, 0));
		}
	}
}

bool DetailsObserver::isOK()
{
	return working;
}
