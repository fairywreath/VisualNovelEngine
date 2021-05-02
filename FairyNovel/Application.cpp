#include "Application.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"


#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>

Application::Application(std::string configPath) :
	nWindow(),
	nTextures(),
	nFonts(),
	nSoundPlayer(),
	nMusicPlayer(),
	nCommands(),
	nCommandLabels(),
	nStateStack(State::Context(nWindow, nTextures, nFonts, nMusicPlayer, nSoundPlayer, nCommands, nCommandLabels)),		// create new state context here and pass it in
	nStatisticsText(),
	nStatisticsUpdateTime(),
	nTimePerFrame(),
	nStatisticsNumFrames(),
	nRegEngine(nTextures, nFonts, nSoundPlayer, nMusicPlayer)
{

	nConfig.setPath(configPath);
	nConfig.parse();
	std::string logPath = nConfig.getOption("LOG_PATH");
	Logger::SetLogger(logPath);

	nScanner = std::make_unique<Scanner>((std::string)nConfig.getOption("SCRIPT_PATH"), 
		(std::string)nConfig.getOption("REG_PATH") ,nCommandFactory, nCommands, nCommandLabels);

	// nScanner->scanAll();
	readCommands();

	nTimePerFrame = sf::seconds(1.f / (float)nConfig.getOption("FPS"));
	nWindow.create(sf::VideoMode((int)nConfig.getOption("WINDOW_WIDTH"), 
		(int)nConfig.getOption("WINDOW_HEIGHT")), 
		sf::String((std::string)nConfig.getOption("WINDOW_NAME")),
		sf::Style::Close);

	nFonts.load("overlock", "Media/Fonts/Overlock-Mod.ttf");

	nStatisticsText.setFont(nFonts.get("overlock"));
	nStatisticsText.setCharacterSize(25);
	nStatisticsText.setFillColor(sf::Color::White);

	registerStates();
	nStateStack.pushState(States::Title);
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

void Application::readCommands()
{
	nScanner->countCommandLines(false);
	nScanner->scan(false);
	std::cout << "Register Commands Size: " << nCommands.size() << std::endl;
	for (const auto& ptr : nCommands) 
	{
		nRegEngine.runCommand(ptr.get());
	}
	nCommands.clear();
	nScanner->countCommandLines();			// open srcipt file and reserve commands vector
	nScanner->scan(true);
	std::cout << "Script Commands Size: " << nCommands.size() << std::endl;
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
			"Frames / Second = " + toString(nStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(nStatisticsUpdateTime.asMicroseconds() / nStatisticsNumFrames) + "us");

		// reset statistics
		nStatisticsUpdateTime -= sf::seconds(1.0f);
		nStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	nStateStack.registerState<TitleState>(States::Title);
	nStateStack.registerState<GameState>(States::Game);
}

