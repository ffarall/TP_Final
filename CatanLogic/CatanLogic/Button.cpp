#include "Button.h"
//#include "ButtonController.h"
#define BUTTON_TINT 0,0,0

Button::Button(EventsHandler* handler_, uint xPos, uint Ypos, uint height, uint width, std::string label, std::string imagePath, std::string fontPath,int fontSize) : BasicController(handler_)
{
	buttonXPos = xPos;
	buttonYPos = Ypos;
	buttonHeight = height;
	buttonWidth = width;
	buttonText = label;
	buttonBitmap = al_load_bitmap(imagePath.c_str);
	buttonFont = al_load_font(fontPath.c_str(),fontSize,0);
	if (buttonBitmap == nullptr||buttonFont==nullptr)
	{
		//error
	}
	press->createType(buttonBitmap, al_map_rgb(BUTTON_TINT), xPos, Ypos);
	
}

void Button::turnUseful(const Action & callback)
{
	addUtility(callback);
}

bool Button::clickIn(uint x_, uint y_)
{
	if ((x_ >= (buttonXPos - buttonWidth / 2)) && (x_ <= (buttonXPos + buttonWidth / 2)) && (y_ >= (buttonYPos - buttonHeight / 2)) && (y_ <= (buttonYPos + buttonHeight / 2)))
	{
		return true;
	}
	else
	{
		return false;
	}
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

bool Button::setBitmap(std::string imagePath)
{
	buttonBitmap = al_load_bitmap(imagePath.c_str);
	if (buttonBitmap == nullptr)
	{
		return false;
	}
	return true;
}

bool Button::setFont(std::string fontPath, int fontSize)
{
	buttonFont = al_load_font(fontPath.c_str(), fontSize, 0);
	if (buttonFont == nullptr)
	{
		return false;
	}
	
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

void Button::addUtility(const Action & callback_)
{
	callback = callback_;
}

GUIEnablerEvent Button::parseMouseDownEvent(uint32_t x, uint32_t y)
{
	if (buttonEnabled)
	{
		if (this->clickIn(x, y))
		{
			this->toggleButton();
			return callback();
		}
	}

	return GUIEnablerEvent::NO_EV;
}

GUIEnablerEvent Button::parseTimerEvent()
{
	return GUIEnablerEvent::NO_EV; // ver
}
