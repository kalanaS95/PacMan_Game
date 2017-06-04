# include "Game.h"
# include "MaleCharacter.h"
#include <chrono>
#include <thread>
# include "Ghost.h"


Game::Game()
{
	level = 1;
	totaldots = 0;
	collectedDots = 0;
	randVal = 1;
	gameLoop = 0;
	
	Source.x = 1;
	Source.y = Down;

	frameCounter = 0;
	switchFrame = 100;
	frameSpeed = 500;

	inGameMenu[0].loadFromFile("ResumeSelected.png");
	inGameMenu[1].loadFromFile("ExitSelected.png");
	inGameMenuSprite[0].setTexture(inGameMenu[0]);
	inGameMenuSprite[1].setTexture(inGameMenu[1]);
	inGameMenuSprite[0].setPosition(350, 200);
	inGameMenuSprite[1].setPosition(350, 200);

	points = 0;
	font.loadFromFile("GameFont.TTF");
	default.setFont(font);
	default.setCharacterSize(36);
	default.setFillColor(sf::Color::White);
	default.setPosition(250, 500); //200
	default.setString("High Score:");
	highscoredefault.setFont(font);
	highscoredefault.setCharacterSize(36);
	highscoredefault.setFillColor(sf::Color::White);
	highscoredefault.setPosition(620, 500);  //475
	highscoredefault.setString("Score:");
	score.setFont(font);
	score.setCharacterSize(36);
	score.setFillColor(sf::Color::White);
	score.setPosition(720, 500); //575
	highscore.setFont(font);
	highscore.setCharacterSize(36);
	highscore.setFillColor(sf::Color::White);
	highscore.setPosition(435, 500); //385
	Lives.setFont(font);
	Lives.setCharacterSize(36);
	Lives.setFillColor(sf::Color::White);
	Lives.setPosition(905, 500); //855
	Lives.setString("Lives:");

	LevelDefault.setFont(font);
	LevelDefault.setCharacterSize(36);
	LevelDefault.setString("Level:");
	LevelDefault.setPosition(20, 500);

	LevelText.setFont(font);
	LevelText.setCharacterSize(36);
	LevelText.setString(std::to_string(level));
	LevelText.setPosition(120, 500);

	Source4.x = 1;
	Source4.y = Down;
	Source3.x = 1;
	Source3.y = Down;
	Source2.x = 1;
	Source2.y = Down;
	Source1.x = 1;
	Source1.y = Down;

	pacHUDTexture[0].loadFromFile("MaleCharacter.png");
	pacHUDTexture[1].loadFromFile("MissPacManSprite.png");

	for (int loop = 0; loop < 3; loop++)
	{
		

		pacHUDSprite[loop].setTexture(pacHUDTexture[0]);
		MisspacHUDSprite[loop].setTexture(pacHUDTexture[1]); 

		pacHUDSprite[loop].setPosition(1000+ loop*30,511);			//setting position HUD
		MisspacHUDSprite[loop].setPosition(1000 + loop * 30, 511);	//setting position HUD
	}




}


Game::~Game() 
{

}


