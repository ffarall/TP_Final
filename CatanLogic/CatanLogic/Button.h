#pragma once
#include"ObserverAndController.h"
#include"allegro5/allegro.h"
#include"allegro5/allegro_font.h"
#include<iostream>
#include <functional>

typedef std::function<GUIEnablerEvent(void)> Action;

using uint = unsigned int;
class Button :public ObserverAndController
{
public:
	Button(uint xPos, uint Ypos,uint height, uint width, std::string label, ALLEGRO_BITMAP *image, ALLEGRO_FONT *font);

	void turnUseful(const Action& callback);
	
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
};