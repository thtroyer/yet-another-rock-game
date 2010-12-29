/*
** YARG Rock.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
*/

#include "Rock.h"
#include "random.h"
	
	Rock::Rock(){
		x = 200;
		y = 200;
		numPoints = 5;
		size = 40;
		point = new MyPoint[5];
		for(int i=0; i<5; i++){
			std::cout << "random = " << (rand() % 10);
			//point[i].setX(x + ((size) * cos(i * 2 * pi / 5)) + ((size) * rand() % 10));
			//point[i].setY(y + ((size) * sin(i * 2 * pi / 5)) + ((size) * rand() % 10));
			point[i].setX(x + ((size) * cos(i * 2 * pi / 5)) + ((size) * randomFloat(1,1)));
			point[i].setY(y + ((size) * sin(i * 2 * pi / 5)) + ((size) * randomFloat(1,1)));

			std::cout << "point " << i << " x = " << point[i].getX() << std::endl;
		}

	}

	Rock::Rock(float xCoord, float yCoord, float xSpeed, float ySpeed, int rockSize, int rockPoints, float rotAngle, b2World* world){
		
		
		
		
		//initialize rock variables;
		x = xCoord;
		y = yCoord;
		dx = xSpeed;
		dy = ySpeed;
		size = rockSize;
		numPoints = rockPoints;
		maxRadius = 0;
		//dAngle = randomFloat(-1,1) * pi/50;
		dAngle = rotAngle;	
		_world = world;	

		point = new MyPoint[numPoints];
		
		//BodyDef 
		//  (create definition, give to world, recieve body object)
		
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x/pixelRatio ,y/pixelRatio);
		body = world->CreateBody(&bodyDef);
		
		b2Vec2 initSpeed;
		initSpeed.Set(dx * 5/ pixelRatio, dy * 5 / pixelRatio);
		
		body->SetLinearVelocity(initSpeed);
		//body->SetAngularVelocity(dAngle);
		
		//Setup shape
		b2PolygonShape rockShape;
		b2Vec2 verts[numPoints];
		

		for(int i=0; i<numPoints; i++){ //loop through points
			//set coords
			//point[i].setX(randomFloat(.7,.701) * size * (cos(i * 2 * pi / numPoints)));
			//point[i].setY(randomFloat(.7,.701) * size * (sin(i * 2 * pi / numPoints)));
			
			
			point[i].setX(randomInt(850,1100)/1000. * size * (cos(i * 2 * pi / numPoints)));
			point[i].setY(randomInt(850,1100)/1000. * size * (sin(i * 2 * pi / numPoints)));
			float isMax = sqrt(pow(point[i].getX(),2) + pow(point[i].getY(),2));
			if(isMax > maxRadius)
				maxRadius = isMax;
			
			
			verts[i].Set((float) (point[i].getX() / pixelRatio) , (float) (point[i].getY() / pixelRatio));
		}
		
		rockShape.Set(verts, numPoints);
		b2FixtureDef rockFixtureDef;
		
		rockFixtureDef.shape = &rockShape;
		//rockFixtureDef.SetFixedRotation(false);
		rockFixtureDef.density = 1.0f;
		rockFixtureDef.friction = 0.9f;
		rockFixtureDef.restitution = 0.8f;
		
		body->CreateFixture(&rockFixtureDef);

		

		//std::cout << "Rock created @ (" << x << "," << y;
		//std::cout << ") , [" << dx << "," << dy << "]" << std::endl;
	}


	
	Rock::Rock(int m, int n){ //(numPoints, size)
		numPoints = m;
		size = n;
		point = new MyPoint[m];
	}
	
	Rock::~Rock(){
		std::cout << "Rock deconstructor " << std::endl;
		_world->DestroyBody(body);
	}
	
	void Rock::draw(){ //deprecated
		/*glColor4f(0.9, 0.2, 0.2, 1.0);
		glBegin(GL_POLYGON);
			for (int i = 0; i < numPoints; i++){
				glVertex2f((x + point[i].getX()), y + point[i].getY());
			}
		glEnd();*/
		//std::cout << body->GetAngle() << std::endl;
		
		
		b2PolygonShape* shape;
		shape = (b2PolygonShape*)(body->GetFixtureList())->GetShape();
		b2Vec2 vert;
		b2Vec2 bodyCenter;
		
		glColor4f(0.0, 0.9, 0.0, 0.5);		
		glBegin(GL_POLYGON);
		
		float pointX;
		float pointY;
		float pointLength;
		float angle;
		
			for (int i = 0; i < numPoints; i++){
				vert = shape->GetVertex(i);
				
				pointX = vert.x;
				pointY = vert.y;
				pointLength = sqrt(pow(pointX,2) + pow(pointY,2));
				angle = atan2(pointY, pointX) + body->GetAngle();
				//body->GetAngle();
				
				pointX = pointLength * cos(angle);
				pointY = pointLength * sin(angle);
				
				
				bodyCenter = body->GetWorldCenter();
				glVertex2f((bodyCenter.x + pointX) * pixelRatio, (bodyCenter.y + pointY) * pixelRatio);
			}
		glEnd();
		
		//temp:
		x = bodyCenter.x * pixelRatio;
		y = bodyCenter.y * pixelRatio;
		
	}


	void Rock::draw(Ship& player){
		
		//std::cout << "Rock X: " << x << " Y: " << y << std::endl;	

		b2PolygonShape* shape;
		shape = (b2PolygonShape*)(body->GetFixtureList())->GetShape();
		b2Vec2 vert;
		b2Vec2 bodyCenter;
		
		glColor4f(0.9, 0.9, 0.9, 1.0);		
		glBegin(GL_POLYGON);
		
		float pointX;
		float pointY;
		float pointLength;
		float angle;
		


			for (int i = 0; i < numPoints; i++){
				vert = shape->GetVertex(i);
				
				pointX = vert.x;
				pointY = vert.y;
				pointLength = sqrt(pow(pointX,2) + pow(pointY,2));
				angle = atan2(pointY, pointX) + body->GetAngle();
				//body->GetAngle();
				
				pointX = pointLength * cos(angle);
				pointY = pointLength * sin(angle);
				

				
				bodyCenter = body->GetWorldCenter();
				glVertex2f(
					((bodyCenter.x + pointX) * pixelRatio) - player.getX() + 400 ,
					((bodyCenter.y + pointY) * pixelRatio) - player.getY() + 300
				);
			}
		glEnd();

		//std::cout << "X: " << ((bodyCenter.x + pointX + player.getX()/pixelRatio) * pixelRatio) << std::endl;
		//std::cout << "Y: " << ((bodyCenter.y + pointY + player.getY()/pixelRatio) * pixelRatio) << std::endl;

		//temp:
		x = bodyCenter.x * pixelRatio;
		y = bodyCenter.y * pixelRatio;
		
	}

	float Rock::getMaxRadius(){
		return maxRadius; 
	}
	void Rock::move(float deltaTime){
		x = x + (dx * deltaTime * deltaTimeConst);
		y = y + (dy * deltaTime * deltaTimeConst);

		rotate(deltaTime);
	}

	void Rock::recalc(){
		for (int i=0; i<numPoints; i++){
			point[i].setX(point[i].getX()+dx);
			point[i].setY(point[i].getY()+dy);
		}
	}


	void Rock::wrap(){
	b2Vec2 trans;
	b2Vec2 bodyCenter;
	bodyCenter = body->GetWorldCenter();
	
		if(bodyCenter.x > PLAYAREA_WIDTH){
			x = 1;
			trans.Set((float)PLAYAREA_WIDTH/pixelRatio, y);
			body->SetTransform(trans, 0);
		}
		else if (bodyCenter.x < 0){
			x = PLAYAREA_WIDTH -1;
			trans.Set((float)(-1 * PLAYAREA_WIDTH/pixelRatio),y);
			body->SetTransform(trans, 0);
		}

		if(bodyCenter.y > PLAYAREA_HEIGHT){
			y = 1;
			trans.Set(x,(float)PLAYAREA_HEIGHT/pixelRatio);
			body->SetTransform(trans, 0);
		}
		else if (bodyCenter.y < 0){
		
			y = PLAYAREA_HEIGHT -1;
			trans.Set(x,(float)(-1 * PLAYAREA_HEIGHT/pixelRatio));
			body->SetTransform(trans, 0);
		}
	}

	void Rock::rotate(float deltaTime){
		for(int i=0; i<numPoints; i++){
			float pointX = point[i].getX();
			float pointY = point[i].getY();
			float pointLen = sqrt(pow(pointX,2) + pow(pointY,2));

			float angle = atan2(pointY, pointX);
			
			angle = angle + dAngle * deltaTimeConst;

			pointX = pointLen * cos(angle);
			pointY = pointLen * sin(angle);

			point[i].setX(pointX);
			point[i].setY(pointY);
		}
	}

	void Rock::setdAngle(float angle){
		dAngle = angle;
	}

	float Rock::getdAngle(){
		return dAngle;
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
	
	b2Body* Rock::getBody(){
		return body;
	}

