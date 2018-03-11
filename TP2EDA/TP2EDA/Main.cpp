#include "allegro.h"
#include "gen.h"
#include "parseCmd.h"
#include <iostream>

int main(int argc, char ** argv)
{
	using namespace std;
	int error;
	float vert[MAX_VERT] = { 0 };
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
		parseData.key[10] = (char*) "N";

		parseData.value[0] = (char*) "UNIFORME";
		parseData.value[1] = (char*) "POLIGONO";
		parseData.value[2] = (char*) "MANDELBROT";

		parseData.parameters[0] = (char*) "NOAUDIO";

		//Default program settings
		parseData.programSettings.fractalType = POLIGONO;
		parseData.programSettings.lStart = 100;
		parseData.programSettings.lEnd = 1;
		parseData.programSettings.lConstant = 0.45;
		parseData.programSettings.leftAngle = 30.0;
		parseData.programSettings.rightAngle = 30.0;
		parseData.programSettings.xo = 0;
		parseData.programSettings.yo = 0;
		parseData.programSettings.xf = 2.0;
		parseData.programSettings.yf = 2.0;
		parseData.programSettings.n = 6;

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
					break;
				}
				case POLIGONO:
				{
					al_play_sample(alUtils.sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &(alUtils.sampleId));
					generatePolygons(&parseData, &alUtils, SCREENWIDTH/2, SCREENHEIGHT/2, parseData.programSettings.lStart, 40, 150, 150, 3);
					al_stop_sample(&(alUtils.sampleId));
					break;
				}
				case MANDELBROT:
				{
					break;
				}
			}
		}
	}

	else
	{
		cout << "Error, cerrando programa.." << endl;
	}
	getchar();
	allegroDestroy(&alUtils);
	
	return 0;
}