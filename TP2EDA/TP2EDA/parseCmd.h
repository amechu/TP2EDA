#pragma once

#include <stdlib.h>
#include <stdio.h>

//DEFINICIONES
#define NPARAMETERS 1
#define NKEYS 11
#define NVALUES 3 //Puede cambiarse el numero para la cantidad de parametros, claves y valores que se deseen
enum { ERROR1 = -1, ERROR2 = -2, ERROR3 = -3 }; //error 1 es opcion sin valor, error 2 es opcion sin clave error3 es no encontrado
enum {UNIFORME, POLIGONO, MANDELBROT}; //values no numericas
enum {FRACTALTYPE,LSTART,LEND,LCONSTANT,LEFTANGLE,RIGHTANGLE,XO,YO,XF,YF,N}; //Tipos de clave

//TYPEDEF
typedef int(*pCallback) (char *, char*, void *);
typedef struct
{
	int fractalType;
	double lStart;
	double lEnd;
	double lConstant;
	double leftAngle;
	double rightAngle;
	double xo;
	double yo;
	double xf;
	double yf;
	double n;

}programsettings;
typedef struct
{
	char *  parameters[NPARAMETERS];
	char *  key[NKEYS];
	char *  value[NVALUES];
	programsettings programSettings;

}parseData;


//DECLARACIONES 
int parseCallback(char *key, char *value, void *parseData);
int parseCmdLine(int argc, char *argv[], pCallback p, void *parseData);
int settingsVerification(parseData* parseData);

