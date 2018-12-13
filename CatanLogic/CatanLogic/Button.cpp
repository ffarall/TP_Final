#include "Button.h"

Button::Button(uint xPos, uint yPos, std::string label, ALLEGRO_BITMAP * image, ALLEGRO_FONT * font)
{
	buttonXPos = xPos;
	buttonYPos = yPos;
	buttonText = label;
	buttonBitmap = image;
	buttonFont = font;
}

void Button::toggleButton()
{
	buttonPressed = !buttonPressed;
}

bool Button::isPressed()
{
	return buttonPressed;
}

bool Button::hasMouseOn()
{
	return mouseOnButton;
}

void Button::toggleAvailability()
{
	buttonEnabled = !buttonEnabled;
}

bool Button::isAvailable()
{
	return buttonEnabled;
}

void Button::setXPos(uint pos)
{
	buttonXPos = pos;

}

void Button::setYpos(uint pos)
{
	buttonYPos = pos;
}

uint Button::getXPos()
{
	return buttonXPos;
}

uint Button::getYPos()
{
	return buttonYPos;
}

ALLEGRO_BITMAP * Button::getBitmap()
{
	return buttonBitmap;
}

bool Button::setBitmap(ALLEGRO_BITMAP * image)
{
	if (image == nullptr)
	{
		return false;
	}
	buttonBitmap = image;
	return true;
}

bool Button::setFont(ALLEGRO_FONT * font)
{
	if (font == nullptr)
	{
		return false;
	}
	buttonFont = font;
	return true;

	
}
