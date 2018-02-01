
//=============================includes========================================

#include "Pacman.h"
#include <cassert>
#include <iostream>
#include "UnMoveAble.h"
#include "Cookie.h"
#include "Board.h"
#include "Level.h"
#include <queue>
#include "Wall.h"

//=============================================================================

// C-tor
Pacman::Pacman(Board&board, Level&level)
	:MoveAble(board), m_lastDirection(STAND), open(false), m_speed(150), m_radius(22.5), m_level(level), m_timeOfChange(0)
	, m_originalSpeed(150), m_color(0)
{
	//get from source pictures
	for (int i = 0; i < 4; i++)
	{
		m_images[i][0] = ImageResource::getSource().getPacman(i, 0);
		m_images[i][1] = ImageResource::getSource().getPacman(i, 1);
		m_images[i][0].setColor(sf::Color::Yellow/*(ImageResource::getSource().getColor(m_color))*/);
		m_images[i][1].setColor(sf::Color::Yellow/*(ImageResource::getSource().getColor(m_color))*/);
	}
	m_image = m_images[0][0];// setting first image
}

//============================================================================

// setting pacmans direction
void Pacman::setDirection(Direction pacmanDirection)
{
	m_nextDirection = pacmanDirection;
}

//===========================================================================

// function checks if player can change direction and moves him
void Pacman::move(float time)
{
	static float picture = 0;

	m_stepSize = beforeMoving(time, picture);

	m_nextStep = m_currPlace;

	checkTimer();

	m_currPlace += doStep(m_speed*m_stepSize);

	checkIfOutOfBoard(m_stepSize);// checking if pacman is trying to go out of range

	changeImage(picture);// changing current inmage of pacman

	m_lastDirection = m_direction;

	bfs();// doing BFS
}

//=============================================================================

// function changes if possible the current image for pacman
void Pacman::changeImage(float &picture)
{
	if (m_direction != STAND)
	{
		if (m_lastDirection != m_direction)
			m_image = getImageIfChangedDirection(m_direction);

		if (picture >= 0.05)
		{
			m_image = getNextImage(m_direction);
			picture = 0;
			open = !open;
		}
	}
}

//=============================================================================

//this function do bfs ones in 2 times
void Pacman::bfs()
{
	static bool bfs;
	bfs = !bfs;

	if (bfs)
		m_board.setBfs(m_currPlace);
}

//=============================================================================

// checking the timer for cookie affect
void  Pacman::checkTimer()
{
	// getting time that passed since cookie started to affect
	float currentTime = ImageResource::getSource().getLastCookieReset().asSeconds();

	// if time passed
	if ((currentTime - m_timerForCookies) > m_timeOfChange)
	{
		m_speed = m_originalSpeed;// changing pacman speed

		ImageResource::getSource().resetCookieClock();// reseting clock
	}
}

//=============================================================================

// if pacman is out of board-fixing his step/walking throw the board
void Pacman::checkIfOutOfBoard(float step_size)
{
	std::vector<std::vector<UnMoveAble*>> board = m_board.getWallsAndCookies();

	//left part
	if (m_currPlace.x < 0)
		dynamic_cast<Wall*>(board[(m_currPlace.y+2) / SQARE_SIZE][m_board.getBoardSize().y - 1])?
			m_currPlace.x = 0:
			m_currPlace.x = (float)m_board.getBoardSize().y* SQARE_SIZE - SQARE_SIZE;

	//up part
	if (m_currPlace.y < 0)
		dynamic_cast<Wall*>(board[m_board.getBoardSize().x-1][(m_currPlace.x+2) / SQARE_SIZE])?
			m_currPlace.y = 0:
			m_currPlace.y = (float)m_board.getBoardSize().x * SQARE_SIZE - SQARE_SIZE;

	//right part
	if (m_currPlace.x > m_board.getBoardSize().y * SQARE_SIZE - SQARE_SIZE)
		dynamic_cast<Wall*>(board[(m_currPlace.y+2) / SQARE_SIZE][0]) ?
		m_currPlace.x = m_board.getBoardSize().y * SQARE_SIZE - SQARE_SIZE:
			m_currPlace.x = 0;

	//down part
	if (m_currPlace.y > m_board.getBoardSize().x * SQARE_SIZE - SQARE_SIZE)
		dynamic_cast<Wall*>(board[0][(m_currPlace.x+2) / SQARE_SIZE]) ?
		m_currPlace.y = m_board.getBoardSize().x * SQARE_SIZE - SQARE_SIZE:
			m_currPlace.y = 0;
}

