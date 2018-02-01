
//=============================includes========================================

#pragma once
#include "Command.h"
#include <iostream>

//====================class decerations========================================

// ending game
class Exit:public Command
{
public:
	virtual void execute(sf::RenderWindow& window) 
	{
		ImageResource::getSource().setDone(true);
		window.close();
	}
};

