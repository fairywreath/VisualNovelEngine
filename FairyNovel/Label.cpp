#include "Label.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


GUI::Label::Label(const std::string& text, const sf::Font& font) :
	nText(text, font)
{
	Util::centerOrigin<sf::Text>(nText);
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
	Util::centerOrigin<sf::Text>(nText);
}

void GUI::Label::setFont(const sf::Font& font)
{
	nText.setFont(font);
}

void GUI::Label::setSize(unsigned int size)
{
	nText.setCharacterSize(size);
}

void GUI::Label::setColor(const sf::Color& color)
{
	nText.setFillColor(color);
}

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(nText, states);
}
