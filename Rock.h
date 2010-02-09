

/*
** YARG Rock.h
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Rock
#define _Rock

#ifndef PLAYAREA_WIDTH
#define PLAYAREA_WIDTH 800
#endif

#ifndef PLAYAREA_HEIGHT
#define PLAYAREA_HEIGHT 600
#endif

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "MyPoint.h"

#include "random.h"
#include "consts.h"

class Rock{
	float x;
	float y;
	float dx;
	float dy;
	float maxRadius;
	float dAngle;

	int size;
	int numPoints;
	
	protected:
	const static int speed = 5;

	public:
	MyPoint* point;

	Rock();

	Rock(float xCoord, float yCoord, float xSpeed, float ySpeed, int rockSize, int rockPoints);
	
	//Rock(float xCoord, float yCoord, float maxSpeed, int rockSize, int rockPoints);

	Rock(int m, int n);
	
	float getMaxRadius();

	void move(Uint32 deltaTime);

	void recalc();

	void wrap();
	
	void setX(float m);
	
	void setY(float m);

	float getX();
	
	float getY();

	int getNumPoints();
	
	int getSize();

	float getDx();

	float getDy();
};

#endif