int Game::RenderPlayGame(Event &event, RenderWindow &window, Sprite Arena, int pacman)
{
	int index = 0;
	int animationType=MrPac;

	gameLoop = 0;
	music.openFromFile("audio/pacman_beginning.wav");
	music.setVolume(50);
	std::cout << "pac man type :" << pacman << std::endl;
	initializeDots();
	WallGenerator(window);
	SetupWallBounds(window); //setting up primary wall for the bounds
	
							 
// write a switch statement to laod corresponding object according to the pacmanType passing varible (u can use enum types since i have included header to mainmenu)

	switch (pacman)
	{
	case ClassicPac:
		if (!player.loadFromFile("MaleCharacter.png"))
			cout << "not loaded" << endl;
		
		animationType = ClassicPac;
		break;
	case MissPac:
		if (!player.loadFromFile("MissPacManSprite.png"))
			cout << "not loaded" << endl;
		animationType = MissPac;
		break;
	case MrPac:
		if (!player.loadFromFile("MaleCharacter.png"))
			cout << "not loaded" << endl;
		animationType = MrPac;
		break;

	}
	
	playerimage.setTexture(player);
	playerimage.setPosition(520, 250); //set player location in the middle
									   //playerimage.setColor(Color::Red);

	createGhostImage(GhostTexture1, GhostSprite1, 25, 25, Source1, 0);
	createGhostImage(GhostTexture2, GhostSprite2, 1032, 25, Source2, 64);
	createGhostImage(GhostTexture3, GhostSprite3, 25, 440, Source3, 128);
	createGhostImage(GhostTexture4, GhostSprite4, 1032, 440, Source4, 256);


	MaleCharacter male(event);
	Ghost g1;
	Ghost g2;
	Ghost g3;
	Ghost g4;

	male.setPacDefaultDirection(Source,1); //setting up pac man's default direction to left //0- down, 1-left, 2-right, 3-up
	male.setheath(3.0f);


	while (window.isOpen() && gameLoop==0)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.key.code == sf::Keyboard::Escape)
			{
				std::cout << "ESC \n";
				inGameMenuINI(window, event,Arena,gameLoop);
				
				//gameLoop = 1;
			}

			if (!window.hasFocus())
			{
				inGameMenuINI(window, event, Arena, gameLoop);
			}
				

			male.movement(event,Source, playerimage);
			
		}
		



		checkBounds(g1, GhostSprite1);
		checkBounds(g2, GhostSprite2);
		checkBounds(g3, GhostSprite3);
		checkBounds(g4, GhostSprite4);






		g1.movement(Source1, GhostSprite1);
		g2.movement(Source2, GhostSprite2);
		g3.movement(Source3, GhostSprite3);
		g4.movement(Source4, GhostSprite4);






		frameCounter += frameSpeed*clock.restart().asSeconds(); //to keep consistant frame rate on each computer
		if (frameCounter >= switchFrame)
		{
			
			frameCounter = 0;
			Source.x++;
			if (Source.x * 32 >= player.getSize().x)
			{
				cout << "pac frame\n";
				Source.x = 0;
			}

			Source1.x++;
			if (Source1.x  > 1)
			{
				cout << "ghost 1\n";
				Source1.x = 0;
			}


			Source2.x++;
			if (Source2.x  > 1)
			{
				cout << "ghost 2\n";
				Source2.x = 0;
			}


			Source3.x++;
			if (Source3.x  > 1)
			{
				cout << "ghost 3\n";
				Source3.x = 0;
			}


			Source4.x++;
			if (Source4.x  > 1)
			{
				cout << "ghost 4\n";
				Source4.x = 0;
			}



			randVal=rand()%3;
			cout << "pac man type :" << animationType << endl;
				if (animationType == MrPac|| animationType == ClassicPac)
				{
					cout << "in pac man\n\n";
					for (int loop = 0; loop < 3; loop++)
					{
						pacHUDSprite[loop].setTextureRect(IntRect(32 * randVal, 64, 32, 32));

					}

				}
				else if (animationType == MissPac)
				{
					//cout <<"in miss pac"
					for (int loop = 0; loop < 3; loop++)
					{
						MisspacHUDSprite[loop].setTextureRect(IntRect(32 * randVal, 64, 32, 32));
					}
				}

				
				

			
		}

		

		




		


		
		//WallGenerator(window,Level1);
		
		playerimage.setTextureRect(IntRect(Source.x * 32, Source.y * 32, 32, 32));
		window.draw(Arena);
		window.draw(playerimage);

		DrawWallbounds(window);

		DrawLevelWalls(window);
		DrawDots(window);
		
		for (int loop = 0; loop < 22; loop++) //for collision with main walls 
		{
			if (loop<4 && (playerimage.getGlobalBounds().intersects(WallBounds[loop].getGlobalBounds()))) // collision detection for bounding walls (main 4 walls)
			{
				switch (male.getPlayerDirection())
				{
				case Down:
					male.setDownintersected(true);
					playerimage.move(0, -5);
					break;

				case Left:
					male.setLeftintersected(true);
					playerimage.move(5, 0);
					break;

				case Right:
					male.setRightintersected(true);
					playerimage.move(-5, 0);
					break;

				case Up:
					male.setUpintersected(true);
					playerimage.move(0, 5);
					break;

				}

				//std::cout << "Intersection detected" << std::endl;

			}

			if (playerimage.getGlobalBounds().intersects(LevelWalls[loop].getGlobalBounds())) // for collision with other walls 
			{
				switch (male.getPlayerDirection())
				{
				case Down:
					male.setDownintersected(true);
					playerimage.move(0, -5);
					break;

				case Left:
					male.setLeftintersected(true);
					playerimage.move(5, 0);
					break;

				case Right:
					male.setRightintersected(true);
					playerimage.move(-5, 0);
					break;

				case Up:
					male.setUpintersected(true);
					playerimage.move(0, 5);
					break;

				}
			}
		}
		
		for (int loop = 0; loop < MAX_DOTS; loop++)
		{
			if (playerimage.getGlobalBounds().intersects(dots[loop].getGlobalBounds()))
			{
				
				collectedDots++;
				dots[loop].setPosition(-10, -10);
				dots[loop].setFillColor(Color::Color(0, 0, 0, 0));
				points += 10; //points variable
				music.play();
				if (collectedDots == totaldots)  // condition to end the game;
				{
					std::cout << "End Game\n";
					level++;							//incrementing level number
					LevelText.setString(std::to_string(level));
					collectedDots = 0;									//resetting variables
					totaldots = 0;

					//incrementing ghosts speed in each level..
					g1.incrementGhostSpeed(g1.getXspeed() + 0.2, g1.getYspeed() + 0.2);
					g2.incrementGhostSpeed(g2.getXspeed() + 0.2, g2.getYspeed() + 0.2);
					g3.incrementGhostSpeed(g3.getXspeed() + 0.2, g3.getYspeed() + 0.2);
					g4.incrementGhostSpeed(g4.getXspeed() + 0.2, g4.getYspeed() + 0.2);

					initializeDots();						// initializing dots again for the second round
					playerimage.setPosition(520, 250);		//setting player location to the defalut postion
					

				}

			}
		}

		if (playerimage.getGlobalBounds().intersects(GhostSprite1.getGlobalBounds()) || playerimage.getGlobalBounds().intersects(GhostSprite2.getGlobalBounds()) || playerimage.getGlobalBounds().intersects(GhostSprite3.getGlobalBounds()) || playerimage.getGlobalBounds().intersects(GhostSprite4.getGlobalBounds()))
		{
			music.openFromFile("audio/pacman_death.wav");
			music.play();
			std::this_thread::sleep_for(std::chrono::seconds(2));
			
			cout << "music" << endl;
			cout << "Intersect" << endl;
			if (male.gethealth() > 1)
			{
				male.setheath(male.gethealth() - 1);
				playerimage.setPosition(520, 250);
				cout << "Health :" << male.gethealth();
			}
			else  //game over
			{
				cout << "WriteToFile" << endl;
				WriteToFile(points, event, window);
				totaldots = 0;		//resetting these variables to 0 because we are ending the session
				collectedDots = 0;	
				gameLoop = 1;
			}
			music.openFromFile("audio/pacman_chomp.wav");
		}
		
		window.draw(default);
		window.draw(showScore(points));
		window.draw(Lives);
		window.draw(showHighScore(points));
		window.draw(highscoredefault);


		for (int loop = 0; loop < male.gethealth()-1; loop++)
		{
			if (animationType == MrPac || animationType == ClassicPac)		//for mr pac man
			{
				//animateLives(pacHUDSprite[loop],0);
				window.draw(pacHUDSprite[loop]);  
			}
			else if (animationType == MissPac)
			{
				
				window.draw(MisspacHUDSprite[loop]);  // for miss pac man
			}
		}
		window.draw(LevelDefault);
		window.draw(LevelText);
		window.draw(GhostSprite1);
		window.draw(GhostSprite2);
		window.draw(GhostSprite3);
		window.draw(GhostSprite4);

		window.display();
		window.clear();
		if (index == 0)
		{
			music.play();
			std::this_thread::sleep_for(std::chrono::seconds(4));
			index++;
			music.openFromFile("audio/pacman_chomp.wav");
		}

	}

	return 1;

	
}


