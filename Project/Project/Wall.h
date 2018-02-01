
//=============================includes========================================

#pragma once
#include "UnMoveAble.h"

//============================forward declerations=============================

class Wall:public UnMoveAble
{
public:
	Wall(int);
	~Wall();

	//--------------------collision double dispach-----------------------------
	virtual void collide(GameObjects& other)
	{
		other.collide(*this);
	};
	virtual void collide(Ghost& other) {};
	virtual void collide(Wall& other) {};
	virtual void collide(Cookie& other) {};
};