//=============================================================================

// function gets next image for pacman's movement
sf::Sprite Pacman::getNextImage(Direction direction)const
{
	return m_images[direction][open ? 1 : 0];
}

//=============================================================================

// getting image if direction was changed
sf::Sprite Pacman::getImageIfChangedDirection(Direction m_direction)const
{
	return m_images[m_direction][0];
}

//=============================================================================

// function calculates pacmans's sprite center
sf::Vector2f Pacman::getPacmanCenter()const
{
	sf::Vector2f pacmanCenter = getCurrPlace();

	pacmanCenter.x += SQARE_SIZE / 2;
	pacmanCenter.y += SQARE_SIZE / 2;

	return pacmanCenter;// returning center
}

//=============================================================================

//--------------------double dispach-------------------------------------------

//==============================================================================

// function hadles collision between pacman and wall
void Pacman::collide(Wall& other)
{
	sf::Vector2f curr = m_currPlace;// current place of pacman

	// if direction is right or left
	if (m_direction == RIGHT || m_direction == LEFT)
		if (abs(getCurrPlace().x - stepToCheck.x) < SQARE_SIZE)
		{
			switch (getDirection())// correction position
			{
			case RIGHT:setCurrPlace(sf::Vector2f(curr.x -= m_stepSize * m_speed, curr.y));
				break;

			case LEFT:setCurrPlace(sf::Vector2f(curr.x += m_stepSize * m_speed, curr.y));
				break;
			}
		}

	// if direction is up or down
	if (m_direction == UP || m_direction == DOWN)
		if (abs(getCurrPlace().y - stepToCheck.y) < SQARE_SIZE)
		{
			switch (getDirection())// correction position
			{
			case UP:setCurrPlace(sf::Vector2f(curr.x, curr.y += m_stepSize * m_speed));
				break;

			case DOWN:setCurrPlace(sf::Vector2f(curr.x, curr.y -= m_stepSize * m_speed));
				break;
			}
		}
}

//==============================================================================

// function hadles collision between pacman and cookie
void Pacman::collide(Cookie& cookie)
{
	sf::Vector2f pacmanCenter = getPacmanCenter();// getting pacman center

	// calculating center of cookie
	sf::Vector2f cookieCenter(cookie.getCol()*SQARE_SIZE, cookie.getRow()*SQARE_SIZE);

	cookieCenter.x += SQARE_SIZE / 2;
	cookieCenter.y += SQARE_SIZE / 2;

	// checking if can eat cookie
	switch (m_direction)
	{
	case UP:
	case DOWN:
		if (abs(cookieCenter.y - pacmanCenter.y) <= m_radius)
			eatCookie(cookie);
		break;

	case RIGHT:
	case LEFT:
		if (abs(cookieCenter.x - pacmanCenter.x) <= m_radius)
			eatCookie(cookie);
		break;
	}
}

//==============================================================================

// fucntion habdles an eating of a cookie from the game board
void Pacman::eatCookie(Cookie& cookie)
{
	ImageResource::getSource().playEatCookie();// playing music for eating a cookie

	if (cookie.getEffectOnPacman() != 1)// new speed according to cookie
	{
		m_speed *= cookie.getEffectOnPacman();
		m_timeOfChange = cookie.getTimeForChange();// numbe of seconds of new speed
	}

	m_level.updateScore((m_numOfGhosts + 1) * 2);// updating player score

	if (cookie.getTimeForChange() == 0)
		m_board.reduceCookies();// number of cookies in level --

	// place of cookie on board
	int row = cookie.getRow(),
		col = cookie.getCol();

	delete(m_board.getCell(cookie.getRow(), cookie.getCol()));// deleting pointer

	m_board.deleteCookie(row, col);// deleting the cookie

	m_timerForCookies = ImageResource::getSource().getLastCookieReset().asSeconds();// start timer
}

