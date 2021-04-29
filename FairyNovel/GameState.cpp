#include "GameState.hpp"

#include <sfml/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack& stack, Context context) :
	State(stack, context),
	nIP(context.commands->begin())
{
	nBackgroundSprite.setTexture(context.textures->get("MMBG"));
	context.musicPlayer->play("mainmenu");
}

void GameState::draw()
{
	// draw the engine
	sf::RenderWindow& window = *getContext().window;
	window.draw(nBackgroundSprite);
}

bool GameState::update(sf::Time dt)
{
	// let engine update
	// if engine not int wait state
	
	

	// push to title state if instructions are over

	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// let engine handle events
	return false;
}
