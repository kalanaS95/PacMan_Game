#pragma once

# include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
# include "Game.h"
#include <string.h>
#include <fstream>
#include <iostream>


using std::fstream;
using std::ios;
using sf::Font;
using sf::Text;
using sf::RenderWindow;
using sf::Vector2u;
using sf::Keyboard;
using sf::Vector2f;
using sf::Event;
using sf::Texture;
using sf::Sprite;
using std::string;

#define LOAD_FAILED 0
#define LOAD_SUCCESS 1
#define MAX_MENU_ITEMS 4
#define MAX_ARENA_TYPES  4
#define MAX_PAC_TYPES 3
enum InGameBackground{Classic,Forest,UnderWater,DeadCity};
enum PackManTypes{ClassicPac,MrPac,MissPac};

class MainMenu {

public:
	MainMenu();
	~MainMenu();

	void initializeComponents();

	void MoveUp();
	void MoveDown();
	void DrawMenu();

	void MainLoop();

	void SelectArena();
	void ArenaMoveUp();
	void ArenaMoveDown();
	void DrawArena();

	void SelectCharacter();
	void CharacterMoveUp();
	void CharacterMoveDown();
	void DrawCharacter();

	void DrawTutorial();


	void ShowScores();

private:

	int HighScores[5];
	string HighScorers[5];
	fstream TextFile;
	Font font;
	Text ScoresDefault;
	Text Tutorial;
	Text NameArray[5];
	Text ScoreArray[5];

	int Selection;
	int ArenaSelection;
	int CharacterSelection;
	int GameArenaBackground;
	int PacManType;
	Text MenuItem[MAX_MENU_ITEMS];
	Text ArenaItem[MAX_ARENA_TYPES];
	Text PacMan[MAX_PAC_TYPES];
	Vector2u WindowAttributes;
	RenderWindow GameWindow;
	Event GameEvents;
	Texture Arenas[MAX_ARENA_TYPES];
	Sprite ArenaBackground[MAX_ARENA_TYPES];
	Texture PacMans[MAX_PAC_TYPES];
	Sprite PacManSprite[MAX_PAC_TYPES];

	Texture PACManTitle;
	Sprite  PACManTitleSprite;
	Texture MainMenuImage;
	Sprite MainMenuSprite;
	Texture MainMenuBackground;
	Sprite MainMenuBackgroundSprite;

	bool ArenaBackgroundLoadingSate;
	bool PackManLoadState;
};
