#pragma once
#include "allegro.h"
#include "parseCmd.h"

#define MAX_VERT 50
#define SIZE_ADJUST 4 //Por razones de estetica
#define TRIANGLE_COORDS 6
#define DOWNOFFSET 60 //Por razones de estetica

void generatePolygons(parseData*, float xo, float yo, float length, int red, int green, int blue, int thickness);
void generateUniforme(parseData* myData, float Ax, float Ay, float Bx, float By, float Cx, float Cy, int red, int green, int blue, int thickness, int rec_count);
void generateMandelbrot(parseData*, allegroUtils*);

void drawPolygon(parseData*, float[MAX_VERT], int red, int green, int blue, int thickness);

void calculateVertices(parseData*, float [MAX_VERT], float xo, float yo, float length);
void centerTriangle(parseData* parseData, float vert[MAX_VERT]);
