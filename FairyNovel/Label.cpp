#include "Label.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GUI::Label::Label(const std::string& text, const sf::Font& font) :
	nText(text, font)
{
	/*
		@default size
	*/
	nText.setCharacterSize(18);

	// Util::centerOrigin<sf::Text>(nText);
	refreshOrigin();
}

bool GUI::Label::isSelectable() const
{
	return false;
}

void GUI::Label::handleEvent(const sf::Event& event)
{
	/*
		@do nothing for label
	*/
}

void GUI::Label::setText(const std::string& text)
{
	nText.setString(text);
	// Util::centerOrigin<sf::Text>(nText);
	refreshOrigin();
}

void GUI::Label::setFont(const sf::Font& font)
{
	nText.setFont(font);
	refreshOrigin();
}

void GUI::Label::setSize(unsigned int size)
{
	nText.setCharacterSize(size);
	refreshOrigin();
}

void GUI::Label::setColor(const sf::Color& color)
{
	nText.setFillColor(color);
}

void GUI::Label::centerOriginX()
{
	std::string curr = nText.getString();
	nText.setString("SHINOBU");			// all caps
	setOrigin((nText.getGlobalBounds().width + nText.getGlobalBounds().left) / 2.f
		, nText.getGlobalBounds().top + nText.getGlobalBounds().height);
	nText.setString(curr);
}

void GUI::Label::refreshOrigin()
{
	/*
		@refresh without underlying below line strokes
	*/
	std::string curr = nText.getString();
	nText.setString("SHINOBU");			// all caps
	setOrigin(0,nText.getGlobalBounds().top +  nText.getGlobalBounds().height);
	nText.setString(curr);
}

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(nText, states);
}
