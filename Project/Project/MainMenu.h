
//=============================includes========================================

#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include <string>
#include <cstdlib>
#include "Command.h"
#include <iostream>
#include <vector>

//===============================using=========================================

using namespace std;

//==================================consts=====================================

const int PLAY = 0;
const int EXIT = 1;
const int RESUME = 2;
const int HELP = 3;
const int NOTHING = 4;


//====================class decerations========================================

class MainMenu
{
public:
	MainMenu();
	virtual ~MainMenu() = 0 {}
	void run();

    // functions for executing player requests
	void add(std::string, std::unique_ptr<Command>);
	bool performAction(unsigned n, sf::RenderWindow&);
	virtual int getOptionFromUser(sf::RenderWindow&) = 0;
	void drawTransparent(sf::RenderWindow& window);
	
protected:
	// menu images
	sf::Sprite m_menueImages[4];
	

	// highlighting rectangles
	sf::RectangleShape m_highlightOn1;
	sf::RectangleShape m_highlightOn2;
	sf::RectangleShape m_highlightOn3;

	sf::Vector2i shift;

	//design pattern part
	typedef pair<string, unique_ptr<Command>> option;
	vector<option> m_options;
};

