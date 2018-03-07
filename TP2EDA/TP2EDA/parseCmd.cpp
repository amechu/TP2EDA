#include "parseCmd.h"
#include <string.h>
#include <fwpstypes.h>
#include <stdio.h>

int parseCmdLine(int argc, char *argv[], pCallback p, void *parseData) {
	int final = 0, posible = 0, error = false;

	for (int i = 1; i<argc; ) {
		if (argv[i][0] == '-') { //Si el primer caracter es un - sera una opcion (opcion es clave+valor)
			if (argv[i][1] == 0) //si pasan - solo
			{
				error = ERROR2;
				i = argc;
			}
			else if ((i + 1) >= argc)
			{
				error = ERROR1; //si es el ultimo caracter obviamente no tiene valor
				i++;
			}

			else
			{
				posible = p(&(argv[i][1]), argv[i + 1], parseData);
				if (posible >= 0) {
					i += 2; //avanzo 2 parametros
				}
				else {
					error = ERROR3;
					i = argc;
				}
			}
		}
		else {
			posible = p(NULL, argv[i], parseData); //si no es opcion es parametro
			if (posible >= 0) {
				i++;
			}
			else {
				error = ERROR3;
				i = argc;
			}
		}
	}
	if (error == ERROR1)
		final = ERROR1;
	else if (error == ERROR2)// reconoce el error
		final = ERROR2;
	else if (error == ERROR3)
		final = ERROR3;
	else
		final = 0;

	return final;

}

int parseCallback(char *key, char *value, void *userinfo)
{
	int i = 0, equal = -1;
	char * ke = key;
	char * val = value;
	bool setsType;

	if (key == NULL)
	{
		while (val[i]) //Case insensitive
		{
			val[i] = toupper(val[i]);
			i++;
		}

		for (i = 0; i < NPARAMETERS; i++) //Busca parametro conocido
		{
			equal = strcmp(val, ((parseData*)userinfo)->parameters[i]);
			if (equal == 0)
				i = NPARAMETERS;
		}
	}
	else
	{

		while (key[i]) //Case insensitive
		{
			ke[i] = toupper(ke[i]);
			i++;
		}

		for (i = 0; i < NKEYS; i++) //Busca Key conocida
		{
			equal = strcmp(ke, ((parseData*)userinfo)->key[i]);
			if (equal == 0)
			{
				setsType = true;
				i = NKEYS;
			}
		}

		if (setsType == true)
		{
			for (i = 0; i < 3; i++)
			{
				equal = strcmp(val, ((parseData*)userinfo)->value[i]);
				if (equal == 0)
				{
					((parseData*)userinfo)->programSettings.type = i;
					i = 3;
				}
			}
		}

		else if (equal == 0)
		{
			i = 0;
			while (val[i]) //Case insensitive
			{
				val[i] = toupper(val[i]);
				i++;
			}

			for (i = 0; i < NVALUES; i++) //Busca opcion conocida
			{
				equal = strcmp(val, ((parseData*)userinfo)->value[i]);
				if (equal == 0)
					i = NVALUES;
			}
		}
	}

	if (equal != 0)
		equal = -1;
	else
		equal = 1;
	return equal;
}