///// Ghost.h//////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "GhostsBase.h"
class Ghost :
	public Ghosts
{
public:
	Ghost();
	~Ghost();


	void Ghosts::initializeGhost();
	virtual void movement(Vector2i &vector, Sprite &player);
};

