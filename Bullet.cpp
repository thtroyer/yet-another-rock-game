
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

	Bullet::Bullet(Ship* owner, float m, int mAge) : Shot(owner, m, mAge){
		
		setType(0);
		setSize(1);
		setReloadTime(.200);
		
	}
	
	void Bullet::draw(){
		glColor4f(0.9, 0.9, 0.9, 1.0);
		glBegin(GL_POLYGON);		
			glVertex2f(x - size, y + size);
			glVertex2f(x + size, y + size);
			glVertex2f(x + size, y - size);
			glVertex2f(x - size, y - size);
		glEnd();
	}


