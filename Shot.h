
/*
** YARG Shot.h
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Shot
#define _Shot

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

//#include <SDL_framerate.h>
#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "Ship.h"

#include "consts.h"

class Shot{
	float dx;
	float dy;
	int size;
	float speed;
	int age;
	int maxAge;
	bool blank;

	float x;
	float y;


	public:

	Shot(bool blanked);

	Shot(float m);

	Shot(float m, int n);

	Shot(Ship* owner, float m, int mAge);
	
	Shot();
	
	void fire(Ship* owner);

	float getX();
	
	float getY();

	void move(Uint32 deltaTime);
	
	int getAge();

	void setAge(int m);

	bool checkAge();
	
	void incAge();

	void incAge(int m);
	
	void wrap();
	
	bool isBlank();

};

//#include "Shot.cpp"
#endif
