
//=============================includes========================================

#pragma once
#include "ImageResource.h"
#include  "MainMenu.h"

//====================class decerations========================================

class MiddleMenu:public MainMenu
{
public:
	MiddleMenu();
	~MiddleMenu();
	virtual int getOptionFromUser(sf::RenderWindow& window);
};

