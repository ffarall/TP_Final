#include "package.h"
#include "Hex.h"
using namespace std;

package::package()
{

}

package::package(headers paquete)
{
	nombre = paquete;
}

package::~package()
{
}

headers package::getPacket()
{
	return nombre;
}

std::string package::getPackage()
{
	std::string ret;
	ret.push_back((static_cast<char>(nombre)));
	return ret;
}

NameIsPkg::NameIsPkg(std::string name_):package(headers::NAME_IS)
{
	name = name_;
	length = name.length();
}

std::string NameIsPkg::getName()
{
	return name;
}

std::string NameIsPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(headers::NAME_IS));
	ret.push_back(length);// ver que no mande un ascii y meta el numero
	ret += name;
	return ret;
}

MapIsPkg::MapIsPkg(Board * board_) :package(headers::MAP_IS)
{
	board = new Board(*board_);

	for (int i = 0; i < 6; i++)
	{
		all[i] = static_cast<char>(board->getPortType(i+'0'));
	}

	for (int i = 0; i < 19; i++)
	{
		all[i + 6] = static_cast<char>(board->getResourceFromHex('A' + i));
	}
}

MapIsPkg::MapIsPkg(const char * mapa) :package(headers::MAP_IS)
{
	int i = 0, j = 0, RobberPos = 0;
	map<char, Token*> table;
	map<string, PortType> puertos;

	for (char a : std::string(mapa,25))
	{
		all[i++] = a;	
	}

	for (int i = 0; i < 6; i++, j++)
	{
		Sea * boo = new Sea();
		boo->setPortType(static_cast<PortType>(all[i]));
		table.insert(pair<char, Token*>(i+'0', static_cast<Token *>(boo)));
	}
	for (int i = 0; i < 19; i++)
	{
		if (all[i + 6] == 'N') { RobberPos = 'A' + i; } // para guardar la posicion del robber
		Hex * boo2 = new Hex();
		boo2->setResource(static_cast<ResourceType>(all[i+6]));
		table.insert(pair<char, Token*>('A' + i, static_cast<Token *>(boo2)));
	}

	for (int i = 0; i < 6; i++)
	{
		PortType var = static_cast<PortType>(all[i]);
		switch (var)
		{
		case PortType::_2Tx1: case PortType::_2Ox1: case PortType::_2Lx1:
			puertos.insert(pair<string, PortType>(utiles[5 * i], PortType::_3x1));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 1], PortType::_3x1));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 3], var));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 4], var));
			break;
		default:
			puertos.insert(pair<string, PortType>(utiles[5 * i + 2], var));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 3], var));
			break;
		}
	}

	board = new Board(table, RobberPos, puertos);
}

MapIsPkg::MapIsPkg(std::vector<PortType>& agua_, std::vector<ResourceType>& piezas) : package(headers::MAP_IS)
{
	map<char, Token*> table ;
	map<string, PortType> puertos;
	int j = 0, RobberPos = 0;
	if (agua_.size() == 6 && piezas.size() == 19)
	{

		for (int i = 0; i < 6; i++, j++)
		{
			agua[i] = agua_[i];
			Sea * boo = new Sea();
			boo->setPortType(agua_.at(i+'0'));
			table.insert(pair<char, Token*>(i, static_cast<Token *>(boo) ));
		}
		for (int i = 0; i < 19; i++)
		{
			tablero[i] = piezas[i];
			if (tablero[i] == ResourceType::DESIERTO) { RobberPos = 'A' + i; }
			Hex * boo2 = new Hex();
			boo2->setResource(piezas[i]);
			table.insert(pair<char, Token*>('A'+i, static_cast<Token *>(boo2)));
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
			agua[i] = PortType::_3x1;
		for (int i = 0; i < 19; i++)
			tablero[i] = ResourceType::DESIERTO;
	}

	for (int i = 0 ; i<6;i++)
	{
		switch (agua[i])
		{
		case PortType::_2Tx1 : case PortType::_2Ox1 : case PortType::_2Lx1 :
			puertos.insert(pair<string, PortType>(utiles[5 * i], PortType::_3x1));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 1], PortType::_3x1));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 3], agua[i]));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 4], agua[i]));
			break;
		default:
			puertos.insert(pair<string, PortType>(utiles[5 * i + 2], agua[i]));
			puertos.insert(pair<string, PortType>(utiles[5 * i + 3], agua[i]));
			break;
		}
	}

	for (int i = 0; i < 6; i++, j++)
		all[j] = static_cast<char>(agua[i]);
	for (int i = 0; i < 19; i++, j++)
		all[j] = static_cast<char>(tablero[i]);

	board = new Board(table, RobberPos, puertos);
}

