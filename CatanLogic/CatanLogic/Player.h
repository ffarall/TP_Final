#pragma once
#include <cstdint>

class Player
{
public:
	Player();
	virtual ~Player();

	void init();

	size_t getVictoryPoints();

private:
	size_t victoryPoints;
};

