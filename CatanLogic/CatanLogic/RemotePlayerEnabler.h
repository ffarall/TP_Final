#pragma once
#include "PlayerEnabler.h"
#include <string>
#include <cstdint>
#include "Player.h"
#include "Board.h"
#include "package.h"

using namespace std;

class RemotePlayerEnabler :
	public PlayerEnabler
{
public:
	RemotePlayerEnabler();
	RemotePlayerEnabler(Networking* pkgSender_,  EventsHandler * nable_);
	virtual ~RemotePlayerEnabler();

	
	// Enables events for when local starts.
	void localStarts();
	// Enables events when remote starts.
	void remoteStarts();
	
private:
	void init();
	void end();

	/* ROUTINES TO BE EXECTUED IN CYCLE */
	void noAct(SubtypeEvent* ev);
	void firstSettlementLocalStarts(SubtypeEvent* ev); // estos 4 van todos juntos
	void firstRoadLocalStarts(SubtypeEvent* ev);
	void firstSettlementRemoteStarts(SubtypeEvent* ev);
	void firstRoadRemoteStarts(SubtypeEvent* ev);
	void primeraParte(SubtypeEvent* ev);
	void secondSettlementLocalStarts(SubtypeEvent* ev);
	void secondRoadLocalStarts(SubtypeEvent* ev);
	void secondSettlementRemoteStarts(SubtypeEvent* ev);
	void secondRoadRemoteStarts(SubtypeEvent* ev);
	void firstTurn(SubtypeEvent * ev);

	void checkDices(SubtypeEvent* ev);
	void sendsRobberCards(SubtypeEvent* ev);
	void remoteLoseCards(SubtypeEvent* ev);
	void remoteMoveRobber(SubtypeEvent* ev);

	void evaluateOffer(SubtypeEvent* ev);
	void checkRemoteSettlement(SubtypeEvent* ev);
	void checkRemoteRoad(SubtypeEvent* ev);
	void checkRemoteCity(SubtypeEvent* ev);
	void checkRemoteBankTrade(SubtypeEvent* ev);
	void checkDevCards(SubtypeEvent * ev);
	void endTurn(SubtypeEvent * ev);

	void remUsedKnight(SubtypeEvent * ev);
	void remUsedMonopoly(SubtypeEvent * ev);
	void remUsedYoP(SubtypeEvent * ev);
	void remUsedRoadBuilding(SubtypeEvent * ev);

	void enableRemoteActions(SubtypeEvent * ev);
	void rejectOffer(SubtypeEvent * ev);
	void exchangeResources(SubtypeEvent* ev);
	void checkRemoteDevCards(SubtypeEvent * ev);

	void road1(SubtypeEvent * ev);
	void road2(SubtypeEvent * ev);

	void finDelJuego(SubtypeEvent * ev);

	// Enables events for beginning of turn.
	void setUpForTurn(SubtypeEvent* ev = NULL);
	

	/* DEFAULT ROUTINES */
	void genericDefault(SubtypeEvent* ev);

	/* AUXILIARY METHODS */
	void emitEvent(EventTypes type);
	void emitSubEvent(EventTypes type, EventSubtypes subtype, package* pkg = nullptr);

	// Adds settlement to remotePlayer and board from both Enablers
	void addSettlementToRemote(string position);
	// Adds road to localPlayer and board from both Enablers
	void addRoadToRemote(string position);;
	// Eliminates Robbers cards
	bool deleteCards(vector<ResourceType> descarte, Player * player_);
	// Enables All posible actions in a turn
	void enableRemoteActions();

	// When receiving an OfferTrade, if local player doesn't have enough resources, it automatically rejects the offer and returns false.
	bool checkResourcesToGiveBackAndRespond(OfferTradePkg* pkg);
	// When local player doesn't have enough resources, calls rejectOffer and writes message to user informing of the situation.
	void respondImposibleOfferTrade();
	// Checks if remotePlayer should own longestRoadCard, comparing with localPlayer. If the remote is the rightful owner of the card, this gives remote de card ant takes it away from local.
	void checkLongestRoad();

	void chackLargestArmy();
};

