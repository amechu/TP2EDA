#include <string.h>
#include <fwpstypes.h>
#include <stdio.h>
#include <iostream>
#include "parseCmd.h"

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
				posible = p(&(argv[i][1]), argv[i + 1],(void *) parseData);
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
			posible = p(NULL, argv[i], (void*)parseData); //si no es opcion es parametro
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
	double convertedValue = 0.0;
	int i = 0, temp, equal = -1;
	char * ke = key;
	char * val = value;
	bool setsType = false;
	bool setsParameter = false;
	parseData* userInfo = (parseData*)userinfo;

	if (key == NULL)
	{
		while (val[i]) //Case insensitive
		{
			val[i] = toupper(val[i]);
			i++;
		}

		for (i = 0; i < NPARAMETERS; i++) //Busca parametro conocido
		{
			equal = strcmp(val, userInfo->parameters[i]);
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
			equal = strcmp(ke, userInfo->key[i]);
			if (equal == 0)
			{
				if (i == FRACTALTYPE) //Si es key de tipo de fractal
					setsType = true;
				else				 //Si es key de otra cosa
				{
					setsParameter = true;
					temp = i;
				}

				i = NKEYS;
			}
		}

		if (setsType == true)
		{
			equal = -1;
			i = 0;
			while (value[i]) //Case insensitive
			{
				val[i] = toupper(val[i]);
				i++;
			}

			for (i = 0; i < 3; i++) //Busca que tipo de fractal es
			{
				equal = strcmp(val, *((userInfo->value)+i));
				if (equal == 0)
				{
					userInfo->programSettings.fractalType = i; //Asigna tipo de fractal a programSettings
					i = 3;
				}
			}
		}

		else if (setsParameter == true) //Busca si la value es correcta y no se escapa del rango
		{
			
			if (convertedValue = atof(value)) //Convierte numero a floating point
			{
				switch (temp) //Busca que key ha sido ingresada
				{
					case LSTART:
					{
						userInfo->programSettings.lStart = convertedValue;
						break;
					}
					case LEND:
					{
						userInfo->programSettings.lEnd = convertedValue;
						break;
					}
					case LCONSTANT:
					{
						userInfo->programSettings.lConstant = convertedValue;
						break;
					}
					case LEFTANGLE:
					{
						userInfo->programSettings.leftAngle = convertedValue;
						break;
					}
					case RIGHTANGLE:
					{
						userInfo->programSettings.rightAngle = convertedValue;
						break;
					}
					case XO:
					{
						userInfo->programSettings.xo = convertedValue;
						break;
					}
					case YO:
					{
						userInfo->programSettings.yo = convertedValue;
						break;
					}
					case XF:
					{
						userInfo->programSettings.xf = convertedValue;
						break;
					}
					case YF:
					{
						userInfo->programSettings.yf = convertedValue;
						break;
					}
					case N:
						userInfo->programSettings.n = convertedValue;
				}
			}

			else
				equal = -1;
		}
	}


	if (equal != 0)
		equal = -1;
	else
		equal = 1;
	return equal;
}

int settingsVerification(parseData* parseData) //Se verifican los settings ingresados (ej. angulos no paralelos)
{
	using namespace std;
	bool result;

	if (!(parseData->programSettings.lStart > 0.0 && parseData->programSettings.lStart <= 100.0))
	{
		cout << "LSTART invalido." << endl;
		result = false;
	}
	else if (!(parseData->programSettings.lEnd > 0.0 && parseData->programSettings.lEnd <= 100.0 && parseData->programSettings.lEnd < parseData->programSettings.lStart))
	{
		cout << "LEND invalido." << endl;
		result = false;
	}
	else if (!(parseData->programSettings.lConstant > 0.0 && parseData->programSettings.lConstant < 1.0))
	{
		cout << "LCONSTANT invalido." << endl;
		result = false;
	}
	else if (!(parseData->programSettings.leftAngle > -90.0 && parseData->programSettings.leftAngle < 90.0 && (parseData->programSettings.leftAngle != (-(parseData->programSettings.rightAngle)))))
	{
		cout << "Angulos invalidos." << endl;
		result = false;
	}
	else if (!(parseData->programSettings.rightAngle > -90.0 && parseData->programSettings.rightAngle <= 90.0 && (parseData->programSettings.leftAngle != (-(parseData->programSettings.rightAngle)))))
	{
		cout << "Angulos invalidos." << endl;
		result = false;
	}
	else if (!(parseData->programSettings.n >= 3 && parseData->programSettings.n <= 12))
	{
		cout << "n invalido." << endl;
		result = false;
	}
	
	else
		result = true;

	return result;
}
