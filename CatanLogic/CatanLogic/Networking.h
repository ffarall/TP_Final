#pragma once

#include <string>
#include <queue>
#include <list>

#include "package.h"
#include "NewEventHandling.h"

enum Status { SERVER, CLIENT };
enum Activity { NOTHING, CONNECTING, WORKING };
#define PORT 13225

#include "boost/asio.hpp"

class Networking : 
	public EventGenerator
{
public:
	Networking(EventsHandler* handler_, const char * _ip = "" , unsigned short _port=PORT , Status _estado = CLIENT); // por defecto arranca como client
	~Networking();

	void setIpToConect(const char * _ip);
	void startConection(); // intenta conectarse,cuando se conecta genera evento de connected
	void closeConection(); // por si me interesa cerrar la conexion
	
	void workPlease();// manda mensajes si hay algo que enviar y recibe mesages + genera eventos

	void pushPackage(package * mensaje);
	
	bool hayMensaje(); // solo de prueba para que hablen

	Status getStatus(); // sobre SERVER-CLIENT
	void setStatus(Status newSt);
	void toggleStatus(void);

private:

	void send(const char * msg_);

	void parseInput(const char * mensaje, size_t length_);
	
	Status estado; //Si funciona como server o como client
	Activity current;
	bool connected;

	std::string ipOtherSide;

	boost::asio::io_service * ioHandler;
	boost::asio::ip::tcp::socket* socket;

	boost::asio::ip::tcp::acceptor* serverAcceptor; //por si trabajo como server o como client
	boost::asio::ip::tcp::resolver* clientResolver;
	
	std::string input;


	std::queue<package *> paraEnviar; // lista de colas de mensajes para enviar
	
	unsigned short port;
};

