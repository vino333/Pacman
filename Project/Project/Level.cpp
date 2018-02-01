
//=============================includes========================================

#include "Level.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cassert>
#include "ImageResource.h"
#include <string>
#include "MiddleMenu.h"

const int SQUARE_SIZE = 32;// size of square on board


// C-tor
Level::Level(int levelNumber, int lives, int score)
	:m_board(levelNumber, *this), levelsRunning(true), m_lives(lives), m_score(score), index(0)
{
	// settings for score board
	setDividingRects();

	setLivesAndScoreText();

	font = ImageResource::getSource().getFont();

	setLivesAndScoreNumbers();

	cheatCollision = { 'g','o','d' };

	cheatLives = { 'l','p','p' };

	cheatGhost = { 'g','m','m' };
}

//=============================================================================

Level::~Level()
{
}

//=============================================================================

// function runs the events of one level
void Level::run(sf::RenderWindow& window)
{
	window.create(m_board.getWindowSize(), 32u, sf::Style::Close);// level window

	sf::Clock clock; // clock for level

	// clock for pacman movement
	float thisTime = 0,
		lastTime = 0;

	if (m_board.getBoardSize().x == 0)// if there isnt a new level
		return;

	m_board.setDemoBfs();

	// while level still running
	while (window.isOpen() && m_board.getNumOfCookies() != 0 && m_lives != 0)
	{
		thisTime = clock.getElapsedTime().asSeconds();// getting current time

		if (thisTime - lastTime > 2)// timer for BFS
		{
			m_board.setDemoBfs();

			lastTime = thisTime;
		}


		window.clear();// clearing window

		getUsersMove(window, clock.getElapsedTime().asSeconds(), clock);// users move

		drawCurrentScreen(window);// drawing game

		window.display();// displating game
	}

	m_won = false;// player didnt win yet

	// updating player score when he finished a level
	updateScore(50 * (m_board.getNumOfGhosts() + 1));
}

//=============================================================================

// drawing current screen of game
void Level::drawCurrentScreen(sf::RenderWindow& window)
{
	m_board.drawBackround(window);// drawing backround

	drawLivesAndScore(window);// drawing lives and score

	m_board.drawBoard(window);// drawing current objects on game board
}

//=============================================================================

// setting pacmans direction to move
void Level::getUsersMove(sf::RenderWindow& window, float time, sf::Clock& clock)
{
	sf::Event event;

	if (window.pollEvent(event))
	{
		if (event.type == sf::Event::TextEntered)
		{
			cheatInput.push_back(event.key.code);
			index++;
		}

		if (event.type == sf::Event::Closed)// if player pressed on close
			m_lives = 0;

		if (event.type == sf::Event::KeyPressed)// if player moved pacman
			playerPressedArrow(event, window, clock);
	}

	if (index == 3)
		checkCheat();

	m_board.moveObjects(clock.getElapsedTime().asSeconds());// move pacman and ghosts
}

//=============================================================================

void Level::playerPressedArrow(sf::Event event, sf::RenderWindow& window, sf::Clock& clock)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Left: m_board.setPacmanDirection(LEFT), index = 0;
		break;

	case sf::Keyboard::Down: m_board.setPacmanDirection(DOWN), index = 0;
		break;

	case sf::Keyboard::Up: m_board.setPacmanDirection(UP), index = 0;
		break;

	case sf::Keyboard::Right: m_board.setPacmanDirection(RIGHT), index = 0;
		break;

	case sf::Keyboard::Space:m_board.setPacmanDirection(STAND), index = 0;
		break;

	case sf::Keyboard::Escape:// rinning middle menu
		startMiddleMenu(window, clock);
		break;
	}
}

//=============================================================================

