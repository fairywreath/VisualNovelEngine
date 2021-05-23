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
#include "CharacterBlueprint.hpp"
#include "ConfigManager.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <unordered_map>

class Application
{
public:
	using CommandPtr = std::unique_ptr<Command>;
	using CommandLbl = std::vector<CommandPtr>::const_iterator;

public:
	Application(const std::string& configPath);
	void run();

private:
	void processInput();
	void update(sf::Time elapseTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void registerStates();

	void initialize(const std::string& configPath);

private:
	std::vector<CommandPtr> nCommands;
	std::unordered_map<std::string, CommandLbl> nCommandLabels;
	std::unordered_map<std::string, CharacterBlueprint> nCharacters;

	sf::Time nTimePerFrame;		// 1/FPS
	sf::RenderWindow nWindow;

	TextureManager nTextures;
	FontManager nFonts;
	SoundPlayer nSoundPlayer;
	MusicPlayer nMusicPlayer;

	StateStack nStateStack;

	ConfigManager nGameConfigManager;

	sf::Text nStatisticsText;
	sf::Time nStatisticsUpdateTime;
	std::size_t nStatisticsNumFrames;

};

#endif

