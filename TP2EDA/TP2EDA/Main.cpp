#include "parseCmd.h"
#include "allegro.h"
#include "gen.h"
#include <iostream>

int main(int argc, char ** argv)
{
	using namespace std;
	int error;
	pCallback p = parseCallback;
	parseData parseData;
	allegroUtils alUtils;

	{//Llenando base de datos
		parseData.key[0] = (char*) "TYPE";
		parseData.key[1] = (char*) "LSTART";
		parseData.key[2] = (char*) "LEND";
		parseData.key[3] = (char*) "LCONSTANT";
		parseData.key[4] = (char*) "LEFTANGLE";
		parseData.key[5] = (char*) "RIGHTANGLE";
		parseData.key[6] = (char*) "XO";
		parseData.key[7] = (char*) "YO";
		parseData.key[8] = (char*) "XF";
		parseData.key[9] = (char*) "YF";

		parseData.value[0] = (char*) "UNIFORME";
		parseData.value[1] = (char*) "OCTOGONO";
		parseData.value[2] = (char*) "MANDELBROT";

		parseData.parameters[0] = (char*) "NOAUDIO";

		//Default program settings
		parseData.programSettings.fractalType = UNIFORME;
		parseData.programSettings.lStart = 0.1;
		parseData.programSettings.lEnd = 100.0;
		parseData.programSettings.lConstant = 0.01;
		parseData.programSettings.leftAngle = 30.0;
		parseData.programSettings.rightAngle = 30.0;
		parseData.programSettings.xo = 0.0;
		parseData.programSettings.yo = 0.0;
		parseData.programSettings.xf = 2.0;
		parseData.programSettings.yf = 2.0;
	}

	if (allegroInit(&alUtils))
	{
		error = parseCmdLine(argc, argv, p, &parseData); //Llamada al parseador de linea de comandos.

		if (error == ERROR1)
			cout << "Error tipo 1, se ha ingresado una opcion sin valor" << endl;
		else if (error == ERROR2)
			cout << "Error tipo 2, se ha ingresado una opcion sin clave" << endl;
		else if (error == ERROR3)
			cout << "Error tipo 3, los datos ingresados no corresponden con nuestra base de datos" << endl;
		else if (!(settingsVerification(&parseData)))
			cout << "Error tipo 4, parametros invalidos." << endl;
		else
		{

			switch (parseData.programSettings.fractalType)
			{
				case UNIFORME:
				{
					generateUniforme(&parseData, &alUtils);
				}
				case OCTOGONO:
				{
					generateOctogono(&parseData, &alUtils);
				}
				case MANDELBROT:
				{
					generateMandelbrot(&parseData, &alUtils);
				}
			}
		}
	}

	else
	{
		cout << "Error, cerrando programa.." << endl;
	}

	allegroDestroy(&alUtils);
	
	return 0;
}