
//=============================includes========================================

#include "StupidGhost.h"
#include "Board.h"

// C-tor
StupidGhost::StupidGhost(int color, Board& board)
	:Ghost(color, board)
{
}

//=============================================================================

// D-tor
StupidGhost::~StupidGhost()
{
}

//=============================================================================

// function return direction of stupids ghost
Direction StupidGhost::getNextStep()
{
	sf::Vector2i ghost = (sf::Vector2i)m_currPlace + sf::Vector2i(2, 2);

	ghost /= 32;

	return wayTo(m_board.getDemoBfs(), ghost);
}
