#pragma once


# include <iostream>
# include <string>
# include <SFML/Graphics.hpp>

using sf::Texture;
using sf::Sprite;
using std::cout;
using std::endl;
using std::string;
using sf::IntRect;
using sf::Event;
using sf::Vector2i;
using sf::RenderWindow;


class Ghosts {


public:
	enum  GhostDirections { right, down, left, up };
	Ghosts();
	~Ghosts();
	virtual void initializeGhost() = 0;
	virtual void movement(Vector2i &vector, Sprite &player) = 0;
	void setUpintersected(bool status);
	void setDownintersected(bool status);
	void setLeftintersected(bool status);
	void setRightintersected(bool status);


	bool getUpintersected();
	bool getDownintersected();
	bool getLeftintersected();
	bool getRightintersected();
	int direction;
	int count;
	int  getGhostDirection();
	void setGhostDirection(GhostDirections direction);
	void incrementGhostSpeed(float xSpeed, float ySpeed);
	float getXspeed();
	float getYspeed();


protected:


	float health;
	int PlayerDirection;;
	float Xmove; 
	float Ymove; 
	Event myEvent;


	bool Upintersected;
	bool Downintersected;
	bool Leftintersected;
	bool Rightintersected;










	float XSpeed;    //determines y axis moving each ghosts
	float YSpeed;    //determines x axis moving each ghosts
	Texture GhostTexture;
	Sprite GhostSprite;


};


