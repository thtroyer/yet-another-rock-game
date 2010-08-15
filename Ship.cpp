
/*
** YARG Ship.h
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Ship.h"

	Ship::Ship(){
		Clock = new sf::Clock();
		Clock->Reset();
		deadTimer = Clock->GetElapsedTime();
		spawnTimer = Clock->GetElapsedTime();

		//deadTimer = SDL_GetTicks();
		//spawnTimer = SDL_GetTicks();
		//deadTime = deadTimer;
		active = false;
		//safeSpawn();
		spawnShip();
		point = new MyPoint[3];
		size = 8;
		angle = pi;
		maxThrust = .1;
		dx = 0;
		dy = 0;
		speed = 0;
		
		
		reloadTime = .200;
		//reloadTimer = SDL_GetTicks();
		reloadTimer = new float[10];
		for (int i = 0; i<10; i++){
			reloadTimer[i] = Clock->GetElapsedTime();
		}
		
		warpSpawn = new WarpEffect();

		deadTime = 3;

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

	void Ship::rotateShip(float rad, float deltaTime){
		angle = angle + (rad * deltaTime * deltaTimeConst);
	}

	void Ship::moveShip(float deltaTime){
		x = x + (dx * deltaTime * deltaTimeConst);
		y = y + (dy * deltaTime * deltaTimeConst);
	}

	void Ship::addThrust(int m, float deltaTime){
		if(!dead){
			thrust = maxThrust * m * (deltaTime * deltaTimeConst);
			dx = dx - (thrust * sin(angle)) * .8;
			dy = dy + (thrust * cos(angle)) * .8;
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

	bool Ship::isReloaded(){ //deprecated
		//if (SDL_GetTicks() >= reloadTimer)
		if(Clock->GetElapsedTime() >= reloadTimer[0])
			return true;
		return false;
	}
	
	bool Ship::isReloaded(Shot* shot){
		if(Clock->GetElapsedTime() >= reloadTimer[shot->getType()])
			return true;
		return false;
	}

	bool Ship::fire(){ //deprecated
		if(isReloaded() && !isDead()){
			//reloadTimer = SDL_GetTicks() + reloadTime;
			//reloadTimer[0] = Clock->GetElapsedTime() + reloadTime[0];
			return true;
		}
		return false;
	}

	bool Ship::fire(Shot* shot){
		if(isReloaded(shot) && !isDead()){
			reloadTimer[shot->getType()] = Clock->GetElapsedTime() + shot->getReloadTime();
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
		active = false;
		x = -100;
		y = -100;
		dx = 0;
		dy = 0;
		//deadTimer = SDL_GetTicks() + deadTime;
		deadTimer = Clock->GetElapsedTime() + deadTime;

	}

	bool Ship::isDead(){
		return (dead || !active);
		//return dead;
	}

	
	void Ship::spawnShip(){
			dead = false;
			x = 400;
			y = 300;
			dx = 0;
			dy = 0;
			angle = pi;	
			//reloadTimer = SDL_GetTicks();
			//spawnTimer = SDL_GetTicks() + 250;

			//reloadTimer = Clock->GetElapsedTime();
			spawnTimer = Clock->GetElapsedTime() + .250;

	}
	
	void Ship::spawnShip(float spawnX, float spawnY){
		dead = false;
		x = spawnX;
		y = spawnY;
		dx = 0;
		dy = 0;
		angle = (randomFloat(0,2*pi));	
		//reloadTimer = SDL_GetTicks();
		//spawnTimer = SDL_GetTicks() + 250;
		//reloadTimer = Clock->GetElapsedTime();
		spawnTimer = Clock->GetElapsedTime() + .250;

	}
	
	void Ship::forceSpawn(){
		dead = false;
		active = true;
		x = 400;
		y = 300;
		dx = 0;
		dy = 0;
		angle = pi;
		//reloadTimer = SDL_GetTicks();
		//reloadTimer = Clock->GetElapsedTime();	
	}

	void Ship::safeSpawn(std::list<Rock*> rocks){
		//std::cout << "dead: " << dead << " active: " << active << std::endl;
		//std::cout << "sdlticks: " << SDL_GetTicks() << " timer: " << spawnTimer << std::endl;
		
		if(!dead && !active){
			//std::cout << "1" << std::endl;
			//if(SDL_GetTicks() > spawnTimer){
			if(Clock->GetElapsedTime() > spawnTimer){
				active = true;
			}
			return;
		}
		
		//if (!(SDL_GetTicks() > deadTimer)){
		if(!(Clock->GetElapsedTime() > deadTimer)){
			return;
		}
	
		bool spawned = false;
		float distance =0;
		float rockX = 0;
		float rockY = 0;
		float minSpawnX = 150;
		float maxSpawnX = 650;
		float minSpawnY = 200;
		float maxSpawnY = 400;
		
		float checkSpawnX;
		float checkSpawnY;
	
		bool rockFlag;

		while(!spawned){
			rockFlag = false;
			checkSpawnX = randomFloat(minSpawnX, maxSpawnX);
			checkSpawnY = randomFloat(minSpawnY, maxSpawnY);
		
			for (std::list<Rock*>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){
				rockX = (*itR)->getX();
				rockY = (*itR)->getY();
				distance = sqrt(pow((rockX - checkSpawnX),2) + pow((rockY - checkSpawnY),2));
				if(distance < 50){
					rockFlag = true;
				}
			}
			if(!rockFlag){
				spawned = true;
			}
		}

		if(spawned){
			spawnShip(checkSpawnX, checkSpawnY);
			warpSpawn->initiate(checkSpawnX, checkSpawnY, 250);
		}
			
	}

	void Ship::draw(){
		
		warpSpawn->incAge();
		warpSpawn->draw();
		
		if(!active){
			return;
		}
		
		//glColor3f(.9, .9, .9);
		
		glColor4f(0.9, 0.9, 0.9, 1.0);
		
		glBegin(GL_LINES);
			glVertex2f(getCoords(2,0), getCoords(2,1));
			glVertex2f(getCoords(0,0), getCoords(0,1));
		glEnd();


		glBegin(GL_LINES);
			glVertex2f(getCoords(0,0), getCoords(0,1));
			glVertex2f(getCoords(1,0), getCoords(1,1));
		glEnd();

		glColor4f(0.8, 0.1, 0.1, 1.0);
		//glColor3f(.8, .1, .1);
		glBegin(GL_LINES);
			glVertex2f(getCoords(1,0), getCoords(1,1));
			glVertex2f(getCoords(2,0), getCoords(2,1));
		glEnd();

		
	}
