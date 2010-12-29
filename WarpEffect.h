#ifndef _WarpEffect
#define _WarpEffect

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

//#include <SDL/SDL.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <time.h>

#include "consts.h"

class WarpEffect{
	float x;
	float y;
	float age;
	int opacity;
	float radius;
	int maxAge;
	int halfLife;
	
	float deltaTime;
	float lastTime;
	
	bool active;

	sf::Clock* Clock;
	
	public:
//	WarpEffect();


	WarpEffect();    
	WarpEffect(float intX, float intY);    
	
	//use either setAge or setHalfLife
	//two ways to set length of effect
	
	void setAge(int);
	void setHalfLife(int);

	void draw(float mX, float mY);
    
//	void incAge(Uint32 deltaTime);
	void incAge();
	
	void initiate(float intX, float intY, int inHalfLife);
	
	float getX();
	float getY();
};

#endif
