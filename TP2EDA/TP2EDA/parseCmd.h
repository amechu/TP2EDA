#pragma once

#include <stdlib.h>
#include <stdio.h>

//DEFINICIONES
#define NPARAMETERS 3
#define NKEYS 3
#define NVALUES 3 //Puede cambiarse el numero para la cantidad de parametros, claves y valores que se deseen
enum { ERROR1 = -3, ERROR2, ERROR3 }; //error 1 es opcion sin valor, error 2 es opcion sin clave error3 es no encontrado

//DECLARACIONES
int parseCallback(char *key, char *value, void *userData);
int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

//TYPEDEF
typedef int(*pCallback) (char *, char*, void *);
typedef struct
{
	char *  parameters[NPARAMETERS];
	char *  key[NKEYS];
	char *  value[NVALUES];
}userData;
