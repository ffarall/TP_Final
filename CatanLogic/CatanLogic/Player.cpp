#include "Player.h"



Player::Player()
{
	init();
}


Player::~Player()
{
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

void Player::allVertexesAvailable()
{
	availableForSettlements = allVertexes;
}
