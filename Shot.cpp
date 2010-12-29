
/*
** YARG Shot.h
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Shot.h"

	Shot::Shot(bool blanked){
		blank = blanked;
	}


	Shot::Shot(float Speed){
		speed = Speed;
		maxAge = 50000;
		blank = false;
	}

	Shot::Shot(float m, int mAge){
		speed = m;
		maxAge = mAge;
		blank = false;
	}

	Shot::Shot(Ship* mOwner, float m, int mAge){
		age = 0;
		maxAge = mAge;
		speed = m;

		dy = mOwner->getDy() + (speed * cos(mOwner->getAngle()));
		dx = -1 * (-1 * mOwner->getDx() + (speed * sin(mOwner->getAngle())));

		x = mOwner->point[0].getX() - 400 + mOwner->getX();
		y = mOwner->point[0].getY() - 300 + mOwner->getY();
		blank = false;
	}
	
	Shot::Shot(Ship* mOwner, float m, int mAge, int mType){
		age = 0;
		maxAge = mAge;
		speed = m;
		type = mType;
		
		dy = mOwner->getDy() + (speed * cos(mOwner->getAngle()));
		dx = -1 * (-1 * mOwner->getDx() + (speed * sin(mOwner->getAngle())));

		x = mOwner->point[0].getX();
		y = mOwner->point[0].getY();
		blank = false;
	}
	
	Shot::Shot(){
		age = 0;
		speed = 2;
		maxAge = 200;
	}


	void Shot::fire(Ship* mOwner){
		dy = mOwner->getDx() + (speed * cos(mOwner->getAngle()));
		dx = -1 * (-1 * mOwner->getDy() + (speed * sin(mOwner->getAngle())));

		x = mOwner->point[0].getX();
		y = mOwner->point[0].getY();

	}

	void Shot::draw(){
		
	}

	float Shot::getX(){
		return x;
	}
	float Shot::getY(){
		return y;
	}

	void Shot::move(float deltaTime){
		//increment age here as well;
		age += deltaTime;
		x = x + (dx * deltaTime * deltaTimeConst);
		y = y + (dy * deltaTime * deltaTimeConst);
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
	//	age++;
	}

	void Shot::incAge(int deltaTime){
		age += deltaTime;
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

	bool Shot::isBlank(){
		return blank;
	}
	
	void Shot::setType(int m){
		type = m;
	}
	
	int Shot::getType(){
		return type;
	}
	
	void Shot::setSize(int m){
		size = m;
	}
	
	int Shot::getSize(){
		return size;
	}

	float Shot::getReloadTime(){
		return reloadTime;
	}

	void Shot::setReloadTime(float m){
		reloadTime = m;
	}


