#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif

//=============================includes========================================

#include <Windows.h>
#include "Controller.h"
#include "Level.h"

//=============================================================================

// C-tor
Controller::Controller()
	:m_levelNum(0), playerWon(false)
{
	ImageResource::getSource().playBackgroundMusic();// starting game music
	
	// reseting lives and score for game
	m_lives = 3;
	m_score = 0;

	//set the textures to winning and losing
	m_win.setTexture(ImageResource::getSource().getTexture("win"));
	m_lose.setTexture(ImageResource::getSource().getTexture("lose"));
}

//=============================================================================

// D-tor
Controller::~Controller()
{
}

//=============================================================================

// function runs the levels of the game untill the player wins or loses
void Controller::run(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		do// levels loop
		{
			m_levelNum++;// going to next level

			Level level(m_levelNum,m_lives,m_score);// creating new level

			level.run(window);// running level

			playerWon = level.getIfWin();// checking if player won

			m_lives = level.getLives();// current lives of player

			m_score = level.getScore();// current score of player

		} while (m_lives != 0 && !playerWon);// while player didnt lose

		window.close();// closing game window

		ImageResource::getSource().stopBackgroundMusic();// stoping game music

		endGame();

		//loop to close window
		if (ImageResource::getSource().getDone())
		{
			window.close();
			return;
		}

		Menu menu;
		menu.run();// running menue again
	}
}

//=============================================================================

//function to end game with the correct message
void Controller::endGame()
{
	//set the window
	sf::RenderWindow window(sf::VideoMode((float)780, (float)488), 32u, sf::Style::Close);

	//show the message
	while (window.isOpen())
	{
		window.clear();

		playerWon ? window.draw(m_win) : window.draw(m_lose);

		checkEvent(window);

		window.display();
	}
}

//=============================================================================

//check if asked to close message window
void Controller::checkEvent(sf::RenderWindow& window)
{
	sf::Event event;

	if (window.pollEvent(event))
		if ((event.type == sf::Event::KeyPressed && event.key.code ==
			sf::Keyboard::Space)||event.type == sf::Event::Closed)// if asked to quit
			window.close();
}
//=============================================================================

//--------------------intitializing static variables---------------------------
int  Controller::m_lives = 3;
int  Controller::m_score = 0;