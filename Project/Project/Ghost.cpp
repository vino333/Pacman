
//=============================includes========================================

#include "Ghost.h"
#include "Board.h"

//========================consts===============================================

const int SPEED = 120;

// C-tor
Ghost::Ghost(int color, Board& board)
	:MoveAble(board), Legs(false)
{
	// getting images for ghost movement
	for (int i = 0; i < 4; i++)
	{
		m_ghostImages[i][0] = ImageResource::getSource().getGhost(i, 0);
		m_ghostImages[i][1] = ImageResource::getSource().getGhost(i, 1);

		m_ghostImages[i][0].setColor(ImageResource::getSource().getColor(color));
		m_ghostImages[i][1].setColor(ImageResource::getSource().getColor(color));
	}

	m_image = ImageResource::getSource().getGhost(0, 0);// setting first image

	m_image.setColor(ImageResource::getSource().getColor(color));// setting color
}

//=============================================================================

// function moves a ghost
void Ghost::move(float time)
{
	static float picture = 0;

	m_nextDirection = getNextStep();

	float step_size = beforeMoving(time, picture);

	m_currPlace += doStep(SPEED*step_size);

	switchImages(picture);
}

//=============================================================================

//this function switch the images
void Ghost::switchImages(float picture)
{
	if (m_direction != STAND && picture >= 0.5)// changing images for movement
	{
		m_image = getNextImage(m_direction);
		picture = 0;
		Legs = !Legs;
	}
}

//=============================================================================

// function gets next image for ghost
sf::Sprite Ghost::getNextImage(Direction m_direction)const
{
	return m_ghostImages[m_direction][Legs ? 1 : 0];
}

//=============================================================================

//this function get the bfs output and the place of the ghost and return the direction
Direction Ghost::wayTo(const std::vector<std::vector<sf::Vector2i>> &bfs,
	const sf::Vector2i &start)
{
	if (!(sf::Vector2i(bfs[start.x][start.y].x, bfs[start.x][start.y].y) == sf::Vector2i(-1, -1)))
	{
		//set vector as destination
		sf::Vector2i destination = sf::Vector2i(bfs[start.x][start.y].x, bfs[start.x][start.y].y);

		//finding thee right direction

		if (start.x > destination.x && start.x > 0.3)
			return LEFT;

		if (start.x < destination.x)
			return RIGHT;

		if (start.y > destination.y)
			return UP;

		if (start.y < destination.y)
			return DOWN;
	}
	return STAND;
}
