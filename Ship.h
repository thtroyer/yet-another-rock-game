
/*
** YARG Ship.h 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
** Some legacy code here too.
*/

#ifndef _Ship
#define _Ship

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

//#include <SDL/SDL.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "Rock.h"
#include "Shot.h"
#include "MyLine.h"
#include "WarpEffect.h"

#include "consts.h"

class Shot;

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
	bool active;
	bool jumping;
	bool returning;
	
	
	sf::Clock* Clock;

	float spawnTimer;
	//const int spawnTime = 250;
	
	WarpEffect* warpSpawn;
	WarpEffect* warpJump;
	
	bool reload;
	//Uint32 reloadTimer;
	float* reloadTimer;
	float reloadTime;

	//Uint32 deadTimer;
	float deadTimer;
	float deadTime;
	
	float jumpTimer;
	float jumpTime;

	
	public:
	
	MyPoint* point;

	Ship();

	~Ship();
	
	float getDx();

	float getDy();

	//float getXSpeed();

	//float getYSpeed();

	float getAngle();

	void rotateShip(float rad, float deltaTime);

	void moveShip(float deltaTime);

	void addThrust(int m, float deltaTime);
	

	

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
	
	bool isReloaded(Shot* shot);

	bool fire();
	
	bool fire(Shot* shot);

	void wrap();

	float getX();
	
	float getY();
	
	int getSize();

	void die();

	bool isDead();

	bool isActive();
	bool isJumping();

	void spawnShip();
	
	void spawnShip(float, float);
	
	void forceSpawn();

	void safeSpawn(std::list<Rock*> rocks);
	
	void jump();
	void jump(bool safe);

	void returnJump();

	void draw();
};

//#include "Ship.cpp"
#endif