void Game::WallGenerator(RenderWindow &GameWindow)
{
	int Walls = 0;
	for (int loop = 0; loop < 22; loop++) //setting outline thickness
	{
		LevelWalls[loop].setFillColor(Color::Color(52, 152, 219, 255));
	}

	for (int Walls = 0; Walls < 10; Walls++) //for vertical walls connected to bounds 0,1 - walls on the top 2,3 - walls on the bottom 4,5 - middle horizontal wall on left
	{
		LevelWalls[Walls].rotate(90);
		LevelWalls[Walls].setSize(Vector2f(100, 20));
	}

	for (Walls; Walls < 18; Walls++)
	{
		LevelWalls[Walls].setSize(Vector2f(120, 20));
	}

	for (Walls; Walls < 20; Walls++) /// walls connected to the middle vertical walls ----------> index  18,19
	{
		LevelWalls[Walls].setSize(Vector2f(200, 20));
	}

	for (Walls; Walls < 22; Walls++)
	{
		LevelWalls[Walls].setSize(Vector2f(320, 20));
	}
	
	//setting up vertical walls

	LevelWalls[0].setPosition(300, 5); //first wall position on the top
	LevelWalls[1].setPosition(GameWindow.getSize().x - 300, 5); //second wall position on the top
	LevelWalls[2].setPosition(300, GameWindow.getSize().y- 240); //first wall position on the bottom
	LevelWalls[3].setPosition(GameWindow.getSize().x - 300, GameWindow.getSize().y - 240); //second wall position on the bottom
	
	LevelWalls[4].setPosition(100, 120);
	LevelWalls[5].setPosition(100, GameWindow.getSize().y - 300);
	LevelWalls[6].setPosition(400,200);
	LevelWalls[7].setPosition(700, 200);

	LevelWalls[8].setPosition(GameWindow.getSize().x-100, 120);
	LevelWalls[9].setPosition(GameWindow.getSize().x - 100, GameWindow.getSize().y - 300);
	
	//setting up horizontal walls

	LevelWalls[10].setPosition(100, 120);
	LevelWalls[11].setPosition(100, GameWindow.getSize().y - 200);

	LevelWalls[12].setPosition(GameWindow.getSize().x-230, 120);
	LevelWalls[13].setPosition(GameWindow.getSize().x - 230, GameWindow.getSize().y - 200);

	LevelWalls[14].setPosition(GameWindow.getSize().x - 330, 280);  // = walls right
	LevelWalls[15].setPosition(GameWindow.getSize().x - 330, 200);

	LevelWalls[16].setPosition(GameWindow.getSize().x - (GameWindow.getSize().x - 190), 280);  // = walls left
	LevelWalls[17].setPosition(GameWindow.getSize().x - (GameWindow.getSize().x - 190), 200);

	LevelWalls[18].setPosition(380, 310);
	LevelWalls[19].setPosition(500, 200);///GameWindow.getSize().y - 200);

	LevelWalls[20].setPosition(380, 120);
	LevelWalls[21].setPosition(380, GameWindow.getSize().y - 200);
}

