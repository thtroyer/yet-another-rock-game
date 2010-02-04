
/*
** YARG main.cpp
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** Here's where the initialization of the game class happens.
*/

#include <iostream>
#include <cstdlib>

#include "random.h"

#include "Game.h"

using std::string;

int main(int argc, char **argv){

	std::cout << "min: -5, max 5" << std::endl;
	for(int i = 0; i < 20; i++){
		std::cout << randomFloat(-5,5) << std::endl;
	}
	
	Game * game = new Game;
	
	if(game->init()){
		std::cout << "Error in game.init()" << std::endl;
		return 1;
	}

	game->loop();
		
	SDL_Quit();
	delete game;

	return 0;
}
