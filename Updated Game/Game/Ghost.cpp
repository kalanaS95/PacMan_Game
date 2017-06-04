#pragma once
#include "Ghost.h"


Ghost::Ghost()
{


	void movement(Event &GameEvent, Vector2i &vector, Sprite &player);


}




Ghost::~Ghost()
{
}
void Ghost::initializeGhost()
{
	GhostSprite.setTexture(GhostTexture); // this line is common for every derived ghost classes, so i can call this base class function to initialize the sprite with the texture
}
void Ghost::movement(Vector2i &vector, Sprite &player)
{




	Ghosts::movement(vector, player);




}
