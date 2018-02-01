
//=============================includes========================================

#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "UnMoveAble.h"
#include "MoveAble.h"
#include "Ghost.h"
#include "Pacman.h"

//=============================classes prototypes==============================

class Level;

//==========================enum===============================================

enum GameObject { PACMAN, COOKIE, WALL, GHOST,SPACE };

//====================class decerations========================================

class Board
{
public:
	Board(int,Level& level);
	~Board();

	//c-tor functions
	void readFile(int);
	void readObjectsToBoard(std::ifstream &);
	std::vector<std::vector<sf::Vector2i>> startBfs();
	GameObject getObjectToInsert(std::ifstream&, Ghost*&, UnMoveAble*&);

	// ghosts in level
	void setNumOfGhosts();
	int getNumOfGhosts()const { return m_Ghosts.size(); };
	void deleteGhost() { m_Ghosts.pop_back();};

	//window functions
	sf::VideoMode getWindowSize()const;
	sf::Vector2u getBoardSize()const{ return m_boardSize; };

	 //drawing functions
	void setBackground();
	void drawBackround(sf::RenderWindow&);
	void drawBoard(sf::RenderWindow&);
	
	//moving functions
	void setPacmanDirection(Direction pacmanDirection);
	void moveObjects(float);
	void checKCollision(float);
	bool notOutOfStaticBoard(sf::Vector2f);
	UnMoveAble * getCell(int i, int j)const { return m_wallsAndCookies[i][j]; };
	void deleteCookie(int i, int j) { m_wallsAndCookies[i][j] = nullptr; };
	void reduceCookies() { m_numOfCookies--; };
	int getNumOfCookies() const { return m_numOfCookies; };
	void setGhostsInOriginPlace();
	void restartMovableCounters();
	void calNextTileToCheck(sf::Vector2f&);
	
	//bfs functions
	std::vector<std::vector<sf::Vector2i>>  check_way(sf::Vector2i &);
	void setBfs(sf::Vector2f);
	const std::vector<std::vector<sf::Vector2i>>& getBfs();
	void setDemoBfs();
	const std::vector<std::vector<sf::Vector2i>>& getDemoBfs();
	const std::vector<std::vector<UnMoveAble*>>& getWallsAndCookies();
	
private:
	sf::Vector2u m_boardSize;// game board size

	//saving the background
	sf::Sprite m_backround;
	sf::Texture m_backgroundName;
	sf::Sprite m_scorBoard;

	// game objects data structures
	std::vector<std::vector<UnMoveAble*>> m_wallsAndCookies;
	std::vector<Ghost*> m_Ghosts;
	Pacman m_pacman;// THE PLAYER
	std::vector<std::vector<sf::Vector2i>> m_bfs;
	std::vector<std::vector<sf::Vector2i>> m_demoBfs;

	int m_numOfGhosts;// number of ghosts in level
	int m_numOfCookies;//number of red cookies in level

	sf::Text m_godMode;
};

