
//=============================includes========================================

#pragma once
#include "MoveAble.h"

//=============================classes prototypes==============================

class Board;

//====================class decerations========================================

class Ghost :public MoveAble
{
public:
	Ghost(int,Board&);
	virtual~Ghost() = 0 {}
	virtual Direction getNextStep() = 0;
	sf::Sprite getNextImage(Direction)const;

	//--------------------collision double dispach----------------------------------
	virtual void collide(GameObjects& other)
	{
		other.collide(*this);
	};
	virtual void collide(Ghost& other) {};
	virtual void collide(Wall& other) {};
	virtual void collide(Cookie& other) {};
	
	//moving functions
	void move(float) override;
	Direction wayTo(const std::vector<std::vector<sf::Vector2i>> &,
		const sf::Vector2i &);
	void switchImages(float);

private:
	sf::Sprite m_ghostImages[4][2];
	bool Legs;
};


