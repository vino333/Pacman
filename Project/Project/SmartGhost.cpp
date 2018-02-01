
//=============================includes========================================

#include "SmartGhost.h"
#include "Board.h"


// C-tor
SmartGhost::SmartGhost(int color, Board& board)
	:Ghost(color, board)
{
}

//=============================================================================

// D-tor
SmartGhost::~SmartGhost()
{
}

//=============================================================================

// function return direction of smart ghost
Direction SmartGhost::getNextStep()
{
	sf::Vector2i ghost = (sf::Vector2i)m_currPlace + sf::Vector2i(2,2);

	ghost /= 32;

	return wayTo(m_board.getBfs(), ghost);
}
