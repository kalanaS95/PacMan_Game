# include "GhostsBase.h"




Ghosts::Ghosts()
{
	Upintersected = Downintersected = Rightintersected = Leftintersected = false;
	direction = 0;
	count = 0;
	Xmove = Ymove = 0.4;
}


Ghosts::~Ghosts()
{


}


void Ghosts::movement(Vector2i &vector, Sprite &ghost)
{

	if (Rightintersected == true || Downintersected == true || Leftintersected == true || Upintersected == true) {
		direction = rand() % 4;
	}

	switch (direction)
	{
	case up:
		if (Upintersected != true)
		{

			vector.y = this->up;
			ghost.move(0, -Ymove);
			PlayerDirection = this->up;
			Downintersected = false;
			Leftintersected = false;
			Rightintersected = false;
			count++;
		}
		break;

	case down:
		if (Downintersected != true)
		{
			vector.y = this->down;
			ghost.move(0, Ymove);
			PlayerDirection = this->down;
			Upintersected = false;
			Leftintersected = false;
			Rightintersected = false;
			count++;
		}
		break;


	case left:
		if (Leftintersected != true)
		{
			vector.y = this->left;
			ghost.move(-Xmove, 0);
			PlayerDirection = this->left;
			Downintersected = false;
			Rightintersected = false;
			Upintersected = false;
			count++;


		}
		break;


	case right:
		if (Rightintersected != true)
		{
			vector.y = this->right;
			ghost.move(Xmove, 0);
			PlayerDirection = this->right;
			Downintersected = false;
			Leftintersected = false;
			Upintersected = false;
			count++;
		}
		break;

	}


}


void Ghosts::initializeGhost()
{
	GhostSprite.setTexture(GhostTexture); // thsi line is common for every derived ghost classes, so i can call this base class function to initialize the sprite with the texture
}


void Ghosts::setUpintersected(bool status)
{
	this->Upintersected = status;
}


void Ghosts::setDownintersected(bool status)
{
	this->Downintersected = status;
}


void Ghosts::setLeftintersected(bool status)
{
	this->Leftintersected = status;
}


void Ghosts::setRightintersected(bool status)
{
	this->Rightintersected = status;
}


bool Ghosts::getUpintersected()
{
	return Upintersected;
}


bool Ghosts::getDownintersected()
{
	return Downintersected;
}


bool Ghosts::getLeftintersected()
{
	return Leftintersected;
}


bool Ghosts::getRightintersected()
{
	return Rightintersected;
}


int Ghosts::getGhostDirection()
{
	return PlayerDirection;
}


void Ghosts::setGhostDirection(GhostDirections direction)
{
	this->PlayerDirection = direction;
}

void Ghosts::incrementGhostSpeed(float xSpeed, float ySpeed)
{
	this->Xmove = xSpeed;
	this->Ymove = ySpeed;
}


float Ghosts::getXspeed()
{
	return this->Xmove;
}

float Ghosts::getYspeed()
{
	return this->Ymove;
}


