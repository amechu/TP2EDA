#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_color.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

//TYPEDEFS
typedef struct 
{
		ALLEGRO_DISPLAY* display;
		ALLEGRO_SAMPLE* sample_mac;
		ALLEGRO_SAMPLE_ID sampleId_mac;
		ALLEGRO_SAMPLE* sample_fart;
		ALLEGRO_SAMPLE_ID sampleId_fart;
		ALLEGRO_SAMPLE* sample_ofortuna;
		ALLEGRO_SAMPLE_ID sampleId_ofortuna;


}allegroUtils;

//DECLARATIONS
bool allegroInit(allegroUtils*);
void allegroDestroy(allegroUtils*);