#include "package.h"

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

MapIsPkg::MapIsPkg(const char * mapa) :package(headers::MAP_IS)
{
	int i = 0;

	for (char a : std::string(mapa))
	{
		all[i++] = a;
	}
}

MapIsPkg::MapIsPkg(std::vector<mar>& agua_, std::vector<recursos>& piezas):package(headers::MAP_IS)
{
	
	int j = 0;
	if (agua_.size() == 6 && piezas.size() == 19)
	{

		for (int i = 0; i < 6; i++, j++)
			agua[i] = agua_[i];
		for (int i = 0; i < 19; i++)
			tablero[i] = piezas[i];
	}
	else
	{
		for (int i = 0; i < 6; i++)
			agua[i] = mar::_3X1;
		for (int i = 0; i < 19; i++)
			tablero[i] = recursos::DESIERTO;
	}

	for (int i = 0; i < 6; i++, j++)
		all[j] = static_cast<char>(agua[i]);
	for (int i = 0; i < 19; i++, j++)
		all[j] = static_cast<char>(tablero[i]);
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

CircularTokensPkg::circularTokens(const char * _tokenList) :package(headers::CIRCULAR_TOKENS)
{
	std::string tokenList(_tokenList);
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
	ret += myTokens;
	return ret;
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

DevCards * DevCardsPkg::getDeck()
{
	return pilon;
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
	return ret;
}

RobberCardsPkg::RobberCardsPkg(const char * devList) :package(headers::ROBBER_CARDS)
{
	std::string _cartas(devList);
	length = _cartas.size();
	for (char a : _cartas)
	{
		cartas.push_back(static_cast<DevCards>(a));
	}
}

RobberCardsPkg::RobberCardsPkg(std::vector<DevCards>& descarte):package(headers::ROBBER_CARDS)
{
	length = descarte.size();
	cartas = descarte;
}	

std::vector<DevCards> RobberCardsPkg::getCards()
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
	for (DevCards a : cartas) { ret.push_back(static_cast<char>(a)); }
	return;
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
	return ;
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
	return;
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
	return;;
}

BanckTradePkg::BanckTradePkg(std::vector<recursos>& myResouces, recursos _pedido):package(headers::BANK_TRADE)
{
	nOfResources = myResouces.size();
	misRecursos = myResouces;
	pedido = _pedido;
}

char BanckTradePkg::getLength()
{
	return nOfResources;
}

std::vector<recursos> BanckTradePkg::getResoucesPaid()
{
	return misRecursos;
}

recursos BanckTradePkg::getResouceBougth()
{
	return pedido;
}

std::string BanckTradePkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0' + nOfResources);
	for (recrsos a : misRecursos) { ret.push_back(static_cast<char>(a)); }
	ret.push_back(static_cast<char>(pedido));
	return ret;
}

OfferTradePkg::OfferTradePkg(std::vector<recursos>& offer, std::vector<recursos>& pedido):package(headers::OFFER_TRADE)
{
	myOffer = offer;
	esperoAcambio = pedido;
}

std::vector<recursos> OfferTradePkg::getMyOnes()
{
	return myOffer;
}

std::vector<recursos> OfferTradePkg::getOponentOnes()
{
	return esperoAcambio;
}

std::string OfferTradePkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back('0'+myOffer.size());
	ret.push_back('0' + esperoAcambio.size());
	for (recrsos a : myOffer) { ret.push_back(static_cast<char>(a)); }
	for (recrsos a : esperoAcambio) { ret.push_back(static_cast<char>(a)); }
	return ret;
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

MonopolyPkg::MonopolyPkg(recursos recurso):package(headers::MONOPOLY)
{
	resource = recurso;
}

recursos MonopolyPkg::getResouce()
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

YearsOfPlentyPkg::YearsOfPlentyPkg(recursos rec1_, recursos rec2_):package(headers::YEARS_OF_PLENTY)
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

CardIsPkg::CardIsPkg(char resource) :package(headers::CARD_IS)
{
	recurso = static_cast<recursos>(resource);
}

std::string CardIsPkg::getPackage()
{
	std::string ret;
	ret.push_back(static_cast<char>(nombre));
	ret.push_back(static_cast<char>(recurso));
	return ret;
}
