#pragma once
#include <string>
#include <vector>
#include "CatanDefs.h"
#include "Board.h"

class package
{
public:
	package();
	package(headers paquete);
	~package();
	headers getPacket();
	virtual std::string getPackage();
protected:
	headers nombre;
};

class NameIsPkg :
	public package
{
public:
	NameIsPkg(std::string name_);
	std::string getName();
	virtual std::string getPackage();
private:
	char length;
	std::string name;
};

class MapIsPkg :
	public package
{
public:
	MapIsPkg(Board * board_);
	MapIsPkg(const char * mapa);
	MapIsPkg(std::vector<PortType>& agua_, std::vector<ResourceType>& piezas);
	char * getMap(); // todava no se en que formato devolverlo (pensar...)
	virtual std::string getPackage();
	Board * getBoard();
private:
	PortType agua[6];
	ResourceType tablero[19];
	char all[25];
	Board * board;

	const vector<string> utiles = // los vertices exteriores en sentido horario
	{
		"05A","0A","0AB","0B","0BC","01C",
		"1C","1CG","1G","1GL","12L",
		"2L","2LP","2P","2PS","23S",
		"3S" ,"3RS","3R","3QR","34Q",
		"4Q","4MQ","4M" ,"4HM","45H",
		"5H","5DH","5D","5AD"
	};
};

class CircularTokensPkg :
	public package
{
public:
	CircularTokensPkg(Board * tablero);
	CircularTokensPkg(const char * tokns);
	CircularTokensPkg(std::vector<char>& tokenList);
	char * getTokenList();
	virtual std::string getPackage();
private:
	char myTokens[19];
};

class DevCardsPkg :
	public package
{
public:
	DevCardsPkg(stack< DevCards > pilaDeCartas);
	DevCardsPkg(const char * deck);
	DevCardsPkg(std::vector<DevCards>& deck);
	stack< DevCards > getDeck();
	virtual std::string getPackage();
private:
	DevCards pilon[25];
};

class DicePkg :
	public package
{
public:
	DicePkg(char dice1_, char dice2_);
	char getValue(bool which); // con true devuelvo uno y con false el otro dado
	virtual std::string getPackage();
private:
	char dice1;
	char dice2;
};

class RobberCardsPkg :
	public package
{
public:
	RobberCardsPkg(char length);
	RobberCardsPkg(const char * devList);
	RobberCardsPkg(std::vector<ResourceType> descarte);
	std::vector<ResourceType> getCards();
	char getLength();
	virtual std::string getPackage();
	char getAmountOf(ResourceType recurso);

	bool isComplete();
	void pushCard(ResourceType recurso);
private:
	char length;
	std::vector<ResourceType> cartas;
};

class RobberMovePkg :
	public package
{
public:
	RobberMovePkg(char newPos);
	char getPos();
	virtual std::string getPackage();
private:
	char pos;
};

class SettlementPkg :
	public package
{
public:
	SettlementPkg(std::string pos_);
	char getLength();
	std::string getPos();
	virtual std::string getPackage();
private:
	char length;
	std::string pos;
};

class CityPkg :
	public package
{
public:
	CityPkg(std::string pos_);
	char getLength();
	std::string getPos();
	virtual std::string getPackage();
private:
	char length;
	std::string pos;

};
class RoadPkg :
	public package
{
public:
	RoadPkg(std::string pos_);
	char getLength();
	std::string getPos();
	virtual std::string getPackage();
private:
	char length;
	std::string pos;
};

class BankTradePkg :
	public package
{
public:
	BankTradePkg();
	BankTradePkg(std::vector<ResourceType>& myResouces, ResourceType pedido);
	BankTradePkg(BankTradePkg * copiar);
	char getLength();//devuelve la cantidad de ResourceType pagados
	std::vector<ResourceType> getResoucesPaid();
	ResourceType getResouceBougth();
	
	void setType(char num);
	void setPaid(std::vector<ResourceType>& myResources);
	void setBougth(ResourceType pedido);
	void closeOffer();

	virtual std::string getPackage();
	bool isComplete();
	bool offerclosed();
private:
	char nOfResources;
	std::vector<ResourceType> misRecursos;
	ResourceType pedido;
	bool offer;
};

class OfferTradePkg :
	public package
{
public:
	OfferTradePkg();
	OfferTradePkg(std::vector<ResourceType>& offer_, std::vector<ResourceType>& pedido);
	OfferTradePkg(OfferTradePkg * copiar);
	std::vector<ResourceType> getMyOnes();
	std::vector<ResourceType> getOpponentOnes();

	char getMyOnes(ResourceType recurso);
	char getOpponent(ResourceType recurso);

	void addToMyOffer(ResourceType offer);
	void closeOffer();
	void addToMyRequest(ResourceType pedido);

	virtual std::string getPackage();
	bool isComplete();
	bool offerclosed();
private:
	std::vector<ResourceType> myOffer;
	std::vector<ResourceType> esperoAcambio;
	bool offer;

};
class KnightPkg :
	public package
{
public:
	KnightPkg(char newPos);
	char getPos();
	virtual std::string getPackage();
private:
	char pos;
};

class MonopolyPkg :
	public package
{
public:
	MonopolyPkg();
	MonopolyPkg(ResourceType recurso);
	ResourceType getResource();
	virtual std::string getPackage();

	void setResource(ResourceType rec);
private:
	ResourceType resource;
};

class YearsOfPlentyPkg :
	public package
{
public:
	YearsOfPlentyPkg();
	YearsOfPlentyPkg(ResourceType rec1_, ResourceType rec2_);
	virtual std::string getPackage();
	ResourceType getResource(bool cual); // true es el 1 y false el 2

	void setResource(bool cual, ResourceType recurso);
private:
	ResourceType rec1;
	ResourceType rec2;
};

class CardIsPkg :
	public package
{
public:
	CardIsPkg(char resource);
	ResourceType getResource();
	virtual std::string getPackage();
private:
	ResourceType recurso;
};