void Game::DrawLevelWalls(RenderWindow &GameWindow)
{
	for (int loop = 0; loop < 22; loop++)
	{
		GameWindow.draw(LevelWalls[loop]);
	}
	
}

void Game::SetupWallBounds(RenderWindow &GameWindow)
{
	//rgba(52, 152, 219, 1.0)
	

	for (int loop = 0; loop < 2; loop++) //setting outline thickness for horizontal lines
	{
			WallBounds[loop].setSize(Vector2f(GameWindow.getSize().x - (GameWindow.getSize().x / 40), 10));
			WallBounds[loop].setFillColor(Color::Color(52, 152, 219, 255));
	}

	for (int loop = 2; loop < 4; loop++) //setting outline thickness for vertical lines
	{
		WallBounds[loop].setSize(Vector2f(GameWindow.getSize().y - (GameWindow.getSize().y / 5), 10));
		//WallBounds[loop].setSize(Vector2f(450, 10));
		WallBounds[loop].setFillColor(Color::Color(52, 152, 219, 255));
	}


	WallBounds[2].rotate(90);
	WallBounds[3].rotate(90);

	WallBounds[0].setPosition(4, 4);
	WallBounds[1].setPosition(4, GameWindow.getSize().y-120);

	WallBounds[2].setPosition(GameWindow.getSize().x - 23, 4);
	WallBounds[3].setPosition(14, 4);
	//GameWindow.draw(WallBounds[0]);



}

