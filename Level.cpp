/*
** YARG Level.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Level.h"

	Level::Level(){
		level = 0;
		numRocks = 1;
	}

	void Level::nextLevel(){
		level++;
		numRocks = numRocks + 2;
	}
	
	int Level::getLevel(){
		return level;
	}
	int Level::getRocks(){
		return numRocks;
	}
