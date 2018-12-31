#pragma once

#include "BasicGUI.h"
#include "Button.h"



class ButtonController :
	public BasicController
{
public:
	ButtonController(Button* toControl);
	virtual ~ButtonController();

	void addUtility(const ParseAction& parseCallback);

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

private:

	ParseAction parseCallback;
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

	35x53
	Campo  (D_ANCHO * 0.05, D_ALTO*0.3)- (D_ANCHO * 0.05 + 35 , D_ALTO*0.3 + 53)
	montaña (D_ANCHO * 0.05 + 35 * 1.05 , D_ALTO*0.3)-(D_ANCHO * 0.05 + 35 * 1.05  + 35 , D_ALTO*0.3 + 53)
	pasto (D_ANCHO * 0.05 + 35 * 1.05 * 2 , D_ALTO*0.3)-(D_ANCHO * 0.05 + 35 * 1.05 * 2  + 35 , D_ALTO*0.3 + 53)
	colina (D_ANCHO * 0.05 + 35 * 1.05 * 3 , D_ALTO*0.3)-(D_ANCHO * 0.05 + 35 * 1.05 * 3  + 35 , D_ALTO*0.3 + 53)
	bosque (D_ANCHO * 0.05 + 35 * 1.05 * 4 , D_ALTO*0.3)-(D_ANCHO * 0.05 + 35 * 1.05 * 4  + 35 , D_ALTO*0.3 + 53)


	{
	Button start(&handler, START_PLAYING_X, START_PLAYING_Y, START_PLAYING_H, START_PLAYING_W, "Start Playing", "", "", 14); //startPlayingButton()
	Button quit(&handler, QUIT_X, QUIT_Y, QUIT_H, QUIT_W, "QUIT", "", "", 14);//quitButton()
	Button newSet(&handler, NEW_SETTLEMENT_X, NEW_SETTLEMENT_Y, NEW_SETTLEMENT_H, NEW_SETTLEMENT_W, "", "settlement.png", "", 0);//newSettlementButton
	Button newCity(&handler, NEW_CITY_X, NEW_CITY_Y, NEW_CITY_H, NEW_CITY_W, "", "CITY.png", "", 0);//newCityButton
	Button newRoad(&handler, NEW_ROAD_X, NEW_ROAD_Y, NEW_ROAD_H, NEW_ROAD_W, "", "ROAD.png", "", 0);//newRoadButton
	Button getDev(&handler, BUY_DEV_CARD_X, BUY_DEV_CARD_Y, BUY_DEV_CARD_H, BUY_DEV_CARD_W, "", "BUY_DEV_CARD.png", "", 0);//getDevCardButton
	Button pass(&handler, PASS_X, PASS_Y, PASS_H, PASS_W, "", "PASS.png", "", 0);//endTurnButton
	Button bankTrade(&handler, NEW_BANK_TRADE_X, NEW_BANK_TRADE_Y, NEW_BANK_TRADE_H, NEW_BANK_TRADE_W, "Bank Trade", "", "catanFont.otf", 14);//bankTradeButton
	Button offerTrade(&handler, NEW_OFFER_TRADE_X, NEW_OFFER_TRADE_Y, NEW_OFFER_TRADE_H, NEW_OFFER_TRADE_W, "Offer Trade", "", "catanFont.otf", 14);//offerTradeButton
	Button dice(&handler, THROW_DICE_X, THROW_DICE_Y, THROW_DICE_H, THROW_DICE_W, "Dice", "dice.png", "catanFont.otf", 14);//throwDicesButton
	Button knight(&handler, USE_KNIGHT_X, USE_KNIGHT_Y, USE_KNIGHT_H, USE_KNIGHT_W, "", "Knight.png", "catanFont.otf", 14);//useKnightButtton
	Button roadB(&handler, USE_ROAD_BUILDING_X, USE_ROAD_BUILDING_Y, USE_ROAD_BUILDING_H, USE_ROAD_BUILDING_W, "", "ROAD_BUILDING.png", "catanFont.otf", 14);//useRoadBuildingButton
	Button monopoly(&handler, USE_MONOPOLY_X, USE_MONOPOLY_Y, USE_MONOPOLY_H, USE_MONOPOLY_W, "", "MONOPOLY.png", "catanFont.otf", 14);//useMonopolyButton
	Button yop(&handler, USE_YEARS_OF_PLENTY_X, USE_YEARS_OF_PLENTY_Y, USE_YEARS_OF_PLENTY_H, USE_YEARS_OF_PLENTY_W, "", "YEARS_OF_PLENTY.png", "catanFont.otf", 14);//useYearsOfPlentyButton
	Button _4x1(&handler, SELECT_4x1_X, SELECT_4x1_Y, SELECT_4x1_H, SELECT_4x1_W, "", "SELECT_4x1.png", "", 14);//port4x1Button
	Button _3x1(&handler, SELECT_3x1_X, SELECT_3x1_Y, SELECT_3x1_H, SELECT_3x1_W, "", "SELECT_3x1.png", "", 14);//port3x1Button
	Button _2mx1(&handler, SELECT_2Mx1_X, SELECT_2Mx1_Y, SELECT_2Mx1_H, SELECT_2Mx1_W, "", "SELECT_2Mx1.png", "", 14);//port2Mx1Button
	Button _2tx1(&handler, SELECT_2Tx1_X, SELECT_2Tx1_Y, SELECT_2Tx1_H, SELECT_2Tx1_W, "", "SELECT_2Tx1.png", "", 14);//port2Tx1Button
	Button _2lx1(&handler, SELECT_2Lx1_X, SELECT_2Lx1_Y, SELECT_2Lx1_H, SELECT_2Lx1_W, "", "SELECT_2Lx1.png", "", 14);//port2Lx1Button
	Button _2ox1(&handler, SELECT_2Ox1_X, SELECT_2Ox1_Y, SELECT_2Ox1_H, SELECT_2Ox1_W, "", "SELECT_2Ox1.png", "", 14);//port2Ox1Button
	Button _2px1(&handler, SELECT_2Px1_X, SELECT_2Px1_Y, SELECT_2Px1_H, SELECT_2Px1_W, "", "SELECT_2Px1.png", "", 14);//port2Px1Button
	Button brick(&handler, SELECT_BRICK_X, SELECT_BRICK_Y, SELECT_BRICK_H, SELECT_BRICK_W, "", "SELECT_BRICK.png", "catanFont.otf", 14);//brickButton
	Button lumber(&handler, SELECT_LUMBER_X, SELECT_LUMBER_Y, SELECT_LUMBER_H, SELECT_LUMBER_W, "", " SELECT_LUMBER.png", "catanFont.otf", 14);//lumberButton
	Button ore(&handler, SELECT_ORE_X, SELECT_ORE_Y, SELECT_ORE_H, SELECT_ORE_W, "", "SELECT_ORE.png", "catanFont.otf", 14);//oreButton
	Button grain(&handler, SELECT_GRAIN_X, SELECT_GRAIN_Y, SELECT_GRAIN_H, SELECT_GRAIN_W, "", "SELECT_GRAIN.png", "catanFont.otf", 14);//grainButton
	Button wool(&handler, SELECT_WOOL_X, SELECT_WOOL_Y, SELECT_WOOL_H, SELECT_WOOL_W, "", "SELECT_WOOL.png", "catanFont.otf", 14);//woolButtton
	Button tick(&handler, ACCEPT_X, ACCEPT_Y, ACCEPT_H, ACCEPT_W, "", "tick.png", "", 0);//confirmButton
	Button cruz(&handler, CANCEL_X, CANCEL_Y, CANCEL_H, CANCEL_W, "", "cruz.png", "", 0);//cancelButton

	buttonList.emplace_back(&start);
	buttonList.emplace_back(&quit);
	buttonList.emplace_back(&newCity);
	buttonList.emplace_back(&newRoad);
	buttonList.emplace_back(&newSet);
	buttonList.emplace_back(&getDev);
	buttonList.emplace_back(&pass);
	buttonList.emplace_back(&bankTrade);
	buttonList.emplace_back(&offerTrade);
	buttonList.emplace_back(&dice);
	buttonList.emplace_back(&knight);
	buttonList.emplace_back(&roadB);
	buttonList.emplace_back(&monopoly);
	buttonList.emplace_back(&yop);
	buttonList.emplace_back(&_4x1);
	buttonList.emplace_back(&_3x1);
	buttonList.emplace_back(&_2mx1);
	buttonList.emplace_back(&_2tx1);
	buttonList.emplace_back(&_2lx1);
	buttonList.emplace_back(&_2ox1);
	buttonList.emplace_back(&_2px1);
	buttonList.emplace_back(&brick);
	buttonList.emplace_back(&lumber);
	buttonList.emplace_back(&ore);
	buttonList.emplace_back(&grain);
	buttonList.emplace_back(&wool);
	buttonList.emplace_back(&tick);
	buttonList.emplace_back(&cruz);
}
*/