
//=============================includes========================================

#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

//====================class decerations========================================

class ImageResource
{
public:
	const sf::Texture& getTexture(const std::string& nameTexture) const;
	// music part
	void loadMusic();
	void playBackgroundMusic() { m_backgroundMusic.play(); };// playing background music
	void pauseBackgroundMusic() { m_backgroundMusic.pause(); };
	void stopBackgroundMusic() { m_backgroundMusic.stop(); };
	void playEatCookie() { m_cookieEating.play(); };
	void playMenuBackground() { m_backgroundMenue.play(); };
	void stopMenuBackground() { m_backgroundMenue.stop(); };
	
	//images part
	void setImages();
	sf::Color getColor(int color)const;
	bool getDone() const { return m_donePlaying; };
	void setDone(bool set) { m_donePlaying = set; };
	sf::Sprite getBackgroundImage()const { return m_backGroundImage; };
	sf::Sprite getMenueImage(int image)const { return m_menuImages[image]; };
	sf::Sprite getPacman(int i, int j)const { return m_pacmanImages[i][j]; };
	sf::Sprite getGhost(int i, int j)const { return m_ghostsImages[i][j]; };
	sf::Sprite getCookie(int i) const { return m_cookieImages[i]; };
	sf::Text getScoreFont()const { return m_scoreText; };
	sf::Text getLivesFont() const { return m_livesText; };
	sf::Text getGodMode()const { return m_godMode; };	
	sf::Font getFont() const { return m_scoreFont; };
	sf::Sprite getEnd(int i)const { return m_endImage[i]; };

	//clock part
	void resetCookieClock();
	sf::Time getLastCookieReset() const;

	sf::Time getLastCheatReset() const { return m_cheatClock.getElapsedTime(); };
	float getStartTimer()const { return m_cheatLast; };

	//general
	static ImageResource& getSource();
	~ImageResource();

	void setcheat(bool set) {
		if (set)
		{
			m_cheatLast = m_cheatClock.getElapsedTime().asSeconds();
			m_cheatOn = true;
		}
		else
			m_cheatOn = false;
	}
	bool getCheatOn()const { return m_cheatOn; };

private:
	sf::Clock m_cheatClock;
	float m_cheatLast;

	//musics for the game
	sf::Music m_backgroundMenue;
	sf::Music m_backgroundMusic;
	sf::Music m_cookieEating;

	//c-tor and copy c-tor
	ImageResource();
	ImageResource(const ImageResource&) = delete;
	ImageResource & operator=(const ImageResource&) = delete;

	// images for the game
	sf::Sprite m_images[3][3];
	sf::Texture m_texture[3];

	sf::Texture m_scoreName;
	sf::Sprite m_scoreImage;

	sf::Texture m_pacmanTexture;
	sf::Sprite m_pacmanImage;

	sf::Sprite m_pacmanImages[4][2];
	sf::Texture m_pacmanTextures[4][2];

	sf::Sprite m_menuImages[4];
	sf::Texture m_menuTexture[4];

	sf::Sprite m_backGroundImage;
	sf::Texture m_backGroundTexture;

	sf::Texture  m_ghostsTextures[4][2];
	sf::Sprite m_ghostsImages[4][2];

	sf::Texture m_cookieNames[3];
	sf::Sprite m_cookieImages[3];

	sf::Texture m_endNames[2];
	sf::Sprite m_endImage[2];

	// fonts for game
	sf::Font m_scoreFont;
	sf::Text m_scoreText;
	sf::Text m_livesText;
	sf::Text m_godMode;

	// cookie clock
	sf::Clock m_cookieClock;
	sf::Time m_lastCookieReset;

	
	bool m_donePlaying;
	bool m_cheatOn;


	sf::Image m_icon;

	// map for some of pictures
	std::map<std::string, sf::Texture> m_objectTextures;
};

