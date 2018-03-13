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
	float vert[MAX_VERT] = { 0 }; //Arreglo de vertices usados en fractal de poligono
	const float angleConvert = M_PI / 180; //Para aceptar input en degrees y operar en radianes

	pCallback p = parseCallback; //Callback de parseo
	parseData parseData;	//Data de parseo
	allegroUtils alUtils;	//Data de allegro

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

		//Inicializando campos en cero.
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

	if (allegroInit(&alUtils)) //Inicializo allegro
	{
		error = parseCmdLine(argc, argv, p, &parseData); //Llamada al parseador de linea de comandos.

		if (error == ERROR1)
			cout << "Error tipo 1, se ha ingresado una opcion sin valor." << endl;
		else if (error == ERROR2)
			cout << "Error tipo 2, se ha ingresado una opcion sin clave." << endl;
		else if (error == ERROR3)
			cout << "Error tipo 3, los datos ingresados no corresponden con nuestra base de datos." << endl;

		//Default program settings, si no se eligio ningun fractal
		if (parseData.programSettings.fractalType == NONECHOSEN)
		{
			parseData.programSettings.fractalType = POLIGONO;
			parseData.programSettings.lStart = 100;
			parseData.programSettings.lEnd = 1;
			parseData.programSettings.lConstant = 0.45;
			parseData.programSettings.n = 7;
		}

		if (!(settingsVerification(&parseData))) //Verificacion de inputs
		{
			cout << "Error tipo 4, parametros invalidos." << endl;
			error = 1;
		}

		if(error == 0) //Si hasta ahora no hubo error
		{
			switch (parseData.programSettings.fractalType) //A partir de tipo de fractal seleccionado
			{											   //se llama a su correspondiente funcion generadora.
				case UNIFORME:
				{   //En el caso de triangulo de
					//centro de masa uniforme, se opto
					//por una velocidad de generacion
					//mas lenta.
					centerTriangle(&parseData, vert);	//Calcula el triangulo pedido por el usuario
														//y lo centra, alineando su centro de masa con el centro
														//de la ventana. Desde ahi se lo corre hacia abajo
														//un valor DOWNOFFSET por razones esteticas.
					if(parseData.programSettings.audio == true)
						al_play_sample(alUtils.sample_ofortuna, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &(alUtils.sampleId_ofortuna));
					//Si el usuario ingreso el parametro "noaudio" no se pasaran los samples.
					//Se llama entonces a la funcion recursiva. Esto se hace con todos los fractales.
					generateUniforme(&parseData, vert[0], vert[1], vert[2], vert[3], vert[4], vert[5], 255, 0, 20, 3, 0);
					if (parseData.programSettings.audio == true)
					{
						al_stop_sample(&(alUtils.sampleId_ofortuna));
						al_play_sample(alUtils.sample_fart, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &(alUtils.sampleId_fart));
					}
						break;
				}
				case POLIGONO:
					//Caso poligono. Los primeros poligonos no estan hardcodeados, sino que estan
					//dibujados a partir de su centro en el centro de la pantalla, rotando con 
					//funciones trigonometricas para dibujar cada uno de los vertices.
					//Esto permite dibujar poligonos de cualquier cantidad de lados. Esta limitado a 25
					//por razones esteticas, y porque el radio de un poligono aumenta proporcional a lstart.
				{
					if (parseData.programSettings.audio == true)
						al_play_sample(alUtils.sample_mac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &(alUtils.sampleId_mac));
					generatePolygons(&parseData, SCREENWIDTH/2, SCREENHEIGHT/2, parseData.programSettings.lStart, 20, 125, 140, 3);
					if (parseData.programSettings.audio == true)
						al_stop_sample(&(alUtils.sampleId_mac));
					break;
				}
				case MANDELBROT:
				{
					if (parseData.programSettings.audio == true)
						al_play_sample(alUtils.sample_xfiles, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &(alUtils.sampleId_xfiles));
					generateMandelbrot(&parseData);
					if (parseData.programSettings.audio == true)
						al_stop_sample(&(alUtils.sampleId_xfiles));
					break;
				}
			}
		}
	}

	else
	{
		cout << "Error, cerrando programa.." << endl;
	}
	
	al_rest(10);

	allegroDestroy(&alUtils);
	
	return 0;
}