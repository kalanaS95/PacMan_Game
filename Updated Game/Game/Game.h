#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <fstream>

# include "MainMenu.h" // including this header to use enum types for pac man (pac man types)
# include "Ghost.h"


using sf::RenderWindow;
using sf::Event;
using sf::Vector2i;
using sf::Vector2f;
using sf::Texture;
using sf::Sprite;
using sf::FloatRect;
using sf::Clock;
using sf::RectangleShape;
using sf::Color;
using sf::CircleShape;
using sf::Music;
using sf::Font;
using sf::Text;
using std::fstream;
using std::ios;
using std::string;

# define MAX_DOTS 350

enum Direction { Down, Left, Right, Up };

class Game {

public:
	Game();
	~Game();
	int RenderPlayGame(Event &event, RenderWindow &window, Sprite Arena, int pacman);

	void WallGenerator(RenderWindow &GameWindow);
	void SetupWallBounds(RenderWindow &GameWindow);
	void DrawWallbounds(RenderWindow &GameWindow);
	void DrawLevelWalls(RenderWindow &GameWindow);

	void initializeDots();
	void DrawDots(RenderWindow &GameWindow);

	void inGameMenuINI(RenderWindow &GameWindow,Event &GameEvents,Sprite &Arena,int &mainGameloop);
	Text showScore(int points);
	void WriteToFile(int points, Event &GameEvent, RenderWindow &GameWindow);
	void createGhostImage(Texture &texture, Sprite &sprite, int x, int y, Vector2i source, int offset);


	void checkBounds(Ghost &g, Sprite &sprite);
	void animateLives(Sprite &live,int type); //0 mr pac 1-miss pac 
	Text showHighScore(int points);


private:
	Font font;
	Text score;
	Text highscore;
	Text highscoredefault;
	Text default;
	Text Lives;
	Music music;
	Text LevelDefault;
	Text LevelText;
	Text ScoreText;
	fstream OutputTextFile;

	int level;
	int points;
	int gameLoop;
	int totaldots;				//keep track of the generated dots
	int collectedDots;			// keep track of the dots intersected with pac man
	int randVal; //for animation in lives
	Vector2i Source;

	float frameCounter;
	float switchFrame;
	float frameSpeed;

	Texture back;
	Texture player;
	Texture inGameMenu[2];

	Sprite playerimage;
	Sprite backgroundsprite;
	Sprite inGameMenuSprite[2];

	Clock clock;

	RectangleShape WallBounds[4]; //this variable is used to draw walls
	RectangleShape LevelWalls[22];


	CircleShape dots[MAX_DOTS];


	Vector2i Source4;
	Vector2i Source3;
	Vector2i Source2;
	Vector2i Source1;





	Texture GhostTexture1;
	Texture GhostTexture2;
	Texture GhostTexture3;
	Texture GhostTexture4;


	Sprite GhostSprite1;
	Sprite GhostSprite2;
	Sprite GhostSprite3;
	Sprite GhostSprite4;


	Texture pacHUDTexture[2];
	Sprite pacHUDSprite[3];
	Sprite MisspacHUDSprite[3];



};
