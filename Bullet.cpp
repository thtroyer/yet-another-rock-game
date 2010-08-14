
/*
** YARG Bullet.cpp
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Bullet.h"

	Bullet::Bullet(Ship* owner, float m, int mAge) : Shot(owner, m, mAge){
		
		setType(0);
		setSize(1);
		
	}


