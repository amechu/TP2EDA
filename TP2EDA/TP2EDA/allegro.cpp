#include "allegro.h"
#include <iostream>

using namespace std;

bool allegroInit(allegroUtils* alUtils)
{
	if (!al_init()) 
	{
		cout << "Failed to initialize allegro." << endl;
		return -1;
	}

	alUtils->display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	if (!(alUtils->display))
	{
		cout << "Failed to initialize display." << endl;
		return -1;
	}

	return true;
}