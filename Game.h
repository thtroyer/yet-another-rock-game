

/*
** YARG Game.h 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** Here's where most of the game's activities happen
** i.e. game loop, keyboard events, etc. 
*/

#ifndef _Game
#define _Game

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>
#include <FTGL/ftgl.h>

#include <SDL/SDL.h>
#include <new>
#include <string>
#include <sstream>
#include <math.h>
#include <time.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYAREA_WIDTH 800
#define PLAYAREA_HEIGHT 600

#include "random.h"
#include "Ship.h"
#include "Shot.h"
#include "Rock.h"
#include "Level.h"

#include "consts.h"


class Game{
	private:
	/*
	** Game variables
	*/

	//SDL stuff
	SDL_Surface * screen; 
	SDL_Event event;

	FTGLBitmapFont* font;
	FTGLPixmapFont* txtCenter;

	//Keyboard bool array
	bool * keyDown;

	//Player stuff
	MyLine* line;
	Ship player;

	std::list<Shot> shots;
	std::list<Rock> rocks;
	
	int rate;
	int frames;
	time_t time1;
	time_t time2;

	Uint32 lastFrameTime;
	Uint32 currFrameTime;
	Uint32 deltaTime;

	Level level;
	bool nextLevel;
	
	bool gameRunning;

	int score;
	int lives;

	public:

	Game();
	~Game();
	bool running();
	
	bool init();
	void events();
	void doActions();

	void loop();
	void newGame();
	void endGame();

	void levelEvents();
	void moveShots();
	void moveRocks();
	void movePlayer();

	void drawInterface();
	void drawFont();	

	void collisionEvents();
	void playerEvents();
	void keyEvents();

	void render();
	
};

#endif
