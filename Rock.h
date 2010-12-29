

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

#include <Box2D/Box2D.h>

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>
//#include <SDL/SDL.h>

#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "MyPoint.h"

#include "random.h"
#include "consts.h"
#include "Ship.h"

class Ship;

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
	
	b2Body* body;
	b2World* _world;

	Rock();

	Rock(float xCoord, float yCoord, float xSpeed, float ySpeed, int rockSize, int rockPoints, float rotAngle, b2World* world);
	
	//Rock(float xCoord, float yCoord, float maxSpeed, int rockSize, int rockPoints);

	Rock(int m, int n);
	
	~Rock();
	
	void draw();
	
	void draw(Ship& player);
	
	float getMaxRadius();

	void move(float deltaTime);

	void recalc();

	void wrap();
	
	void setX(float m);
	
	void setY(float m);

	float getX();
	
	float getY();

	int getNumPoints();
	
	int getSize();

	void setdAngle(float);

	float getdAngle();

	float getDx();

	float getDy();

	void rotate(float deltaTime);
	
	b2Body* getBody();
};

#endif

