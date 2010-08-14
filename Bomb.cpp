
/*
** YARG Bomb.cpp
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Bomb.h"

	Bomb::Bomb(Ship* owner, float m, int mAge) : 
		Shot(owner, m, mAge){
		
		setType(1);
		setSize(5);
		
	}


