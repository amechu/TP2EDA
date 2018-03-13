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

	if (!al_reserve_samples(4)) {
		cout << "Falla al reservar samples." << endl;
		return -1;
	}

	alUtils->sample_mac = al_load_sample("macintosh_plus.wav"); //by Vektroid
	if (!alUtils->sample_mac) {
		cout << "Falla al inicializar sample." << endl;
		return -1;
	}

	alUtils->sample_fart = al_load_sample("quick_fart.wav"); //SoundBible.com
	if (!alUtils->sample_fart) {
		cout << "Falla al inicializar sample." << endl;
		al_destroy_sample(alUtils->sample_mac);
		return -1;
	}

	alUtils->sample_ofortuna = al_load_sample("o_fortuna.wav"); //Carl Orff - Carmina Burana
	if (!alUtils->sample_ofortuna) {
		cout << "Falla al inicializar sample." << endl;
		al_destroy_sample(alUtils->sample_mac);
		al_destroy_sample(alUtils->sample_fart);
		return -1;
	}

	alUtils->sample_xfiles = al_load_sample("xfiles.wav"); //Xfiles
	if (!alUtils->sample_xfiles) {
		cout << "Falla al inicializar sample." << endl;
		al_destroy_sample(alUtils->sample_mac);
		al_destroy_sample(alUtils->sample_fart);
		al_destroy_sample(alUtils->sample_ofortuna);
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		cout << "Falla al inicializar primitivas." << endl;
		al_destroy_sample(alUtils->sample_mac);
		al_destroy_sample(alUtils->sample_fart);
		al_destroy_sample(alUtils->sample_ofortuna);
		al_destroy_sample(alUtils->sample_xfiles);
		outcome = false;
	}

	alUtils->display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	if (!(alUtils->display))
	{
		cout << "Falla al inicializar display." << endl;	
		al_shutdown_primitives_addon();
		al_destroy_sample(alUtils->sample_mac);
		al_destroy_sample(alUtils->sample_fart);
		al_destroy_sample(alUtils->sample_ofortuna);
		al_destroy_sample(alUtils->sample_xfiles);
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
	al_destroy_sample(alUtils->sample_mac);
	al_destroy_sample(alUtils->sample_fart);
	al_destroy_sample(alUtils->sample_ofortuna);
	al_destroy_sample(alUtils->sample_xfiles);
	return;

}
