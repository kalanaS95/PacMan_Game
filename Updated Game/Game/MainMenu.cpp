# include "MainMenu.h"

MainMenu::MainMenu()
{
	initializeComponents();
}

MainMenu::~MainMenu()
{

}

void MainMenu::MoveUp()
{

	if (Selection - 1 >= 0)
	{
		MenuItem[Selection].setStyle(Text::Regular);
		MenuItem[Selection].setFillColor(sf::Color::White);
		Selection--;
		MenuItem[Selection].setStyle(Text::Bold);
		MenuItem[Selection].setFillColor(sf::Color::Color(8, 96, 208, 255));
	}
}

void MainMenu::MoveDown()
{

	if (Selection + 1 < MAX_MENU_ITEMS)
	{
		MenuItem[Selection].setStyle(Text::Regular);
		MenuItem[Selection].setFillColor(sf::Color::White);
		Selection++;
		MenuItem[Selection].setStyle(Text::Bold);
		MenuItem[Selection].setFillColor(sf::Color::Color(8, 96, 208, 255));
	}
}

void MainMenu::MainLoop()
{
	

	while (GameWindow.isOpen())
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
							MoveUp();
							break;

					case Keyboard::Down:
						MoveDown();
						break;

					case Keyboard::Return:
							switch (Selection)		// game main menu
							{
							case 0:
								SelectArena();
								break;

							case 1: //tutorial
								DrawTutorial();
								break;

							case 2: //high scores
								ShowScores();
								break;

							case 3:
								GameWindow.close();
								break;
							}
					}
				}
		}
		GameWindow.draw(MainMenuBackgroundSprite);
		GameWindow.draw(PACManTitleSprite);
		GameWindow.draw(MainMenuSprite);
		DrawMenu();
		GameWindow.display();
		GameWindow.clear();
	}
}


void MainMenu::SelectArena()
{
	int loop = 0;
	while (GameWindow.isOpen() && loop==0)
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
						ArenaMoveUp();
						break;

					case Keyboard::Down:
						ArenaMoveDown();
						break;

					case Keyboard::Return:
						SelectCharacter();
						break;

					case Keyboard::Escape:
						loop = 1;
						break;

					}
				}
			}

		if(ArenaBackgroundLoadingSate!=LOAD_FAILED)
		GameWindow.draw(ArenaBackground[GameArenaBackground]);

		if (PackManLoadState != LOAD_FAILED)
			GameWindow.draw(PacManSprite[PacManType]);

		DrawArena();
		GameWindow.display();
		GameWindow.clear();

		}
}

void MainMenu::SelectCharacter()
{
	int state = 0;  //0 - keep looping 1- break the selectCharacter loop
	int loop = 0;
	Game pacman;
	PacMan[0].setFillColor(sf::Color::Red);



	while (GameWindow.isOpen() && loop==0)
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

					CharacterMoveUp();
					break;

				case Keyboard::Down:
					CharacterMoveDown();
					break;

				case Keyboard::Return:

					state=pacman.RenderPlayGame(GameEvents,GameWindow, ArenaBackground[GameArenaBackground],PacManType);
					if (state = 1)
					{
						
						PacMan[CharacterSelection].setFillColor(sf::Color::White);
						PacMan[CharacterSelection].setStyle(Text::Regular);
						CharacterSelection = 0;
						PacManType = MrPac;
						loop = 1;
					}
					


					

					break;

				case Keyboard::Escape:
					PacMan[CharacterSelection].setFillColor(sf::Color::White);
					PacMan[CharacterSelection].setStyle(Text::Regular);
					CharacterSelection = 0;
					PacManType = MrPac;
					loop = 1;
				}
			}
		}
		
		if (ArenaBackgroundLoadingSate != LOAD_FAILED)
			GameWindow.draw(ArenaBackground[GameArenaBackground]);
		
		if (PackManLoadState != LOAD_FAILED)
			GameWindow.draw(PacManSprite[PacManType]);

		DrawArena();
		GameWindow.display();
		GameWindow.clear();

	}
}