char * MapIsPkg::getMap()
{
	return all;
}

std::string MapIsPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret += all;
	return ret;
}

Board * MapIsPkg::getBoard()
{
	return board;
}

CircularTokensPkg::CircularTokensPkg(Board * tablero) :package(headers::CIRCULAR_TOKENS)
{
	for (int i = 0; i < 19; i++)
	{
		if (tablero->getResourceFromHex('A'+i) != DESIERTO)
		{
			myTokens[i] = static_cast<char>(tablero->getCircToken('A' + i));
		}
		else
		{
			myTokens[i] = 0;
		}
	}
}

CircularTokensPkg::CircularTokensPkg(const char * _tokenList) :package(headers::CIRCULAR_TOKENS)
{
	std::string tokenList(_tokenList,19);
	if (tokenList.size() == 19)
	{
		for (int i = 0; i < 19; i++)
			myTokens[i] = tokenList[i];
	}
}

CircularTokensPkg::CircularTokensPkg(std::vector<char>& tokenList):package(headers::CIRCULAR_TOKENS)
{
	if (tokenList.size() == 19)
	{
		for (int i = 0; i < 19; i++)
			myTokens[i] = tokenList[i];
	}
}

char * CircularTokensPkg::getTokenList()
{
	return myTokens;
}

std::string CircularTokensPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	for (int i = 0; i < 19; i++)
		ret.push_back(myTokens[i]);
	return ret;
}

DevCardsPkg::DevCardsPkg(stack<DevCards> pilaDeCartas) :package(headers::DEV_CARDS)
{
	for (int i = 0; i < 25; i++)
	{
		pilon[i] = pilaDeCartas.top();
		pilaDeCartas.pop();
	}
}

DevCardsPkg::DevCardsPkg(const char * _deck) :package(headers::DEV_CARDS)
{
	std::string deck(_deck);
	if (deck.size() == 25)
	{
		for (int i = 0; i < 25; i++)
			pilon[i] = static_cast<DevCards>(deck[i]);
	}
}

DevCardsPkg::DevCardsPkg(std::vector<DevCards>& deck):package(headers::DEV_CARDS)
{
	if (deck.size() == 19)
	{
		for (int i = 0; i < 25; i++)
			pilon[i] = deck[i];
	}
}

stack< DevCards > DevCardsPkg::getDeck()
{
	stack< DevCards > auxiliar;
	for (int i = 0; i < 25; i++)
	{
		auxiliar.push(pilon[24-i]);
	}
	return auxiliar;
}

std::string DevCardsPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	for (int i = 0; i < 25; i++)
	{
		ret.push_back(static_cast<char>(pilon[i]));
	}
	return ret;
}

DicePkg::DicePkg(char dice1_, char dice2_):package(headers::DICE_ARE)
{
	if (dice1_ > 0 && dice1_ < 7)
		dice1 = dice1_;
	if (dice2_ > 0 && dice2_ < 7)
		dice2 = dice2_;
}

char DicePkg::getValue(bool which)
{
	return which?dice1:dice2;
}

std::string DicePkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(dice1+'0');
	ret.push_back(dice2+'0');
	return ret;
}

RobberCardsPkg::RobberCardsPkg(char length_):package(headers::ROBBER_CARDS)
{
	length = length_;
}

RobberCardsPkg::RobberCardsPkg(const char * devList) :package(headers::ROBBER_CARDS)
{
	std::string _cartas(devList);
	length = _cartas.size();
	for (char a : _cartas)
	{
		cartas.push_back(static_cast<ResourceType>(a));
	}
}

RobberCardsPkg::RobberCardsPkg(std::vector<ResourceType> descarte):package(headers::ROBBER_CARDS)
{
	length = descarte.size();
	cartas = descarte;
}	

