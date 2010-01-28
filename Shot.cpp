
/*
** YARG Shot.h
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Shot.h"

	Shot::Shot(float Speed){
		speed = Speed;
		maxAge = 200;
	}

	Shot::Shot(float m, int mAge){
		speed = m;
		maxAge = mAge;
	}

	Shot::Shot(Ship* owner, float m, int mAge){
		age = 0;
		maxAge = mAge;
		speed = m;

		dy = owner->getDy() + (speed * cos(owner->getAngle()));
		dx =-1 * (-1 * owner->getDx() + (speed * sin(owner->getAngle())));

		x = owner->point[0].getX();
		y = owner->point[0].getY();
	}
	
	Shot::Shot(){
		age = 0;
		speed = 2;
		maxAge = 200;
	}


	void Shot::fire(Ship* owner){	
		dy = owner->getDy() + (speed * cos(owner->getAngle()));
		dx =-1 * (-1 * owner->getDx() + (speed * sin(owner->getAngle())));
		
		x = owner->point[0].getX();
		y = owner->point[0].getY();

	}

	float Shot::getX(){
		return x;
	}
	float Shot::getY(){
		return y;
	}

	void Shot::move(){
		x = x + dx;
		y = y + dy;
	}

	int Shot::getAge(){
		return age;
	}

	void Shot::setAge(int m){
		age = m;
	}

	bool Shot::checkAge(){
		if (age > maxAge)
			return false;
		return true;
	}

	void Shot::incAge(){
		age++;
	}

	void Shot::incAge(int m){
		age += m;
	}
	
	void Shot::wrap(){
		if(x > PLAYAREA_WIDTH)
			x = 1;
		else if (x < 0)
			x = PLAYAREA_WIDTH -1;

		if(y > PLAYAREA_HEIGHT)
			y = 1;
		else if (y < 0)
			y = PLAYAREA_HEIGHT -1;

	}


