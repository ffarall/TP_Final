#pragma once
#include <cstdint>
#include <map>
#include <list>
#include <string>
#include <vector>
#include "Settlement.h"
#include "Road.h"

using namespace std;

class Player
{
public:
	Player();
	virtual ~Player();

	void init();

	size_t getVictoryPoints();
	string getName();

	// Asks if player has won.
	bool hasWon();

private:
	// True when player has won.
	bool iWon;
	// Counter of victory points.
	size_t victoryPoints;
	// Name of the player.
	string name;
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
	list< string > availableForSettlements;

	// Sets all corners of board available for building Settlements.
	void allJunctionsAvailable();

	// All combinations of edges.
	const vector< const string > allEdges = {
		"A05", "B0A", "0BC", "C0", "1C0",
		"A5", "BA", "CB", "1CG",
		"D5A", "AD"
	};
	// All combinations for vertexes.
	const vector< const string > allVertexes = { 
		"0A", "0B", "10C",
		"A05", "B0A", "C0B", "1C",
		"A5D", "BA3", "CBF", "1CG",
		"D5", "EAD", "FBE", "GCF", "1G",
		"D5H", "EDI", "FEJ", "GFK", "1GL",
		"H5", "IDH", "JEI", "KFG", "LGK", "1L2",
		"H54", "IHM", "JIN", "KJO", "LKP", "2L",
		"MH4", "NIM", "OJN", "PKO", "2LP",
		"M4", "NMQ", "ONR", "POS", "2P",
		"QM4", "RNQ", "SOR", "2PS",
		"Q4", "RQ3", "SR3", "2S3",
		"3Q4", "3R", "3S"
	};
};

