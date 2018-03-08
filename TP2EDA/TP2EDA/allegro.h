#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_color.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

typedef struct 
{
		ALLEGRO_DISPLAY* display;
		ALLEGRO_EVENT_QUEUE* eventqueue;
		ALLEGRO_TIMER* timer;
		double timerSpeed;

}allegroUtils;