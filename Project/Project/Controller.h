
//=============================includes========================================

#pragma once
#include "Menu.h"
#include "Pacman.h"

//====================class decerations========================================

class Controller
{
public:
	Controller();
	~Controller();

	// running+winning+losing the game
	void run(sf::RenderWindow&);
	void endGame();// end of game-win or lose
	void checkEvent(sf::RenderWindow&);

private:
	int m_levelNum;// current level number
	
	// lives and score of player
	static int m_lives;
	static int m_score;

	// if player won the game
	bool playerWon;

	sf::Sprite m_win;
	sf::Sprite m_lose;
};

