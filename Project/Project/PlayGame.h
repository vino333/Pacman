
//=============================includes========================================

#pragma once
#include "Controller.h"
#include "Command.h"
#include <iostream>

//====================class decerations========================================

class PlayGame :public Command
{
public:
	virtual void execute(sf::RenderWindow& window)
	{
		ImageResource::getSource().stopMenuBackground();// stoping menu background music

		Controller controller;// starting a new game
		controller.run(window);
	}

};

