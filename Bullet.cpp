
/*
** YARG Bullet.cpp
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Bullet.h"

	Bullet::Bullet() : Shot(){
		
		setType(0);
		setSize(1);
		setReloadTime(.200);
		
	}

	Bullet::Bullet(Ship* mOwner, float m, int mAge) : Shot(mOwner, m, mAge){
		
		setType(0);
		setSize(1);
		setReloadTime(.200);
		owner = mOwner;
		
	}
	
	void Bullet::draw(){
		glColor4f(0.9, 0.9, 0.9, 1.0);
		
		float X = x - owner->getX() + 400;
		float Y = y - owner->getY() + 300;

		glBegin(GL_POLYGON);		
			glVertex2f(X - size, Y + size);
			glVertex2f(X + size, Y + size);
			glVertex2f(X + size, Y - size);
			glVertex2f(X - size, Y - size);
		glEnd();
	}


