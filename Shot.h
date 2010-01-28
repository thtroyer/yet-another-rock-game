
/*
** YARG Shot.h
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Shot
#define _Shot

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

#include <SDL_framerate.h>
#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "Ship.h"

class Shot{
	float dx;
	float dy;
	int size;
	float speed;
	int age;
	int maxAge;

	float x;
	float y;


	public:

	Shot(float m);

	Shot(float m, int n);

	Shot(Ship* owner, float m, int mAge);
	
	Shot();
	
	void fire(Ship* owner);

	float getX();
	
	float getY();

	void move();
	
	int getAge();

	void setAge(int m);

	bool checkAge();
	
	void incAge();

	void incAge(int m);
	
	void wrap();

};

//#include "Shot.cpp"
#endif
