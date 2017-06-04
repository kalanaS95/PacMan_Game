# include "MaleCharacter.h"



MaleCharacter::MaleCharacter(Event &event)
{
	this->myEvent = event;
	health = 100;
	
}

void MaleCharacter::movement(Event &GameEvent, Vector2i &vector, Sprite &player)
{
	//std::cout << "derived movement" << std::endl;
	Character::movement(GameEvent,vector,player);


}

