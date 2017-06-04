# include "CharacterBase.h"

Character::Character()
{
	Upintersected = Downintersected= Rightintersected = Leftintersected = false;

}

Character::Character(Event event)
{

}

void Character::movement(Event &GameEvent, Vector2i &vector, Sprite &player)
{
	//std::cout << "Up stat : " <<Upintersected << std::endl;
	//std::cout << "Down stat : " << Downintersected << std::endl;
	//std::cout << "Right stat : " << Rightintersected << std::endl;
	//std::cout << "Left stat : " << Leftintersected << std::endl;
	switch (GameEvent.type)
	{
		//std::cout << "Base movement switch" << std::endl;
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (Upintersected != true)
			{
				vector.y = this->Up;
				player.move(0, -7);
				PlayerDirection = this->Up;

				Downintersected = false;
				Leftintersected = false;
				Rightintersected = false;
			}
			//cout << "in up" <<endl;
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (Downintersected != true)
			{
				vector.y = this->Down;
				player.move(0, 7);
				PlayerDirection = this->Down;

				Upintersected = false;
				Leftintersected = false;
				Rightintersected = false;
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (Rightintersected != true)
			{
				vector.y = this->Right;
				player.move(7, 0);
				PlayerDirection = this->Right;

				Downintersected = false;
				Leftintersected = false;
				Upintersected = false;

			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (Leftintersected != true)
			{
				vector.y = this->Left;
				player.move(-7, 0);
				PlayerDirection = this->Left;

				Downintersected = false;
				Rightintersected = false;
				Upintersected = false;
			}
			
		}
	}

	
}


void Character::setUpintersected(bool status)
{
	this->Upintersected = status;
}

void Character::setDownintersected(bool status)
{
	this->Downintersected = status;
}

void Character::setLeftintersected(bool status)
{
	this->Leftintersected = status;
}

void Character::setRightintersected(bool status)
{
	this->Rightintersected = status;
}

bool Character::getUpintersected()
{
	return Upintersected;
}

bool Character::getDownintersected()
{
	return Downintersected;
}

bool Character::getLeftintersected()
{
	return Leftintersected;
}

bool Character::getRightintersected()
{
	return Rightintersected;
}

int Character::getPlayerDirection()
{
	return PlayerDirection;
}

void Character::setPlayerDirection(Direction direction)
{
	this->PlayerDirection = direction;
}

void Character::setPacDefaultDirection(Vector2i &vector, int direction)
{
	vector.y = direction;
	PlayerDirection = direction;
}

void Character::setheath(float health)
{
	this->health = health;
}

float Character::gethealth()
{
	return this->health;
}

