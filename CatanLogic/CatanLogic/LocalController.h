#pragma once
#include "ObserverAndController.h"
#include "Player.h"
#include "LocalPlayerEnabler.h"
#include "Button.h"

#include "MapDecoder.h"
#include "CatanDefs.h"

#include "MovableType.h"
#include "GutenbergsPressAllegro.h"

#include <map>
#include <string>
#include <vector>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

using namespace std;

class ClickZone
{
public:
	ClickZone(uint32_t fromX, uint32_t fromY, uint32_t toX, uint32_t toY);
	~ClickZone();

	bool isInZone(int x, int y);

private:
	pair< uint32_t, uint32_t > from;
	pair< uint32_t, uint32_t > to;
};

class LocalController :
	public BasicController
{
public:
	LocalController(EventsHandler* handler_, GutenbergsPressAllegro * printer, Player * local, LocalPlayerEnabler * localEn);
	virtual ~LocalController();
	virtual void update();
	bool isOK();
	void attachAllButtons(vector<Button * >& lista);

	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseMouseUpEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();

	bool isThrowDiceActive();
	bool isPassActive();
	bool isAcceptActive();
	bool isCancelActive();
	bool isNewRoadActive();
	bool isNewSettlementActive();
	bool isNewCityActive();
	bool isBuyDevCardActive();
	bool isNewBankTradeActive();
	bool isNewOfferTradeActive();
	bool isUseKnightActive();
	bool isUseYearsOfPlentyActive();
	bool isUseMonopolyActive();
	bool isUseRoadBuildingActive();
	bool isSelectWoolActive();
	bool isSelectOreActive();
	bool isSelectLumberActive();
	bool isSelectGrainActive();
	bool isSelectBrickActive();
	bool isSelect4x1Active();
	bool isSelect3x1Active();
	bool isSelect2Tx1Active();
	bool isSelect2Ox1Active();
	bool isSelect2Lx1Active();
	bool isSelect2Px1Active();
	bool isSelect2Mx1Active();

	void setThrowDice(bool value);
	void setPass(bool value);
	void setAccept(bool value);
	void setCancel(bool value);
	void setNewRoad(bool value);
	void setNewSettlement(bool value);
	void setNewCity(bool value);
	void setBuyDevCard(bool value);
	void setNewBankTrade(bool value);
	void setNewOfferTrade(bool value);
	void setUseKnight(bool value);
	void setUseYearsOfPlenty(bool value);
	void setUseMonopoly(bool value);
	void setUseRoadBuilding(bool value);
	void setSelectWool(bool value);
	void setSelectOre(bool value);
	void setSelectLumber(bool value);
	void setSelectGrain(bool value);
	void setSelectBrick(bool value);
	void setSelect4x1(bool value);
	void setSelect3x1(bool value);
	void setSelect2Tx1(bool value);
	void setSelect2Ox1(bool value);
	void setSelect2Lx1(bool value);
	void setSelect2Px1(bool value);
	void setSelect2Mx1(bool value);

private:
	bool working;

	Player * localPlayer;
	LocalPlayerEnabler * localEnabler;
	GutenbergsPressAllegro * impresora;
	
	MapDecoder toDraw;

	map< string, MovableType * > roads;
	map< string, MovableType * > sellos; // aca voy guardando los 
	
	
	map<ResourceType, pair<int, MovableType*>> cartas;

	ALLEGRO_FONT * fuente;
	map<string,ALLEGRO_BITMAP *> dibujo;
	map<ResourceType, ALLEGRO_BITMAP * > cartasfotos;

	map<string,MovableType*> botones;
	
	vector<Button *> allButtons;
	// Flags that determine whether a button is activated.
	bool throwDiceActivated;
	bool passActivated;
	bool acceptActivated;
	bool cancelActivated;
	bool newRoadActivated;
	bool newSettlementActivated;
	bool newCityActivated;
	bool buyDevCardActivated;
	bool newBankTradeActivated;
	bool newOfferTradeActivated;
	bool useKnightActivated;
	bool useYearsOfPlentyActivated;
	bool useMonopolyActivated;
	bool useRoadBuildingActivated;
	bool selectWoolActivated;
	bool selectOreActivated;
	bool selectLumberActivated;
	bool selectGrainActivated;
	bool selectBrickActivated;
	bool select4x1Activated;
	bool select3x1Activated;
	bool select2Tx1Activated;
	bool select2Ox1Activated;
	bool select2Lx1Activated;
	bool select2Px1Activated;
	bool select2Mx1Activated;

	// Zones in which buttons accept a click.
	map< string, ClickZone > buttonsZones;
	
};

