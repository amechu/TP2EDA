#include "allegro.h"
#include "gen.h"
#include "parseCmd.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

int main(int argc, char ** argv)
{
	using namespace std;
	int error = 0;
	float vert[MAX_VERT] = { 0 };
	const float angleConvert = M_PI / 180;

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

		parseData.programSettings.fractalType = NONECHOSEN;
		parseData.programSettings.lStart = 0;
		parseData.programSettings.lEnd = 0;
		parseData.programSettings.lConstant = 0;
		parseData.programSettings.leftAngle = 0;
		parseData.programSettings.rightAngle = 0;
		parseData.programSettings.xo = 0;
		parseData.programSettings.yo = 0;
		parseData.programSettings.xf = 0;
		parseData.programSettings.yf = 0;
		parseData.programSettings.n = 0;
		parseData.programSettings.audio = true;
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

		//Default program settings, si no se eligio ningun fractal
		if (parseData.programSettings.fractalType == NONECHOSEN)
		{
			parseData.programSettings.fractalType = POLIGONO;
			parseData.programSettings.lStart = 100;
			parseData.programSettings.lEnd = 1;
			parseData.programSettings.lConstant = 0.45;
			parseData.programSettings.n = 6;
		}

		if (!(settingsVerification(&parseData)))
		{
			cout << "Error tipo 4, parametros invalidos." << endl;
			error = 1;
		}

		if(error == 0)
		{
			switch (parseData.programSettings.fractalType)
			{
				case UNIFORME:
				{
					centerTriangle(&parseData, vert);
					if(parseData.programSettings.audio == true)
						al_play_sample(alUtils.sample_ofortuna, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &(alUtils.sampleId_ofortuna));
					generateUniforme(&parseData, vert[0], vert[1], vert[2], vert[3], vert[4], vert[5], 255, 0, 20, 3, 0);
					if (parseData.programSettings.audio == true)
					{
						al_stop_sample(&(alUtils.sampleId_ofortuna));
						al_play_sample(alUtils.sample_fart, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &(alUtils.sampleId_fart));
					}
						break;
				}
				case POLIGONO:
				{
					if (parseData.programSettings.audio == true)
						al_play_sample(alUtils.sample_mac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &(alUtils.sampleId_mac));
					generatePolygons(&parseData, SCREENWIDTH/2, SCREENHEIGHT/2, parseData.programSettings.lStart, 40, 150, 150, 3);
					if (parseData.programSettings.audio == true)
						al_stop_sample(&(alUtils.sampleId_mac));
					break;
				}
				case MANDELBROT:
				{
					generateMandelbrot(&parseData);
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