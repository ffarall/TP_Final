#include "Player.h"
#include <algorithm>


Player::Player()
{
	init();
}


Player::~Player()
{
	for (auto settlement : mySettlements)	// Deletes mySettlement
	{
		delete settlement.second;
	}
	for (auto settlement : rivalsSettlements)	// Deletes rivalsSettlement
	{
		delete settlement.second;
	}
	for (auto road : myRoads)	// Deletes myRoads
	{
		delete road.second;
	}
	for (auto road : rivalsRoads)	// Deletes rivalsRoads
	{
		delete road.second;
	}
}

void Player::init()
{
	victoryPoints = 0;
	iWon = false;
	mySettlements.clear();
	myRoads.clear();
	rivalsRoads.clear();
	rivalsSettlements.clear();
	availableForRoad.clear();
	allVertexesAvailable();
}

size_t Player::getVictoryPoints()
{
	return victoryPoints;
}

void Player::addToMySettlements(string position)
{
	Settlement* newSettlement = new Settlement(position);
	mySettlements.insert(pair< string, Settlement* >(position, newSettlement));
}

void Player::addToRivalsSettlements(string position)
{
	Settlement* newSettlement = new Settlement(position);
	rivalsSettlements.insert(pair< string, Settlement* >(position, newSettlement));
}

void Player::addToMyRoads(string position)
{
	Road* newRoad = new Road(position);
	myRoads.insert(pair< string, Road* >(position, newRoad));
}

void Player::addToRivalsRoads(string position)
{
	Road* newRoad = new Road(position);
	rivalsRoads.insert(pair< string, Road* >(position, newRoad));
}

void Player::promoteToMyCity(string position)
{
	Settlement* newCity = new City(position);
	mySettlements[position] = newCity;
}

void Player::promoteToRivalsCity(string position)
{
	Settlement* newCity = new City(position);
	rivalsSettlements[position] = newCity;
}

void Player::allVertexesAvailable()
{
	availableForSettlements = allVertexes;
}
