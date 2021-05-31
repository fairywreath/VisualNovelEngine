#include "ConfigLabel.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

GUI::ConfigLabel::ConfigLabel(const std::string& text, const sf::Font& font) :
	Label(text, font),
	nFadableRect(nRect)
{
	/*
		@default fixed values
	*/
	setColor(sf::Color(249, 169, 178));
	setSize(50);

	nRect.setSize(sf::Vector2f(RectLength, RectLength));

	nRect.setPosition(nText.getGlobalBounds().left - RectDist - RectLength
		, nText.getGlobalBounds().height + nText.getGlobalBounds().top - RectLength);
	nRect.setFillColor(sf::Color(232, 126, 146));

	setOriginBottom();
}

void GUI::ConfigLabel::update(sf::Time dt)
{
	Label::update(dt);
	nFadableRect.update(dt);
}

void GUI::ConfigLabel::fade(float time, int targetAlpha, int startAlpha)
{
	Label::fade(time, targetAlpha, startAlpha);
	nFadableRect.fade(time, targetAlpha, startAlpha);
}

void GUI::ConfigLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Label::draw(target, states);

	states.transform *= getTransform();
	target.draw(nRect, states);
}
