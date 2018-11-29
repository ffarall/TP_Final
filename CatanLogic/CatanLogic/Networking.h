#pragma once

#include "boost/asio.hpp"
#include "boost/chrono.hpp"
#include "boost/timer/timer.hpp"
#include <string>
#include <queue>
#include <list>

#define PORT 13225

enum Status {SERVER,CLIENT};

class Networking
{
public:
	Networking(const char * _ip = "" , unsigned short _port=PORT , Status _estado = CLIENT); // por defecto arranca como client
	~Networking();

	void setIpToConect(const char * _ip);
	bool startConection(); // intenta conectarse, si no puede devuelve false;
	void closeConection(); // por si me interesa cerrar la conexion
	
	void workPlease();// manda mensajes si hay algo que enviar y recibe mesages + genera eventos

	void pushPackage(package * mensaje);
	
	bool hayMensaje(); // solo de prueba para que hablen

	Status getStatus(); // sobre SERVER-CLIENT
	void setStatus(Status newSt);
	void toggleStatus(void);

private:

	bool send(const char * msg_);

	void parseInput(const char * mensaje);
	
	Status estado; //Si funciona como server o como client
	bool connected;

	std::string ipOtherSide;

	boost::asio::io_service* ioHandler;
	boost::asio::ip::tcp::socket* socket;

	boost::asio::ip::tcp::acceptor* serverAcceptor; //por si trabajo como server o como client
	boost::asio::ip::tcp::resolver* clientResolver;
	
	std::string input;


	std::queue<package *> paraEnviar; // lista de colas de mensajes para enviar
	
	unsigned short port;
};

