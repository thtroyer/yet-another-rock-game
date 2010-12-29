
#include "WarpEffect.h"

WarpEffect::WarpEffect(){
	x = 0;
	y = 0;
	age = 0;
	radius = 10;
	active = false;
	Clock = new sf::Clock();
	Clock->Reset();
	//lastTime = 0;
}

WarpEffect::WarpEffect(float intX, float intY){
	x = intX;
	y = intY;
	age = 0;
	radius = 10;	
}

void WarpEffect::setAge(int mAge){
	maxAge = mAge;
	halfLife = maxAge/2;
}

void WarpEffect::setHalfLife(int mHalf){
	halfLife = mHalf;
	maxAge = halfLife * 2;
}

void WarpEffect::draw(float mX, float mY){
	//dRadius = 1/x ?
	//Radius = ln(abs(age)) + C
	
	float X = x - mX + 400;
	float Y = y - mY + 300;
	
	//std::cout << "Age: " << age << std::endl;
	if(!active){
		return;
	}
	
	if(age>1500){
		return;
	}
	
	float opacity;
	
	radius = 5 * log(abs((age/5)-(halfLife/5))) + 4;
	 
	//opacity = 5/radius;
	//if(opacity >= 1.0)
	//	opacity = 1;
	
	opacity = -1/1500.0 * age + 1;
	//std::cout << "op: " << opacity << std::endl;
	
	//opacity = 1.0;
	
	//std::cout << "Radius: " << radius << std::endl;
	glColor4f(0.0, 0.1, 0.85, opacity);
	glBegin(GL_LINE_LOOP);
	for(float angle=0; angle<2*pi; angle+=.17){ //.17 ~= 10 degrees
		glVertex2f(X + sin(angle) * radius, Y + cos(angle) * radius);
	}
	glEnd();
	
	radius = 5 * log(abs(((age-100)/5)-(halfLife/5))) + 4;
	
	glBegin(GL_LINE_LOOP);
	for(float angle=0; angle<2*pi; angle+=.17){ //.17 ~= 10 degrees
		glVertex2f(X + sin(angle) * (radius), Y + cos(angle) * (radius));
	}
	glEnd();

	radius = 5 * log(abs(((age-300)/5)-(halfLife/5))) + 4;
	
	glBegin(GL_LINE_LOOP);
	for(float angle=0; angle<2*pi; angle+=.17){ //.17 ~= 10 degrees
		glVertex2f(X + sin(angle) * (radius), Y + cos(angle) * (radius));
	}
	glEnd();
}

//void WarpEffect::incAge(Uint32 deltaTime){
void WarpEffect::incAge(){
	//deltaTime = SDL_GetTicks() - lastTime;
	//lastTime = SDL_GetTicks();
	deltaTime = (Clock->GetElapsedTime() * 1000) - lastTime;
	lastTime = Clock->GetElapsedTime() * 1000;

	//std::cout << "deltaTime: " << deltaTime << std::endl;
	age += deltaTime;
	//std::cout << "age: " << age << std::endl;
}

void WarpEffect::initiate(float intX, float intY, int inHalfLife){
	age = 0;
	x = intX;
	y = intY;
	halfLife = inHalfLife;
	maxAge = halfLife * 2;
	active = true;
}

float WarpEffect::getX(){
	return x;
}

float WarpEffect::getY(){
	return y;
}
