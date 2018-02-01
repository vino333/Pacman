
//=============================includes========================================

#include "Board.h"
#include <fstream>
#include <string.h>
#include <cstdio>
#include "Ghost.h"
#include "Cookie.h"
#include "Wall.h"
#include <iostream>
#include "ImageResource.h"
#include <queue>
#include "SmartGhost.h"
#include "StupidGhost.h"

//=========================consts==============================================

const int MAX_FILE_NAME = 30;// maximum length of level file

// forward declerations
class GameObjects;
class UnMovable;

// C-tor
Board::Board(int levelNumber, Level &level)
	:m_pacman(*this, level), m_numOfCookies(0)
{
	readFile(levelNumber);// reading level 

	setBackground();// setting background of level

	setNumOfGhosts();// setting number of ghosts in level

	m_godMode=ImageResource::getSource().getGodMode();

	// BFS
	m_bfs = startBfs();
	m_demoBfs = startBfs();
}

//=============================================================================

//D-tor
Board::~Board()
{
	// deleting all allocations
	for (int i = 0; i < (int)m_boardSize.x; i++)
		for (int j = 0; j < (int)m_boardSize.y; j++)
			delete(m_wallsAndCookies[i][j]);

	for (int i = 0; i < (int)m_Ghosts.size(); i++)
		delete(m_Ghosts[i]);
}

//=============================================================================

// reading the level from file
void  Board::readFile(int levelNumber)
{
	std::ifstream myFile;

	char fileName[MAX_FILE_NAME];

	// creating the name for each level file
	sprintf_s(fileName, MAX_FILE_NAME, "level%d.txt", levelNumber);

	myFile.open(fileName);// opening file

	myFile.fail() ? m_pacman.ifLevelsFinished(true) : m_pacman.ifLevelsFinished(false);

	readObjectsToBoard(myFile);// turning the file to objects on the game board

	myFile.close();// closing the file
}

//=============================================================================

//set default to the bfs on the start
std::vector<std::vector<sf::Vector2i>> Board::startBfs()
{
	std::vector<std::vector<sf::Vector2i>> bfs;

	//if its not the end
	if (m_wallsAndCookies.size() != 0)
	{
		bfs.assign(m_wallsAndCookies.size(),
			std::vector<sf::Vector2i>(m_wallsAndCookies[0].size(),
				sf::Vector2i(0, 0)));
	}

	return bfs;
}

//=============================================================================

// turning the file to game objects on the board
void Board::readObjectsToBoard(std::ifstream & myFile)
{
	myFile >> m_boardSize.x >> m_boardSize.y; // reading board size

	// creating level board
	m_wallsAndCookies.assign(m_boardSize.x, std::vector<UnMoveAble*>(m_boardSize.y, nullptr));

	GameObject newObject;// name of new object to insert

	for (int row = 0; row < (int)m_boardSize.x; row++)
	{
		for (int col = 0; col < (int)m_boardSize.y; col++)
		{
			if (myFile.peek() == '\n')
				myFile.get();

			Ghost* newGhost;
			UnMoveAble* newUnmovable;

			// getting new objects name and pointer to insert to the game data structures
			newObject = getObjectToInsert(myFile, newGhost, newUnmovable);

			// setting new object posiotion
			sf::Vector2f currPlace((float)(SQARE_SIZE * col), (float)(SQARE_SIZE * row));

			switch (newObject)
			{
			case COOKIE:// inserting new cookie
			{
				m_wallsAndCookies[row][col] = newUnmovable;
				m_wallsAndCookies[row][col]->setCurrPlace(sf::Vector2f(currPlace.x + SQARE_SIZE / 4,
					currPlace.y + SQARE_SIZE / 4));
				m_wallsAndCookies[row][col]->setRowAndCol(row, col);
				break;
			}

			case WALL:// inserting new wall
			{
				m_wallsAndCookies[row][col] = newUnmovable;
				m_wallsAndCookies[row][col]->setCurrPlace(currPlace);
				m_wallsAndCookies[row][col]->setRowAndCol(row, col);
				break;
			}

			case PACMAN:// setting place of pacman
			{
				m_pacman.setOriginPlace(currPlace);
				m_pacman.setCurrPlace(currPlace);
				break;
			}

			case GHOST:// inserting new ghost
			{
				m_Ghosts.push_back(newGhost);
				m_Ghosts[m_Ghosts.size() - 1]->setOriginPlace(currPlace);
				m_Ghosts[m_Ghosts.size() - 1]->setCurrPlace(currPlace);
				break;
			}
			}
		}
	}
}

