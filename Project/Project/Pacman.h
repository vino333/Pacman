
//=============================includes========================================

#pragma once
#include <iostream>
#include "MoveAble.h"

//=============================forwared declerations==============================

class Board;
class Cookie;
class Level;

//====================class decerations========================================

class Pacman : public MoveAble
{
public:
	Pacman(Board&, Level&);
	void setColor(int color) { m_color = color; };

	// pacman movement
	Direction getDirection()const { return m_direction; };
	void setDirection(Direction);
	void move(float)override;
	void checkIfOutOfBoard(float);
	void setNextToCheck(sf::Vector2f vec) { stepToCheck = vec; };
	bool checkIfOutOfBoard(sf::Vector2f, const std::vector<std::vector<UnMoveAble*>> &);
	std::vector<std::vector<sf::Vector2i>> check_way(sf::Vector2i &start,
		const std::vector<std::vector<UnMoveAble*>> &board);
	std::vector<sf::Vector2i> getNeighbors(const sf::Vector2i &center,
		const std::vector<std::vector<UnMoveAble*>> &board);
	void bfs();
	void changeImage(float &picture);

	// pacman images
	//void draw(sf::RenderWindow& window);
	sf::Sprite getCurrentImage() const{ return m_image; };
	sf::Sprite getNextImage(Direction)const;
	sf::Sprite getImageIfChangedDirection(Direction m_direction)const;

	// pacman locations
	sf::Vector2f getCurrPlace()const { return m_currPlace; };
	sf::Vector2f getPacmanCenter()const;

	//lives and score
	void setNumOfGhosts(int ghosts) { m_numOfGhosts = ghosts; };
	void checkTimer();
	void ifLevelsFinished(bool isFinished);
	void eatCookie(Cookie&);
	void pacmanDie();

	//--------------------collision double dispach----------------------------------
	virtual void collide(GameObjects& other)
	{
		other.collide(*this);
	};
	virtual void collide(Ghost& other);
	virtual void collide(Wall& other);
	virtual void collide(Cookie& other);

private:
	// pacman images
	sf::Sprite m_images[4][2];
	bool open;

	Direction m_lastDirection;

	// clockn related
	float m_speed;
	float m_stepSize;
	float m_originalSpeed;
	float m_timeOfChange;
	float m_timerForCookies;
	
	sf::Vector2f stepToCheck;// pacman step for collision
	sf::Vector2f m_nextStep;

	int m_numOfGhosts;
	float m_radius;// radius for eating cookie
	int m_color;

	Level& m_level;// refernce for level
};

