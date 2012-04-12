#include "assembly.h"
#include "testPlayer.h"

int main (int argc, char **argv)
{
	/*******************************
	*	  GameEngine Variables     *
	*******************************/
	//Check for when the game engine has completed running
	bool gameComplete = false;
	//Initalize the width and height Variables of the monitor
	int Width = 0, Height = 0;
	//Set The Frames Per Second to smooth out and standardize the gameplay
	const int FPS = 60;
	//Number of bullets you can have on screen
	const int NUM_BULLETS = 10;
	//Check to see if we should redraw the Display
	bool redraw = true;
	//Keybord Keys to press
	bool key[7] = {false};
	
	//map
	int xOff = 0;
	int yOff = 0;

	int mapColumns = 10;
	int mapSize = 100;
	int tileSize = 30;

	int map[] = {5,3,3,3,3,3,3,3,3,5,
		         1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 1,0,0,0,0,0,0,0,0,2,
				 5,4,4,4,4,4,4,4,4,5};

	/******************************
	*      Object Variables       *
	******************************/
	//Test Player
	PlAyEr player;
	BusterCannon shot[10];

	/******************************
	*     Allegro Variables       *
	******************************/
	//Initializing the event queue that deals with all the Events taking place in the game
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//Allegro Timer to set the Frames Per Second
	ALLEGRO_TIMER *timer = NULL;
	//Display Variable
	ALLEGRO_DISPLAY *display = NULL;
	//Map Sprite
	ALLEGRO_BITMAP *mapSprite = NULL;
	/******************************
	*  Initialization Functions   *
	******************************/
	//Initailizes Allegro
	if(!al_init())
		return -1;
	//Gains the Monitors Correct Width and Height
	Width = widthHeight(0);
	Height = widthHeight(1);
	//Initializes the display set up
	displaySet(Width, Height, display);
	//Creates event the Queue
	event_queue = al_create_event_queue();
	//Creates the timer
	timer = al_create_timer(1.0/FPS);
	//Initialize Test Player
	initPlayer(player, Width, Height);
	initShot(shot, NUM_BULLETS);

	/******************************
	*      Allegro Installs       *
	******************************/
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//Assign mapSprite with tiles.png
	mapSprite = al_load_bitmap("tiles.png");

	/******************************
	* Allegro EVENT_QUEUE Sources *
	******************************/
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	/****************************
	*     Game Engine Loop      *
	****************************/
	al_start_timer(timer);
	while(!gameComplete)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			if(key[W])
				MovePlayerUp(player);
			if(key[S])
				MovePlayerDown(player, Height);
			if(key[A])
				MovePlayerLeft(player);
			if(key[D])
				MovePlayerRight(player, Height);
			if(key[ENTER])
				gameComplete = true;

			xOff -= key[D] * 5;
			xOff += key[A] * 5;
			yOff -= key[S] * 5;
			yOff += key[W] * 5;

			redraw = true;
			updateShot(shot, NUM_BULLETS, Height, Width);
		}
		
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				key[W] = true;
				break;
			case ALLEGRO_KEY_A:
				key[A] = true;
				break;
			case ALLEGRO_KEY_S:
				key[S] = true;
				break;
			case ALLEGRO_KEY_D:
				key[D] = true;
				break;
			case ALLEGRO_KEY_E:
				key[E] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				key[ENTER] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[SPACE] = true;
				fireShot(shot, NUM_BULLETS, player);
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				key[W] = false;
				break;
			case ALLEGRO_KEY_A:
				key[A] = false;
				break;
			case ALLEGRO_KEY_S:
				key[S] = false;
				break;
			case ALLEGRO_KEY_D:
				key[D] = false;
				break;
			case ALLEGRO_KEY_E:
				key[E] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				key[ENTER] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[SPACE] = false;
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			//Draws map
			for(int i = 0; i < mapSize; i++)
			{
				al_draw_bitmap_region(mapSprite, tileSize * map[i], 0, tileSize, tileSize, xOff + tileSize * (i % mapColumns), yOff + tileSize * (i / mapColumns), 0);
			}

			//Set redraw it false since we're about to draw to screen
			redraw = false;
			//Draws Player on the preFlipped Display
			drawPlayer(player);
			//Draw the bullet if its live
			drawShot(shot,NUM_BULLETS);

			//Sends the changes to the screen
			al_flip_display();
			//Changes the color of the game window that's not flipped
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_bitmap(mapSprite);

	return 0;
}