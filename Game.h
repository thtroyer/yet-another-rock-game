

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

//#include <GL/gl.h>
//#include <FTGL/ftgl.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


//#include <SDL/SDL.h>
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
#include "WarpEffect.h"

#include "consts.h"


class Game{
	private:
	/*
	** Game variables
	*/

	sf::RenderWindow* App;
	sf::Clock* Clock;

	sf::Font* statsFont;
	sf::Font* centerFont;
	sf::String* strScore;
	sf::String* strMessage;

	//Keyboard bool array
	//bool * keyDown;
	bool KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_SHOOT;

	//Player stuff
	MyLine* line;
	Ship player;

	std::list<Shot> shots;
	std::list<Rock> rocks;
	
	int rate;
	int frames;
	float deltaTime;

 	WarpEffect* test;

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
