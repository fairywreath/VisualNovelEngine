#include "Application.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "ConfigState.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

Application::Application(const std::string& configPath) :
	nWindow(),
	nTextures(),
	nFonts(),
	nSoundPlayer(),
	nMusicPlayer(),
	nCommands(),
	nCommandLabels(),
	nCharacters(),
	nStateStack(State::Context(nWindow, nTextures, nFonts, nMusicPlayer, nSoundPlayer, 
		nCommands, nCommandLabels, nCharacters, nGameConfigManager)),		// create new state context here and pass it in
	nStatisticsText(),
	nStatisticsUpdateTime(),
	nTimePerFrame(),
	nStatisticsNumFrames(),
	nGameConfigManager()
{
	initialize(configPath);
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

	auto scanner = std::make_unique<Scanner>((std::string)config.getOption("SCRIPT_PATH"),
		(std::string)config.getOption("REG_PATH"), commandFactory, nCommands, nCommandLabels);
	
	RegisterEngine regEngine(nTextures, nFonts, nSoundPlayer, nMusicPlayer, nCharacters);

	scanner->scanCommands(false);		// reserve register vector
	for (const auto& ptr : nCommands)
	{
		regEngine.runCommand(ptr.get());
	}


	nCommands.clear();						// reuse the vector

	scanner->scanCommands();			// open srcipt file and reserve commands vector



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


	/*
		@setup misc text
	*/
	nStatisticsText.setFont(nFonts.get("overlock"));
	nStatisticsText.setCharacterSize(17);
	nStatisticsText.setFillColor(sf::Color::Cyan);

	registerStates();
	nStateStack.pushState(States::ID::Config);
	/*
		@need guards 
	*/
	nTextures.load("checkmark", "Media/GUI/checkmark.JPG");
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

}


