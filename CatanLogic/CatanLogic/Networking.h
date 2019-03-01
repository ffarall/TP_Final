#pragma once

#include <string>
#include <queue>
#include <list>

#include "package.h"
#include "NewEventHandling.h"
#include "BasicGUI.h"
#include "GUIEnabler.h"

#include <chrono>

enum Status { SERVER, CLIENT };
enum Activity { NOTHING, CONNECTING, WORKING };
#define PORT 13225

#include "boost/asio.hpp"

typedef std::function<GUIEnablerEvent(void)> TimeAction;

class Networking : 
	public BasicController
{
public:
	Networking(EventsHandler* handler_, const char * _ip = "" , unsigned short _port=PORT , Status _estado = CLIENT); // por defecto arranca como client
	~Networking();
	
	virtual GUIEnablerEvent parseMouseDownEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseMouseUpEvent(uint32_t x, uint32_t y);
	virtual GUIEnablerEvent parseTimerEvent();
	virtual GUIEnablerEvent parseCloseWindow();

	virtual void update();


	void setIpToConect(const char * _ip);
	void startConection(); // intenta conectarse,cuando se conecta genera evento de connected
	void closeConection(); // por si me interesa cerrar la conexion
	
	void workPlease();// manda mensajes si hay algo que enviar y recibe mesages + genera eventos

	void pushPackage(package * mensaje);
	
	bool hayMensaje(); // solo de prueba para que hablen

	Status getStatus(); // sobre SERVER-CLIENT
	void setStatus(Status newSt);
	void toggleStatus(void);

	void setControllerRoutine(const TimeAction & callback_);
private:

	TimeAction callback;

	void send(const char * msg_, int largo);

	void parseInput(const char * mensaje, size_t length_);
	std::string msgDecoder(char* msg);
	
	Status estado; //Si funciona como server o como client
	Activity current;
	bool connected;

	std::string ipOtherSide;

	boost::asio::io_service * ioHandler;
	boost::asio::ip::tcp::socket* socket;

	boost::asio::ip::tcp::acceptor* serverAcceptor; //por si trabajo como server o como client
	boost::asio::ip::tcp::resolver* clientResolver;
	
	std::string input;

	std::chrono::high_resolution_clock::time_point timeout;

	std::queue<package *> paraEnviar; // lista de colas de mensajes para enviar
	
	unsigned short port;
	GUIEnablerEvent robber;
};

