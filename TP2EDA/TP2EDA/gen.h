#pragma once
#include "allegro.h"
#include "parseCmd.h"

#define MAX_VERT 24

void generatePolygons(parseData*, allegroUtils*, float xo, float yo, float length, int red, int green, int blue, int thickness);
void generateUniforme(parseData*, allegroUtils*);
void generateMandelbrot(parseData*, allegroUtils*);

void drawPolygon(parseData*, float[MAX_VERT], int red, int green, int blue, int thickness);

void calculateVertices(parseData*, float [MAX_VERT], float xo, float yo, float length);