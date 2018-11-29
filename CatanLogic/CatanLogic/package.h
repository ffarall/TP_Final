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

class nameIs :
	public package
{
public:
	nameIs(std::string name_);
	std::string getName();
	virtual std::string getPackage();
private:
	char length;
	std::string name;
};

class mapIs :
	public package
{
public:
	mapIs(const char * mapa);
	mapIs(std::vector<mar>& agua_, std::vector<recursos>& piezas);
	char * getMap(); // todava no se en que formato devolverlo (pensar...)
	virtual std::string getPackage();
private:
	mar agua[6];
	recursos tablero[19];
	char all[25];
};

class circularTokens :
	public package
{
public:
	circularTokens(std::vector<char>& tokenList);
	char * getTokenList();
	virtual std::string getPackage();
private:
	char myTokens[19];
};

class devCards :
	public package
{
public:
	devCards(const char * deck);
	devCards(std::vector<DevCards>& deck);
	DevCards * getDeck();
	virtual std::string getPackage();
private:
	DevCards pilon[25];
};

class dice :
	public package
{
public:
	dice(char dice1_, char dice2_);
	char getValue(bool which); // con true devuelvo uno y con false el otro dado
	virtual std::string getPackage();
private:
	char dice1;
	char dice2;
};

class robberCards :
	public package
{
public:
	robberCards(const char * devList);
	robberCards(std::vector<DevCards>& descarte);
	std::vector<DevCards> getCards();
	char getLength();
	virtual std::string getPackage();
private:
	char length;
	std::vector<DevCards> cartas;
};

class robberMove :
	public package
{
public:
	robberMove(char newPos);
	char getPos();
	virtual std::string getPackage();
private:
	char pos;
};

class settlement :
	public package
{
public:
	settlement(std::string pos_);
	char getLength();
	std::string getPos();
	virtual std::string getPackage();
private:
	char length;
	std::string pos;
};

class city :
	public package
{
public:
	city(std::string pos_);
	char getLength();
	std::string getPos();
	virtual std::string getPackage();
private:
	char length;
	std::string pos;

};
class road :
	public package
{
public:
	road(std::string pos_);
	char getLength();
	std::string getPos();
	virtual std::string getPackage();
private:
	char length;
	std::string pos;
};

class banckTrade :
	public package
{
public:
	banckTrade(std::vector<recursos>& myResouces, recursos pedido);
	char getLength();//devuelve la cantidad de recursos pagados
	std::vector<recursos> getResoucesPaid();
	recursos getResouceBougth();
	virtual std::string getPackage();
private:
	char nOfResources;
	std::vector<recursos> misRecursos;
	recursos pedido;
};

class offerTrade :
	public package
{
public:
	offerTrade(std::vector<recursos>& offer, std::vector<recursos>& pedido);
	std::vector<recursos> getMyOnes();
	std::vector<recursos> getOponentOnes();
	virtual std::string getPackage();
private:
	std::vector<recursos> myOffer;
	std::vector<recursos> esperoAcambio;
};
class knight :
	public package
{
public:
	knight(char newPos);
	char getPos();
	virtual std::string getPackage();
private:
	char pos;
};

class monopoly :
	public package
{
public:
	monopoly(recursos recurso);
	recursos getResouce();
	virtual std::string getPackage();
private:
	recursos resource;
};

class yearsOfPlenty :
	public package
{
public:
	yearsOfPlenty(recursos rec1_, recursos rec2_);
	virtual std::string getPackage();
private:
	recursos rec1;
	recursos rec2;
};

class cardIs :
	public package
{
public:
	cardIs(char resource);
	virtual std::string getPackage();
private:
	recursos recurso;
};