//=============================================================================

// function reads a char from the file and creats a new object according to it
GameObject Board::getObjectToInsert(std::ifstream& myFile, Ghost* &newGhost, UnMoveAble* &newUnmovable)
{
	char Char;

	//get the char
	myFile.get(Char);

	//switch case to find the correct object+color
	switch (Char)
	{
	case '@':
		m_pacman.setColor(RED);
		return PACMAN;

	case '#':
		newUnmovable = new Wall(RED);
		return WALL;

	case '%':
		rand()%2==0? newGhost = new SmartGhost(RED, *this):
			newGhost = new StupidGhost(RED, *this);
		return GHOST;

	case '*':
		newUnmovable = new Cookie(RED);
		m_numOfCookies++;
		return COOKIE;

	case 'W':
		m_pacman.setColor(GREEN);
		return PACMAN;

	case 'E':
		newUnmovable = new Wall(GREEN);
		return WALL;

	case 'T':
		rand() % 2 == 0 ? newGhost = new SmartGhost(GREEN, *this) :
			newGhost = new StupidGhost(GREEN, *this);
		return GHOST;

	case 'I':
		newUnmovable = new Cookie(GREEN);
		return COOKIE;

	case 'S':
		m_pacman.setColor(BLUE);
		return PACMAN;

	case 'D':
		newUnmovable = new Wall(BLUE);
		return WALL;

	case 'G':
		rand() % 2 == 0 ? newGhost = new SmartGhost(BLUE, *this) :
			newGhost = new StupidGhost(BLUE, *this); 
		return GHOST;

	case 'K':
		newUnmovable = new Cookie(BLUE);
		return COOKIE;
	}

	return SPACE;
}

//=============================================================================

// setting the background for the levels
void Board::setBackground()
{
	m_backround.setTexture(ImageResource::getSource().getTexture("background"));
}

//=============================================================================

// drawing background of the level
void Board::drawBackround(sf::RenderWindow& window)
{
	window.draw(m_backround);
}

//=============================================================================

// drawing static and not static objects current place on board
void Board::drawBoard(sf::RenderWindow& window)
{
	//draw the static objects
	for (int row = 0; row < (int)m_boardSize.x; row++)
		for (int col = 0; col < (int)m_boardSize.y; col++)
			if (m_wallsAndCookies[row][col] != nullptr)
				m_wallsAndCookies[row][col]->draw(window);

	//draw the ghost
	for (int ghost = 0; ghost < (int)m_Ghosts.size(); ghost++)
		m_Ghosts[ghost]->draw(window);

	//draw pacman
	m_pacman.draw(window);

	if (ImageResource::getSource().getCheatOn())// cheat game
		window.draw(m_godMode);
}

//=============================================================================

// setting number of ghosts in level 
void Board::setNumOfGhosts()
{
	m_numOfGhosts = m_Ghosts.size();

	m_pacman.setNumOfGhosts(m_numOfGhosts);
}

//=============================================================================

// setting pacmans direction of movement
void Board::setPacmanDirection(Direction pacmanDirection)
{
	m_pacman.setDirection(pacmanDirection);
}

//=============================================================================

// getting window size according to size of current level board size
sf::VideoMode Board::getWindowSize()const
{
	return sf::VideoMode(m_boardSize.y * SQARE_SIZE,
		m_boardSize.x * SQARE_SIZE + 75);
}

//=============================================================================

// moving ghosts and pacman 
void  Board::moveObjects(float time)
{
	m_pacman.move(time);// move pacman

	for (int i = 0; i < (int)m_Ghosts.size(); i++)// move ghosts
		m_Ghosts[i]->move(time);

	checKCollision(time);// checking collisions in game
}

//=============================================================================

