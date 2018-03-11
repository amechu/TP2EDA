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
		ALLEGRO_SAMPLE* sample;
		ALLEGRO_SAMPLE_ID sampleId;

}allegroUtils;

//DECLARATIONS
bool allegroInit(allegroUtils*);
void allegroDestroy(allegroUtils*);