void Game::DrawWallbounds(RenderWindow &GameWindow)
{
	for (int loop = 0; loop < 4; loop++)
	{
		GameWindow.draw(WallBounds[loop]);
	}
}


void Game::initializeDots()
{
	cout << "1.total dots: " << totaldots << endl;
	for (int loop = 0; loop < MAX_DOTS; loop++)
	{
		dots[loop].setRadius(5);
		dots[loop].setFillColor(sf::Color::White);
	}
	
	//int totaldots = 0;
	int space = 0;

	cout << "2.total dots: " << totaldots << endl;
	//left vertical dots
	for (int loop=0; loop < 21; loop++)
	{
		totaldots++;
		space = 50 + loop*20.0f;
		dots[totaldots].setPosition(40.0f, space);
	}

	for (int loop = 0; loop < 6; loop++)
	{
		totaldots++;
		space = 32 + loop*20.0f;
		dots[totaldots].setPosition(240.0f, space);
	}

	for (int loop = 0; loop < 5; loop++)
	{
		totaldots++;
		space = 52 + loop*20.0f;
		dots[totaldots].setPosition(320.0f, space);
	}


	for (int loop = 0; loop < 8; loop++)
	{
		totaldots++;
		space = 190 + loop*20.0f;
		dots[totaldots].setPosition(120.0f, space);
	}

	for (int loop = 0; loop < 8; loop++)
	{
		totaldots++;
		space = 190 + loop*20.0f;
		dots[totaldots].setPosition(340.0f, space);
	}

	for (int loop = 0; loop < 5; loop++)
	{
		totaldots++;
		space = 190 + loop*20.0f;
		dots[totaldots].setPosition(440.0f, space);
	}

	for (int loop = 0; loop < 5; loop++)
	{
		totaldots++;
		space = 260 + loop*20.0f;
		dots[totaldots].setPosition(640.0f, space);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		totaldots++;
		space = 385 + loop*20.0f;
		dots[totaldots].setPosition(740.0f, space);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		totaldots++;
		space = 385 + loop*20.0f;
		dots[totaldots].setPosition(820.0f, space);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		totaldots++;
		space = 385 + loop*20.0f;
		dots[totaldots].setPosition(240.0f, space);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		totaldots++;
		space = 385 + loop*20.0f;
		dots[totaldots].setPosition(320.0f, space);
	}



	
	for (int loop = 0; loop < 9; loop++)
	{
		totaldots++;
		space = 170 + loop*20.0f;
		dots[totaldots].setPosition(940.0f, space);
	} 


	for (int loop = 0; loop < 8; loop++)
	{
		totaldots++;
		space = 190 + loop*20.0f;
		dots[totaldots].setPosition(740.0f, space);
	}



	for (int loop = 0; loop < 5; loop++)
	{
		totaldots++;
		space = 52 + loop*20.0f;
		dots[totaldots].setPosition(740.0f, space);
	} 

	for (int loop = 0; loop < 5; loop++)
	{
		totaldots++;
		space = 52 + loop*20.0f;
		dots[totaldots].setPosition(820.0f, space);
	}


	cout << "3.total dots: " << totaldots << endl;

	//right vertical dots
	for (int loop = 0; loop < 21; loop++)
	{
		totaldots++;
		space = 30 + loop*20.0f;
		dots[totaldots].setPosition(1040.0f, space);
	}

	cout << "4.total dots: " << totaldots << endl;
	//top first part 
	for (int loop=0; loop < 10; loop++)
	{
		totaldots++;
		space = 40 + loop*20.0f;
		dots[totaldots].setPosition(space, 30);
		
	}
	cout << "5.total dots: " << totaldots << endl;
	//bottom first part 
	for (int loop = 0; loop < 10; loop++)
	{
		totaldots++;
		space = 60 + loop*20.0f;
		dots[totaldots].setPosition(space, 450);
	}


	//middle (3)
	for (int loop = 0; loop < 10; loop++)
	{
		totaldots++;
		space = 140 + loop*20.0f;
		dots[totaldots].setPosition(space, 330);
	}

	for (int loop = 0; loop < 9; loop++)
	{
		totaldots++;
		space = 760 + loop*20.0f;
		dots[totaldots].setPosition(space, 330);
	}

	for (int loop = 0; loop < 4; loop++)
	{
		totaldots++;
		space = 960 + loop*20.0f;
		dots[totaldots].setPosition(space, 270);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		totaldots++;
		space = 580 + loop*20.0f;
		dots[totaldots].setPosition(space, 260);
	}

	for (int loop = 0; loop < 2; loop++)
	{
		totaldots++;
		space = 460 + loop*20.0f;
		dots[totaldots].setPosition(space, 270);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		totaldots++;
		space = 60 + loop*20.0f;
		dots[totaldots].setPosition(space, 270);
	}
	//working
	

	cout << "6.total dots: " << totaldots << endl;
	//bottom(2) first part 
	for (int loop = 0; loop < 7; loop++)
	{
		totaldots++;
		space = 120 + loop*20.0f;
		dots[totaldots].setPosition(space, 360);
	}

	cout << "8.total dots: " << totaldots << endl;
	//middle first part 
	for (int loop = 0; loop < 10; loop++)
	{
		totaldots++;
		space = 140 + loop*20.0f;
		dots[totaldots].setPosition(space, 250);
	}

	cout << "9.total dots: " << totaldots << endl;
	//bottom second part 
	for (int loop = 0; loop < 22; loop++)
	{
		totaldots++;
		space = 320 + loop*20.0f;
		dots[totaldots].setPosition(space, 450);
	}

	cout << "10.total dots: " << totaldots << endl;
	//bottom(2) second part 
	for (int loop = 0; loop < 22; loop++)
	{
		totaldots++;
		space = 320 + loop*20.0f;
		dots[totaldots].setPosition(space, 360);
	}

	cout << "11.total dots: " << totaldots << endl;
	//top second part
	for (int loop = 0; loop < 22; loop++)
	{
		totaldots++;
		space = 320 + loop*20.0f;
		dots[totaldots].setPosition(space, 30);
	}
	
	cout << "12.total dots: " << totaldots << endl;
	//bottom last part
	for (int loop = 0; loop < 12; loop++)
	{
		totaldots++;
		space = 820 + loop*20.0f;
		dots[totaldots].setPosition(space, 450);
	}

	cout << "13.total dots: " << totaldots << endl;
	//top last part
	for (int loop = 0; loop < 12; loop++)
	{
		totaldots++;
		space = 820 + loop*20.0f;
		dots[totaldots].setPosition(space, 30);
	}

	cout << "14.total dots: " << totaldots << endl;
	//bottom(2) last part
	for (int loop = 0; loop < 7; loop++)
	{
		totaldots++;
		space = 820 + loop*20.0f;
		dots[totaldots].setPosition(space, 360);
	}

	cout << "15.total dots: " << totaldots << endl;
	//middle last part
	for (int loop = 0; loop < 9; loop++)
	{
		totaldots++;
		space = 760 + loop*20.0f;
		dots[totaldots].setPosition(space, 250);
	}

	cout << "16.total dots: " << totaldots << endl;
	//top(2) long line
	for (int loop = 0; loop < 41; loop++)
	{
		totaldots++;
		space = 120 + loop*20.0f;
		dots[totaldots].setPosition(space, 165);
	}

	cout << "17.total dots: " << totaldots << endl;
	std::cout << "number of dots :" << totaldots << std::endl;
}


