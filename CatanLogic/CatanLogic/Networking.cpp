#include "Networking.h"
#include "package.h"
#include "subEvents.h"
#include <string>
#include <iostream>
#include <map>

#define MAX_SIZE 100

using namespace std;


Networking::Networking(const char * ip, unsigned short _port, Status _estado)
{
	ipOtherSide = string(ip);

	input.clear();
	
	estado = _estado;
	port = _port ;
	
	connected = false;

	ioHandler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*ioHandler);
	
	if (estado == SERVER)
	{
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port); // que tipo de ip uso con ese puerto (IPv4)
		serverAcceptor = new boost::asio::ip::tcp::acceptor(*ioHandler, ep); //el server puede empezar a escuchar
		clientResolver = nullptr;
		cout << "[SERVER] inicio\n";
	}
	else
	{
		clientResolver = new boost::asio::ip::tcp::resolver(*ioHandler);
		serverAcceptor = nullptr;
		cout << "[CLIENT] inicio\n";
	}


}

Networking::~Networking()
{
	if (estado == SERVER)
	{
		cout << "[SERVER] close\n";
		serverAcceptor->close();
		delete serverAcceptor;
	}
	else
	{
		cout << "[CLIENT] close\n";
		delete clientResolver;
	}
	socket->close();
	delete socket;
	delete ioHandler;
	
}

void Networking::setIpToConect(const char * _ip)
{
	ipOtherSide = _ip;
}

bool Networking::startConection()
{
	if (!connected)
	{
		if (estado == SERVER)
		{
			boost::system::error_code error;
			serverAcceptor->non_blocking(true);

			serverAcceptor->accept(*socket, error);
			
			if (!error)
			{
				connected = true;
				cout << "[SERVER] connected\n";
			}
		}
		else
		{
			boost::system::error_code error;
			boost::asio::ip::tcp::resolver::iterator endpoint;
			endpoint = clientResolver->resolve(boost::asio::ip::tcp::resolver::query(ipOtherSide, to_string(port)));

			boost::asio::connect(*socket, endpoint, error); // me intento conectar

			if (!error)
			{
				cout << "[CLIENT] connected\n";
				connected = true;
			}
		}
	}
	return connected;
}

void Networking::closeConection() // cierra la conexion y vuelve a ser cliente
{
	/***Tengo que cerrar y abrir otro socket*****/
	socket->close();
	delete socket;
	socket = new  boost::asio::ip::tcp::socket(*ioHandler);

	if (estado == SERVER)
	{
		cout << "[SERVER] close\n";
		serverAcceptor->close();
		delete serverAcceptor;
		serverAcceptor = nullptr; // ceirro el servre y abro un client nuevo
		clientResolver = new boost::asio::ip::tcp::resolver(*ioHandler);
		cout << "[CLIENT] init\n";
	}
	else
	{
		cout << "[CLIENT] close\n";
		delete clientResolver;
		clientResolver = new boost::asio::ip::tcp::resolver(*ioHandler); // cierro client y abro uno nuevo
		cout << "[CLIENT] init\n";
	}
	connected = false;
}

void Networking::workPlease()
{
	if (!(paraEnviar.empty()))
	{
		const char * msg = paraEnviar.front()->getPackage().c_str();
		cout << "Envio: " << msg << endl; //  en lugar de tener algo bloqueante podria tener algo con write_some para ver si pasa mucho tiempo y eso
		send(msg);
		paraEnviar.pop(); // lo saco de la cola
	}
	
	size_t len = 0,dataLength = socket->available();
	boost::system::error_code error;

	if (dataLength > 0)
	{
		char * buffer = new char[dataLength+1];

		do { 
			len = socket->read_some(boost::asio::buffer(buffer, dataLength), error);
		} while (error.value() == WSAEWOULDBLOCK && len < dataLength );
		
		if (error)
		{
			//tiro evento de error
		}
		else
		{
			buffer[dataLength] = '\0';
			cout << "Recibi: " << buffer << endl;
			parseInput(buffer);
		}
		delete []buffer;
	}
}

