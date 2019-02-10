#include "Board.h"
#include "Hex.h"
#include <ctime>

Board::Board()
{
}

Board::Board(map<char, Token*>& board_, char robber_) : board(board_), robber(robber_)
{
}

Board::Board(map<char, Token*>& board_, char robber_, map<Coordinate, PortType>& ports_) : board(board_), robber(robber_), ports(ports_)
{
}

Board::~Board()
{
	for (auto token : board)
	{
		delete token.second;
	}
}

void Board::shuffleBoard()
{
	vector<PortType> puertos = { PortType::_2Lx1,PortType::_2Mx1,PortType::_2Ox1,PortType::_2Px1,PortType::_2Tx1,PortType::_3x1 };
	vector<ResourceType> resources = {BOSQUE,BOSQUE, BOSQUE, BOSQUE, CAMPOS,CAMPOS,CAMPOS,CAMPOS,COLINAS,COLINAS,COLINAS,DESIERTO,MONTAÑAS,MONTAÑAS,MONTAÑAS,PASTOS,PASTOS,PASTOS,PASTOS };
	vector<char> circTkns = { 2,12,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11 };
	map<DevCards, int> devs = { {KNIGHT,14},{ROAD_BUILDING,2},{MONOPOLY,2},{YEARS_OF_PLENTY,2},{VICTORY_POINTS,5} };
	
	const vector<string> utiles = // los vertices exteriores en sentido horario
	{
		"05A","0A","0AB","0B","0BC","01C",
		"1C","1CG","1G","1GL","12L",
		"2L","2LP","2P","2PS","23S",
		"3S" ,"3RS","3R","3QR","34Q",
		"4Q","4MQ","4M" ,"4HM","45H",
		"5H","5DH","5D","5AD"
	};

	srand(time(NULL));
	for (int i = 0; i < 6; i++) // sorteo los mares
	{
		size_t randPos = rand() % puertos.size();
		PortType randPort = puertos.at(randPos);
		puertos.erase(puertos.begin()+randPos);
		Sea * mar = new Sea();
		mar->setPortType(randPort);
		board['0'+i] = mar;
	}

	for (int i = 0; i < 6; i++) // me armo la lista de puertos
	{
		PortType water = static_cast<Sea *>(board['0'+i])->getPortType();
		switch (water)
		{
		case PortType::_2Tx1: case PortType::_2Ox1: case PortType::_2Lx1:
			ports.insert(pair<string, PortType>(utiles[5 * i], PortType::_3x1));
			ports.insert(pair<string, PortType>(utiles[5 * i + 1], PortType::_3x1));
			ports.insert(pair<string, PortType>(utiles[5 * i + 3], water));
			ports.insert(pair<string, PortType>(utiles[5 * i + 4], water));
			break;
		default:
			ports.insert(pair<string, PortType>(utiles[5 * i + 2], water));
			ports.insert(pair<string, PortType>(utiles[5 * i + 3], water));
			break;
		}
	}

	for (int i = 0; i < 19; i++) // sorteo los recursos
	{
		size_t randPos = rand() % resources.size();
		ResourceType randRec = resources.at(randPos);
		resources.erase(resources.begin() + randPos); // lo saco de la lista
		Hex * token = new Hex;
		token->setResource(randRec);
		board['A'+i] = token;
	}

	for (int i = 0; i < 19; i++) // sorteo los circular tokens
	{
		if (static_cast<Hex *>(board.at('A' + i))->giveResource() != DESIERTO)
		{
			size_t randPos = rand() % circTkns.size();
			char randCirc = circTkns.at(randPos);
			static_cast<Hex *>(board.at('A' + i))->setDiceNum(randCirc);
			circTkns.erase(circTkns.begin() + randPos);
		}
		else
		{
			robber = 'A' + i;
			static_cast<Hex *>(board.at('A' + i))->setDiceNum(0);
		}
	}

	while (!pileOfDevCards.empty()) { pileOfDevCards.pop(); } // vacio la pila de dev cards por las dudas
	for (int i = 0; i < 25; i++) // sorteo las dev cards
	{
		switch (rand() % 5)
		{
		case 0:
			if (devs[KNIGHT] != 0) 
			{
				pileOfDevCards.push(KNIGHT); // si todavia tengo cartas de ese tipo afrego
				devs[KNIGHT]--;
			}
			else
				i--; // si no tengo vuelvo a sortear otro numero
			break;
		case 1:
			if (devs[YEARS_OF_PLENTY] != 0)
			{
				pileOfDevCards.push(YEARS_OF_PLENTY);
				devs[YEARS_OF_PLENTY]--;
			}
			else
				i--;
			break;
		case 2:
			if (devs[ROAD_BUILDING] != 0)
			{
				pileOfDevCards.push(ROAD_BUILDING);
				devs[ROAD_BUILDING]--;
			}
			else
				i--; 
			break;
		case 3:
			if (devs[MONOPOLY] != 0)
			{
				pileOfDevCards.push(MONOPOLY);
				devs[MONOPOLY]--;
			}
			else
				i--;
			break;
		case 4:
			if (devs[VICTORY_POINTS] != 0)
			{
				pileOfDevCards.push(VICTORY_POINTS);
				devs[VICTORY_POINTS]--;
			}
			else
				i--;
			break;
		}
	} 
	// swich case medio feo, no abrir

}

