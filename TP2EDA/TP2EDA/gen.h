#pragma once
#include "allegro.h"
#include "parseCmd.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>

#define MAX_VERT 50 //Maxima cantidad de vertices de poligono
#define SIZE_ADJUST 4 //Por razones de estetica
#define TRIANGLE_COORDS 6 //Coordenadas de triangulo
#define DOWNOFFSET 60 //Por razones de estetica
#define N_MAX   255.0 //Maximas iteraciones de mandelbrot

void generatePolygons(parseData*, float xo, float yo, float length, int red, int green, int blue, int thickness);
void generateUniforme(parseData* myData, float Ax, float Ay, float Bx, float By, float Cx, float Cy, int red, int green, int blue, int thickness, int rec_count);
void generateMandelbrot(parseData*);

void calculateVertices(parseData*, float [MAX_VERT], float xo, float yo, float length);
void centerTriangle(parseData* parseData, float vert[MAX_VERT]);
int get_num_it(std::complex <double> z, std::complex <double> z0, int *cont, float radio);
