
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

	}

	Game::~Game(){

	}

	bool Game::running(){
		return gameRunning;
	}


	bool Game::init(){

		

		//box2D init
		
		b2Vec2 gravity(0.0f, 0.0f);
		bool doSleep = false;
		
		world = new b2World(gravity, doSleep);
		
		createWalls();

		//SFML init

		App = new sf::RenderWindow(sf::VideoMode(800,600,24), "yarg");
		Clock = new sf::Clock();

		App->SetFramerateLimit(80);

		//Correct for this later
		App->PreserveOpenGLStates(true);

		glClearDepth(1.f);
		glClearColor(0.f,0.f,0.f,0.f);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//test = new WarpEffect(50,50);

		statsFont = new sf::Font();
		centerFont = new sf::Font();

		statsFont->LoadFromFile("cour.ttf",15);
		centerFont->LoadFromFile("cour.ttf",30);

		strScore = new sf::String();
		strMessage = new sf::String();

		strScore->SetFont(*statsFont);
		strMessage->SetFont(*centerFont);

		Clock->Reset();
		deltaTime = 0;

		srand(time(NULL));



		std::cout << std::endl;

		//Game init
		
		KEY_UP = false;
		KEY_DOWN = false;
		KEY_RIGHT = false;
		KEY_LEFT = false;
		KEY_SHOOT = false;
		KEY_BOMB = false;
		KEY_JUMP = false;

		player.calcPoints();

		newGame();

		player.forceSpawn();

		return 0;
	}
	
	void Game::createWalls(){
		b2BodyDef bodyDef;
		b2Body* wall;
		bodyDef.type = b2_staticBody;
		b2PolygonShape wallShape;
		b2FixtureDef wallFix;
		wallFix.density=0.0f;
		wallFix.friction = 0.6f;
		wallFix.restitution = 0.9f;
		
		wallShape.SetAsBox(1600/pixelRatio,2/pixelRatio);		
		
		bodyDef.position.Set((WINDOW_WIDTH/2)/pixelRatio , WINDOW_HEIGHT/pixelRatio);
		
		wall = world->CreateBody(&bodyDef);
		wallFix.shape= &wallShape;
		wall->CreateFixture(&wallFix);	
		
	    bodyDef.position.Set((WINDOW_WIDTH/2)/pixelRatio , 0/pixelRatio);
		wall = world->CreateBody(&bodyDef);
	
		wall = world->CreateBody(&bodyDef);
		wallFix.shape= &wallShape;
		wall->CreateFixture(&wallFix);	
		
		
		wallShape.SetAsBox(2/pixelRatio,1200/pixelRatio);	
		
		bodyDef.position.Set((WINDOW_WIDTH)/pixelRatio , (WINDOW_HEIGHT/2)/pixelRatio);
		
		wall = world->CreateBody(&bodyDef);
		wallFix.shape= &wallShape;
		wall->CreateFixture(&wallFix);	
		
		bodyDef.position.Set(0/pixelRatio , (WINDOW_HEIGHT/2)/pixelRatio);
		
		wall = world->CreateBody(&bodyDef);
		wallFix.shape= &wallShape;
		wall->CreateFixture(&wallFix);	
		
		//b2Vec2 initSpeed;
		//initSpeed.Set(dx * 5/ pixelRatio, dy * 5 / pixelRatio);
		
		//body->SetLinearVelocity(initSpeed);
		//body->SetAngularVelocity(dAngle);
		
		//Setup shape
;
		
	}

	void Game::loop(){

		while(App->IsOpened()){

			//calculate deltaTime (time since last frame)
			//  (deltaTime originally designed for miliseconds)
			deltaTime = Clock->GetElapsedTime() * 1000;
			Clock->Reset();

			if(deltaTime > 5000){ //this shouldn't happen
				deltaTime = 1;
				std::cout << "Error in deltaTime" << std::endl;
			}
			
			world->Step(deltaTime/1000, 6, 3);
			world->ClearForces();

			levelEvents();

			frames++;

			collisionEvents();
			keyEvents();


			render();
		}
	}

	void Game::newGame(){
	   gameRunning = true;
	  	nextLevel = true;

		score = 0;
		lives = 5;
	}


	void Game::drawInterface(){
	}

	void Game::drawFont(){

		sf::String drawString;
		drawString.SetFont(*statsFont);
		drawString.SetSize(15);

		drawString.Move(10.f,0.f);


		std::stringstream strScore;
		strScore << "Score: " << score;
		drawString.SetText(strScore.str().c_str());

		App->Draw(drawString);

		std::stringstream strLives;
		strLives << "Lives: " << lives;

		drawString.SetText(strLives.str().c_str());

		drawString.Move(0.f,15.9f);

		App->Draw(drawString);

		if(lives<=0){
			drawString.SetFont(*centerFont);
			drawString.SetSize(25);
			drawString.SetPosition(325.0f, 250.0f);
			drawString.SetText("Game over");
			App->Draw(drawString);
			std::stringstream strScore;
			strScore << "Score: " << score;
			drawString.SetPosition(325.0f,285.0f);
			drawString.SetText(strScore.str().c_str());
			App->Draw(drawString);
		}

	}

	void Game::levelEvents(){
		if (nextLevel){
				nextLevel = false;
				level.nextLevel();
				shots.clear();
				player.safeSpawn(rocks);
				std::cout << "level: " << level.getLevel() << std::endl << "rocks: " << level.getRocks();
				std::cout << std::endl;

				for (int i=0; i<level.getRocks(); i++){
					rocks.push_back(new Rock(randomInt(50,750),randomInt(5,550), randomFloat(-2,2), randomFloat(-2,2), 40, randomInt(5,8), randomFloat(-2,2)*pi/50, world));
				}
		}
		moveShots();
		moveRocks();
		movePlayer();
	}

	void Game::moveShots(){
		for (std::list<Shot*>::iterator it = shots.begin(); it != shots.end(); it++){
			if((*it)->checkAge()){
					(*it)->move(deltaTime);
					(*it)->wrap();
					(*it)->incAge(deltaTime);
			}
			else{
				it = shots.erase(it);
				break;
			}
		}
	}

	void Game::moveRocks(){
		for (std::list<Rock*>::iterator it = rocks.begin(); it != rocks.end(); it++){
			(*it)->move(int(deltaTime));
			(*it)->wrap();
		}

	}

	void Game::movePlayer(){

		if (player.isDead() && (lives > 0))
			player.safeSpawn(rocks);

		if(player.isJumping()){
			player.returnJump();
		}

		player.moveShip(deltaTime);
		player.wrap();
		player.calcPoints();

	}


	void Game::collisionEvents(){

		/*
		** Check for collision between rocks and shots
		*/

		std::list<Shot*>::iterator itS = shots.begin();

		bool breakOut = false;

		for (std::list<Shot*>::iterator itS = shots.begin(); itS != shots.end(); itS++){
			for (std::list<Rock*>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){
				float shotX = (*itS)->getX();
				float shotY = (*itS)->getY();
				float rockX = (*itR)->getX();
				float rockY = (*itR)->getY();
				float distance = sqrt(pow((shotX-rockX),2) + (pow((shotY-rockY),2)));
				/*std::cout << "shotX = " << shotX << std::endl;
				std::cout << "shotY = " << shotY << std::endl;
				std::cout << "rockX = " << rockX << std::endl;
				std::cout << "rockY = " << rockY << std::endl;
				std::cout << "distance = " << distance << std::endl;*/

				if(distance < (*itR)->getMaxRadius()){
					int rockSize = (*itR)->getSize();

					if (rockSize > 20){
						for(int i=0; i<randomInt(1,3); i++){
							float xSpeed = randomFloat(-30,30);
							float ySpeed = randomFloat(-30,30);
							float angle = randomFloat(0,pi);

							rocks.push_back(new Rock((rockX + randomInt(-20,20)),
						   	                         (rockY + randomInt(-20,20)),
												     ((*itR)->getDx() + (xSpeed * cos(angle))),
												     ((*itR)->getDy() + (ySpeed * sin(angle))),
												     (rockSize - 10),
												     (randomInt(6,8)),
							                         ((*itR)->getdAngle() + randomFloat(-2,2)*pi/50), 
							                         world));
						}
					}
					score += 100;
					world->DestroyBody((*itR)->getBody());
					itR = rocks.erase(itR);
					itS = shots.erase(itS);
					breakOut = true;

					if(breakOut){
						break;
					}
				}

			}
			if(breakOut){
					break;
			}
		}

		/*
		** Collision detection for player
		*/
		int i = 0;
		for (std::list<Rock*>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){

			float rockX = (*itR)->getX();
			float rockY = (*itR)->getY();
			float playerX = player.getX();
			float playerY = player.getY();
			float distance = sqrt(pow((playerX-rockX),2) + (pow((playerY-rockY),2)));
			if(distance < ((*itR)->getSize() + player.getSize())){
			    if(!player.isJumping()){
                    player.die();
                    lives--;
			    }

			}
			i++;
		}

		if(i==0) //list is empty, end level
			nextLevel = true;
	}


	void Game::keyEvents(){
		sf::Event Event;
		//const sf::Input& Input = App->GetInput();
		//multiple keypress problem.
		while (App->GetEvent(Event)){
			if(Event.Type == sf::Event::Closed)
				App->Close();
			if(Event.Type == sf::Event::KeyPressed ||
			   Event.Type == sf::Event::KeyReleased){
				//eventType = true if pressed, false if released
				bool eventType = (Event.Type==sf::Event::KeyPressed);
				if(Event.Key.Code == sf::Key::Q){
					App->Close();
				}
				if(Event.Key.Code == sf::Key::Up){
					KEY_UP = eventType;
				}
				if(Event.Key.Code == sf::Key::Down){
					KEY_DOWN = eventType;
				}
				if(Event.Key.Code == sf::Key::Left){
					KEY_LEFT = eventType;
				}
				if(Event.Key.Code == sf::Key::Right){
					KEY_RIGHT = eventType;
				}
				if(Event.Key.Code == sf::Key::Space ||
						  Event.Key.Code == sf::Key::Z){
					KEY_SHOOT = eventType;
				}
				if(Event.Key.Code == sf::Key::Tab){
					KEY_BOMB = eventType;
				}
				if(Event.Key.Code == sf::Key::X){
					KEY_JUMP = eventType;
				}
			}
		}

		/*while(SDL_PollEvent(&event)){
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
		}*/



		if(KEY_UP){
			player.addThrust(150, deltaTime);
		}
		if(KEY_DOWN){
			player.addThrust(-150, deltaTime);
		}
		if(KEY_RIGHT){
			player.rotateShip(pi/3, deltaTime);
		}
		if(KEY_LEFT){
			player.rotateShip(-pi/3, deltaTime);
		}
		if(KEY_JUMP){
			if(!player.isJumping()){
				player.jump();
			}
			//std::cout << "KEY JUMP" << std::endl;
		}
		if(KEY_SHOOT){
		//fix Bullet/Bomb passing
			Bullet* b = new Bullet(&player, 35.f, 3500);
			if(player.fire(b)){
				shots.push_back(b);
			}
			else{
				delete b;
			}
		}
		if(KEY_BOMB){
			Bomb* b = new Bomb(&player, 35.f, 3500);
			if(player.fire(b)){
				shots.push_back(b);
			}
			else{
				delete b;
			}
		}


	}


	void Game::render(){
		App->SetActive();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//draw walls:
		float x1, x2, y1, y2;
		float offsetX = 400 - player.getX();
		float offsetY = 300 - player.getY();
		
		glColor4f(0.9, 0.9, 0.9, 1.0);
		
		glBegin(GL_LINES);
			x1 = 0; y1 = 0;
			x2 = 800; y2 = 0;
			
			glVertex2f(x1 + offsetX, y1 + offsetY);
			glVertex2f(x2 + offsetX, y2 + offsetY);
		glEnd();
		
		glBegin(GL_LINES);
			x1 = 800; y1 = 0;
			x2 = 800; y2 = 600;
			
			glVertex2f(x1 + offsetX, y1 + offsetY);
			glVertex2f(x2 + offsetX, y2 + offsetY);
		glEnd();
		
		glBegin(GL_LINES);
			x1 = 800; y1 = 600;
			x2 = 0; y2 = 600;
			
			glVertex2f(x1 + offsetX, y1 + offsetY);
			glVertex2f(x2 + offsetX, y2 + offsetY);
		glEnd();
		
		glBegin(GL_LINES);
			x1 = 0; y1 = 600;
			x2 = 0; y2 = 0;
			
			glVertex2f(x1 + offsetX, y1 + offsetY);
			glVertex2f(x2 + offsetX, y2 + offsetY);
		glEnd();
		
		

		player.draw();
		/************
		*Draw shots *
		*************/

		for (std::list<Shot*>::iterator it = shots.begin(); it != shots.end(); it++){
			(*it)->draw();

		}



		/************
		*Draw rock *
		*************/


		for (std::list<Rock*>::iterator it = rocks.begin(); it != rocks.end(); it++){
			(*it)->draw(player);
			//(*it)->draw();
		}


		/************
		*Draw effects*
		*************/


		drawFont();
		/************
		*Display and delay *
		*************/
		App->Display();

	//	SDL_GL_SwapBuffers();
	}


