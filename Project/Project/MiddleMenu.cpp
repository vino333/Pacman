
//=============================includes========================================

#include "MiddleMenu.h"

//C-tor
MiddleMenu::MiddleMenu()
	:MainMenu()
{
	// getting resume button image
	m_menueImages[1].setTexture(ImageResource::getSource().getTexture("resumeButton"));

	m_menueImages[1].setPosition(156, 115);// setting resume button position

	//m_highlightOn1.setPosition(230, 140);// setting highlight position

	m_highlightOn1.setPosition(230, 125);// setting highlight position
}

//=============================================================================

// D-tor
MiddleMenu::~MiddleMenu()
{
}

//=============================================================================

// function gets events from player
int  MiddleMenu::getOptionFromUser(sf::RenderWindow& window)
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

			// if player pressed the resume game button
			if (m_x > 229 && m_x < 430 && m_y > 148 && m_y < 200)
				return RESUME;

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
