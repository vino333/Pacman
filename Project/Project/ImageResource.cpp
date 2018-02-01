
//=============================includes========================================

#include "ImageResource.h"
#include <fstream>
#include <string>

// C-tor
ImageResource::ImageResource()
	:m_donePlaying(false),m_cheatOn(false)
{
	setImages();// loaidng images

	loadMusic();// loading music
}

//=============================================================================

//D-tor
ImageResource::~ImageResource()
{
}

//=============================================================================

// getting access to singleton
ImageResource& ImageResource::getSource()
{
	static ImageResource m_imageResource;

	return m_imageResource;
}

//=============================================================================

// fucntion loads images for game
void ImageResource::setImages()
{
	// some of images are loades to a map
//----------------------------------map--------------------------------------
	std::ifstream file;

	std::string nameObject;
	std::string nameFileTexture;

	file.open("images.txt");
	
	std::getline(file, nameObject);// name of object

	while (nameObject != "-1")
	{
		std::getline(file, nameFileTexture);// name of image file

		// Load the texture 
		sf::Texture texture;
		if (!texture.loadFromFile(nameFileTexture))
		{
			std::cout << "Failed to load texture" << std::endl;
			exit(EXIT_FAILURE);
		}

		//Add it to the list of textures 
		this->m_objectTextures[nameObject] = texture;

		std::getline(file, nameObject);
	}
	file.close();
	
	// pacman images for movement
	m_pacmanTextures[0][0].loadFromFile("pacmans.png", sf::IntRect(320, 0, 32, 32));
	m_pacmanTextures[0][1].loadFromFile("pacmans.png", sf::IntRect(352, 0, 32, 32));
	m_pacmanTextures[1][0].loadFromFile("pacmans.png", sf::IntRect(320, 32, 32, 32));
	m_pacmanTextures[1][1].loadFromFile("pacmans.png", sf::IntRect(352, 32, 32, 32));
	m_pacmanTextures[2][0].loadFromFile("pacmans.png", sf::IntRect(320, 64, 32, 32));
	m_pacmanTextures[2][1].loadFromFile("pacmans.png", sf::IntRect(352, 64, 32, 32));
	m_pacmanTextures[3][0].loadFromFile("pacmans.png", sf::IntRect(320, 96, 32, 32));
	m_pacmanTextures[3][1].loadFromFile("pacmans.png", sf::IntRect(352, 96, 32, 32));

	m_pacmanImages[0][0].setTexture(m_pacmanTextures[0][0]);
	m_pacmanImages[0][1].setTexture(m_pacmanTextures[0][1]);
	m_pacmanImages[1][0].setTexture(m_pacmanTextures[1][0]);
	m_pacmanImages[1][1].setTexture(m_pacmanTextures[1][1]);
	m_pacmanImages[2][0].setTexture(m_pacmanTextures[2][0]);
	m_pacmanImages[2][1].setTexture(m_pacmanTextures[2][1]);
	m_pacmanImages[3][0].setTexture(m_pacmanTextures[3][0]);
	m_pacmanImages[3][1].setTexture(m_pacmanTextures[3][1]);

	// ghosts images for movement
	m_ghostsTextures[0][0].loadFromFile("pacmans.png", sf::IntRect(0, 0, 32, 32));
	m_ghostsTextures[0][1].loadFromFile("pacmans.png", sf::IntRect(32, 0, 32, 32));
	m_ghostsTextures[1][0].loadFromFile("pacmans.png", sf::IntRect(0, 32, 32, 32));
	m_ghostsTextures[1][1].loadFromFile("pacmans.png", sf::IntRect(32, 32, 32, 32));
	m_ghostsTextures[2][0].loadFromFile("pacmans.png", sf::IntRect(0, 64, 32, 32));
	m_ghostsTextures[2][1].loadFromFile("pacmans.png", sf::IntRect(32, 64, 32, 32));
	m_ghostsTextures[3][0].loadFromFile("pacmans.png", sf::IntRect(0, 96, 32, 32));
	m_ghostsTextures[3][1].loadFromFile("pacmans.png", sf::IntRect(32, 96, 32, 32));

	m_ghostsImages[0][0].setTexture(m_ghostsTextures[0][0]);
	m_ghostsImages[0][1].setTexture(m_ghostsTextures[0][1]);
	m_ghostsImages[1][0].setTexture(m_ghostsTextures[1][0]);
	m_ghostsImages[1][1].setTexture(m_ghostsTextures[1][1]);
	m_ghostsImages[2][0].setTexture(m_ghostsTextures[2][0]);
	m_ghostsImages[2][1].setTexture(m_ghostsTextures[2][1]);
	m_ghostsImages[3][0].setTexture(m_ghostsTextures[3][0]);
	m_ghostsImages[3][1].setTexture(m_ghostsTextures[3][1]);

	// cookie images
	m_cookieNames[0].loadFromFile("cookie.png");
	m_cookieNames[1].loadFromFile("green cookie.png");
	m_cookieNames[2].loadFromFile("blue cookie.png");

	m_cookieImages[0].setTexture(m_cookieNames[0]);
	m_cookieImages[1].setTexture(m_cookieNames[1]);
	m_cookieImages[2].setTexture(m_cookieNames[2]);

	m_cookieImages[0].setColor(sf::Color(209, 18, 18));
	m_cookieImages[1].setColor(sf::Color(13, 176, 21));
	m_cookieImages[2].setColor(sf::Color(30, 55, 198));

	// fons for score and lives
	m_scoreFont.loadFromFile("score.ttf");

	m_scoreText.setFont(m_scoreFont);
	m_scoreText.setString("Score:");

	m_livesText.setFont(m_scoreFont);
	m_livesText.setString("Lives:");

	// god mode text
	m_godMode.setFont(m_scoreFont);
	m_godMode.setString("GOD MODE!");
	m_godMode.setCharacterSize(50);
	m_godMode.setFillColor(sf::Color::Green);
	m_godMode.setPosition(sf::Vector2f(0, 0));

	// win and lose images
	m_endImage[0].setTexture(m_endNames[0]);
	m_endImage[1].setTexture(m_endNames[1]);
}

//=============================================================================

//will return a reference to the texture
const sf::Texture& ImageResource::getTexture(const std::string& nameTexture) const
{
	return this->m_objectTextures.at(nameTexture);
}

//=============================================================================

// function return a color for an object
sf::Color ImageResource::getColor(int color)const
{
	switch (color)
	{
	case 0:
		return sf::Color(sf::Color(209, 18, 18));

	case 1:
		return sf::Color (sf::Color(13, 176, 21));

	case 2:
		return sf::Color(sf::Color(30, 55, 198));
	}
}

//=============================================================================
// restart the cookie clock
void ImageResource::resetCookieClock()
{
	m_lastCookieReset = m_cookieClock.restart();
}

//=============================================================================

// getting time for cookie clock
sf::Time ImageResource::getLastCookieReset() const
{
	return m_cookieClock.getElapsedTime();
}

//=============================================================================

// function loads music for game
void ImageResource::loadMusic()
{
	// background music for level
	m_backgroundMusic.openFromFile("backgroundMusic.wav");

	m_backgroundMusic.setLoop(true);// make music a loop

	m_backgroundMusic.setVolume(50);

	// music for cokie eating
	m_cookieEating.openFromFile("eatNormalCookie.wav");

	// background music for menues
	m_backgroundMenue.openFromFile("backgroundMusicMenu.wav");

	m_backgroundMenue.setLoop(true);
}