std::vector<ResourceType> RobberCardsPkg::getCards()
{
	return cartas;
}

char RobberCardsPkg::getLength()
{
	return length;
}

std::string RobberCardsPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret += length;
	for (ResourceType a : cartas) { ret.push_back(static_cast<char>(a)); }
	return ret;
}

char RobberCardsPkg::getAmountOf(ResourceType recurso)
{
	char amount = 0;
	for (auto each : cartas)
	{
		if (each == recurso)
			amount++;
	}
	return amount;
}

bool RobberCardsPkg::isComplete()
{
	if (length == cartas.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RobberCardsPkg::pushCard(ResourceType recurso)
{
	if (cartas.size() < length)
	{
		cartas.push_back(recurso);
	}
}

RobberMovePkg::RobberMovePkg(char newPos):package(headers::ROBBER_MOVE)
{
	if (newPos >= 'A' &&  newPos <= 'S')
		pos = newPos;
}

char RobberMovePkg::getPos()
{
	return pos;
}

std::string RobberMovePkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(pos);
	return ret;
}

SettlementPkg::SettlementPkg(std::string pos_):package(headers::SETTLMENT)
{
	length = pos_.size();
	pos = pos_;
}

char SettlementPkg::getLength()
{
	return length;
}

std::string SettlementPkg::getPos()
{
	return pos;
}

std::string SettlementPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0' + length);
	ret += pos;
	return ret ;
}

CityPkg::CityPkg(std::string pos_):package(headers::CITY)
{
	length = pos_.length();
	pos = pos_;
}

char CityPkg::getLength()
{
	return length;
}

std::string CityPkg::getPos()
{
	return pos;
}

std::string CityPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0' + length);
	ret += pos;
	return ret;
}

RoadPkg::RoadPkg(std::string pos_):package(headers::ROAD)
{
	length = pos_.length();
	pos = pos_;
}

char RoadPkg::getLength()
{
	return length;
}

std::string RoadPkg::getPos()
{
	return pos;
}

std::string RoadPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0' + length);
	ret += pos;
	return ret;
}

BankTradePkg::BankTradePkg():package(headers::BANK_TRADE) // crea el package vacio
{
	nOfResources = 0;
	misRecursos.clear();
	pedido = ResourceType::DESIERTO; // es el recurso que no existe
	offer = false;
}

BankTradePkg::BankTradePkg(std::vector<ResourceType>& myResouces, ResourceType _pedido) :package(headers::BANK_TRADE)
{
	nOfResources = myResouces.size();
	misRecursos = myResouces;
	pedido = _pedido;
	offer = false;
}

BankTradePkg::BankTradePkg(BankTradePkg * copiar) :package(headers::BANK_TRADE)
{
	nOfResources = copiar->getLength();
	pedido = copiar->getResouceBougth();
	for (auto rec : copiar->getResoucesPaid())
	{
		misRecursos.push_back(rec);
	}
	offer = false;
}

char BankTradePkg::getLength()
{
	return nOfResources;
}

std::vector<ResourceType> BankTradePkg::getResoucesPaid()
{
	return misRecursos;
}

ResourceType BankTradePkg::getResouceBougth()
{
	return pedido;
}

void BankTradePkg::setType(char num)
{
	nOfResources = num;
}

void BankTradePkg::setPaid(std::vector<ResourceType>& myResources)
{
	misRecursos = myResources;
}

void BankTradePkg::setBougth(ResourceType pedido_)
{
	pedido = pedido_;
}

void BankTradePkg::closeOffer()
{
	offer = true;
}

std::string BankTradePkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0' + nOfResources);
	for (ResourceType a : misRecursos) { ret.push_back(static_cast<char>(a)); }
	ret.push_back(static_cast<char>(pedido));
	return ret;
}

bool BankTradePkg::isComplete()
{
	bool ret = false;
	if (nOfResources != 0 && pedido != ResourceType::DESIERTO)
	{
		ret = true;
	}
	return ret;
}

bool BankTradePkg::offerclosed()
{
	return offer;
}

OfferTradePkg::OfferTradePkg():package(headers::OFFER_TRADE)
{
	myOffer.clear();
	esperoAcambio.clear();
	offer = false;
}

