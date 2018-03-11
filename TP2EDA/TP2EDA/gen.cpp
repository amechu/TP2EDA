#include "allegro.h"
#include "gen.h"
#define _USE_MATH_DEFINES
#include <math.h>

void drawPolygon(parseData* myData, float vert[MAX_VERT], int red, int green, int blue, int thickness)
{
		al_draw_polygon(vert, myData->programSettings.n, ALLEGRO_LINE_JOIN_ROUND, al_map_rgb(red, green, blue), thickness, 1);
		return;
}

void calculateVertices(parseData* myData, float vert[MAX_VERT], float xo, float yo, float length)
{
	float r = (length) / (2 * (sin(M_PI / myData->programSettings.n)));
	float alpha = (2 * M_PI / myData->programSettings.n);
	int h;

	for (int i = 0, h = 1; i < 2 * myData->programSettings.n; i += 2)
	{
		vert[i] = xo + (r) * cos(alpha * h);
		h++;
	}

	for (int i = 1, h = 1; i < 2 * myData->programSettings.n; i += 2)
	{
		vert[i] = yo + (r) * sin(alpha*h);
		h++;
	}
}

void generatePolygons(parseData* myData, allegroUtils* alUtils, float xo, float yo, float length, int red, int green, int blue, int thickness)
{

	
	float vert[MAX_VERT] = { 0 };

	if (length < myData->programSettings.lEnd)
	{
		return; //Caso base
	}

	else //Caso recursivo
	{
		calculateVertices(myData, vert, xo, yo, length);
		drawPolygon(myData, vert, red, green, blue, thickness); //Dibuja nuevo poligono

		//Achico lado
		length = (length*(myData->programSettings.lConstant));
		green += 20;
		red += 10;
		blue += 20;
		if (thickness > 0)
			thickness -= 1;
		for (int i = 0; i < myData->programSettings.n; i++)
		{
			generatePolygons(myData, alUtils, vert[2*i], vert[2*i+1], length, red, green, blue, thickness); //Calcula la proxima generacion
		}
	}

	al_flip_display();
	al_rest(myData->programSettings.lEnd * myData->programSettings.lConstant * 0.001);

	return;
}