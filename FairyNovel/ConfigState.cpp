#include "ConfigState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

ConfigState::ConfigState(StateStack& stack, Context context) :
	State(stack, context),
	nLabel("CONFIG", context.fonts->get("sinkins")),
	nBackground(context.textures->get("BG2")),
	nCButton(context)
{
	nLabel.setPosition(100.f, 500.f);
	nLabel.setSize(100);
	nLabel.setColor(sf::Color::Magenta);

	nCButton.setPosition(500.f, 100.f);
}


void ConfigState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(nBackground);
	window.draw(nLabel);
	window.draw(nCButton);
}


bool ConfigState::update(sf::Time dt)
{
	return false;
}


bool ConfigState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
	{
	//	requestStackPop();;
	//	requestStackPush(States::ID::Game);
	}

	nCButton.handleEvent(event);

	return false;
}
