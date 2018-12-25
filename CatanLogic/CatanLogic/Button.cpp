#include "Button.h"
#include "ButtonController.h"

Button::Button(uint xPos, uint Ypos, uint height, uint width, std::string label, ALLEGRO_BITMAP *image, ALLEGRO_FONT *font)
{
	controller = new ButtonController(this);
	buttonXPos = xPos;
	buttonYPos = Ypos;
	buttonHeight = height;
	buttonWidth = width;
	buttonText = label;
	buttonBitmap = image;
	buttonFont = font;
}

void Button::turnUseful(const Action & callback)
{
	(static_cast<ButtonController *>(controller))->addUtility(callback);
}

void Button::toggleButton()
{
	buttonPressed = !buttonPressed;
}

bool Button::isPressed()
{
	return buttonPressed;
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

void Button::update()
{
	if (buttonEnabled)
	{
		if (buttonBitmap != NULL)
		{
			if (buttonPressed)
			{
				al_draw_tinted_bitmap(buttonBitmap, al_map_rgba_f(1.0, 0.5, 0.5, 1.0), buttonXPos, buttonYPos, 0); // medio rojizo
			}
			else
			{
				al_draw_tinted_bitmap(buttonBitmap, al_map_rgba_f(1.0, 1.0, 1.0, 1.0), buttonXPos, buttonYPos, 0); // normal
			}
			if (buttonFont != NULL)
			{
				al_draw_text(buttonFont, al_map_rgba(0, 0, 0, 1), buttonXPos + buttonWidth / 2, buttonYPos + buttonHeight / 2, 0, buttonText.c_str());
			}
		}
		else
		{
			//podria dibujarlo con primitives
		}
	}
}