void Board::copyBoard(Board * original)
{
	const vector<string> utiles = // los vertices exteriores en sentido horario
	{
		"05A","0A","0AB","0B","0BC","01C",
		"1C","1CG","1G","1GL","12L",
		"2L","2LP","2P","2PS","23S",
		"3S" ,"3RS","3R","3QR","34Q",
		"4Q","4MQ","4M" ,"4HM","45H",
		"5H","5DH","5D","5AD"
	};

	robber = original->getRobberPos();
	Hex * aux;
	Sea * aux2;
	for (int i = 0; i < 19; i++)
	{
		aux = new Hex;
		aux->setDiceNum(original->getCircToken('A' + i));
		aux->setResource(original->getResourceFromHex('A' + i));
		board['A' + i] = aux;
	}
	for (int i = 0; i < 6; i++)
	{
		aux2 = new Sea;
		aux2->setPortType(original->getPortType(i));
		board[i] = aux;
	}

	for (int i = 0; i < 6; i++) // me armo la lista de puertos
	{
		PortType water = static_cast<Sea *>(board[i])->getPortType();
		switch (water)
		{
		case PortType::_2Tx1: case PortType::_2Ox1: case PortType::_2Lx1:
			ports.insert(pair<string, PortType>(utiles[5 * i], PortType::_3x1));
			ports.insert(pair<string, PortType>(utiles[5 * i + 1], PortType::_3x1));
			ports.insert(pair<string, PortType>(utiles[5 * i + 3], water));
			ports.insert(pair<string, PortType>(utiles[5 * i + 4], water));
			break;
		default:
			ports.insert(pair<string, PortType>(utiles[5 * i + 2], water));
			ports.insert(pair<string, PortType>(utiles[5 * i + 3], water));
			break;
		}
	}

	pileOfDevCards = original->getDevCards();
}

void Board::setDevCards(stack<DevCards>const & pileOfDevCards_)
{
	pileOfDevCards = pileOfDevCards_;
}

void Board::setCircularToken(char token, unsigned int circToken)
{
	((Hex*)board[token])->setDiceNum(circToken);
}

bool Board::addSettlementToTokens(string position, Player* owner)
{
	bool ret = true;
	for (char c : position)					// For every token in coordinate...
	{
		ret &= board[c]->addSettlement(owner);		// Adds settlement.
	}
	return ret;
}

bool Board::addRoadToTokens(string position, Player * owner)
{
	bool ret = true;
	for (char c : position)						// For every token in coordinate...
	{
		ret &= board[c]->addRoad(owner);		// Adds road.
	}
	return ret;
}

bool Board::addCityToTokens(string position, Player * owner)
{
	bool ret = true;
	for (char c : position)						// For every token in coordinate...
	{
		ret &= board[c]->addCity(owner);		// Adds city.
	}
	return ret;
}

ResourceType Board::getResourceFromHex(char tokenChar)
{
	Hex* hex = static_cast< Hex* >(board[tokenChar]);
	return hex->giveResource();
}

void Board::assignResourcesForNum(int num)
{
	for (auto token : board)
	{
		if (isalpha(token.first))							// If it's a Hex...
		{
			Hex* hex = static_cast<Hex*>(token.second);
			if (hex->getDiceNum() == num)					// If it's diceNum is the given...
			{
				if (token.first != robber)
				{
					hex->assignResources();
				}
			}
		}
	}
}

void Board::moveRobber(char position)
{
	robber = position;
}

char Board::getRobberPos()
{
	return robber;
}

DevCards Board::pickDevCard()
{
	DevCards card = pileOfDevCards.top();
	pileOfDevCards.pop();
	return card;
}

bool Board::checkIfIsPort(string position)
{
	return (ports.find(position) != ports.end());
}

PortType Board::getPortType(string position)
{
	return ports[position];
}

PortType Board::getPortType(char position)
{
	if (board[position]->whatAmI().compare("Sea") == 0)
	{
		return static_cast<Sea *>(board[position])->getPortType();
	}
	else
	{
		return PortType::_4x1; // deffault/error
	}
}

char Board::getCircToken(char hex_)
{
	if (board[hex_]->whatAmI().compare("Hex") == 0)
	{
		return static_cast<Hex *>(board[hex_])->getDiceNum();
	}
	else
	{
		return 0;
	}
}

stack<DevCards> Board::getDevCards(void)
{
	return pileOfDevCards;
}

void Board::setPort(string position, PortType type)
{
	ports[position] = type;
}
