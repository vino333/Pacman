
//=============================includes========================================

#pragma once
#include "UnMoveAble.h"

//====================class decerations========================================

class Cookie:public UnMoveAble
{
public:
	Cookie(int );
	~Cookie();

	// cookie affect on pacman
	float getEffectOnPacman() const { return m_factor; }
	float getTimeForChange() const { return m_time; };

	//--------------------collision double dispach----------------------------------
	virtual void collide(GameObjects& other)
	{
		other.collide(*this);
	};
	virtual void collide(Ghost& other) {};
	virtual void collide(Wall& other) {};
	virtual void collide(Cookie& other) {};

private:
	sf::Sprite m_cookies[3];// images
	
	// affect on pacman
	float m_factor;
	float m_time;
};

