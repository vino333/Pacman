
//====================class decerations========================================
#pragma once

// abstarcat class for menu commands-buttons
class Command
{
public:
	virtual ~Command() = 0 {}
	virtual void execute(sf::RenderWindow&) = 0;
};