void Game::DrawDots(RenderWindow &GameWindow)
{
	for (int loop = 0; loop < MAX_DOTS; loop++)
	{
		GameWindow.draw(dots[loop]);
	}
}

void Game::inGameMenuINI(RenderWindow &GameWindow, Event &GameEvents,Sprite &Arena,int &mainGameloop)
{
	int userSelection = 1;
	int inGameMenuLoop = 0;
	cout << "In Game Menu" << endl;
	while (GameWindow.isOpen()&& inGameMenuLoop==0)
	{
		while (GameWindow.pollEvent(GameEvents))
		{
			if (GameEvents.type == sf::Event::Closed)
				GameWindow.close();

			switch (GameEvents.type)
			{
			case Event::KeyReleased:
				switch (GameEvents.key.code)
				{
				case Keyboard::Up:
					cout << "UP" << endl;
					userSelection = 1;
					break;

				case Keyboard::Down:
					cout << "Down" << endl;
					userSelection = 2;
					break;

				case Keyboard::Return:
					cout << "Return" << endl;
					if (userSelection == 1)
					{
						inGameMenuLoop = 1;
					}
					else if (userSelection == 2)
					{
						totaldots = 0;		//resetting these variables to 0 because we are ending the session
						collectedDots = 0;
						inGameMenuLoop = mainGameloop =1;

					}
					
					break;

				}

			}
		}
		
		GameWindow.draw(Arena);
		GameWindow.draw(inGameMenuSprite[userSelection-1]);
		GameWindow.display();
		GameWindow.clear();
	}
}

