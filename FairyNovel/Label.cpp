#include "Label.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GUI::Label::Label()
{
}

GUI::Label::Label(const std::string& text, const sf::Font& font) :
	nText(text, font),
	nFadableText(nText)
{
	/*
		@default size
	*/
	nText.setCharacterSize(18);

	setOriginBottom();
	nFadableText.setObjectColor(nText.getFillColor());
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
	setOriginBottom();
}

void GUI::Label::setFont(const sf::Font& font)
{
	nText.setFont(font);
	setOriginBottom();
}

void GUI::Label::setSize(unsigned int size)
{
	nText.setCharacterSize(size);
	setOriginBottom();
}

void GUI::Label::setColor(const sf::Color& color)
{
	nText.setFillColor(color);
	nFadableText.setObjectColor(nText.getFillColor());
}

int GUI::Label::getSize() const
{
	return nText.getCharacterSize();
}

void GUI::Label::centerOriginX()
{
	/*
		@set origin center and bottom
	*/
	std::string curr = nText.getString();
	nText.setString("SHINOBU");			// all caps
	setOrigin((nText.getGlobalBounds().width + nText.getGlobalBounds().left) / 2.f
		, nText.getGlobalBounds().top + nText.getGlobalBounds().height);
	nText.setString(curr);
}


void GUI::Label::setOriginBottom()
{
	/*
		@refresh without underlying below line strokes
	*/
	std::string curr = nText.getString();
	nText.setString("SHINOBU");			// all caps
	setOrigin(getOrigin().x, nText.getGlobalBounds().top + nText.getGlobalBounds().height);
	nText.setString(curr);
}

void GUI::Label::setOriginLeft()
{
	setOrigin(nText.getGlobalBounds().left, getOrigin().y);
}

void GUI::Label::setOriginRight()
{
	auto bounds = nText.getGlobalBounds();
	setOrigin(nText.getGlobalBounds().left + nText.getGlobalBounds().width, getOrigin().y);

}

void GUI::Label::setOriginTop()
{
	std::string curr = nText.getString();
	nText.setString("SHINOBU");			// all caps
	setOrigin(getOrigin().x, nText.getGlobalBounds().top);
	nText.setString(curr);
}

void GUI::Label::fade(float time, int targetAlpha, int startAlpha)
{
	nFadableText.fade(time, targetAlpha, startAlpha);
}

void GUI::Label::update(sf::Time dt)
{
	nFadableText.update(dt);
}

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(nText, states);
}
