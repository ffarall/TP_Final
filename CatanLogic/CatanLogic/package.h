#pragma once
#include <string>
#include <vector>
#include "CatanDefs.h"

class package
{
public:
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
	MapIsPkg(const char * mapa);
	MapIsPkg(std::vector<SeaType>& agua_, std::vector<ResourceType>& piezas);
	char * getMap(); // todava no se en que formato devolverlo (pensar...)
	virtual std::string getPackage();
private:
	SeaType agua[6];
	ResourceType tablero[19];
	char all[25];
};

class CircularTokensPkg :
	public package
{
public:
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
	DevCardsPkg(const char * deck);
	DevCardsPkg(std::vector<DevCards>& deck);
	DevCards * getDeck();
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
	RobberCardsPkg(const char * devList);
	RobberCardsPkg(std::vector<DevCards>& descarte);
	std::vector<DevCards> getCards();
	char getLength();
	virtual std::string getPackage();
private:
	char length;
	std::vector<DevCards> cartas;
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

class BanckTradePkg :
	public package
{
public:
	BanckTradePkg(std::vector<ResourceType>& myResouces, ResourceType pedido);
	char getLength();//devuelve la cantidad de ResourceType pagados
	std::vector<ResourceType> getResoucesPaid();
	ResourceType getResouceBougth();
	virtual std::string getPackage();
private:
	char nOfResources;
	std::vector<ResourceType> misRecursos;
	ResourceType pedido;
};

class OfferTradePkg :
	public package
{
public:
	OfferTradePkg(std::vector<ResourceType>& offer, std::vector<ResourceType>& pedido);
	std::vector<ResourceType> getMyOnes();
	std::vector<ResourceType> getOponentOnes();
	virtual std::string getPackage();
private:
	std::vector<ResourceType> myOffer;
	std::vector<ResourceType> esperoAcambio;
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
	MonopolyPkg(ResourceType recurso);
	ResourceType getResouce();
	virtual std::string getPackage();
private:
	ResourceType resource;
};

class YearsOfPlentyPkg :
	public package
{
public:
	YearsOfPlentyPkg(ResourceType rec1_, ResourceType rec2_);
	virtual std::string getPackage();
private:
	ResourceType rec1;
	ResourceType rec2;
};

class CardIsPkg :
	public package
{
public:
	CardIsPkg(char resource);
	virtual std::string getPackage();
private:
	ResourceType recurso;
};