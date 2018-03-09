#include "allegro.h"
#include "parseCmd.h"
#include <iostream>

using namespace std;

bool allegroInit(allegroUtils* alUtils)
{

	bool outcome = true;

	if (!al_init()) 
	{
		cout << "Falla al inicializar allegro." << endl;
		outcome = false;
	}

	if (!al_init_primitives_addon())
	{
		cout << "Falla al inicializar primitivas." << endl;
		outcome = false;
	}

	alUtils->display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	if (!(alUtils->display))
	{
		cout << "Falla al inicializar display." << endl;	
		al_shutdown_primitives_addon();
		outcome = false;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	return outcome;
}

void allegroDestroy(allegroUtils* alUtils)
{
	al_destroy_display(alUtils->display);

	return;

}
