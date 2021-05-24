#include "GameState.hpp"
#include "Logger.hpp"
#include "Command.hpp"


#include <sfml/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(StateStack& stack, Context context) :
	State(stack, context),
	nCommandManager(*context.commandManager),
	nEngine(context)
{
	nBackgroundSprite.setTexture(context.textures->get("MMBG"));

	context.configManager->applySettings(nEngine);

	std::cout << "COMMAND SIZE: " << nCommandManager.getCommands().size() << std::endl;

	nCommandManager.setEngine(nEngine);
}

GameState::~GameState()
{
	/*
		@engine is scoped inside the game state, release it
	*/
	nCommandManager.releaseEngine();
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(nEngine);
}

bool GameState::update(sf::Time dt)
{
	nEngine.update(dt);
	nCommandManager.update(dt);
	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		/*
			@maybe need to safeguard states, dont push same state twice
			or have two same states at the top of the stack
		*/
		requestStackPush(States::ID::Config);
		return false;
	}

	nEngine.handleEvent(event);

	/*
		@return true for cascading events between states
	*/
	return false;
}

void GameState::refresh()
{
	getContext().configManager->applySettings(nEngine);
}
