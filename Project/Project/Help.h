#pragma once
#include <Windows.h>
#include "Command.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class Help :public Command
{
public:
	Help() { m_helpScreen.setTexture(ImageResource::getSource().getTexture("helpScreen")); };

	virtual void execute(sf::RenderWindow& window)
	{
		while (window.isOpen())
		{
			window.clear();

			window.draw(m_helpScreen);

			sf::Event event;
			if(window.pollEvent(event))
				if (event.type == sf::Event::KeyPressed)// if player moved pacman
					if( sf::Keyboard::Space)
						break;
			window.display();
		}
	}

private:
	sf::Sprite m_helpScreen;
};
