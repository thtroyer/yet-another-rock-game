
/*
** YARG Game.cpp 
**	Copyright Tom Troyer 2010 (tom.troyer@gmail.com)
** Released under GPLv3
**
** Here's where most of the game's activities happen
** i.e. game loop, keyboard events, etc. 
*/

#include "Game.h"
	
	Game::Game(){
		
		/*
		** Initialize Game variables
		*/	
		keyDown = new bool[323];
		for(int i=0; i<323; i++)
			keyDown[i] = false;
		line = new MyLine[2];
	}
	Game::~Game(){
		delete [] keyDown;
		delete [] line;
	}
	
	bool Game::running(){
		return gameRunning;
	}
	
	bool Game::init(){
		srand(time(NULL));

		if (SDL_Init(SDL_INIT_VIDEO) != 0){
			std::cout << "Unable to initialize SDL: " << SDL_GetError()
				     << std::endl;
			return 1; //error, die
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_OPENGL);  
	
		glDisable(GL_DEPTH_TEST);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		SDL_GL_SwapBuffers();

		
		rate = 60;	
		SDL_initFramerate(&fpsm);
		SDL_setFramerate(&fpsm,rate);
	
		time (&time1);
		std::cout << std::endl;

		
		player.calcPoints();
		
	   gameRunning = true;
	  	nextLevel = true;
	   	
	   player.forceSpawn();
	
		return 0;
	}

	void Game::loop(){
		while(gameRunning){
			levelEvents();
				
			frames++;	
			if(frames>1000){
				time(&time2);
				frames=0;
				std::cout << 1000.0/(difftime (time2, time1)) << "fps" << std::endl;
				time (&time1);
			}
	
			collisionEvents();
			//playerEvents();
			keyEvents();
			render();
		}
	}

	void Game::drawInterface(){
	}

	void Game::levelEvents(){
		if (nextLevel){
				nextLevel = false;
				level.nextLevel();
				shots.clear();
				player.safeSpawn(rocks);
				std::cout << "level: " << level.getLevel() << std::endl << "rocks: " << level.getRocks();
				std::cout << std::endl;
			
				for (int i=0; i<level.getRocks(); i++)
				{
					rocks.push_back(Rock((rand()%800),(rand()%600),((float(rand()) / float((RAND_MAX+1))) + 0.5),(float(rand()) / float((RAND_MAX+1)) + 0.5),40,(rand()%4)+12));
				}
		}
		moveShots();
		moveRocks();
		movePlayer();
	}

	void Game::moveShots(){
		for (std::list<Shot>::iterator it = shots.begin(); it != shots.end(); it++){
			if(it->checkAge()){
					it->move();
					it->wrap();
					it->incAge();
			}
			else
				it = shots.erase(it);
		}
	}

	void Game::moveRocks(){
		for (std::list<Rock>::iterator it = rocks.begin();
		     it != rocks.end();
			  it++){
			it->move();
			it->wrap();
		}

	}

	void Game::movePlayer(){
		
		if (player.isDead())
			player.safeSpawn(rocks);

		player.moveShip();
		player.wrap();
		player.calcPoints();
		
	}


	void Game::collisionEvents(){

		/*
		** Check for collision between rocks and shots
		*/

		for (std::list<Shot>::iterator itS = shots.begin(); itS != shots.end(); itS++){
			for (std::list<Rock>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){
				float shotX = itS->getX();
				float shotY = itS->getY();
				float rockX = itR->getX();
				float rockY = itR->getY();
				float distance = sqrt(pow((shotX-rockX),2) + (pow((shotY-rockY),2)));

				if(distance < itR->getMaxRadius()){
					int rockSize = itR->getSize();

					if (rockSize > 20){
						for(int i=0; i<randomInt(1,3); i++){
							float speed = randomFloat(0,2);
							float angle = randomFloat(0,pi);
							
							rocks.push_back(Rock((rockX + rand()%10),
						   	                  (rockY + rand()%10),
														(itR->getDx() + (speed * cos(angle))),
														(itR->getDy() + (speed * sin(angle))),											
														(rockSize - 10),
														(rand()%4)+12));
						}
					}		
					itR = rocks.erase(itR);
					itS = shots.erase(itS);
					break;
				}
			}
		}

		/*
		** Collision detection for player
		*/
		int i = 0;
		for (std::list<Rock>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){
			float rockX = itR->getX();
			float rockY = itR->getY();
			float playerX = player.getX();
			float playerY = player.getY();
			float distance = sqrt(pow((playerX-rockX),2) + (pow((playerY-rockY),2)));
			if(distance < (itR->getSize() + player.getSize())){
				player.die();
			}
			i++;
		}

		if(i==0) //list is empty, end level
			nextLevel = true;
	}

		
	void Game::keyEvents(){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			switch (event.type){ 
				case SDL_KEYDOWN:
					//std::cout << "keypress: " << SDL_GetKeyName(event.key.keysym.sym);
					//std::cout << " #: " << event.key.keysym.sym << std::endl; 
					keyDown[event.key.keysym.sym] = true;
					break;
				case SDL_KEYUP:
					//std::cout << "keyup: " << SDL_GetKeyName(event.key.keysym.sym);
					//std::cout << " #: " << event.key.keysym.sym << std::endl; 
					keyDown[event.key.keysym.sym] = false;
					break;
				
			}
		}



		for(int i=0; i<323; i++){  
			if(keyDown[i]==true){
				switch (i){
					case 113: //q, quit
						gameRunning = !gameRunning;
						break;
					case 273: //up
						player.addThrust(1);
						line[0].setY(0,((int)line[0].getY(0))-1);	
						break;
					case 274: //down
						player.addThrust(-1);
						line[0].setY(0,((int)line[0].getY(0))+1);	
						break;
					case 275: //right
						player.rotateShip(pi/25);
						line[0].setX(0,((int)line[0].getX(0))+1);	
						break;
					case 276: //left
						player.rotateShip(-pi/25);
						line[0].setX(0,((int)line[0].getX(0))-1);	
						break;
					case 122:
						if(player.fire()){
							shots.push_back(Shot(&player, 2.5, 500));
						}
						break;
				}	
			}
		}
	}
	

	void Game::render(){
		glClear(GL_COLOR_BUFFER_BIT);
		
		//drawInterface();	
	
		player.draw();
	
		/************
		*Draw shots *
		*************/
		for (std::list<Shot>::iterator it = shots.begin(); it != shots.end(); it++){
			glBegin(GL_POLYGON);				
				glVertex2f(it->getX() - 1, it->getY() + 1);
				glVertex2f(it->getX() + 1, it->getY() + 1);
				glVertex2f(it->getX() + 1, it->getY() - 1);
				glVertex2f(it->getX() - 1, it->getY() - 1);
			glEnd();
		}

	

		/************
		*Draw rock *
		*************/

		for (std::list<Rock>::iterator it = rocks.begin(); it != rocks.end(); it++){
			glBegin(GL_POLYGON);
			for (int i = 0; i < it->getNumPoints(); i++){
				glVertex2f((it->getX() + it->point[i].getX()), (it->getY() + it->point[i].getY()));
			}
			glEnd();
		}
			
		/************
		*Display and delay *
		*************/
		SDL_GL_SwapBuffers();
		SDL_framerateDelay(&fpsm);
	}

