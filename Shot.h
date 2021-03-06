
/*
** YARG Shot.h
** Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#ifndef _Shot
#define _Shot

#if _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>

#include <GL/gl.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <new>
#include <string>
#include <math.h>
#include <time.h>
#include <list>

#include "Ship.h"

#include "consts.h"

class Ship;

class Shot{
	
	protected:
	float dx;
	float dy;
	int size;
	float speed;
	int age;
	int maxAge;
	bool blank;
	//int size;
	float reloadTime;
	
	Ship* owner;
	
	
	int type; //0 = bullet; 1 = bomb

	float x;
	float y;


	public:

	Shot(bool blanked);

	Shot(float m);

	Shot(float m, int n);

	Shot(Ship* mOwner, float m, int mAge);
	Shot(Ship* mOwner, float m, int mAge, int mType);
	
	Shot();
	
	virtual void draw();
	
	void fire(Ship* mOwner);

	float getX();
	
	float getY();

	void move(float deltaTime);
	
	int getAge();

	void setAge(int m);

	bool checkAge();
	
	void incAge();

	void incAge(int m);
	
	void wrap();
	
	bool isBlank();
	
	int getType();
	void setType(int m);
	
	int getSize();
	void setSize(int m);
	
	float getReloadTime();
	void setReloadTime(float m);

};

#endif
