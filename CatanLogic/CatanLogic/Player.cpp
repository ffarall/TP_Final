#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::init()
{
	victoryPoints = 0;
}

size_t Player::getVictoryPoints()
{
	return victoryPoints;
}
