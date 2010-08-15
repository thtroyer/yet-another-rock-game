
/*
** YARG Bomb.cpp
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Bomb.h"

	Bomb::Bomb(Ship* owner, float m, int mAge) : 
		Shot(owner, m, mAge){
		
		setType(1);
		setSize(3);
		
	}
	
	void Bomb::draw(){
		glColor4f(0.0, 0.9, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
			for(float angle=0; angle<2*pi; angle+=.17){ //.17 ~= 10 degrees
				glVertex2f(x + sin(angle) * size, y + cos(angle) * size);
			}
		glEnd();
		
		
	}


