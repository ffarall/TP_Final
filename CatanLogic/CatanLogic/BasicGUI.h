#pragma once
#include <list>
#include <map>
#include <cstdint>

using namespace std;

enum GUIEventTypes { GUI_TIMER, GUI_MOUSE };

class BasicController
{
public:
	BasicController();
	virtual  ~BasicController();
	virtual void parseMouseEvent(uint32_t x, uint32_t y) = 0;
	virtual void parseTimerEvent() = 0;
};

class BasicGUI
{
public:
	BasicGUI();
	virtual ~BasicGUI();
	virtual void checkForEvents() = 0;
	void parseEvent();
	void attachController(BasicController* newController);

protected:
	list< BasicController* > controllers;
	GUIEventTypes GUIEv;
	pair< uint32_t, uint32_t > mouseCoordinates;
};
