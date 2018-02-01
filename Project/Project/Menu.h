
//=============================includes========================================

#pragma once
#include "MainMenu.h"

//==========================using==============================================
using namespace ::std;

//====================class decerations========================================

class Menu:public MainMenu
{
public:
	Menu();
	~Menu();

	virtual int getOptionFromUser(sf::RenderWindow&);
};

