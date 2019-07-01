#include<iostream>
#include<vector>
#include"Board.h"
#include"Player.h"
#include"RemotePlayerEnabler.h"
#include"LocalPlayerEnabler.h"
#include"BasicGUI.h"
#include"Networking.h"
#include"MainFSM.h"
#include"HandShakingFSM.h"
#include"Button.h"
#include"NewEventHandling.h"
#include"AllegroGUI.h"
#include "PosDef.h"
#include "PlayersObserver.h"
#include "BoardController.h"
#include "GutenbergsPressAllegro.h"
#include "SubEvents.h"
#include "DetailsObserver.h"
#include "TimerController.h"
#include "parseCmd.h"


#define NAME 1
#define IP 2
#define MIN_OPT 2

typedef class
{
public:
	std::string localPlayerName;
	std::string remotePlayerIP;
	std::string  error;
}UserData;

int is_known(const char *key, const char *knownOpt[], int size);
int strcicmp(char const *a, char const *b);
int parseCallback(char *key, char *value, void *userData);
void instructions(std::string error);

void createButtons(GutenbergsPressAllegro* printer, EventsHandler * evH,Player * jugador, MainFSM* mainFSM, AllegroGUI* GUI, Board * tablero, std::vector<Button*> &buttonList, RemotePlayerEnabler * remEneb, LocalPlayerEnabler * locEneb, Networking * networ);


int main(int argc, char* argv[])
{
	UserData userData;
	if (parseCmdLine(argc, argv, parseCallback, &userData) != MIN_OPT )
	{
		instructions(userData.error);
	}
	else
	{
		Player localPlayer(userData.localPlayerName);
		Player remotePlayer;
		Board globalBoard;
		EventsHandler handler;
		Networking network(&handler, userData.remotePlayerIP.c_str());
		RemotePlayerEnabler remotePlayerEnabler(&network, &handler);
		LocalPlayerEnabler localPlayerEnabler(&network, &remotePlayerEnabler, &handler, &localPlayer, &remotePlayer);
		HandShakingFSM hsFSM(&network, userData.localPlayerName, &globalBoard, &handler);
		MainFSM mainFSM(&hsFSM, &network, &handler, &localPlayerEnabler, &remotePlayerEnabler, &globalBoard);
		AllegroGUI GUI;
		GutenbergsPressAllegro printer(NULL);
		BoardController boardCont(&handler, &printer, &mainFSM, &globalBoard, &localPlayerEnabler);
		TimerController timerCont(&handler);

		std::vector<Button*> buttonList;
		createButtons(&printer, &handler, &localPlayer, &mainFSM, &GUI, &globalBoard, buttonList, &remotePlayerEnabler, &localPlayerEnabler, &network);	// Also adds them to the GUI.
		GUI.attachController("BoardController", &boardCont);
		GUI.attachController("TimerController", &timerCont);
		GUI.initGUIEnabler();

		DetailsObserver observerFSM(&mainFSM, &printer);
		PlayersObserver localObs(&printer, &localPlayer, &remotePlayer, &localPlayerEnabler, &remotePlayerEnabler, &mainFSM);

		localPlayer.attach(&localObs);
		localPlayer.attach(&boardCont);													// localObs and boardCont are observers of localPlayer.
		remotePlayer.attach(&localObs);
		remotePlayer.attach(&boardCont);												// localObs and boardCont are observers of remotePlayer.
		globalBoard.attach(&localObs);
		globalBoard.attach(&boardCont);													// localObs and boardCont are observers of globalBoard.
		remotePlayerEnabler.attach(&localObs);
		remotePlayerEnabler.attach(&boardCont);											// localObs and boardCont are observers of remotePlayerEnabler.
		localPlayerEnabler.attach(&localObs);
		localPlayerEnabler.attach(&boardCont);											// localObs and boardCont are observers of localPlayerEnabler.
		mainFSM.attach(&localObs);
		mainFSM.attach(&boardCont);														// localObs and boardCont are observers of mainFSM.
		mainFSM.attach(&observerFSM);

		mainFSM.notifyAllObservers();

		while (!mainFSM.isQuit() && !GUI.displayWasClosed())
		{
			GUI.cycle();
			network.workPlease();
			if (handler.isEvent())
			{
				GenericEvent* ev = handler.getNextEvent();
				mainFSM.cycle(ev);
				delete ev;
			}
		}
	}
}


int parseCallback(char *key, char *value, void *userData)
{
	UserData *p2Class = (UserData*)userData;//casteo del puntero a clase
	const char *knownOptions[] = { "name","ip"};
	int receivedOpt;
	int returnValue;
	if (key != NULL)
	{
		if ((receivedOpt = is_known(key, knownOptions, sizeof(knownOptions) / sizeof(knownOptions[1]))) != 0)// si key coincide con conocido le asigno su valor
		{
			switch (receivedOpt)
			{
			case NAME:
				p2Class->localPlayerName = (std::string)value;
				returnValue = true;
				break;
			case IP:
				p2Class->remotePlayerIP = (std::string)value;
				returnValue = true;
				break;
			
			default:
				p2Class->error = "don't know what happened (LOL)\n";
				returnValue = false;
				break;

			}
		}
		else
		{
			
			p2Class->error = "Una de las opciones ingresadas no es valida\n";
			returnValue = false;
		}
	}
	else
	{
		p2Class->error = "Se ingreso un parametro, por favor solo ingrese opciones\n";
		returnValue = false;
	}
	return returnValue;
}

int is_known(const char *key, const char *knownOpt[], int size)
{
	int i;
	int ready = 0;
	for (i = 0; i < size && !ready; i++)
	{
		if (!strcicmp(key, knownOpt[i]))
		{
			ready = 1;
		}

	}
	return ready ? i - 1 : 0;
}

int strcicmp(char const *a, char const *b)
{
	for (;; a++, b++)
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
		{
			return d;
		}
	}
}

void instructions(std::string error)
{

	cout << "FATAL ERROR!!!\n\n";
	cout << error;

	/*cambiar esto para las instrucciones de este programa*//*
	printf("Recuerde que las opciones validas son:\n");
	printf("1) -type:UNIFORME, POLIGONO o MANDELBROT\n2) -lStart: un valor entre 0 y 100\n3) -lEnd: un valor entre 0 y 100\n4) -lConstant: un valor entre 0 y 1\n");
	printf("5) -leftAngle y -rightAngle: un valor entre -90 y 0 y entre 0 y 90 respectivamente \n6) -n: un valor mayor o igual que 3\n7) -x0,-y0,-xf,-yf: valores numericos para el radio en mandelbrot\n");
	printf("Todos los valores numericos excepto n pueden tomar valores flotantes, esto se debera indicar con '.' y no con ',' /n ");
	printf("Las opciones utilizadas para cada deberan ser precisamente las que cada dibujador necesita, estas seran especificadas en los ejemplos a continuacion \n");
	printf("-type uniforme -lStart 60.4 -lEnd 3.45 -leftAngle 50 -rightAngle 60\n");
	printf("-type poligono -lstart 100 -lEnd 10 -lConstant 0.4 -n 8\n");
	printf("-type MANDELBROT -x0 -0 -y0 -0 -yf 2 -xf 2\n");
	printf("Todas las opciones son case insensitive, es decir que LcONstaNT es igual de valido que lconstant, por ejemplo\n");
	printf("Presione Enter para salir\n");
	*/
	getchar();
}


