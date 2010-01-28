/*
** YARG MyLine.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** More leftover legacy code.  It works, so it's still here for now.
*/

#include "MyPoint.h"

	MyPoint::MyPoint (float n, float m){
		x = n; m = y;
		up = true; right = true;
		minX = 0; minY = 0;
		maxX = 800; maxY = 600;
	}
	MyPoint::MyPoint (){
		x = 100; y=100;
		up = true; right = true;
		minX=0; minY = 0;
		maxX = 800; maxY = 600;
	}
	MyPoint::~MyPoint (){
		//std::cout << "\nmypoint destructed?";
	}
	float MyPoint::getX(){
		return x;
	}
	float MyPoint::getY(){
		return y;
	}
	void MyPoint::setX(float n){
		x = n;
		if(x>maxX)
			right = false;
		else if(x<0)
			right = true;
	}
	void MyPoint::setY(float m){
		y = m;
		if(y>maxY)
			up = false;
		else if(y<0)
			up = true;
	}


	bool MyPoint::getUp(){
		return up;
	}
	bool MyPoint::getRight(){
		return right;
	}		
