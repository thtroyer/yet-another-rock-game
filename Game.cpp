
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
		/*keyDown = new bool[323];
		for(int i=0; i<323; i++)
			keyDown[i] = false;
		line = new MyLine[2];*/
		KEY_UP = false;
		KEY_DOWN = false;
		KEY_RIGHT = false;
		KEY_LEFT = false;
		KEY_SHOOT = false;
	}

	Game::~Game(){
		//delete [] keyDown;
		//delete [] line;
		//delete App;
		//delete Clock;

	}
	
	bool Game::running(){
		return gameRunning;
	}
	

	bool Game::init(){

		App = new sf::RenderWindow(sf::VideoMode(800,600,24), "yarg");
		Clock = new sf::Clock();

		//Correct for this later
		App->PreserveOpenGLStates(true);

		glClearDepth(1.f);
		glClearColor(0.f,0.f,0.f,0.f);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluPerspective(90.f,1.f,1.f,500.f);
		glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
		//Event = new sf::Event();
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		test = new WarpEffect(50,50);
	
		statsFont = new sf::Font();
		centerFont = new sf::Font();

		statsFont->LoadFromFile("cour.ttf",15);
		centerFont->LoadFromFile("cour.ttf",30);

		strScore = new sf::String();
		strMessage = new sf::String();

		strScore->SetFont(*statsFont);
		strMessage->SetFont(*centerFont);

		//lastFrameTime = SDL_GetTicks();
		//currFrameTime = SDL_GetTicks();
		Clock->Reset();
		deltaTime = 0;

		srand(time(NULL));

		//if (SDL_Init(SDL_INIT_VIDEO) != 0){
		//	std::cout << "Unable to initialize SDL: " << SDL_GetError()
		//		     << std::endl;
		//	return 1; //error, die
		//}

		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_OPENGL);  
	
	/*	glDisable(GL_DEPTH_TEST);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SDL_GL_SwapBuffers();*/


		//font = new FTGLBitmapFont("cour.ttf");
		//txtCenter = new FTGLPixmapFont("cour.ttf");
	
		///time (&time1);




		std::cout << std::endl;

		
		player.calcPoints();
		
		newGame();

		player.forceSpawn();
	
		return 0;
	}

	void Game::loop(){

		//while(gameRunning){
		while(App->IsOpened()){

			//lastFrameTime = currFrameTime;
			//currFrameTime = SDL_GetTicks();
			//deltaTime = currFrameTime - lastFrameTime;
			
			//deltaTime originally designed for miliseconds
			//todo: change all deltaTime instances to floats 
			deltaTime = Clock->GetElapsedTime() * 1000;
			Clock->Reset();
			
			if(deltaTime > 5000){ //this shouldn't happen
				deltaTime = 1;
				std::cout << "Error in deltaTime" << std::endl;
			}
	
			levelEvents();
					
			frames++;	
			/*if(frames>1000){
				time(&time2);
				frames=0;
				std::cout << 1000.0/(difftime (time2, time1)) << "fps" << std::endl;
				time (&time1);
				std::cout << "deltaTime: " << deltaTime << std::endl;
			}*/
	
			collisionEvents();
			keyEvents();
			

			render();
		}
		//delete font;
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
	
		//int score = 35;
		//int lives = 5;	
		sf::String drawString;
		drawString.SetFont(*statsFont);
		drawString.SetSize(15);

		drawString.Move(10.f,0.f);
		
		//strScore->SetText("Hi");
		//strScore->SetFont(*statsFont);
		//strScore->SetSize(50);

		//strScore->SetColor(sf::Color(255,255,255,255));
		//strScore->Move(100.f,200.f);

		//App->Draw(*strScore);
		
		//glColor3f(1.0f, 1.0f, 1.0f);	
		//glRasterPos2f(15.0f,17.0f);
		//font->FaceSize(15);
		
		std::stringstream strScore;
		strScore << "Score: " << score;
		//font->Render(strScore.str().c_str());
		drawString.SetText(strScore.str().c_str());
		//font->Render(strScore);

		App->Draw(drawString);
		//glRasterPos2f(15.0f,30.0f);

		std::stringstream strLives;
		strLives << "Lives: " << lives;
		
		drawString.SetText(strLives.str().c_str());

		drawString.Move(0.f,15.9f);

		App->Draw(drawString);
		//font->Render(strLives.str().c_str());

		//font->Render("Hello World");	
	
		if(lives<=0){
		//if(true){
			drawString.SetFont(*centerFont);
			drawString.SetSize(25);
			drawString.SetPosition(325.0f, 250.0f);
			drawString.SetText("Game over");
			App->Draw(drawString);
		//	glColor3f(1.0f, 1.0f, 1.0f);
		//	glRasterPos2f(325.0f, 300.0f);
		//	txtCenter->FaceSize(20);
	
		//	txtCenter->Render("Game over");
			
		//	glRasterPos2f(325.0f, 330.0f);
			std::stringstream strScore;
			strScore << "Score: " << score;
			//txtCenter->Render(strScore.str().c_str());
			drawString.SetPosition(325.0f,285.0f);
			drawString.SetText(strScore.str().c_str());
			App->Draw(drawString);
		}

		//App->Draw(drawString);
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
					rocks.push_back(Rock(randomInt(0,800),randomInt(0,600), randomFloat(-2,2), randomFloat(-2,2), 40, randomInt(5,12), randomFloat(-2,2)*pi/50));
				}
		}
		moveShots();
		moveRocks();
		movePlayer();
	}

	void Game::moveShots(){

	//	if(shots.size()==0){
	//		shots.push_back(Shot(true));
	//	}

		for (std::list<Shot>::iterator it = shots.begin(); it != shots.end(); it++){
			if(it->checkAge()){
					it->move(deltaTime);
					it->wrap();
					it->incAge(deltaTime);
			}
			else{
				it = shots.erase(it);
				break;
			}
		}
	}

	void Game::moveRocks(){
		for (std::list<Rock>::iterator it = rocks.begin();
		     it != rocks.end();
			  it++){
			it->move(int(deltaTime));
			it->wrap();
		}

	}

	void Game::movePlayer(){
		
		if (player.isDead() && (lives > 0))
			player.safeSpawn(rocks);
		
		
		player.moveShip(deltaTime);
		player.wrap();
		player.calcPoints();
		
	}


	void Game::collisionEvents(){

		/*
		** Check for collision between rocks and shots
		*/

		std::list<Shot>::iterator itS = shots.begin();
		
		bool breakOut = false;

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
							float xSpeed = randomFloat(-30,30);
							float ySpeed = randomFloat(-30,30);
							float angle = randomFloat(0,pi);
							
							rocks.push_back(Rock((rockX + randomInt(-20,20)),
						   	                  (rockY + randomInt(-20,20)),
												      (itR->getDx() + (xSpeed * cos(angle))),
												      (itR->getDy() + (ySpeed * sin(angle))),	
												      (rockSize - 10),
												      (randomInt(6,12)),
							                     (itR->getdAngle() + randomFloat(-2,2)*pi/50)));
						}
					}		
					score += 100;
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
		for (std::list<Rock>::iterator itR = rocks.begin(); itR != rocks.end(); itR++){
			float rockX = itR->getX();
			float rockY = itR->getY();
			float playerX = player.getX();
			float playerY = player.getY();
			float distance = sqrt(pow((playerX-rockX),2) + (pow((playerY-rockY),2)));
			if(distance < (itR->getSize() + player.getSize())){
				player.die();
				lives--;
			}
			i++;
		}

		if(i==0) //list is empty, end level
			nextLevel = true;
	}

		
	void Game::keyEvents(){
		sf::Event Event;
		const sf::Input& Input = App->GetInput();
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
		if(KEY_SHOOT){	
			if(player.fire()){
				shots.push_back(Shot(&player, 35, 3500));
			}
		}

		/*for(int i=0; i<323; i++){  
			if(keyDown[i]==true){
				switch (i){
					case 113: //q, quit
						gameRunning = !gameRunning;
						break;
					case 273: //up
						player.addThrust(150, deltaTime);
						line[0].setY(0,((int)line[0].getY(0))-1);	
						break;
					case 274: //down
						player.addThrust(-150, deltaTime);
						line[0].setY(0,((int)line[0].getY(0))+1);	
						break;
					case 275: //right
						//player.rotateShip(pi/25, deltaTime);
						player.rotateShip(pi/3, deltaTime);
						line[0].setX(0,((int)line[0].getX(0))+1);	
						break;
					case 276: //left
						//player.rotateShip(-pi/25, deltaTime);
						player.rotateShip(-pi/3, deltaTime);
						line[0].setX(0,((int)line[0].getX(0))-1);	
						break;
					case 32: //Spacebar
					case 122: //z, shoot
						if(player.fire()){
							shots.push_back(Shot(&player, 35, 3500));
						}
						break;
				}	
			}
		}*/
	}
	

	void Game::render(){
		App->SetActive();
	//	glClear(GL_COLOR_BUFFER_BIT);
//		App->Clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//drawInterface();	

	
		player.draw();
		//App->Draw(sf::Shape::Line(10,10,710,100,15, sf::Color::Red));
	
		/************
		*Draw shots *
		*************/
		//glColor3f(.9, .9, .9);

		glColor3f(.9, .9, .9);
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

		glColor3f(.9, .9, .9);
		for (std::list<Rock>::iterator it = rocks.begin(); it != rocks.end(); it++){
			glBegin(GL_POLYGON);
			for (int i = 0; i < it->getNumPoints(); i++){
				glVertex2f((it->getX() + it->point[i].getX()), (it->getY() + it->point[i].getY()));
			}
			glEnd();
		}
		
		/************
		*Draw effects*
		*************/
		
		
		//test->incAge(deltaTime);
		//test->draw();
		
		drawFont();
		/************
		*Display and delay *
		*************/
		App->Display();
		
	//	SDL_GL_SwapBuffers();
	}


