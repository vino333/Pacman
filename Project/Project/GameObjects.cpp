
//=============================includes========================================

#include "GameObjects.h"

//=============================consts==========================================

const int PACMAN = 0;
const int GHOST = 1;
const int WALL = 2;
const int COOKIE = 3;

//=============================================================================

// drawing object
void GameObjects::draw(sf::RenderWindow& window)
{
	m_image.setPosition(m_currPlace);

	window.draw(m_image);
}

//=============================================================================

// setting currnt place of object
void GameObjects::setCurrPlace(sf::Vector2f place)
{
	m_currPlace = place;
}

//=============================================================================