Text Game::showScore(int points)
{
	score.setString(std::to_string(points));
	return score;
}


void Game::WriteToFile(int points, Event &GameEvent, RenderWindow &GameWindow)
{


	int index = 0, scores[5] = {}, loop2 = 4, loop = 0, output = 0, equivalent = 0, trigger = 0;
	string scorers[5] = {};
	char line[25] = "";
	OutputTextFile.open("scores.txt", ios::in);
	ScoreText.setString("High Score!\n\nName:");
	ScoreText.setPosition(400, 0);
	ScoreText.setFont(font);
	ScoreText.setCharacterSize(48);
	ScoreText.setFillColor(sf::Color::White);
	sf::String sentence;
	sf::Text text;
	text.setPosition(545, 100);
	text.setFont(font);
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::White);


	while ((index != 5) && (!OutputTextFile.eof()))
	{
		OutputTextFile.getline(line, 24);
		scorers[index] = line;
		OutputTextFile.getline(line, 24);
		scores[index] = atoi(line);
		index++;

	}
	index = 0;
	while (index < 5)
	{
		if (points>scores[index])
		{
			trigger = 1;
			while (loop2 >= index)
			{


				if (loop2 != 4)
				{
					scorers[loop2 + 1] = scorers[loop2];
					scores[loop2 + 1] = scores[loop2];
				}
				loop2--;
			}
			scores[index] = points;
			equivalent = index;
			index = 5;
			while (GameWindow.isOpen() && loop == 0)
			{

				while (GameWindow.pollEvent(GameEvent))
				{


					if (GameEvent.type == sf::Event::Closed)
						GameWindow.close();




					switch (GameEvent.type)
					{
					case sf::Event::TextEntered:
						if (GameEvent.text.unicode >= 32 && GameEvent.text.unicode <= 126)
						{
							sentence += char(GameEvent.text.unicode);
						}
						else if (GameEvent.text.unicode == 8 && sentence.getSize()>0)
						{
							sentence.erase(sentence.getSize() - 1, sentence.getSize());
						}
						text.setString(sentence);
						std::cout << "Before kedyreleased" << std::endl;
						break;


					case Event::KeyReleased:


						switch (GameEvent.key.code)
						{
							std::cout << "Switch" << std::endl;
						case Keyboard::Return:
							std::cout << "Return" << std::endl;
							scorers[equivalent] = sentence;
							loop = 1;
							OutputTextFile.close();
							OutputTextFile.open("scores.txt", ios::out);
							while (output<5)
							{
								OutputTextFile << scorers[output] << endl;
								OutputTextFile << scores[output];
								if (output != 4)
								{
									OutputTextFile << endl;
								}
								output++;
							}


							break;
							break;
						case Keyboard::Escape:
							std::cout << "Escape" << std::endl;
							loop = 1;
							break;
						}

					}

				}
				
				GameWindow.draw(text);
				
				GameWindow.draw(ScoreText);
				
				GameWindow.display();
				GameWindow.clear();












			}
		}
		index++;
	}
	if (trigger == 0)
	{
		ScoreText.setString("Game Over");
		while (GameWindow.isOpen() && loop == 0)
		{


			while (GameWindow.pollEvent(GameEvent))
			{


				if (GameEvent.type == sf::Event::Closed)
					GameWindow.close();




				switch (GameEvent.type)
				{
				case Event::KeyReleased:


					switch (GameEvent.key.code)
					{
						std::cout << "Switch" << std::endl;
					case Keyboard::Return:

						loop = 1;
						break;
					case Keyboard::Escape:
						std::cout << "Escape" << std::endl;
						loop = 1;
						break;
					}


				}


			}
			
			GameWindow.draw(ScoreText);
			
			GameWindow.display();
			GameWindow.clear();












		}
	}



	OutputTextFile.close();
}

