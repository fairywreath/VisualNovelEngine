#include "ConfigState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

ConfigState::ConfigState(StateStack& stack, Context context) :
	State(stack, context),
	nLabel("CONFIG", context.fonts->get("sinkins")),
	nBackground(context.textures->get("BG2")),
	nCButton(context),
	nCBox(context)
{
	nLabel.setPosition(100.f, 500.f);
	nLabel.setSize(100);
	nLabel.setColor(sf::Color::Magenta);

	nCBox.setPosition(200.f, 200.f);
	nCButton.setPosition(700.f, 400.f);
}


void ConfigState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	// window.draw(nBackground);
	window.draw(nLabel);
	window.draw(nCButton);
	// std::cout << nCBox.getPosition().x << " " << nCBox.getPosition().y << std::endl;
	window.draw(nCBox);
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
	nCBox.handleEvent(event);

	return false;
}
