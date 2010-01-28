
/*
** YARG Ship.h 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Ship
#define _Ship

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

#include <SDL_framerate.h>
#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "Rock.h"
#include "MyLine.h"

class Ship{
	float x;
	float y;
	float direction;
	float speed;
	float thrust;
	float dx;
	float dy;
	float angle; //radians from east, counter clockwise
	float maxSpeed;
	float maxThrust;
	int size;
	bool dead;
	
	bool reload;
	Uint32 reloadTimer;
	int reloadTime; //= 666;

	Uint32 deadTimer;
	int deadTime;

	public:
	
	MyPoint* point;

	Ship();

	~Ship();
	
	float getDx();

	float getDy();

	float getAngle();

	void rotateShip(float rad);

	void moveShip();

	void addThrust(int m);

	void calcPoints();

	MyLine * getLine(int m);

	/*
	 * getLine() causes memory leak
	 * coding alternate implementation
	 * using primitives to pass same 
	 * information
	 */

	/*
	 * (line, pair), where line is one of the three lines (takes 0-2)
	 * and pair returns one of the ordered pairs (takes 0-1)
	 */

	float getCoords(int lineSeg, int pair);

	bool isReloaded();

	bool fire();

	void wrap();

	float getX();
	
	float getY();
	
	int getSize();

	void die();

	bool isDead();

	void spawnShip();
	
	void forceSpawn();

	void safeSpawn(std::list<Rock> rocks);

	void draw();
};

//#include "Ship.cpp"
#endif

