#pragma once
#include"ObserverAndController.h"
#include"allegro5/allegro.h"
#include"allegro5/allegro_font.h"
#include"GutenbergsPressAllegro.h"
#include<iostream>
#include <functional>

typedef std::function<GUIEnablerEvent(void)> Action;

using uint = unsigned int;
class Button :public BasicController
{
public:
	Button(EventsHandler* handler_, uint xPos, uint Ypos,uint height, uint width, std::string label, std::string imagePath, ALLEGRO_FONT *font);

	void turnUseful(const Action& callback);
	bool clickIn(uint x_, uint y_);

	void toggleButton();
	bool isPressed();
	void toggleAvailability();
	bool isAvailable();
	void setXPos(uint pos);
	void setYpos(uint pos);
	uint getXPos();
	uint getYPos();
	ALLEGRO_BITMAP* getBitmap();	
	bool setBitmap(ALLEGRO_BITMAP* image);
	bool setFont(ALLEGRO_FONT* font);

	virtual void update();

	void addUtility(const Action& callback_);

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

private:
	uint buttonXPos;
	uint buttonYPos;
	uint buttonHeight;
	uint buttonWidth;
	std::string buttonText;
	bool buttonPressed;
	bool buttonEnabled;
	ALLEGRO_BITMAP* buttonBitmap;
	ALLEGRO_FONT* buttonFont;
	GutenbergsPressAllegro* press;

	Action callback;
	Button * controlado;
};

/*

{  // como usar las funciones lambda

	Button a(...),b(...),c(...);

	a.turnUseful([&b]() // entre corchetes con el & le paso los botones, controles, etc, que se vallan a habilitar o desabilitar cuando se clikea el boton 
				{  	    // entre llaves el callback que se tiene que ejecutar (tiene que tener un retrun GUIEnablerevent)
					b.toggleAvaliability();
					return ...;
				}
				);

}

*/