// drawing current score and lives of player
void Level::drawLivesAndScore(sf::RenderWindow& window)
{
	window.draw(m_scoreText);

	window.draw(m_livesText);

	window.draw(dividegTop);

	window.draw(dividegDown);

	setCurrentScoreAndLives();

	window.draw(m_scoreNumber);

	window.draw(m_livesNumber);
}

//=============================================================================

// calculating the bounds for score and live section
void Level::setDividingRects()
{
	// top dividing rect
	dividegTop.setSize(sf::Vector2f(m_board.getBoardSize().x * SQUARE_SIZE, 8));
	dividegTop.setFillColor(sf::Color(67, 140, 31));
	dividegTop.setPosition(0, m_board.getBoardSize().x * SQUARE_SIZE + 1);

	// down dividing rect
	dividegDown.setSize(sf::Vector2f(m_board.getBoardSize().x * SQUARE_SIZE, 8));
	dividegDown.setFillColor(sf::Color(67, 140, 31));
	dividegDown.setPosition(0, m_board.getBoardSize().x * SQUARE_SIZE + 70);
}

//=============================================================================

//  function sets the live and score text on the level's board
void Level::setLivesAndScoreText()
{
	// setting score text
	m_scoreText = ImageResource::getSource().getScoreFont();
	m_scoreText.setPosition(sf::Vector2f(0, m_board.getBoardSize().x * SQUARE_SIZE + 5));
	m_scoreText.setCharacterSize(50);
	m_scoreText.setFillColor(sf::Color(67, 140, 31));

	// setting live text
	m_livesText = ImageResource::getSource().getLivesFont();
	m_livesText.setPosition(sf::Vector2f(m_board.getBoardSize().x * SQUARE_SIZE / 2 + SQARE_SIZE,
		m_board.getBoardSize().x * SQUARE_SIZE + 5));
	m_livesText.setCharacterSize(50);
	m_livesText.setFillColor(sf::Color(67, 140, 31));
}

//=============================================================================

// function sets the lives and score fons size and color of the player
void Level::setLivesAndScoreNumbers()
{
	m_scoreNumber.setFont(font);// setting font
	m_livesNumber.setFont(font);

	m_scoreNumber.setCharacterSize(35);// setting size
	m_livesNumber.setCharacterSize(35);

	m_scoreNumber.setFillColor(sf::Color(182, 78, 242));// setting color
	m_livesNumber.setFillColor(sf::Color(182, 78, 242));

	// setting position
	m_scoreNumber.setPosition(sf::Vector2f(SQARE_SIZE*4.3, m_board.getBoardSize().x * SQUARE_SIZE + 20));
	m_livesNumber.setPosition(sf::Vector2f(m_board.getBoardSize().x * SQUARE_SIZE / 2 + 160,
		m_board.getBoardSize().x * SQUARE_SIZE + 20));
}

//=============================================================================

// function sets current number of score and lives
void Level::setCurrentScoreAndLives()
{
	// convrting the numbers to strings
	std::string text1 = std::to_string(m_score);
	std::string text2 = std::to_string(m_lives);

	// setting the strings
	m_scoreNumber.setString(text1);
	m_livesNumber.setString(text2);
}

//=============================================================================

void Level::checkCheat()
{
	if (cheatCollision == cheatInput)
		ImageResource::getSource().setcheat(true);

	if (cheatLives == cheatInput)
		m_lives++;
	if (cheatGhost == cheatInput)
	{
		m_board.deleteGhost();
		m_board.setNumOfGhosts();
	}

	index = 0;

	cheatInput.clear();
}

//=============================================================================

void  Level::startMiddleMenu(sf::RenderWindow& window, sf::Clock& clock)
{
	m_board.setPacmanDirection(STAND);

	index = 0;

	ImageResource::getSource().stopBackgroundMusic();

	MiddleMenu menu;

	menu.run();

	if (ImageResource::getSource().getDone())
	{
		m_lives = 0;
		window.close();
	}
	else
	{
		m_board.restartMovableCounters();
		clock.restart();
	}
}