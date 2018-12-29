#pragma once

#include "BasicGUI.h"
#include "Button.h"



class ButtonController :
	public BasicController
{
public:
	ButtonController(Button* toControl);
	virtual ~ButtonController();

	void addUtility(const Action& callback);

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

private:

	Action callback;
	Button * controlado;
};

/*
	dice (no todavia)
	pass (no todavia)

	tick  ( D_ANCHO*0.47   ,  D_ALTO*0.9 )-( D_ANCHO*0.47  + 50,  D_ALTO*0.9 +50)

	cruz  ( D_ANCHO*0.53 ,  D_ALTO*0.9)-(D_ANCHO*0.53 + 50 , D_ALTO*0.9 + 50)

	road  (D_ANCHO * 0.148, D_ALTO * 0.438)-(D_ANCHO * 0.148 + 40, D_ALTO * 0.438 + 30)
	settle  (D_ANCHO * 0.105, D_ALTO * 0.43)-( D_ANCHO * 0.105 + 26, D_ALTO * 0.43 + 35)
	city (D_ANCHO * 0.053, D_ALTO * 0.43)-(D_ANCHO * 0.053 + 30, D_ALTO * 0.43 + 35)

	buy devcards  ( D_ANCHO * 0.65, D_ALTO * 0.85)-( D_ANCHO * 0.65 +50 , D_ALTO * 0.85 + 75)

	bankTrade  (D_ANCHO*0.05, D_ALTO*0.6)-( D_ANCHO*0.15, D_ALTO*0.65)

	(+ los que tengas disponibles + botones de recursos + más - menos)

	Offer  (D_ANCHO*0.825, D_ALTO*0.3)-(D_ANCHO*0.925, D_ALTO*0.35)

	knight  ( D_ANCHO * 0.12, D_ALTO * 0.7)-( D_ANCHO * 0.12+50, D_ALTO * 0.7+77)
	YoP  (D_ANCHO * 0.06 , D_ALTO * 0.7)-(D_ANCHO * 0.06 +50, D_ALTO * 0.7+77)
	Monopoly  (D_ANCHO * 0.18, D_ALTO * 0.7)-(D_ANCHO * 0.18+50, D_ALTO * 0.7+77)
	RoadBuilding  (D_ANCHO * 0.145, D_ALTO * 0.83)-(D_ANCHO * 0.145+50, D_ALTO * 0.83+77)
	victory point (D_ANCHO * 0.095, D_ALTO * 0.83)-(D_ANCHO * 0.095+50, D_ALTO * 0.83+77)




*/