// fucntion checks collision between pacman and wall,cookies or ghosts
void Board::checKCollision(float time)
{
	// calculating square at walls and cookies matrix
	sf::Vector2f stepToCheck = m_pacman.getPacmanCenter();

	stepToCheck.x = (stepToCheck.x - ((int)stepToCheck.x % SQARE_SIZE)) / SQARE_SIZE;
	stepToCheck.y = (stepToCheck.y - ((int)stepToCheck.y % SQARE_SIZE)) / SQARE_SIZE;

	/*stepToCheck=*/calNextTileToCheck(stepToCheck);
	
	// activating double dispach
	if (notOutOfStaticBoard(stepToCheck))// checking if the step is not out of range
	{
		// coliision with cookies and walls
		if (m_wallsAndCookies[(const unsigned)stepToCheck.y]
			[(const unsigned)stepToCheck.x] != nullptr)
		{
			GameObjects* object = m_wallsAndCookies[(const unsigned)stepToCheck.y]
				[(const unsigned)stepToCheck.x];

			stepToCheck.x *= SQARE_SIZE;
			stepToCheck.y *= SQARE_SIZE;

			m_pacman.setNextToCheck(sf::Vector2f(stepToCheck.x, stepToCheck.y));

			object->collide(m_pacman);
		}
	}

	// coliision with ghosts
	if (!ImageResource::getSource().getCheatOn())
		for (int ghostIndex = 0; ghostIndex < (int)m_Ghosts.size(); ghostIndex++) // collision with ghosts
		{
			GameObjects* ghost = m_Ghosts[ghostIndex];

			ghost->collide(m_pacman);
		}

	//control the cheat
	else if ((ImageResource::getSource().getLastCheatReset().asSeconds() -
		ImageResource::getSource().getStartTimer()) > 8)
			ImageResource::getSource().setcheat(false);
}
//=============================================================================

void Board::calNextTileToCheck(sf::Vector2f& stepToCheck)
{
	switch (m_pacman.getDirection())// calcualting the square to check according to direction
	{
	case RIGHT:stepToCheck.x++;
	break;

	case LEFT:stepToCheck.x--;
	break;

	case UP:stepToCheck.y--;
	break;

	case DOWN:stepToCheck.y++;
	break;
	}

	//return stepToCheck;
}

//=============================================================================

// function checks that the step to check is not out of range
bool Board::notOutOfStaticBoard(sf::Vector2f stepToCheck)
{
	return stepToCheck.x > -1 && stepToCheck.x<m_boardSize.y &&
		stepToCheck.y>-1 && stepToCheck.y < m_boardSize.x;
}

//=============================================================================

//the function that calculate ways from an item
std::vector<std::vector<sf::Vector2i>> Board::check_way(sf::Vector2i &start)
{
	////return the bfs that was faund
	return m_pacman.check_way(start, m_wallsAndCookies);// bfs;
}

//=============================================================================

void Board::setBfs(sf::Vector2f pacman)
{
	sf::Vector2i intPacman(pacman);

	m_bfs = check_way(intPacman);
}

//=============================================================================

const std::vector<std::vector<sf::Vector2i>>& Board::getBfs()
{
	return m_bfs;
}

//=============================================================================

const std::vector<std::vector<UnMoveAble*>>& Board::getWallsAndCookies()
{
	return m_wallsAndCookies;
}

//=============================================================================

// setting the ghosts in there original place
void Board::setGhostsInOriginPlace()
{
	for (int ghost = 0; ghost < (int)m_Ghosts.size(); ghost++)
		m_Ghosts[ghost]->setCurrPlace(m_Ghosts[ghost]->getOriginPlace());
}

//=============================================================================

void Board::setDemoBfs()
{
	srand((unsigned)time(nullptr));

	sf::Vector2i intDemo(rand() % (m_wallsAndCookies[0].size()),
		rand() % (m_wallsAndCookies.size()));

	do {
		intDemo = sf::Vector2i(rand() % (m_wallsAndCookies[0].size()),
			rand() % (m_wallsAndCookies.size()));
	} while (dynamic_cast<Wall*>(m_wallsAndCookies[intDemo.y][intDemo.x]));

	intDemo *= SQARE_SIZE;

	m_demoBfs = check_way(intDemo);
}

//=============================================================================

const std::vector<std::vector<sf::Vector2i>>& Board::getDemoBfs()
{
	return m_demoBfs;
}

//=============================================================================

void Board::restartMovableCounters()
{
	m_pacman.restartTimers();

	for (int ghost = 0; ghost < (int)m_Ghosts.size(); ghost++)
	{
		m_Ghosts[ghost]->restartTimers();
	}
}