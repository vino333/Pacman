
//=============================includes========================================

#pragma once
#include "Board.h"
#include "Pacman.h"

//====================class decerations========================================

class Level
{
public:
	Level(int, int, int);
	~Level();
	void run(sf::RenderWindow&);

	//draw and move functions
	void drawCurrentScreen(sf::RenderWindow&);
	void drawLivesAndScore(sf::RenderWindow&);
	void getUsersMove(sf::RenderWindow&, float, sf::Clock&);

	//live and score functions
	void setDividingRects();
	void setLivesAndScoreText();
	void setLivesAndScoreNumbers();
	void setCurrentScoreAndLives();
	void setLives() { m_lives = 0; };
	int getScore()const { return m_score; };
	int getLives() const{ return m_lives; };
	void updateScore(int scoreToAdd) { m_score += scoreToAdd; };
	void reduceLives() { m_lives--; };
	bool getIfWin() const{ return m_won; };
	void ifLevelsFinished(bool isFinished) { isFinished ? m_won = true : m_won = false; };
	void startMiddleMenu(sf::RenderWindow& , sf::Clock& );
	void playerPressedArrow(sf::Event,sf::RenderWindow&, sf::Clock&);


	void checkCheat();
private:
	Board m_board;// game board

	// lives and score text variables
	sf::Text m_scoreText;
	sf::Text m_livesText;

	sf::Text m_scoreNumber;
	sf::Text m_livesNumber;

	sf::Font font;// for lives and score numbers

	sf::RectangleShape dividegTop;
	sf::RectangleShape dividegDown;

	// lives and score
	int m_lives;
	int m_score;

	// for running of the level
	bool levelsRunning;
	bool m_won;

	std::string cheatCollision;
	std::string cheatLives;
	std::string cheatInput;
	std::string cheatGhost;

	int index;
};

