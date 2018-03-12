#pragma once
#include "allegro.h"
#include "parseCmd.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>

#define X_MAX	800.0
#define Y_MAX	600.0
#define N_MAX   255.0
#define X_PASO  ((1 - (-1))/X_MAX)      // EN LUGAR DE 2 Y -2 IRIAN LOS argv[]
#define Y_PASO  ((1 - (-1))/Y_MAX)
#define RADIO   1                    // QUE EL RADIO SE MODIFIQUE SEGUN LOS argv[]

#define MAX_VERT 50
#define SIZE_ADJUST 4 //Por razones de estetica
#define TRIANGLE_COORDS 6
#define DOWNOFFSET 60 //Por razones de estetica

void generatePolygons(parseData*, float xo, float yo, float length, int red, int green, int blue, int thickness);
void generateUniforme(parseData* myData, float Ax, float Ay, float Bx, float By, float Cx, float Cy, int red, int green, int blue, int thickness, int rec_count);
void generateMandelbrot(parseData*);

void drawPolygon(parseData*, float[MAX_VERT], int red, int green, int blue, int thickness);

void calculateVertices(parseData*, float [MAX_VERT], float xo, float yo, float length);
void centerTriangle(parseData* parseData, float vert[MAX_VERT]);
int get_num_it(std::complex <double> z, std::complex <double> z0, int *cont);