void MainMenu::ArenaMoveUp()
{
	if (ArenaSelection - 1 >= 0)
	{
		ArenaItem[ArenaSelection].setStyle(Text::Regular);
		ArenaItem[ArenaSelection].setFillColor(sf::Color::White);
		ArenaSelection--;
		ArenaItem[ArenaSelection].setStyle(Text::Bold);
		ArenaItem[ArenaSelection].setFillColor(sf::Color::Color(8, 96, 208, 255));


		if (ArenaBackgroundLoadingSate == LOAD_SUCCESS)
		{
			std::cout << "in Laod successful" << std::endl;
			switch (ArenaSelection)
			{
			case 0:
				GameArenaBackground = Classic;
				break;
			case 1:
				std::cout << "Laod successful case 1" << std::endl;
				GameArenaBackground = Forest;
				break;

			case 2:
				GameArenaBackground = UnderWater;
				break;

			case 3:
				GameArenaBackground = DeadCity;
				break;
			}
		}
		

	}
}

void MainMenu::ArenaMoveDown()
{
	if (ArenaSelection + 1 < MAX_ARENA_TYPES)
	{
		ArenaItem[ArenaSelection].setStyle(Text::Regular);
		ArenaItem[ArenaSelection].setFillColor(sf::Color::White);
		ArenaSelection++;
		ArenaItem[ArenaSelection].setStyle(Text::Bold);
		ArenaItem[ArenaSelection].setFillColor(sf::Color::Color(8, 96, 208, 255));

		if (ArenaBackgroundLoadingSate == LOAD_SUCCESS)
		{
			std::cout << "in Laod successful" << std::endl;
			switch (ArenaSelection)
			{
			case 0:
				GameArenaBackground = Classic;
				break;
			case 1:
				std::cout << "Laod successful case 1" << std::endl;
				GameArenaBackground = Forest;
				break;

			case 2:
				GameArenaBackground = UnderWater;
				break;

			case 3:
				GameArenaBackground = DeadCity;
				break;
			}
		}
	}
}

void MainMenu::CharacterMoveUp()
{
	if (CharacterSelection - 1 >= 0)
	{
		PacMan[CharacterSelection].setStyle(Text::Regular);
		PacMan[CharacterSelection].setFillColor(sf::Color::White);
		CharacterSelection--;
		PacMan[CharacterSelection].setStyle(Text::Bold);
		PacMan[CharacterSelection].setFillColor(sf::Color::Red);

		if (PackManLoadState == LOAD_SUCCESS)
		{
			
			switch (CharacterSelection)
			{
			case 0:
				PacManType =MrPac ;
				break;
			case 1:
				PacManType =MissPac ;
				break;

			case 2:
				PacManType = Classic;
				break;

			}
		}


	}
}

void MainMenu::CharacterMoveDown()
{
	if (CharacterSelection + 1 < 2)
	{
		PacMan[CharacterSelection].setStyle(Text::Regular);
		PacMan[CharacterSelection].setFillColor(sf::Color::White);
		CharacterSelection++;
		PacMan[CharacterSelection].setStyle(Text::Bold);
		PacMan[CharacterSelection].setFillColor(sf::Color::Red);

		if (PackManLoadState == LOAD_SUCCESS)
		{
			switch (CharacterSelection)
			{
			case 0:
				PacManType = MrPac;
				break;
			case 1:
				PacManType = MissPac;
				break;


			}
		}


	}
}

void MainMenu::DrawCharacter()
{
	for (int index = 0; index < MAX_PAC_TYPES; index++)
	{

		GameWindow.draw(PacManSprite[index]);
	}
}

void MainMenu::DrawMenu()
{
	for (int index = 0; index < MAX_MENU_ITEMS; index++)
	{
		GameWindow.draw(MenuItem[index]);
	}

}

