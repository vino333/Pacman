
//=============================includes========================================

#include "Wall.h"

const int WALL = 2;

// C-tor
Wall::Wall(int color)
{
	// getting image of wall
	m_image.setTexture(ImageResource::getSource().getTexture("wall"));

	// coloring image 
	m_image.setColor(sf::Color(ImageResource::getSource().getColor(color)));
}

//=============================================================================

// D-tor
Wall::~Wall()
{
}

