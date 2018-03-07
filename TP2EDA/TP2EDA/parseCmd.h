#pragma once

#include <stdlib.h>
#include <stdio.h>

//DEFINICIONES
#define NPARAMETERS 1
#define NKEYS 10
#define NVALUES 1 //Puede cambiarse el numero para la cantidad de parametros, claves y valores que se deseen
enum { ERROR1 = -1, ERROR2 = -2, ERROR3 = -3 }; //error 1 es opcion sin valor, error 2 es opcion sin clave error3 es no encontrado
enum {UNIFORME, OCTOGONO, MANDELBROT};

//TYPEDEF
typedef int(*pCallback) (char *, char*, void *);
typedef struct
{
	char *  parameters[NPARAMETERS];
	char *  key[NKEYS];
	char *  value[NVALUES];
	programSettings programSettings;

}parseData;

typedef struct
{
int fractalType;
int lStart;
int lEnd;
int lConstant;
int leftAngle;
int rightAngle;
int xo;
int yo;
int xf;
int yf;

}programSettings;

//DECLARACIONES 
int parseCallback(char *key, char *value, void *parseData);
int parseCmdLine(int argc, char *argv[], pCallback p, void *parseData);

