
/*
** YARG Bullet.h
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Bullet
#define _Bullet

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

#include "Shot.h"

#include "Ship.h"

#include "consts.h"

class Bullet : public Shot{
	//private:

	public:

	Bullet();
	Bullet(Ship* owner, float m, int mAge);
	
	void draw();
	
};

#endif
