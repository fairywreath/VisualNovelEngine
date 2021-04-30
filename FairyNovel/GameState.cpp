#include "GameState.hpp"

#include <sfml/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(StateStack& stack, Context context) :
	State(stack, context),
	nCommands(*context.commands),
	nIP(context.commands->begin()),
	nEngine(context)
{
	nBackgroundSprite.setTexture(context.textures->get("MMBG"));
	context.musicPlayer->play("mainmenu");
}

void GameState::draw()
{
	// draw the engine
	sf::RenderWindow& window = *getContext().window;
	window.draw(nEngine);
//	window.draw(nBackgroundSprite);
}

bool GameState::update(sf::Time dt)
{
	// let engine update
	// if engine not int wait state
	nEngine.update(dt);
	
	if (!nEngine.shouldWait() && nIP != nCommands.end())
	{
		if((*nIP) != nullptr)
			(*nIP)->execute(nEngine);
		
		nIP++;
	}

	// push to title state if instructions are over

	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// let engine handle events
	nEngine.handleEvent(event);
//	std::cout << "handling\n";

	return false;
}
