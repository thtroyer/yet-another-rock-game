
/*
** YARG Ship.h
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Ship.h"

	Ship::Ship(){
		deadTimer = SDL_GetTicks();
		deadTime = deadTimer;
		//safeSpawn();
		spawnShip();
		point = new MyPoint[3];
		size = 8;
		angle = pi;
		maxThrust = .1;
		dx = 0;
		dy = 0;
		speed = 0;
		reloadTime = 200;
		reloadTimer = SDL_GetTicks();

		deadTime = 3000;

	}

	Ship::~Ship(){
		delete [] point;
		point = 0;
	}
	
	float Ship::getDx(){
		return dx;
	}

	float Ship::getDy(){
		return dy;
	}

	float Ship::getAngle(){
		return angle;
	}

	void Ship::rotateShip(float rad){
		angle = angle + rad;
	}

	void Ship::moveShip(){
		x = x + dx;
		y = y + dy;
	}

	void Ship::addThrust(int m){
		if(!dead){
			thrust = maxThrust*m;
			dx = dx - (thrust * sin(angle));
			dy = dy + (thrust * cos(angle));
		}
	}

	void Ship::calcPoints(){
		float sideAngle[3];
		sideAngle[0]= pi/2;
		sideAngle[1] = 7 * pi / 6;
		sideAngle[2] = 11 * pi / 6;
		//add angles, calc points;
		for (int i=0; i<3; i++){
			point[i].setX((size * cos(sideAngle[i] + angle)) + x);
			point[i].setY((size * sin(sideAngle[i] + angle)) + y);
		}
	}


	MyLine * Ship::getLine(int m){
		MyLine * tmpLine = new MyLine();
		
		tmpLine->setX(0,(point[m].getX()));
		tmpLine->setY(0,(point[m].getY()));
		
		if(m<2){
			tmpLine->setX(1,(point[m+1].getX()));
			tmpLine->setY(1,(point[m+1].getY()));
		}
		else{
			tmpLine->setX(1,(point[0].getX()));
			tmpLine->setY(1,(point[0].getY()));
		}
		return tmpLine;
	}
	
	/*
	 * (line, pair), where line is one of the three lines (takes 0-2)
	 * and pair returns one of the ordered pairs (takes 0-1)
	 */

	float Ship::getCoords(int lineSeg, int pair){
		switch(pair){
			case 0:
				return point[lineSeg].getX();
				break;
			case 1:
				return point[lineSeg].getY();
				break;
		}
		return -1;
	}

	bool Ship::isReloaded(){
		if (SDL_GetTicks() >= reloadTimer)
			return true;
		return false;
	}

	bool Ship::fire(){
		 if(isReloaded() && !isDead()){
			reloadTimer = SDL_GetTicks() + reloadTime;
			return true;
		}
		return false;
	}


	void Ship::wrap(){
		if(!dead){
			if(x > PLAYAREA_WIDTH)
				x = 0;
			else if (x < 0)
				x = PLAYAREA_WIDTH;

			if(y > PLAYAREA_HEIGHT)
				y = 0;
			else if (y < 0)
				y = PLAYAREA_HEIGHT;
		}
	}

	float Ship::getX(){
		return x;
	}
	
	float Ship::getY(){
		return y;
	}
	
	int Ship::getSize(){
		return size;
	}

	void Ship::die(){
		dead = true;
		x = -100;
		y = -100;
		dx = 0;
		dy = 0;
		deadTimer = SDL_GetTicks() + deadTime;

	}

	bool Ship::isDead(){
		return dead;
	}

	
	void Ship::spawnShip(){
		if (SDL_GetTicks() > deadTimer){
			dead = false;
			x = 400;
			y = 300;
			dx = 0;
			dy = 0;
			angle = pi;	
			reloadTimer = SDL_GetTicks();
		}
	}
	
	void Ship::forceSpawn(){
		dead = false;
		x = 400;
		y = 300;
		dx = 0;
		dy = 0;
		angle = pi;
		reloadTimer = SDL_GetTicks();
	}

	void Ship::safeSpawn(std::list<Rock> rocks){
		bool spawn = true;
		float distance =0;
		float rockX = 0;
		float rockY = 0;
		float centreX = 300;
		float centreY = 200;
		for (std::list<Rock>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){
			rockX = itR->getX();
			rockY = itR->getY();
			distance = sqrt(pow((rockX - centreX),2) + pow((rockY - centreY),2));
			if(distance < 50){
				spawn = false;
			}
		}

		if(spawn)
			spawnShip();
	}

	void Ship::draw(){
	
		glColor3f(.9, .9, .9);

		glBegin(GL_LINES);
			glVertex2f(getCoords(2,0), getCoords(2,1));
			glVertex2f(getCoords(0,0), getCoords(0,1));
		glEnd();


		glBegin(GL_LINES);
			glVertex2f(getCoords(0,0), getCoords(0,1));
			glVertex2f(getCoords(1,0), getCoords(1,1));
		glEnd();

		glColor3f(.8, .1, .1);
		glBegin(GL_LINES);
			glVertex2f(getCoords(1,0), getCoords(1,1));
			glVertex2f(getCoords(2,0), getCoords(2,1));
		glEnd();

		glColor3f(.9,.9,.9);
	}
