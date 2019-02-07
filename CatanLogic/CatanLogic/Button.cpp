#include "Button.h"
//#include "ButtonController.h"
#define BUTTON_TINT 0,0,0

Button::Button(GutenbergsPressAllegro* press_, EventsHandler* handler_, uint xPos, uint Ypos, uint height, uint width, std::string label, std::string imagePath, std::string fontPath,int fontSize) : BasicController(handler_)
{
	press = press_;
	type = new MovableType(press, NULL);
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



void Button::enable()
{
	buttonEnabled = true;
}

void Button::disable()
{
	buttonEnabled = false;
}

bool Button::isEnabled()
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
	updateCallback(type);
	type->redraw();
}

void Button::addUtility(const ParseAction & callback_)
{
	parseCallback = callback_;
}

void Button::addUpdate(const UpdateAction & callback_)
{
	updateCallback = callback_;
}

GUIEnablerEvent Button::parseMouseDownEvent(uint32_t x, uint32_t y)
{
	if (buttonEnabled)
	{
		if (this->clickIn(x, y))
		{
			this->toggleButton();
		}
	}

	return GUIEnablerEvent::NO_EV;
}

GUIEnablerEvent Button::parseMouseUpEvent(uint32_t x, uint32_t y)
{
	if (buttonEnabled)
	{
		if (this->clickIn(x, y))
		{
			if (buttonPressed)
			{
				return parseCallback();
			}
		}
	}
	return NO_EV;
}

GUIEnablerEvent Button::parseTimerEvent()
{
	return GUIEnablerEvent::NO_EV; // ver
}