//=============================================================================

// function hadles collision between pacman and ghost
void Pacman::collide(Ghost& ghost)
{
	sf::Vector2f ghostPlace = ghost.getCurrPlace();// getting ghost location

	// checking if ghost killed pacman
	if (abs(m_currPlace.x - ghostPlace.x) < SQARE_SIZE - 2 && abs(m_currPlace.y - ghostPlace.y) < SQARE_SIZE - 2)
		pacmanDie();// pacman dies
}

//=============================================================================

// function handles the dying of pacman
void Pacman::pacmanDie()
{
	m_level.reduceLives();// lives--

	m_board.setGhostsInOriginPlace();// reaseting ghosts place

	m_currPlace = m_originPlace;// reaseting pacman place

	m_nextDirection = STAND;   // reseting pacman direction

	m_image = m_images[0][0];// reseting start pacman image

	open = false;     // reseting image
}

//=============================================================================

//the function that calculate ways from an item
std::vector<std::vector<sf::Vector2i>> Pacman::check_way(sf::Vector2i &start,
	const std::vector<std::vector<UnMoveAble*>> &board)
{
	start += sf::Vector2i(16,16);
	start /= 32;

	//set a vector for a bfs
	std::vector<std::vector<sf::Vector2i>> bfs;

	//put 0 in the vector
	bfs.assign(board[0].size(), std::vector<sf::Vector2i>(board.size(),
		sf::Vector2i(-1, -1)));

	//set a queue to hold cordinate
	std::queue<sf::Vector2i> que;

	//put cordinate in the queue
	que.push(start);

	//chek if the queue is empty
	while (!que.empty())
	{
		//take a cordinate from the queue
		sf::Vector2i current = que.front();
		que.pop();

		//set a vector of all the legal neighboors
		std::vector<sf::Vector2i> neighbors = getNeighbors(current, board);

		//check all the neighbors and set them ways 
		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			//set next and check it
			sf::Vector2i next = neighbors[i];

			//if its a good neighbor, set his way
			if ((next.y != start.y || next.x != start.x) &&
				bfs[next.x][next.y].x == -1)
			{
				que.push(next);
				bfs[next.x][next.y].x = current.x;
				bfs[next.x][next.y].y = current.y;
			}
		}
	}

	//return the bfs that was faund
	return bfs;
}

//=============================================================================

//get all the legal neighbors of a cordinate
std::vector<sf::Vector2i> Pacman::getNeighbors(const sf::Vector2i &center,
	const std::vector<std::vector<UnMoveAble*>> &board)
{
	//vector of the ways to the neighbors
	std::vector<sf::Vector2i> shifts = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };

	//set vector to hold the result
	std::vector<sf::Vector2i> neighbors;

	sf::Vector2i next;

	//this board check if a neighbor is legal
	for (int i = 0; i < 4; i++)
	{
		next = center + shifts[i];

		if (checkIfOutOfBoard((sf::Vector2f)next, board) &&
			!dynamic_cast<Wall*> (board[next.y][next.x]))
			neighbors.push_back(next);
	}

	//return the neighbors
	return neighbors;
}

//=============================================================================

// function checks if player finished levels and updates level division
void Pacman::ifLevelsFinished(bool isFinished)
{
	isFinished ? m_level.ifLevelsFinished(true) : m_level.ifLevelsFinished(true);
}

//=============================================================================

// if out of board
bool Pacman::checkIfOutOfBoard(sf::Vector2f place,
	const std::vector<std::vector<UnMoveAble*>> &board)
{
	return !(place.x < 0 || place.y < 0 || place.x >= board[0].size() ||
		place.y >= board.size());
}