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
	LocalPlayerEnabler(Networking* pkgSender_, PlayerEnabler* remoteEnabler_, EventsHandler* handler_, Player* localPlayer_, Player* remotePlayer_);
	virtual ~LocalPlayerEnabler();

	// Enables events for the user to select when local starts.
	void localStarts(string nameLocal, string nameRemote, Board* board_);
	// Enables events when remote starts.
	void remoteStarts(string nameLocal, string nameRemote,Board* board_);

	void setRemoteEnabler(PlayerEnabler* remoteEnabler_);

	// Returns "local" or "remote", depending on who won, or "no one" if game ended because of an error.
	string whoWon();

	string getRemoteName();

private:
	void init();
	void end();

	// To be used to set a common board, localPlayer and remotePlayer.
	PlayerEnabler* remoteEnabler;

	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(SubtypeEvent* ev);
	void firstSettlementLocalStarts(SubtypeEvent* ev);
	void waitingConfFstSetLocStarts(SubtypeEvent* ev);
	void firstRoadLocalStarts(SubtypeEvent* ev);
	void firstTurnFinish(SubtypeEvent* ev);
	void secondSettlementLocalStarts(SubtypeEvent* ev);
	void waitingConfSndSetLocStarts(SubtypeEvent* ev);
	void secondRoadLocalStarts(SubtypeEvent* ev);
	void firstSettlementRemoteStarts(SubtypeEvent* ev);
	void waitingConfFstSetRemStarts(SubtypeEvent* ev);
	void firstRoadRemoteStarts(SubtypeEvent* ev);
	void waitingConfFstRoadRemStarts(SubtypeEvent* ev);
	void secondSettlementRemoteStarts(SubtypeEvent* ev);
	void waitingConfSndSetRemStarts(SubtypeEvent* ev);
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
	void firstTurn(SubtypeEvent * ev);

	/* DEFAULT ROUTINES */
	void genericDefault(SubtypeEvent* ev);

	/* AUXILIARY METHODS */
	// Puts new event in queue for general fsm, using the handler given when creating this enabler.
	void emitEvent(EventTypes type);
	// Puts new event in queue, but in this case is a SubEvent that can have a package.
	void emitSubEvent(EventTypes type, EventSubtypes subtype, package* pkg=nullptr);
	// Adds resources to player using board.
	void getResourceFromSettlement(string position, Player* who);
	// If local won, emits event I_WON.
	void checkIfLocalWon();
	// Checks if localPlayer should own longestRoadCard, comparing with remotePlayer. If the local is the rightful owner of the card, this gives local de card ant takes it away from remote.
	void checkLongestRoad();
	// Checks if localPlayer should own largestArmyCard, comparing with remotePlayer. If the local is the rightful owner of the card, this gives local de card ant takes it away from remote.
	void checkLargestArmy();

	// Adds settlement to localPlayer and board from both Enablers
	void addSettlementToLocal(string position);
	// Adds road to localPlayer and board from both Enablers
	void addRoadToLocal(string position);
	// Enables events for beginning of turn.
	void setUpForTurn();
};

