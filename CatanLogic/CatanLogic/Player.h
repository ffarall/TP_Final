#pragma once
#include <cstdint>
#include <map>
#include <list>
#include <vector>
#include <string>
#include "Settlement.h"
#include "Road.h"
#include "City.h"
#include "Hex.h"
#include "Sea.h"
#include "EDASubject.h"
#include "Board.h"

using namespace std;
using DevCardRoutine = void (Player::*)();

struct DevCardUsage
{
	size_t amount;
	void (Player::*useDevCard)();
};

class Player :
	public EDASubject
{
public:
	Player();
	Player(string name_);
	virtual ~Player();

	void reset();
	void init();

	size_t getVictoryPoints();
	string getName();

	// Asks if player has won.
	bool hasWon(bool playingWithDevs);

	// Increments the given resource.
	void addResource(ResourceType resource, int amount = 1);
	// Decrements the given resource if it's not 0. Returns false if there are not enough resources
	bool useResource(ResourceType resource, int amount = 1);
	// Returns total amount of resources.
	size_t totalResourcesAmount();
	// Returns amount of the given resource.
	size_t getResourceAmount(ResourceType resource);

	// Add a settlement to mySettlements. User must check if position is available. Uses resources. Adds 1 victoryPoint.
	void addToMySettlements(string postion);
	// Add a settlement to rivalsSettlements. User must check if position is available.
	void addToRivalsSettlements(string position);
	// Add a road to myRoads. User must check if position is available. Uses resources.
	void addToMyRoads(string position);
	// Add a road to rivalsRoads. User must check if position is available.
	void addToRivalsRoads(string position);
	// Promote a Settlement in mySettlements to a City. User must check if exists. Uses resources. Adds 2 victoryPoints.
	void promoteToMyCity(string position);
	// Promote a Settlement in rivalsSettlements to a City. User must check if exists.
	void promoteToRivalsCity(string position);

	size_t getRemainingSettlements();
	size_t getRemainingRoads();
	size_t getRemainingCities();

	list<string> getMySettlements();
	list<string> getMyCities();
	list<string> getMyRoads();

	// Checks if position is available for settlement and if player has enough resources. Uses resources.
	bool checkSettlementAvailability(string position);
	// Checks if position is available for road and if player has enough resources.
	bool checkRoadAvailability(string position);
	// Checks if a Settlement is promotable to a City and if player has enough resources.
	bool checkPromotionOfCity(string position);
	// Checks if user has enough resources to build a Settlement.
	bool checkSettlementResources();
	// Checks if user has enough resources to build a Road.
	bool checkRoadResources();
	// Checks if user has enough resources to build a City.
	bool checkCityResources();
	// Checks if there is a Settlement or City adjacent to the given token.
	bool isThereSetOrCity(char token);

	// Checks if given position is a port in given board.
	bool checkIfIsPort(string position, Board* board);
	// Check if any settlement or city is connected to a port
	bool checkForAnyPort(Board * board, PortType port_);
	// Does the bank trade and exchanges the resources. When the bank trade is with a port that has fixed resourcesOffered, this parameter is not needed.
	void makeBankTrade(PortType type, ResourceType resourceAsked, ResourceType resourcesOffered = MONTAÑAS);
	// Checks if player has enough resources for the given type of port.
	bool checkResourcesForBankTrade(PortType type);

	// Picks DevCard from the pile in the board. Uses resources.
	void getNewDevCard(Board* board);
	// Uses DevCard.
	void useDevCard(DevCards card);
	// Returns amount of given DevCard.
	size_t getDevCardAmount(DevCards card);
	// Checks if player has enough resources to get a DevCard.
	bool checkResourcesForDevCard();
	// Check if user has this devCard.
	bool isThereDevCard(DevCards card);

	// Returns true when this player has the Longest Road card.
	bool hasLongestRoad();
	// Gives the Longest Road Card to this player.
	void setLongestRoadCard(bool doesItHaveTheCard);
	// Returns size of longest Road.
	size_t getLongestRoad();
	// Calculates the length of a road to both sides of the given edge (which must me a road itself) and updates the longestRoad.
	void updateLongestRoad(string startingEdge);

	// Returns true when this player has the Largest Army card.
	bool hasLargestArmy();
	// Gives the Largest Army Card to this player.
	void setLargestArmyCard(bool doesItHaveTheCard);
	// Returns size of this player's army (times this player used KNIGHT DevCard).
	size_t getArmySize();

private:

	// True when player has won.
	bool iWon;
	// Counter of victory points.
	size_t victoryPoints;
	// Victory points earned by DevCard (hidden to other player).
	size_t cardVictoryPoints;
	// True when player has the Longest Road card. Counts as a Victory Point.
	bool longestRoadCard;
	// True when player has the Largest Army card. Counts as a Victory Point.
	bool largestArmyCard;
	// Name of the player.
	string name;
	// Resources the player has.
	map< ResourceType, size_t > resources;
	// Map of this player's settlements (some can be cities).
	map< string, Settlement* > mySettlements;
	// Number of Settlements remaining to build (once this reaches 0, no more Settlements can be built).
	size_t remainingSettlements;
	// Number of Cities remaining to build (once this reaches 0, no more Cities can be built).
	size_t remainingCities;
	// Map of this player's roads.
	map< string, Road* > myRoads;
	// Number of Roads remaining to build (once this reaches 0, no more Roads can be built).
	size_t remainingRoads;
	// Map of rivals' settlements (some can be cities).
	map< string, Settlement* > rivalsSettlements;
	// Map of rivals' roads.
	map< string, Road* > rivalsRoads;
	// List of coordinates available for putting roads.
	list< string > availableForRoad;
	// List of coordinates available for putting settlements.
	list< string > availableForSettlement;
	// DevCards this player has.
	map< DevCards, DevCardUsage > devCards;
	// Variable containing size of this player's army (times this player used a KNIGHT DevCard).
	size_t army;
	// Longest road of this player.
	size_t longestRoad;

	// List used when calculating the longestRoad. Stores all the edges that have roads and have already been visited.
	list< string > roadsVisited;

	// Sets all corners of board available for building Settlements.
	void allVertexesAvailable();
	// Updates available coordinates for roads and settlements.
	void updateAvailability();

	// Increment victoryPoints and checks if has Won.
	void incVictoryPoints();

	// Returns the pair of adjacent vertexes to an edge of the board.
	vector< string > getAdjacentVertexes(string edge);
	// Returns a list with the adjacent edges to a vertex of the board. Can be 2 or 3.
	vector< string > getAdjacentEdges(string vertex);
	// Recursive function used to visit all the adjacent edges which have a Road (used for calculating longestRoad).
	void followRoad(string vertex);

	// Functions for using DevCards.
	void useKnight();
	void useVictoryPoint();
	void useMonopoly();
	void useYearsOfPlenty();
	void useRoadBuilding();

	// All combinations of edges.
	const list< string > allEdges = {
		"0A5", "0AB", "0BA", "0BC", "0C", "1C0",
		"5A", "AB", "BC", "1CG",
		"5DA", "AD", "AE", "BE", "BF", "CF", "CG", "1GC",
		"5DH", "DE", "EF", "FG", "1GL",
		"5HD", "DH", "DI", "EI", "EJ", "FJ", "FK", "GK", "GL", "1L",
		"5H4", "HI", "IJ", "JK", "KL", "2L1",
		"H4", "HM", "IM", "IN", "JN", "JO", "KO", "KP", "LP", "2LP",
		"4MH", "MN", "NO", "OP", "2PL",
		"4MQ", "MQ", "NQ", "NR", "OR", "OS", "PS", "2PS",
		"4QM", "QR", "RS", "2S",
		"4Q3", "3Q", "3RQ", "3RS", "3SR", "3S2"
	};
	// All combinations for vertexes.
	const list< string > allVertexes = { 
		"0A", "0B", "01C",
		"05A", "0AB", "0BC", "1C",
		"5AD", "ABE", "BCF", "1CG",
		"5D", "ADE", "BEF", "CFG", "1G",
		"5DH", "DEI", "EFJ", "FGK", "1GL",
		"5H", "DHI", "EIJ", "FJK", "GKL", "12L",
		"45H", "HIM", "IJN", "JKO", "KLP", "2L",
		"4HM", "IMN", "JNO", "KOP", "2LP",
		"4M", "NMQ", "NOR", "OPS", "2P",
		"4MQ", "NQR", "ORS", "2PS",
		"4Q", "3QR", "3RS", "23S",
		"34Q", "3R", "3S"
	};
	//useful matrix to compre
	const string boardInStrings[14][13] =
	{
	{""	  ,""	,""	  ,""   ,""   ,""   ,""	  ,""   ,""   ,""   ,""   ,""   ,""	  },
	{""	  ,""	,""   ,""   ,"0A" ,""   ,"0B" ,""   ,"01C",""   ,""   ,""	,""   },
	{""	  ,""   ,""   ,"05A",""   ,"0AB",""   ,"0BC",""   ,"1C" ,""   ,""	,""   },
	{""	  ,""   ,""   ,"5AD",""   ,"ABE",""   ,"BCF",""   ,"1CG",""   ,""	,""   },
	{""	  ,""   ,"5D" ,""   ,"ADE",""   ,"BEF",""   ,"CFG",""   ,"1G" ,""	,""   },
	{""	  ,""   ,"5DH",""   ,"DEI",""   ,"EFJ",""   ,"FGK",""   ,"1GL",""	,""   },
	{""	  ,"5H" ,""   ,"DHI",""   ,"EIJ",""   ,"FJK",""   ,"GKL",""   ,"12L",""	  },
	{""	  ,"45H",""   ,"HIM", ""  ,"IJN",""   ,"JKO",""   ,"KLP",""   ,"2L" ,""	  },
	{""	  ,""   ,"4HM",""   ,"IMN",""   ,"JNO",""   ,"KOP",""   ,"2LP",""   ,""	  },
	{""	  ,""   ,"4M" ," "  ,"NMQ",""   ,"NOR",""   ,"OPS", ""  ,"2P" ,""   ,""	  },
	{""	  ,""   ,""   ,"4MQ",""   ,"NQR",""   ,"ORS",""   ,"2PS",""   ,""   ,""	  },
	{""	  ,""   ,""   ,"4Q" ,""   ,"3QR",""   ,"3RS",""   ,"23S",""   ,""   ,""	  },
	{""	  ,""   ,""   ,""   ,"34Q",""   ,"3R" ,""   ,"3S" ,""   ,""   ,""   ,""	  },
	{""	  ,""	,""	  ,""   ,""	  ,""	,""	  ,""   ,""	  ,""   ,""	  ,""   ,""	  }
	};
};

