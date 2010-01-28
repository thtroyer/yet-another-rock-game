/*
** YARG MyLine.h 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** This is a bit of a messy left-over from original prototyping.
** It works without complaining, so I haven't revisited it.
*/

#ifndef _MyLine
#define _MyLine

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "MyPoint.h"

#include "random.h"

class MyLine{
	public:
		MyPoint* point;

		MyLine();
		~MyLine();


		void moveLine();
		
		float getX(int m);
		float getY(int m);
		void setX(int m, float n);
		void setY(int m, float n);
};

#endif

