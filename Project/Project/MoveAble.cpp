
//=============================includes========================================

#include "MoveAble.h"
#include "Board.h"

// C-tor
MoveAble::MoveAble(Board&board)
:m_board(board),m_direction(STAND), m_nextDirection(STAND), m_currentTime(0), m_lastTime(0)
{
}

//=============================================================================

// function checks if a movable object can now change his direction
bool MoveAble::canChangeDirection()
{
	return ((int)m_currPlace.x % 32 <= 1 || (int)m_currPlace.x % 32 >= 31) &&
		((int)m_currPlace.y % 32 <= 1 || (int)m_currPlace.y % 32 >= 31);
}

//=============================================================================

//this function do the steps
sf::Vector2f MoveAble::doStep(float step)
{
	sf::Vector2f move = { 0,0 };

	switch (m_direction)
	{
	case RIGHT:move.x += step;
		break;

	case LEFT:move.x -= step;
		break;

	case UP:move.y -= step;
		break;

	case DOWN:move.y += step;
		break;
	}

	return move;
}

//=============================================================================

//preper for moving
float MoveAble::beforeMoving(float time, float &picture)
{
	m_currentTime = time;

	float step_size = m_currentTime - m_lastTime;

	if (canChangeDirection() && step_size != 0)
		m_direction = m_nextDirection;

	picture += step_size;

	m_lastTime = m_currentTime;

	return step_size;
}