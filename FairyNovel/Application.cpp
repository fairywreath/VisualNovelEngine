#include "Application.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "ConfigState.hpp"
#include "BacklogState.hpp"
#include "MainMenuState.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

Application::Application(const std::string& configPath) :
	nWindow(),
	nTextures(),
	nFonts(),
	nSoundPlayer(),
	nMusicPlayer(),
	nCharacters(),
	nStateStack(State::Context(nWindow, nTextures, nFonts, nMusicPlayer, nSoundPlayer, 
		nCommandManager, nCharacters, nGameConfigManager)),		// create new state context here and pass it in
	nStatisticsText(),
	nStatisticsUpdateTime(),
	nTimePerFrame(),
	nStatisticsNumFrames(),
	nGameConfigManager()
{
	initialize(configPath);

	nStateStack.pushState(States::ID::MainMenu);
}

void Application::initialize(const std::string& configPath)
{
	// set up config
	Config config;
	config.setPath(configPath);
	config.parse();
	std::string logPath = config.getOption("LOG_PATH");
	Logger::SetLogger(logPath);

	// read commands from file
	CommandFactory commandFactory;
	
	Scanner scanner((std::string)config.getOption("SCRIPT_PATH"),
		(std::string)config.getOption("REG_PATH"), commandFactory,
		nCommandManager.getCommands(), nCommandManager.getCommandLabels());

	RegisterEngine regEngine(nTextures, nFonts, nSoundPlayer, nMusicPlayer, nCharacters);

	scanner.scanCommands(false);		// reserve register vector
	for (const auto& ptr : nCommandManager.getCommands())
	{
		regEngine.runCommand(ptr.get());
	}

	nCommandManager.getCommands().clear();
	scanner.scanCommands();				// read rest of game commands



	// set up window
	nTimePerFrame = sf::seconds(1.f / (float)config.getOption("FPS"));
	nWindow.create(sf::VideoMode((int)config.getOption("WINDOW_WIDTH"),
		(int)config.getOption("WINDOW_HEIGHT")),
		sf::String((std::string)config.getOption("WINDOW_NAME")),
		sf::Style::Close);

	/*
		@load fonts
	*/
	nFonts.load("overlock", "Media/Fonts/Overlock-Mod.ttf");
	nFonts.load("huxleyv", "Media/Fonts/Huxley Vertical Regular.otf");
	nFonts.load("ttcommons", "Media/Fonts/TT Commons Regular.otf");
	nFonts.load("sinkins", "Media/Fonts/SinkinSans-100Thin.otf");
	nFonts.load("aria", "Media/Fonts/Aria Pro Regular.otf");
	nFonts.load("veljovic", "Media/Fonts/VeljovicStd-Book.otf");

	/*
		@setup misc text
	*/
	nStatisticsText.setFont(nFonts.get("overlock"));
	nStatisticsText.setCharacterSize(17);
	nStatisticsText.setFillColor(sf::Color::Cyan);

	registerStates();

	/*
		@need guards 
	*/
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (nWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > nTimePerFrame)
		{
			timeSinceLastUpdate -= nTimePerFrame;

			processInput();
			update(nTimePerFrame);

			if (nStateStack.isEmpty())	nWindow.close();
		}

		render();
		updateStatistics(elapsedTime);
	}
}

void Application::processInput()
{
	sf::Event event;
	while (nWindow.pollEvent(event))
	{
		nStateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			nWindow.close();
	}
}

void Application::update(sf::Time elapsedTime)
{
	nStateStack.update(elapsedTime);
}

void Application::render()
{
	nWindow.clear();

	nStateStack.draw();
	nWindow.setView(nWindow.getDefaultView());
	nWindow.draw(nStatisticsText);
	nWindow.display();
}

void Application::updateStatistics(sf::Time elapsedTime)
{
	nStatisticsUpdateTime += elapsedTime;
	nStatisticsNumFrames += 1;

	if (nStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		nStatisticsText.setString(
			"Frames / Second = " + Util::toString(nStatisticsNumFrames) + "\n" +
			"Time / Update = " + Util::toString(nStatisticsUpdateTime.asMicroseconds() / nStatisticsNumFrames) + "us");

		nStatisticsUpdateTime -= sf::seconds(1.0f);
		nStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	nStateStack.registerState<TitleState>(States::ID::Title);
	nStateStack.registerState<GameState>(States::ID::Game);
	nStateStack.registerState<ConfigState>(States::ID::Config);
	nStateStack.registerState<BacklogState>(States::ID::Backlog);
	nStateStack.registerState<MainMenuState>(States::ID::MainMenu);
}