void Networking::parseInput(const char * mensaje) // aca parseo 
{
	input.append(mensaje);
	bool complete = true; //asumo que el paquete llego completo

	headers name = static_cast<headers>(input[0]);
	
	SubEvents * evento = new SubEvents;
	evento->setEvent(MainTypes::NETWORK);

	switch (name) //no es prolijo pero eficiente
	{
	case headers::ACK: 
		evento->setSubtype(SubType::NET_ACK);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::NAME:
		evento->setSubtype(SubType::NET_NAME);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::NAME_IS:
		evento->setSubtype(SubType::NET_NAME_IS);
		if ((input.length() >= 2) && ((input[1] + 2) <= input.length()) )//si esta completo el paquete name_is
		{
			evento->addPackage(new nameIs(input.substr(2, input[1])));
			input.erase(0, input[1]+2);  
		}
		else
			complete = false;
		break;
	case headers::MAP_IS:
		evento->setSubtype(SubType::NET_NAME_IS);
		if (input.length() >= 26)
		{
			evento->addPackage(new mapIs(input.substr(1, 25).c_str()));
			input.erase(0, 26);
		}
		else
			complete = false;
		break;
	case headers::CIRCULAR_TOKENS:
		evento->setSubtype(SubType::NET_CIRCULAR_TOKENS);
		if (input.length() >= 20)
		{
			evento->addPackage(new circularTokens(input.substr(1, 19).c_str()));
			input.erase(0, 20);
		}
		else
			complete = false;
		break;
	case headers::PLAY_WITH_DEV:
		evento->setSubtype(SubType::NET_PLAY_WITH_DEV);
		evento->addPackage(new package(name));
		input.erase(0, 1);
		break;
	case headers::DEV_CARDS:
		evento->setSubtype(SubType::NET_DEV_CARDS);
		if (input.length() >= 26)
		{
			evento->addPackage(new devCards(input.substr(1, 25).c_str()));
			input.erase(0, 26);
		}
		else
			complete = false;
		break;
	case headers::YOU_START:
		evento->setSubtype(SubType::NET_YOU_START);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::I_START:
		evento->setSubtype(SubType::NET_I_START);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::DICE_ARE:
		evento->setSubtype(SubType::NET_DICES_ARE);
		if (input.length() >= 4)
		{
			evento->addPackage(new dice(input[2],input[3]));
			input.erase(0, 4);
		}
		else
			complete = false;
		break;
	case headers::ROBBER_CARDS:
		evento->setSubtype(SubType::NET_ROBBER_CARDS);
		if ((input.length() >= 2) && (input.length() >= (input[1]+2)) )
		{
			evento->addPackage(new robberCards(input.substr(2,input[1]).c_str()));
			input.erase(0, input[1]+2);
		}
		else
			complete = false;
		break;
	case headers::CARD_IS:
		evento->setSubtype(SubType::NET_CARD_IS);
		if (input.length() >= 26)
		{
			evento->addPackage(new mapIs(input.substr(1, 25).c_str()));
			input.erase(0, 26);
		}
		else
			complete = false;
		break;
	case headers::ROBBER_MOVE:
		evento->setSubtype(SubType::NET_ROBBER_MOVE);
		if (input.length() >= 2)
		{
			evento->addPackage(new robberMove(input[1]));
			input.erase(0, 2);
		}
		else
			complete = false;
		break;
	case headers::SETTLMENT:
		evento->setSubtype(SubType::NET_SETTLEMENT);
		if ((input.length() >= 2) && (input.length() >= input[1]-'0'+2 ))
		{
			evento->addPackage(new settlement(input.substr(2,input[1]-'0').c_str()));
			input.erase(0, input[1]-'0');
		}
		else
			complete = false;
		break;
	case headers::ROAD:
		evento->setSubtype(SubType::NET_ROAD);
		if ((input.length() >= 2) && (input.length() >= input[1] - '0' + 2))
		{
			evento->addPackage(new road(input.substr(2, input[1] - '0').c_str()));
			input.erase(0, input[1] - '0');
		}
		else
			complete = false;
		break;
	case headers::CITY:
		evento->setSubtype(SubType::NET_CITY);
		if ((input.length() >= 2) && (input.length() >= input[1] - '0' + 2))
		{
			evento->addPackage(new city(input.substr(2, input[1] - '0').c_str()));
			input.erase(0, input[1] - '0');
		}
		else
			complete = false;
		break;
	case headers::BANK_TRADE:
		evento->setSubtype(SubType::NET_BANK_TRADE);
		if ((input.length() >= 2)&& (input.length() >= input[1]-'0'+3))
		{
			std::vector<recursos> temp;
			for (char a : input.substr(2, input[1] - '0')) { temp.push_back(static_cast<recursos>(a)); }
			evento->addPackage(new banckTrade(temp, static_cast<recursos>(input[input[1] - '0' + 3])));
			input.erase(0, input[1]-'0'+3);
		}
		else
			complete = false;
		break;
	case headers::OFFER_TRADE:
		evento->setSubtype(SubType::NET_OFFER_TRADE);
		if ((input.length() >= 3)&&(input.length() >= (input[1]-'0'+input[2]-'0'+3)) ) 
		{
			std::vector<recursos> temp1,temp2;
			for (char a : input.substr(3, input[1] - '0')) { temp1.push_back(static_cast<recursos>(a)); }
			for(char a : input.substr(3+input[1]-'0',input[2]-'0')){temp2.push_back(static_cast<recursos>(a));}
			evento->addPackage(new offerTrade(temp1,temp2));
			input.erase(0, input[1]+input[2]-'0'-'0'+3);
		}
		else
			complete = false;
		break;
	case headers::PASS:
		evento->setSubtype(SubType::NET_PASS);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::DEV_CARD:
		evento->setSubtype(SubType::NET_DEV_CARD);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::MONOPOLY:
		evento->setSubtype(SubType::NET_MONOPOLY);
		if (input.length() >= 2)
		{
			evento->addPackage(new monopoly(static_cast<recursos>(input[1])));
			input.erase(0, 2);
		}
		else
			complete = false;
		break;
	case headers::YEARS_OF_PLENTY:
		evento->setSubtype(SubType::NET_DEV_CARDS);
		if (input.length() >= 3)
		{
			evento->addPackage(new yearsOfPlenty(static_cast<recursos>(input[1]), static_cast<recursos>(input[2])) );
			input.erase(0, 3);
		}
		else
			complete = false;
		break;
	case headers::ROAD_BUILDING:
		evento->setSubtype(SubType::NET_ROAD_BUILDING);
		evento->addPackage(new package(name));
		input.erase(0, 1);
		break;
	case headers::KNIGHT:
		evento->setSubtype(SubType::NET_KNIGHT);
		if (input.length() >= 2)
		{
			evento->addPackage(new knight(input[1]));
			input.erase(0, 2);
		}
		else
			complete = false;
		break;
	case headers::YES:
		evento->setSubtype(SubType::NET_YES);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::NO:
		evento->setSubtype(SubType::NET_NO);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::I_WON:
		evento->setSubtype(SubType::NET_I_WON);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::PLAY_AGAIN:
		evento->setEvent(MainTypes::PLAY_AGAIN);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::GAME_OVER:
		evento->setEvent(MainTypes::GAME_OVER);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::QUIT:
		evento->setSubtype(SubType::NET_QUIT);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	case headers::ERROR_:
		evento->setEvent(MainTypes::ERR_IN_COM);
		evento->addPackage(new package(name));
		input.erase(0, 1); //saco el primer caracter 
		break;
	}
}