void MainMenu::DrawArena()
{
	for (int index = 0; index < MAX_ARENA_TYPES; index++)
	{

		GameWindow.draw(ArenaItem[index]);
	}

	for (int index = 0; index < MAX_PAC_TYPES; index++)
	{

		GameWindow.draw(PacMan[index]);
	}

}

void MainMenu::initializeComponents()
{
	ScoresDefault.setString("High Scores");
	ScoresDefault.setPosition(400, 0);
	ScoresDefault.setFont(font);
	ScoresDefault.setCharacterSize(48);
	ScoresDefault.setFillColor(sf::Color::White);

	PacManType = MrPac;
	GameArenaBackground = Classic;
	ArenaBackgroundLoadingSate = LOAD_FAILED;
	PackManLoadState = LOAD_FAILED;
	Selection = 0;
	ArenaSelection = 0;
	CharacterSelection = 0;
	WindowAttributes.x = 1100;
	WindowAttributes.y = 600;
	GameWindow.create(sf::VideoMode(WindowAttributes.x, WindowAttributes.y), "PAC-MAN");


	if (font.loadFromFile("GameFont.TTF"))
	{
		MenuItem[0].setFont(font);
		MenuItem[0].setFillColor(sf::Color::Color(8, 96, 208, 255));
		MenuItem[0].setStyle(Text::Bold);
		MenuItem[0].setCharacterSize(40);
		MenuItem[0].setString("Play");
		MenuItem[0].setPosition(Vector2f((float)GameWindow.getSize().x / 2, (float)GameWindow.getSize().y / (MAX_MENU_ITEMS + 1) * 1));


		MenuItem[1].setFont(font);
		MenuItem[1].setFillColor(sf::Color::White);
		MenuItem[1].setStyle(Text::Regular);
		MenuItem[1].setCharacterSize(40);
		MenuItem[1].setString("Tutorial");
		MenuItem[1].setPosition(Vector2f((float)GameWindow.getSize().x / 2, (float)GameWindow.getSize().y / (MAX_MENU_ITEMS + 1) * 2));

		MenuItem[2].setFont(font);
		MenuItem[2].setFillColor(sf::Color::White);
		MenuItem[2].setStyle(Text::Regular);
		MenuItem[2].setCharacterSize(40);
		MenuItem[2].setString("High Score");
		MenuItem[2].setPosition(Vector2f((float)GameWindow.getSize().x / 2, (float)GameWindow.getSize().y / (MAX_MENU_ITEMS + 1) * 3));

		MenuItem[3].setFont(font);
		MenuItem[3].setFillColor(sf::Color::White);
		MenuItem[3].setStyle(Text::Regular);
		MenuItem[3].setCharacterSize(40);
		MenuItem[3].setString("Exit");
		MenuItem[3].setPosition(Vector2f((float)GameWindow.getSize().x / 2, (float)GameWindow.getSize().y / (MAX_MENU_ITEMS + 1) * 4));

	// initializing arena text components

		ArenaItem[0].setFont(font);
		ArenaItem[0].setFillColor(sf::Color::Color(8, 96, 208, 255));
		ArenaItem[0].setStyle(Text::Bold);
		ArenaItem[0].setCharacterSize(40);
		ArenaItem[0].setString("Classic");
		ArenaItem[0].setPosition(Vector2f((float)GameWindow.getSize().x/20, (float)GameWindow.getSize().y / (MAX_ARENA_TYPES + 1) * 1));


		ArenaItem[1].setFont(font);
		ArenaItem[1].setFillColor(sf::Color::White);
		ArenaItem[1].setStyle(Text::Regular);
		ArenaItem[1].setCharacterSize(40);
		ArenaItem[1].setString("Forest");
		ArenaItem[1].setPosition(Vector2f((float)GameWindow.getSize().x / 20, (float)GameWindow.getSize().y / (MAX_ARENA_TYPES + 1) * 2));

		ArenaItem[2].setFont(font);
		ArenaItem[2].setFillColor(sf::Color::White);
		ArenaItem[2].setStyle(Text::Regular);
		ArenaItem[2].setCharacterSize(40);
		ArenaItem[2].setString("Underwater");
		ArenaItem[2].setPosition(Vector2f((float)GameWindow.getSize().x / 20 ,(float)GameWindow.getSize().y / (MAX_ARENA_TYPES + 1) * 3));

		ArenaItem[3].setFont(font);
		ArenaItem[3].setFillColor(sf::Color::White);
		ArenaItem[3].setStyle(Text::Regular);
		ArenaItem[3].setCharacterSize(40);
		ArenaItem[3].setString("Dead City");
		ArenaItem[3].setPosition(Vector2f((float)GameWindow.getSize().x / 20, (float)GameWindow.getSize().y / (MAX_ARENA_TYPES + 1) * 4));


		// initializing pac character names

		PacMan[0].setFont(font);
		PacMan[0].setFillColor(sf::Color::White);
		PacMan[0].setStyle(Text::Regular);
		PacMan[0].setCharacterSize(40);
		PacMan[0].setString("Mr.Pac");
		PacMan[0].setPosition(Vector2f((float)GameWindow.getSize().x / 3, (float)GameWindow.getSize().y / (MAX_PAC_TYPES + 1) * 1));


		PacMan[1].setFont(font);
		PacMan[1].setFillColor(sf::Color::White);
		PacMan[1].setStyle(Text::Regular);
		PacMan[1].setCharacterSize(40);
		PacMan[1].setString("Miss.Pac");
		PacMan[1].setPosition(Vector2f((float)GameWindow.getSize().x / 3, (float)GameWindow.getSize().y / (MAX_PAC_TYPES + 1) * 2));

		/*PacMan[2].setFont(font);
		PacMan[2].setFillColor(sf::Color::White);
		PacMan[2].setStyle(Text::Regular);
		PacMan[2].setCharacterSize(40);
		PacMan[2].setString("Custom Character");
		PacMan[2].setPosition(Vector2f((float)GameWindow.getSize().x / 3, (float)GameWindow.getSize().y / (MAX_PAC_TYPES + 1) * 3));*/

			
	}


	if (Arenas[Classic].loadFromFile("Classic.jpg"))
	{
		ArenaBackground[Classic].setTexture(Arenas[Classic]);

		if (Arenas[Forest].loadFromFile("background.jpg"))
		{
			ArenaBackground[Forest].setTexture(Arenas[Forest]);

			if (Arenas[UnderWater].loadFromFile("UnderWater.jpg"))
			{
				ArenaBackground[UnderWater].setTexture(Arenas[UnderWater]);

				if (Arenas[DeadCity].loadFromFile("Zombie.jpg"))
				{
					ArenaBackground[DeadCity].setTexture(Arenas[DeadCity]);
					ArenaBackgroundLoadingSate = LOAD_SUCCESS;
				}
			}
		}

	}


	if (PacMans[ClassicPac].loadFromFile("ClassicPac.png"))
	{
		PacManSprite[ClassicPac].setTexture(PacMans[ClassicPac]);
		PacManSprite[ClassicPac].setPosition((float)GameWindow.getSize().x / 1.5, (float)GameWindow.getSize().y / 3);

		if (PacMans[MrPac].loadFromFile("ClassicPac.png"))
		{
			PacManSprite[MrPac].setTexture(PacMans[MrPac]);
			PacManSprite[MrPac].setPosition((float)GameWindow.getSize().x / 1.5, (float)GameWindow.getSize().y / 3);

			if (PacMans[MissPac].loadFromFile("MissPacMan.png"))
			{
				PacManSprite[MissPac].setTexture(PacMans[MissPac]);
				PacManSprite[MissPac].setPosition((float)GameWindow.getSize().x / 1.5, (float)GameWindow.getSize().y / 3);
				PackManLoadState = LOAD_SUCCESS;
			}
		}
	}


	//laod PacMan Title
	if (PACManTitle.loadFromFile("PacManTitle.png"))
	{
		PACManTitleSprite.setTexture(PACManTitle);
		PACManTitleSprite.setPosition(280, 20);
	}
	else
	{
		std::cout << "Pac Man Title laoding failed !\n";
	}


	//laoding menu image
	if (MainMenuImage.loadFromFile("TitlePAC.png"))
	{
		MainMenuSprite.setTexture(MainMenuImage);
		MainMenuSprite.setPosition(-50, 200);
	}
	else
	{
		std::cout << "Pac Man Title laoding failed !\n";
	}


	//laoding mainmenu background
	if (MainMenuBackground.loadFromFile("Background2.jpg"))
	{
		MainMenuBackgroundSprite.setTexture(MainMenuBackground);
	}
	else
	{
		std::cout << "Pac Man Title laoding failed !\n";
	}

}

