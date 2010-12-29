
/*
** YARG Bomb.cpp
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/


#include "Bomb.h"

	Bomb::Bomb() : Shot(){
		
		setType(1);
		setSize(3);
		setReloadTime(.500);
		
	}

	Bomb::Bomb(Ship* mOwner, float m, int mAge) : 
		Shot(mOwner, m, mAge){
		
		setType(1);
		setSize(3);
		setReloadTime(.500);
		
		owner = mOwner;
		
	}
	
	void Bomb::draw(){
		float X = x - owner->getX() + 400;
		float Y = y - owner->getY() + 300;
		
		glColor4f(0.0, 0.9, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
			for(float angle=0; angle<2*pi; angle+=.17){ //.17 ~= 10 degrees
				glVertex2f(X + sin(angle) * size, Y + cos(angle) * size);
			}
		glEnd();
		
		
	}

