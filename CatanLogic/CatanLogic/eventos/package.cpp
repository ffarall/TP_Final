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

nameIs::nameIs(std::string name_):package(headers::NAME_IS)
{
	name = name_;
	length = name.length();
}

std::string nameIs::getName()
{
	return name;
}

mapIs::mapIs(std::vector<mar>& agua_, std::vector<recursos>& piezas):package(headers::MAP_IS)
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
}

circularTokens::circularTokens(std::vector<char>& tokenList):package(headers::CIRCULAR_TOKENS)
{
	if (tokenList.size() == 19)
	{
		for (int i = 0; i < 19; i++)
			myTokens[i] = tokenList[i];
	}
}

char * circularTokens::getTokenList()
{
	return myTokens;
}

devCards::devCards(std::vector<DevCards>& deck):package(headers::DEV_CARDS)
{
	if (deck.size() == 19)
	{
		for (int i = 0; i < 25; i++)
			pilon[i] = deck[i];
	}
}

DevCards * devCards::getDeck()
{
	return pilon;
}

dice::dice(char dice1_, char dice2_):package(headers::DICE_ARE)
{
	if (dice1_ > 0 && dice1_ < 7)
		dice1 = dice1_;
	if (dice2_ > 0 && dice2_ < 7)
		dice2 = dice2_;
}

char dice::getValue(bool which)
{
	return which?dice1:dice2;
}

robberCards::robberCards(std::vector<DevCards>& descarte):package(headers::ROBBER_CARDS)
{
	length = descarte.size();
	cartas = descarte;
}

std::vector<DevCards> robberCards::getCards()
{
	return cartas;
}

char robberCards::getLength()
{
	return length;
}

robberMove::robberMove(char newPos):package(headers::ROBBER_MOVE)
{
	if (newPos >= 'A' &&  newPos <= 'S')
		pos = newPos;
}

char robberMove::getPos()
{
	return pos;
}

settlement::settlement(std::string pos_):package(headers::SETTLMENT)
{
	length = pos_.size();
	pos = pos_;
}

char settlement::getLength()
{
	return length;
}

std::string settlement::getPos()
{
	return pos;
}

city::city(std::string pos_):package(headers::CITY)
{
	length = pos_.length();
	pos = pos_;
}

road::road(std::string pos_):package(headers::ROAD)
{
	length = pos_.length();
	pos = pos_;
}

char road::getLength()
{
	return length;
}

std::string road::getPos()
{
	return pos;
}

banckTrade::banckTrade(std::vector<recursos>& myResouces, recursos _pedido):package(headers::BANK_TRADE)
{
	nOfResources = myResouces.size();
	misRecursos = myResouces;
	pedido = _pedido;
}

char banckTrade::getLength()
{
	return nOfResources;
}

std::vector<recursos> banckTrade::getResoucesPaid()
{
	return misRecursos;
}

recursos banckTrade::getResouceBougth()
{
	return pedido;
}

offerTrade::offerTrade(std::vector<recursos>& offer, std::vector<recursos>& pedido):package(headers::OFFER_TRADE)
{
	myOffer = offer;
	esperoAcambio = pedido;
}

std::vector<recursos> offerTrade::getMyOnes()
{
	return myOffer;
}

std::vector<recursos> offerTrade::getOponentOnes()
{
	return esperoAcambio;
}

knight::knight(char newPos):package(headers::KNIGHT)
{
	if (newPos >= 'A' && newPos <= 'S')
		pos = newPos;
}

char knight::getPos()
{
	return pos;
}

monopoly::monopoly(recursos recurso):package(headers::MONOPOLY)
{
	resource = recurso;
}

recursos monopoly::getResouce()
{
	return resource;
}

yearsOfPlenty::yearsOfPlenty(recursos rec1_, recursos rec2_):package(headers::YEARS_OF_PLENTY)
{
	rec1 = rec1_;
	rec2 = rec2_;
}