OfferTradePkg::OfferTradePkg(std::vector<ResourceType>& offer_, std::vector<ResourceType>& pedido):package(headers::OFFER_TRADE)
{
	myOffer = offer_;
	esperoAcambio = pedido;
	offer = false;
}

OfferTradePkg::OfferTradePkg(OfferTradePkg * copiar) :package(headers::OFFER_TRADE)
{
	for (auto rec : copiar->getMyOnes())
	{
		addToMyOffer(rec);
	}
	for (auto req : copiar->getOpponentOnes())
	{
		addToMyRequest(req);
	}
	offer = false;
}

std::vector<ResourceType> OfferTradePkg::getMyOnes()
{
	return myOffer;
}

std::vector<ResourceType> OfferTradePkg::getOpponentOnes()
{
	return esperoAcambio;
}

char OfferTradePkg::getMyOnes(ResourceType recurso)
{
	char amount = 0;
	for (auto each : myOffer)
	{
		if (each == recurso)
			amount++;
	}
	return amount;
}

char OfferTradePkg::getOpponent(ResourceType recurso)
{
	char amount = 0;
	for (auto each : esperoAcambio)
	{
		if (each == recurso)
			amount++;
	}
	return amount;
}

void OfferTradePkg::addToMyOffer(ResourceType offer_)
{
	if (myOffer.size() < 9)
	{
		myOffer.emplace_back(offer_);
	}
	
}

void OfferTradePkg::closeOffer()
{
	offer = true;
}

void OfferTradePkg::addToMyRequest(ResourceType pedido_)
{
	if (esperoAcambio.size() < 9)
	{
		esperoAcambio.emplace_back(pedido_);
	}
}

std::string OfferTradePkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0'+myOffer.size());
	ret.push_back('0' + esperoAcambio.size());
	for (ResourceType a : myOffer) { ret.push_back(static_cast<char>(a)); }
	for (ResourceType a : esperoAcambio) { ret.push_back(static_cast<char>(a)); }
	return ret;
}

bool OfferTradePkg::isComplete()
{
	bool ret = false;
	if (myOffer.size() > 0 && esperoAcambio.size() > 0)
	{
		ret = true;
	}
	return ret;
}

bool OfferTradePkg::offerclosed()
{
	return offer;
}

KnightPkg::KnightPkg(char newPos):package(headers::KNIGHT)
{
	if (newPos >= 'A' && newPos <= 'S')
		pos = newPos;
}

char KnightPkg::getPos()
{
	return pos;
}

std::string KnightPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(pos);
	return ret;
}

MonopolyPkg::MonopolyPkg():package(headers::MONOPOLY)
{
	resource = ResourceType::DESIERTO; // es el que no puede ser nunca
}

MonopolyPkg::MonopolyPkg(ResourceType recurso):package(headers::MONOPOLY)
{
	resource = recurso;
}

ResourceType MonopolyPkg::getResource()
{
	return resource;
}

std::string MonopolyPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(static_cast<char>(resource));
	return ret;
}

void MonopolyPkg::setResource(ResourceType rec)
{
	resource = rec;
}

YearsOfPlentyPkg::YearsOfPlentyPkg():package(headers::YEARS_OF_PLENTY)
{
	rec1 = rec2 = ResourceType::DESIERTO; 
}

YearsOfPlentyPkg::YearsOfPlentyPkg(ResourceType rec1_, ResourceType rec2_):package(headers::YEARS_OF_PLENTY)
{
	rec1 = rec1_;
	rec2 = rec2_;
}

std::string YearsOfPlentyPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(static_cast<char>(rec1));
	ret.push_back(static_cast<char>(rec2));
	return ret;
}

ResourceType YearsOfPlentyPkg::getResource(bool cual)
{
	return cual ? rec1:rec2 ;
}

void YearsOfPlentyPkg::setResource(bool cual, ResourceType recurso)
{
	if (cual)
	{
		rec1 = recurso;
	}
	else
	{
		rec2 = recurso;
	}
}

CardIsPkg::CardIsPkg(char resource) :package(headers::CARD_IS)
{
	recurso = static_cast<ResourceType>(resource);
}

ResourceType CardIsPkg::getResource()
{
	return recurso;
}

std::string CardIsPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(static_cast<char>(recurso));
	return ret;
}
