/*
** YARG MyLine.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** This is a bit of a messy left-over from original prototyping.
** It works without complaining, so I haven't revisited it.
*/

#include "MyLine.h"

		MyLine::MyLine(){	
			point = new MyPoint[2];
		}
		MyLine::~MyLine(){
			if(point!=0){
				delete [] point;
				point = 0;
			}
		}

		void MyLine::moveLine(){
			for(int i=0; i<2; i++){
				if(point[i].getUp())
					point[i].setY(point[i].getY()+1);
				else
					point[i].setY(point[i].getY()-1);
				if(point[i].getRight())
					point[i].setX(point[i].getX()+1);
				else
					point[i].setX(point[i].getX()-1);
			}
		}
		float MyLine::getX(int m){
			return point[m].getX();
		}
		float MyLine::getY(int m){
			return point[m].getY();
		}
		void MyLine::setX(int m, float n){
			point[m].setX(n);
		}
		void MyLine::setY(int m, float n){
			point[m].setY(n);
		}
