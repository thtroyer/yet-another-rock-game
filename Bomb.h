
/*
** YARG Bomb.h
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Bomb
#define _Bomb

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "Ship.h"

#include "Shot.h"

#include "consts.h"

class Bomb : public Shot{
	//private:

	public:
	Bomb(Ship* owner, float m, int mAge);
	
	void draw();
};

#endif
