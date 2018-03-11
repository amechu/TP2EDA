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

	if (!al_install_audio()) {
		cout << "Falla al inicializar audio." << endl;
		return -1;
	}

	if (!al_init_acodec_addon()) {
		cout << "Falla al inicializar acodec." << endl;
		return -1;
	}

	if (!al_reserve_samples(1)) {
		cout << "Falla al reservar samples." << endl;
		return -1;
	}

	alUtils->sample = al_load_sample("macintosh_plus.wav");
	if (!alUtils->sample) {
		cout << "Falla al inicializar sample." << endl;
		al_destroy_sample(alUtils->sample);
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		cout << "Falla al inicializar primitivas." << endl;
		al_destroy_sample(alUtils->sample);
		outcome = false;
	}

	alUtils->display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	if (!(alUtils->display))
	{
		cout << "Falla al inicializar display." << endl;	
		al_shutdown_primitives_addon();
		al_destroy_sample(alUtils->sample);
		outcome = false;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	return outcome;
}

void allegroDestroy(allegroUtils* alUtils)
{
	al_destroy_display(alUtils->display);
	al_shutdown_primitives_addon();
	al_destroy_sample(alUtils->sample);

	return;

}
