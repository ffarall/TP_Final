#include "Button.h"
//#include "ButtonController.h"
#define BUTTON_TINT 0,0,0

Button::Button(GutenbergsPressAllegro* press_, EventsHandler* handler_, uint xPos, uint Ypos, uint height, uint width, std::string label, std::string imagePath, std::string fontPath,int fontSize, int angle) : BasicController(handler_)
{
	info = nullptr;
	press = press_;
	buttonXPos = xPos;
	buttonYPos = Ypos;
	buttonHeight = height;
	buttonWidth = width;
	buttonText = label;
	buttonBitmap = al_load_bitmap(imagePath.c_str());
	ALLEGRO_BITMAP * bototn = al_load_bitmap(imagePath.c_str());
	buttonFont = al_load_font(fontPath.c_str(),fontSize,0);
	if (buttonBitmap == NULL||buttonFont==NULL || bototn)
	{
		//error
	}
	type = press->createType(bototn, al_map_rgb(BUTTON_TINT), xPos, Ypos);
	type->setAngle(angle*ALLEGRO_PI/180);
}

Button::~Button()
{
	if (buttonBitmap != NULL)
		al_destroy_bitmap(buttonBitmap);
	if (buttonFont != NULL)
		al_destroy_font(buttonFont);
	if (info != NULL)
		delete info;
}

bool Button::clickIn(uint x_, uint y_)
{
	if ((x_ >= buttonXPos ) && (x_ <= (buttonXPos + buttonWidth)) && (y_ >= buttonYPos) && (y_ <= (buttonYPos + buttonHeight)))
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

ALLEGRO_FONT * Button::getFont()
{
	return buttonFont;
}

bool Button::setBitmap(std::string imagePath)
{
	buttonBitmap = al_load_bitmap(imagePath.c_str());
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

void Button::setTypeTint(char r_, char g_, char b_, char a_)
{
	type->setTint(al_map_rgba(r_, g_, b_, a_));
}

void Button::update()
{
	updateCallback();
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
		if (buttonPressed)
		{
			if (this->clickIn(x, y))
			{
				return parseCallback();
			}
			else
			{
				toggleButton();
			}
		}
		else
		{
			buttonPressed = false;
		}
	}
	return NO_EV;
}

GUIEnablerEvent Button::parseTimerEvent()
{
	return GUIEnablerEvent::NO_EV; // ver
}

MovableType * Button::getType()
{
	return type;
}

package * Button::getPackage()
{
	return info;
}

void Button::setPackage(package * data)
{
	info = data;
}


