
/*
** YARG Rock.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Rock.h"

	Rock::Rock(){
		x = 200;
		y = 200;
		numPoints = 5;
		size = 40;
		point = new MyPoint[5];
		for(int i=0; i<5; i++){
			std::cout << "random = " << (rand() % 10);
			point[i].setX(x + ((size) * cos(i * 2 * pi / 5)) + ((size) * rand() % 10));
			point[i].setY(y + ((size) * sin(i * 2 * pi / 5)) + ((size) * rand() % 10));

			std::cout << "point " << i << " x = " << point[i].getX() << std::endl;
		}

	}

	Rock::Rock(float xCoord, float yCoord, float xSpeed, float ySpeed, int rockSize, int rockPoints){
		//initialize rock variables;
		x = xCoord;
		y = yCoord;
		dx = xSpeed;
		dy = ySpeed;
		size = rockSize;
		numPoints = rockPoints;
		maxRadius = 0;

		point = new MyPoint[numPoints];

		for(int i=0; i<numPoints; i++){ //loop through points
			//set coords
			point[i].setX(randomInt(-8,8) + size * (cos(i * 2 * pi / numPoints)));
			point[i].setY(randomInt(-8,8) + size * (sin(i * 2 * pi / numPoints)));
			float isMax = sqrt(pow(point[i].getX(),2) + pow(point[i].getY(),2));
			if(isMax > maxRadius)
				maxRadius = isMax;
		}
		std::cout << "Rock created @ (" << x << "," << y;
		std::cout << ") , [" << dx << "," << dy << "]" << std::endl;
	}

	
	Rock::Rock(int m, int n){ //(numPoints, size)
		numPoints = m;
		size = n;
		point = new MyPoint[m];
	}
	
	float Rock::getMaxRadius(){
		return maxRadius; 
	}
	void Rock::move(){
		x = x + dx;
		y = y + dy;
		//recalc();
	}

	void Rock::recalc(){
		for (int i=0; i<numPoints; i++){
			point[i].setX(point[i].getX()+dx);
			point[i].setY(point[i].getY()+dy);
		}
	}


	void Rock::wrap(){
		if(x > PLAYAREA_WIDTH)
			x = 1;
		else if (x < 0)
			x = PLAYAREA_WIDTH -1;

		if(y > PLAYAREA_HEIGHT)
			y = 1;
		else if (y < 0)
			y = PLAYAREA_HEIGHT -1;

	}

	void Rock::setX(float m){
		x = m;
	}
	
	void Rock::setY(float m){
		y = m;
	}

	float Rock::getX(){
		return x;
	}
	
	float Rock::getY(){
		return y;
	}

	int Rock::getNumPoints(){
		return numPoints;
	}
	
	int Rock::getSize(){
		return size;
	}

	float Rock::getDx(){
		return dx;
	}
	
	float Rock::getDy(){
		return dy;
	}

