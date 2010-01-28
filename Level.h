/*
** YARG Level.h 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Level
#define _Level


class Level{
	
	int level;
	int numRocks;
	
	public:

	Level();

	void nextLevel();
	
	int getLevel();
	
	int getRocks();
};

#endif
