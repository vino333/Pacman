
//=============================includes========================================

#pragma once
#include <SFML\Graphics.hpp>
#include "ImageResource.h"

//=============================classes prototypes==============================

class Cookie;
class Wall;
class Ghost;

//================================consts=======================================

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;
const int SQARE_SIZE = 32;

//====================class decerations========================================

class GameObjects
{
public:
	GameObjects() {}
	virtual ~GameObjects() = 0 {}
	void draw(sf::RenderWindow&);
	void setCurrPlace(sf::Vector2f);
	sf::Sprite getCurrentImage()const { return m_image; };
	sf::Vector2f getCurrPlace()const { return m_currPlace; };

	//--------------------collision double dispach----------------------------------
    virtual void collide(GameObjects& other) = 0;
	virtual void collide(Ghost& other) = 0;;
	virtual void collide(Wall& other) = 0;
	virtual void collide(Cookie& other) = 0;

protected:
	sf::Sprite m_image;// current image

	sf::Vector2f m_currPlace;
	int m_color;
};

