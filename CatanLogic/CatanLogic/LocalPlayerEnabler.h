#pragma once
#include "PlayerEnabler.h"
#include <string>
#include <cstdint>
#include "Player.h"
#include "Board.h"
#include "package.h"

using namespace std;

class LocalPlayerEnabler :
	public PlayerEnabler
{
public:
	LocalPlayerEnabler();
	LocalPlayerEnabler(Networking* pkgSender_, PlayerEnabler* remoteEnabler_);	
	virtual ~LocalPlayerEnabler();

	// Enables events for the user to select when local starts.
	void localStarts(string nameLocal, string nameRemote, Board* board_);
	// Enables events when remote starts.
	void remoteStarts(string nameLocal, string nameRemote,Board* board_);

	void setRemoteEnabler(PlayerEnabler* remoteEnabler_);

	// Returns "local" or "remote", depending on who won, or "no one" if game ended because of an error.
	string whoWon();

private:
	void init();
	void end();

	// To be used to set a common board, localPlayer and remotePlayer.
	PlayerEnabler* remoteEnabler;

	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(SubtypeEvent* ev);
	void firstSettlementLocalStarts(SubtypeEvent* ev);
	void firstRoadLocalStarts(SubtypeEvent* ev);
	void secondSettlementLocalStarts(SubtypeEvent* ev);
	void secondRoadLocalStarts(SubtypeEvent* ev);
	void firstSettlementRemoteStarts(SubtypeEvent* ev);
	void firstRoadRemoteStarts(SubtypeEvent* ev);
	void secondSettlementRemoteStarts(SubtypeEvent* ev);
	void secondRoadRemoteStarts(SubtypeEvent* ev);
	void checkDices(SubtypeEvent* ev);
	void remoteSendsRobberCards(SubtypeEvent* ev);
	void checkLocalResources(SubtypeEvent* ev);
	void enablePlayerActions(SubtypeEvent* ev);
	void checkDevCards(SubtypeEvent* ev);
	void discardLocalResources(SubtypeEvent* ev);
	void moveRobber(SubtypeEvent* ev);
	void checkOffer(SubtypeEvent* ev);
	void checkSettlement(SubtypeEvent* ev);
	void checkRoad(SubtypeEvent* ev);
	void checkCity(SubtypeEvent* ev);
	void checkBankTrade(SubtypeEvent* ev);
	void drawDevCard(SubtypeEvent* ev);
	void useKnight(SubtypeEvent* ev);
	void useMonopoly(SubtypeEvent* ev);
	void useYearsOfPlenty(SubtypeEvent* ev);
	void useRoadBuilding(SubtypeEvent* ev);
	void exchangeResources(SubtypeEvent* ev);
	void takeRobberCard(SubtypeEvent* ev);
	void enableFstRoad(SubtypeEvent* ev);
	void checkFstRoad(SubtypeEvent* ev);
	void enableSndRoad(SubtypeEvent* ev);
	void checkSndRoad(SubtypeEvent* ev);
	void endTurn(SubtypeEvent* ev);

	/* DEFAULT ROUTINES */
	void genericDefault(SubtypeEvent* ev);

	/* AUXILIARY METHODS */
	void emitEvent(EventTypes type);
	void emitSubEvent(EventTypes type, EventSubtypes subtype, package* pkg=nullptr);
	void getResourceFromSettlement(string position, Player* who);

	// Adds settlement to localPlayer and board from both Enablers
	void addSettlementToLocal(string position);
	// Adds road to localPlayer and board from both Enablers
	void addRoadToLocal(string position);
	// Enables events for beginning of turn.
	void setUpForTurn();
};

