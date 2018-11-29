#pragma once
#include <cstdint>
#include <map>
#include <list>
#include <string>
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
	void allVertexesAvailable();

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
		"0A", "0B", "10C",
		"05A", "0AB", "0BC", "1C",
		"5AD", "3AB", "BCF", "1CG",
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
};

