#pragma once

# include "CharacterBase.h"

class MaleCharacter :public Character {

public:
	MaleCharacter(Event &event);
	void movement(Event &GameEvent, Vector2i &vector, Sprite &player);


protected:


};