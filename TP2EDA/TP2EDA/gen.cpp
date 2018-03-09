#include "gen.h"

void generateUniforme(parseData* myData, allegroUtils* alUtils)
{
	float vertices[] = { 2,2,36,36,4,100 };

	al_draw_polygon(vertices, 3, ALLEGRO_LINE_JOIN_NONE, al_map_rgb(32, 51, 51), 2, 1);
	al_rest(20);
}

void generateOctogono(parseData* myData, allegroUtils* alUtils)
{

}

void generateMandelbrot(parseData* myData, allegroUtils* alUtils)
{

}