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



class Character {

public:
	enum Direction { Down, Left, Right, Up };
	
	Character();
	Character(Event event);   //remove this one -----u are no longer using this
	virtual void movement(Event &GameEvent,Vector2i &vector,Sprite &player) =0;
	void setUpintersected(bool status);
	void setDownintersected(bool status);
	void setLeftintersected(bool status);
	void setRightintersected(bool status);

	bool getUpintersected();
	bool getDownintersected();
	bool getLeftintersected();
	bool getRightintersected();

	int  getPlayerDirection();
	void setPlayerDirection(Direction direction);

	void setPacDefaultDirection(Vector2i &vector, int direction); //0- down, 1-left, 2-right, 3-up
	void setheath(float health);
	float gethealth();

protected:
	
	float health;
	int PlayerDirection;;
	float Xmove; //havent used them yet !
	float Ymove; //havent used them yet !
	Event myEvent;
	
	bool Upintersected;
	bool Downintersected;
	bool Leftintersected;
	bool Rightintersected;

};