#pragma once
#include"ObserverAndController.h"
#include"allegro5/allegro.h"
#include"allegro5/allegro_font.h"
#include<iostream>
using uint = unsigned int;
class Button :public ObserverAndController
{
public:
	Button(uint xPos, uint Ypos, std::string label, ALLEGRO_BITMAP *image, ALLEGRO_FONT *font );

	void toggleButton();
	bool isPressed();
	bool hasMouseOn();
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
private:
	uint buttonXPos;
	uint buttonYPos;
	std::string buttonText;
	bool buttonPressed;
	bool mouseOnButton;
	bool buttonEnabled;
	ALLEGRO_BITMAP* buttonBitmap;
	ALLEGRO_FONT* buttonFont;
};