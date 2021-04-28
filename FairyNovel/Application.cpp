#include "Application.hpp"
#include "Logger.hpp"
#include "Utility.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

Application::Application(std::string configPath) :
	nWindow(),
	nTextures(),
	nFonts(),
	nSoundPlayer(),
	nMusicPlayer(),
//	nStateStack(State::Context(nWindow, nTextures, nFonts, nMusicPlayer, nSoundPlayer)),		// create new state context here and pass it in
	nStatisticsText(),
	nStatisticsUpdateTime(),
	nTimePerFrame(),
	nStatisticsNumFrames()
{
	nConfig.setPath(configPath);
	nConfig.parse();
	std::string logPath = nConfig.getOption("LOG_PATH");
	Logger::SetLogger(logPath);

	nTimePerFrame = sf::seconds(1.f / (float)nConfig.getOption("FPS"));
	nWindow.create(sf::VideoMode((int)nConfig.getOption("WINDOW_WIDTH"), 
		(int)nConfig.getOption("WINDOW_HEIGHT")), 
		sf::String((std::string)nConfig.getOption("WINDOW_NAME")),
		sf::Style::Close);

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

		//	if (nStateStack.isEmpty())	nWindow.close();
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
	//	nStateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			nWindow.close();
	}
}

void Application::update(sf::Time elapsedTime)
{
//	nStateStack.update(elapsedTime);
}

void Application::render()
{
	nWindow.clear();

//	nStateStack.draw();
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
//	nStateStack.registerState<TitleState>(States::Title);
//	nStateStack.registerState<GameState>(States::Game);
}

