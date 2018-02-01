
//=============================includes========================================

#include "MainMenu.h"
#include <iostream>
#include "ImageResource.h"
#include "PlayGame.h"
#include "Resume.h"
#include "Exit.h"
#include "Help.h"

// C-tor
MainMenu::MainMenu()
{
	// getting images for menu
	m_menueImages[0].setTexture(ImageResource::getSource().getTexture("menuBackground"));
	m_menueImages[2].setTexture(ImageResource::getSource().getTexture("exitButton"));
	m_menueImages[3].setTexture(ImageResource::getSource().getTexture("helpButton"));
	

	m_menueImages[2].setPosition(150, 300);//exit button
	m_menueImages[3].setPosition(157, 230);// help buton
	//m_menueImages[2].setPosition(150, 215);//exit button

	// transparent rectangle for emphasizing
	m_highlightOn1.setSize(sf::Vector2f(210, 70));
	m_highlightOn1.setFillColor(sf::Color(100, 100, 100, 100));

	m_highlightOn2.setSize(sf::Vector2f(210, 70));
	m_highlightOn2.setFillColor(sf::Color(100, 100, 100, 100));
	m_highlightOn2.setPosition(230, 363);

	m_highlightOn3.setSize(sf::Vector2f(210, 70));
	m_highlightOn3.setFillColor(sf::Color(100, 100, 100, 100));
	m_highlightOn3.setPosition(230, 240);

	shift = sf::Vector2i(0, -30);

	// buttons for menu
	add("PlayGame", std::make_unique<PlayGame>());
	add("Exit", std::make_unique<Exit>());
	add("Resume", std::make_unique<Resume>());
	add("Help", std::make_unique<Help>());

	// playing menu background music
	ImageResource::getSource().playMenuBackground();
}

//=============================================================================

// fucntion runs the menu and handles the events from the user
void MainMenu::run()
{
	// window of menu
	sf::RenderWindow window(sf::VideoMode((float)660, (float)500), 32u, sf::Style::Close);

	int action;// action to do

	while (window.isOpen())
	{
		window.clear();

		for (int i = 0; i < 4; i++)// drawing menu images
			window.draw(m_menueImages[i]);

		action = getOptionFromUser(window);// getting event from user

		performAction(action, window);// performing action

		window.display();
	}
}

//=============================================================================

// adding a button to the vector of buttons
void MainMenu::add(std::string name, std::unique_ptr<Command> c)
{
	m_options.emplace_back(option(name, move(c)));
}

//=============================================================================

// performing action from user
bool MainMenu::performAction(unsigned n, sf::RenderWindow& window)
{
	if (n >= m_options.size())
		return false;

	m_options[n].second->execute(window);// executing action
	return true;
}

//=============================================================================

// setting transparebt rectangles for the buttons
void  MainMenu::drawTransparent(sf::RenderWindow& window)
{
	sf::Vector2i place = sf::Mouse::getPosition() - window.getPosition() + shift;
	if (m_highlightOn1.getGlobalBounds().contains((sf::Vector2f)place))
		window.draw(m_highlightOn1);

	if (m_highlightOn2.getGlobalBounds().contains((sf::Vector2f)place))
		window.draw(m_highlightOn2);

	if (m_highlightOn3.getGlobalBounds().contains((sf::Vector2f)place))
		window.draw(m_highlightOn3);
};