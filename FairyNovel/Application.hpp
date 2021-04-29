#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Config.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceManager.hpp"
#include "SoundPlayer.hpp"
#include "MusicPlayer.hpp"
#include "StateStack.hpp"
#include "Scanner.hpp"
#include "RegisterEngine.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>


class Application
{
public:
	Application(std::string configPath);
	void run();

private:
	void readCommands();

	void processInput();
	void update(sf::Time elapseTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void registerStates();


private:
	Config nConfig; 
	sf::Time nTimePerFrame;		// 1/FPS
	sf::RenderWindow nWindow;

	std::vector<std::unique_ptr<Command>> nCommands;
	CommandFactory nCommandFactory;

	std::vector<std::unique_ptr<Command>> nRegCommands;

	std::unique_ptr<Scanner> nScanner;
	RegisterEngine nRegEngine;

	TextureManager nTextures;
	FontManager nFonts;
	SoundPlayer nSoundPlayer;
	MusicPlayer nMusicPlayer;

	StateStack nStateStack;

	sf::Text nStatisticsText;
	sf::Time nStatisticsUpdateTime;
	std::size_t nStatisticsNumFrames;

};

#endif

