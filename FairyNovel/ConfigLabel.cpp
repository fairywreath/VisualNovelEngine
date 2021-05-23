#include "ConfigLabel.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

GUI::ConfigLabel::ConfigLabel(const std::string& text, const sf::Font& font) :
	Label(text, font)
{
	/*
		@default fixed values
	*/
	setColor(sf::Color(249, 169, 178));
	setSize(55);

	nRect.setSize(sf::Vector2f(RectLength, RectLength));

	nRect.setPosition(nText.getGlobalBounds().left - RectDist - RectLength
		, nText.getGlobalBounds().height + nText.getGlobalBounds().top - RectLength);
	//nRect.setPosition(0 - RectDist - RectLength, nText.getLocalBounds().height - RectLength);
	nRect.setFillColor(sf::Color(201, 95, 110));

}

void GUI::ConfigLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Label::draw(target, states);

	states.transform *= getTransform();
	target.draw(nRect, states);
}
