/************************************************************************
*                     Headers go in this header file!!                  *
*************************************************************************/
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

enum ID{PLAYER, ENEMY, BULLET};

enum KEYS {W, A, S, D, E, SPACE, ENTER};

//Function that Reads the width and height
int widthHeight (int variable);
//Function to initialize the display
void displaySet (int width, int height, ALLEGRO_DISPLAY *display);
//Function to set up the keyBoard
void keyboardUse(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT ev);

