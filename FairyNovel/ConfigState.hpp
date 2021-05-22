#ifndef CONFIGSTATE_HPP
#define CONFIGSTATE_HPP

#include "State.hpp"
#include "Label.hpp"
#include "ConfigButton.hpp"

#include <SFML/Graphics/Sprite.hpp>

class ConfigState : public State
{
public:
	ConfigState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

private:
	/*
		@settings UI components?
	*/
	GUI::Label nLabel;
	GUI::ConfigButton nCButton;

	/*
		@bg
	*/
	sf::Sprite nBackground;

};


#endif