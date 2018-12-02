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

	size_t getVictoryPoints();
	string getName();

	// Asks if player has won.
	bool hasWon();

	// Increments the given resource.
	void addResource(ResourceType resource, int amount);
	// Decrements the given resource if it's not 0. Returns false if there are not enough resources
	bool useResource(ResourceType resource, int amount);
	// Returns total amount of resources.
	size_t totalResourcesAmount();

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

	// Checks if position is available for settlement and if player has enough resources. Uses resources.
	bool checkSettlementAvailability(string position);
	// Checks if position is available for road and if player has enough resources.
	bool checkRoadAvailability(string position);
	// Checks if a Settlement is promotable to a City and if player has enough resources.
	bool checkPromotionOfCity(string position);

	bool checkSettlementResources();
	bool checkRoadResources();
	bool checkCityResources();

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

private:
	void init();

	// True when player has won.
	bool iWon;
	// Counter of victory points.
	size_t victoryPoints;
	// Victory points earned by DevCard (hidden to other player).
	size_t cardVictoryPoints;
	// Name of the player.
	string name;
	// Resources the player has.
	map< ResourceType, size_t > resources;
	// Map of this player's settlements (some can be cities).
	map< string, Settlement* > mySettlements;
	// Map of this player's roads.
	map< string, Road* > myRoads;
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

	// Sets all corners of board available for building Settlements.
	void allVertexesAvailable();
	// Updates available coordinates for roads and settlements.
	void updateAvailability();

	// Increment victoryPoints and checks if has Won.
	void incVictoryPoints();

	// DevCards Routines.
	void useKnight();
	void useVictoryPoint();
	void useMonopoly();
	void useYearsOfPlenty();
	void useRoadConstruction();

	// All combinations of edges.
	const vector< string > allEdges = {
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
	const vector< string > allVertexes = { 
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