void MainMenu::DrawTutorial()
{
	int loop = 0;
	Texture tutorial;
	Sprite tutorialSprite;

	if (tutorial.loadFromFile("Tutorial.png"))  //loading tutorial elements.
	{ 
		tutorialSprite.setTexture(tutorial);
	}
	else
	{
		cout << "Tutorial loading failed!\n";
	}

	while (GameWindow.isOpen() && loop == 0)
	{
		while (GameWindow.pollEvent(GameEvents))
		{
			if (GameEvents.type == sf::Event::Closed)
				GameWindow.close();


			switch (GameEvents.type)
			{
				std::cout << "Before kedyreleased" << std::endl;
			case Event::KeyReleased:
				switch (GameEvents.key.code)
				{
					std::cout << "Switch" << std::endl;
				case Keyboard::Return:
					std::cout << "Return" << std::endl;
					loop = 1;
					break;

				case Keyboard::Escape:
					std::cout << "Return" << std::endl;
					loop = 1;
					break;

				}
			}

		}
		
		GameWindow.draw(MainMenuBackgroundSprite);
		GameWindow.draw(tutorialSprite);
		GameWindow.display();
		GameWindow.clear();
	}
}


void MainMenu::ShowScores()
{
	int index = 0, increment1 = 100, index2 = 0;
	int loop = 0;
	char line[25] = "";
	TextFile.open("scores.txt", ios::in);

	while ((index != 5) && (!TextFile.eof()))		//loading thingies
	{
		TextFile.getline(line, 24);
		HighScorers[index] = line;
		NameArray[index].setString(line);
		NameArray[index].setPosition(25, increment1);
		NameArray[index].setFont(font);
		NameArray[index].setCharacterSize(48);
		NameArray[index].setFillColor(sf::Color::White);

		TextFile.getline(line, 24);
		HighScores[index] = atoi(line);
		ScoreArray[index].setString(line);
		ScoreArray[index].setPosition(425, increment1);
		ScoreArray[index].setFont(font);
		ScoreArray[index].setCharacterSize(48);
		ScoreArray[index].setFillColor(sf::Color::White);

		index++;
		increment1 += 100;
		std::cout << "One more line read.\n";

	}



	while (GameWindow.isOpen() && loop == 0)
	{
		while (GameWindow.pollEvent(GameEvents))
		{
			if (GameEvents.type == sf::Event::Closed)
				GameWindow.close();


			switch (GameEvents.type)
			{
				std::cout << "Before kedyreleased" << std::endl;
			case Event::KeyReleased:
				switch (GameEvents.key.code)
				{
					std::cout << "Switch" << std::endl;
				case Keyboard::Return:
					std::cout << "Return" << std::endl;
					loop = 1;
					break;
				case Keyboard::Escape:
					std::cout << "Escape" << std::endl;
					loop = 1;
					break;
				}
			}

		}
		
		GameWindow.draw(MainMenuBackgroundSprite);
		GameWindow.draw(ScoresDefault);

		for (int index = 0; index < 5; index++)
		{
			GameWindow.draw(NameArray[index]);
			GameWindow.draw(ScoreArray[index]);
		}
		
		
		GameWindow.display();
		GameWindow.clear();


	}
	TextFile.close();
}
