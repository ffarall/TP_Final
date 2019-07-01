#include "parseCmd.h"

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData)
{
	int i;
	int error = 0;
	int repeatcounter = 0;    //cuenta las veces que se recibe una opcion o argumento valido
	char *key;
	char *value;
	for (i = 1; i < argc && !error && argv[i] != NULL; i++, repeatcounter++)
	{
		if (*argv[i] == '-' && argv[i + 1] != NULL)      // si es un key y no es el ultimo string recibido (lo que implica que no tiene value)
		{

			key = argv[i] + 1;
			value = argv[++i];
			if (!p(key, value, userData))
			{
				error = 1;
			}
		}

		else if (*argv[i] != '-')
		{
			value = argv[i];
			if (!p(NULL, value, userData))
			{
				error = 1;
			}
		}

		else    //si no es ninguno de los casos anteriores entonces hubo un error
		{
			error = 1;
		}


	}
	return error ? -1 : repeatcounter;
}