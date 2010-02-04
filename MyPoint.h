
/*
** YARG MyPoint.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** More leftover legacy code.  It works, so it's still here for now.
*/

#ifndef _MyPoint
#define _MyPoint

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

class MyPoint{
		float x;
		float y;
		bool up;
		bool right;
		int minX; int maxX; int minY; int maxY;
	public:
		MyPoint (float n, float m);
		MyPoint ();
		~MyPoint ();
		float getX();
		float getY();
		void setX(float n);
		void setY(float m);
		bool getUp();
		bool getRight();
};

//#include "MyPoint.cpp"
#endif

