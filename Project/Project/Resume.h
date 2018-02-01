
//=============================includes========================================

#pragma once
#include <iostream>
#include "Command.h"

//====================class decerations========================================

class Resume :public Command
{
public:
	virtual void execute(sf::RenderWindow& window) 
	{
		// stoping menu background music
		ImageResource::getSource().stopMenuBackground();

		// starting level backgrounfd music
		ImageResource::getSource().playBackgroundMusic();
		window.close();
	};
};

