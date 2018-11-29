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
}

size_t Player::getVictoryPoints()
{
	return victoryPoints;
}