void Networking::pushPackage(package * mensaje)
{
	paraEnviar.push(mensaje); 
}

bool Networking::hayMensaje() // para ver que funcione!!!
{
	bool ret = false;
	if (!input.empty()) // si tengo algun mensaje lo saco 
 	{
		ret = true;
		input.clear();
	}
	return ret;
}

Status Networking::getStatus()
{
	return estado;
}

void Networking::setStatus(Status newSt)
{
	if (newSt != estado) // me fijo que quiera cambiar de estado
	{
		/***Tengo que cerrar y abrir otro socket*****/
		socket->close(); 
		delete socket;
		socket = new  boost::asio::ip::tcp::socket(*ioHandler);
		
		estado = newSt;
		/**Priero cierro las cosas del estado anterior ***/
		/**** y luego abro lo del nuevo estado ***/
		if (estado == CLIENT) // si quiero pasar a cliente cierro las cosas de server
		{
			cout << "[SERVER] close\n";
			serverAcceptor->close();
			delete serverAcceptor;
			serverAcceptor = nullptr;
			clientResolver = new boost::asio::ip::tcp::resolver(*ioHandler);
			cout << "[CLIENT] init\n";
		}
		else
		{
			cout << "[CLIENT] close\n";
			delete clientResolver;
			clientResolver = nullptr;
			boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port); // que tipo de ip uso con ese puerto (IPv4)
			serverAcceptor = new boost::asio::ip::tcp::acceptor(*ioHandler, ep); //el server puede empezar a escuchar
			cout << "[SERVER] init\n";
		}
	}
}

void Networking::toggleStatus(void)
{
	/***Tengo que cerrar y abrir otro socket*****/
	socket->close();
	delete socket;
	socket = new  boost::asio::ip::tcp::socket(*ioHandler);

	/**Priero cierro las cosas del estado anterior ***/
	/**** y luego abro lo del nuevo estado ***/
	
	if (estado == SERVER) // si quiero pasar a cliente cierro las cosas de server
	{
		cout << "[SERVER] close\n";
		serverAcceptor->close();
		delete serverAcceptor;
		serverAcceptor = nullptr;
		clientResolver = new boost::asio::ip::tcp::resolver(*ioHandler);
		cout << "[CLIENT] init\n";
		estado = CLIENT;
	}
	else
	{
		cout << "[CLIENT] close\n";
		delete clientResolver;
		clientResolver = nullptr;
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port); // que tipo de ip uso con ese puerto (IPv4)
		serverAcceptor = new boost::asio::ip::tcp::acceptor(*ioHandler, ep); //el server puede empezar a escuchar
		cout << "[SERVER] init\n";
		estado = SERVER;
	}
}

bool Networking::send(const char* msg) {

	boost::system::error_code error; /* Creo receptor de errores */
	size_t dataCount;

	do { /* Mando la informacion de a partes */
		/* Mando la data */
		dataCount = socket->write_some(boost::asio::buffer(msg, strlen(msg)), error);
	} while (error.value() == WSAEWOULDBLOCK && dataCount < strlen(msg));

	/* Verifico el error */
	if (error)
	{ // deberia generar evento de error a la fsm gral
		return false;
	}
	else
	{
		return true;
	}
} 