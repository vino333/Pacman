
//=============================includes========================================

#include "ImageResource.h"
#include "Menu.h"

// C-tor
Menu::Menu()
	:MainMenu()
{	
	// getting play button image
	m_menueImages[1].setTexture((ImageResource::getSource().getTexture("playButton")));

	m_menueImages[1].setPosition(150, 60);// setting play button posiotion
    //m_menueImages[1].setPosition(150, 90);// setting play button posiotion
	
//	m_highlightOn1.setPosition(230, 152);// setting highlight position
	m_highlightOn1.setPosition(230, 120);// setting highlight position
}

//=============================================================================

//D-tor
Menu::~Menu()
{
}

//=============================================================================

// function gets events from player
int  Menu::getOptionFromUser(sf::RenderWindow& window)
{
	sf::Event event;

	if (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)// if player wants to exit
			return EXIT;

		if (event.type == sf::Event::MouseButtonPressed)
		{
			int m_x = event.mouseButton.x;
			int m_y = event.mouseButton.y;
		
			// if player wants to play a new game
			if (m_x > 233 && m_x < 436 && m_y > 129 && m_y < 179)
				return PLAY;

			// if player pressed the help button
			if (m_x > 232 && m_x < 429 && m_y > 251 && m_y < 296)
				return HELP;

			// if player pressed the exit button
			if (m_x > 230 && m_x < 436 && m_y > 370 && m_y < 416)
				return EXIT;
		}
	}

	drawTransparent(window);// drawing highlighting rectangle
	
	return NOTHING;// if player didnt do anything
}








































































