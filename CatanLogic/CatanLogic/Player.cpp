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

void Player::allJunctionsAvailable()
{
	availableForSettlements = { "0A", "0B", "10C", 
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
}
