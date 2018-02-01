
//=============================includes========================================


//=============================includes========================================

#pragma once
#include "GameObjects.h"
#include "UnMoveAble.h"

//=============================classes prototypes==============================

class Board;
enum Direction { RIGHT, DOWN, LEFT, UP, STAND };

//====================class decerations========================================

class MoveAble:public GameObjects
{
public:
	MoveAble(Board& board);
	virtual ~MoveAble() = 0 {}
	// object position
	virtual sf::Vector2f getOriginPlace() const{ return m_originPlace; };
	virtual void setOriginPlace(sf::Vector2f place) { m_originPlace = place; };
	bool canChangeDirection();
	virtual void move(float) = 0;// pure virtual movment function
	sf::Vector2f doStep(float);
	float beforeMoving(float time, float &picture);
	void restartTimers() { m_currentTime = 0; m_lastTime = 0; };

protected:
	// object location and direction
	sf::Vector2f m_originPlace;
	Direction m_nextDirection;
	Direction m_direction;
	float m_lastTime;
	float m_currentTime;

	Board& m_board;// reference to game board
};