void Game::checkBounds(Ghost &g, Sprite &sprite)
{
	for (int loop = 0; loop < 22; loop++)
	{

		if (loop<4 && (sprite.getGlobalBounds().intersects(WallBounds[loop].getGlobalBounds()))) // collision detection for bounding walls (main 4 walls)
		{

			std::cout << g.getGhostDirection() << std::endl;
			switch (g.getGhostDirection())
			{
			case Ghosts::down:
				g.setDownintersected(true);

				sprite.move(0, -5);
				break;


			case Ghosts::left:
				g.setLeftintersected(true);

				sprite.move(5, 0);
				break;


			case Ghosts::right:
				g.setRightintersected(true);

				sprite.move(-5, 0);
				break;


			case Ghosts::up:
				g.setUpintersected(true);

				sprite.move(0, 5);
				break;


			}






		}


		if (sprite.getGlobalBounds().intersects(LevelWalls[loop].getGlobalBounds()))
		{
			switch (g.getGhostDirection())
			{
			case Ghosts::down:
				g.setDownintersected(true);
				sprite.move(0, -5);
				break;


			case Ghosts::left:
				g.setLeftintersected(true);
				sprite.move(5, 0);
				break;


			case Ghosts::right:


				g.setRightintersected(true);

				sprite.move(-5, 0);



				break;


			case Ghosts::up:
				g.setUpintersected(true);
				sprite.move(0, 5);
				break;


			}
		}
	}
}


void Game::createGhostImage(Texture &texture, Sprite &sprite, int x, int y, Vector2i source, int offset)
{
	if (!texture.loadFromFile("GhostsSprite.png"))
	{
		cout << "not loaded" << endl;
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);




	sprite.setTextureRect(IntRect(source.x * 32 + offset, source.y * 32, 32, 32));







}

void Game::animateLives(Sprite &live, int type)
{
	int randVal = rand() % 3;


		for (int loop = 0; loop < 3; loop++)
		{
			if (type == 0)  // for mr pac
			{
				pacHUDSprite[loop].setTextureRect(IntRect(32 * randVal, 64, 32, 32));
			}
			else if (type == 1)  // miss pac
			{
				MisspacHUDSprite[loop].setTextureRect(IntRect(32 * randVal, 64, 32, 32));
			}
			
		}
	//MisspacHUDSprite[loop].setTextureRect(IntRect(32, 64, 32, 32))


}

Text Game::showHighScore(int points)
{
	int previousHighScore = 0;
	char line[25];
	OutputTextFile.open("scores.txt", ios::in);
	OutputTextFile.getline(line, 24);
	OutputTextFile.getline(line, 24);
	previousHighScore = atoi(line);
	if (points>previousHighScore)
	{
		previousHighScore = points;
	}
	highscore.setString(std::to_string(previousHighScore));
	OutputTextFile.close();
	return highscore;
}