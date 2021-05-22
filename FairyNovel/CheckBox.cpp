#include "CheckBox.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GUI::CheckBox::CheckBox(State::Context context) :
	nWindow(*context.window),
	nChecked(false),
	nRect(),
	nSprite(context.textures->get("checkmark")),
	Color(255, 187, 202)
{
	nRect.setPosition(0, 0);
	nRect.setSize(sf::Vector2f(BoxHeight, BoxHeight));
	nRect.setFillColor(sf::Color::White);
	nRect.setOutlineColor(Color);
	nRect.setOutlineThickness(OutlineThickness);

	nSprite.setPosition(1.f, 1.f);
}

void GUI::CheckBox::handleEvent(const sf::Event& event)
{
	if (checkMouseLocation() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		activate();
	}

}

void GUI::CheckBox::activate()
{
	nChecked = !nChecked;
}

bool GUI::CheckBox::getStatus() const
{
	return nChecked;
}

void GUI::CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(nRect, states);
	if (nChecked) target.draw(nSprite, states);
}

bool GUI::CheckBox::checkMouseLocation() const
{
	return (getTransform().transformRect(nRect.getGlobalBounds()).
		contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(nWindow))));
}


bool GUI::CheckBox::isSelectable() const
{
	/*
		@ does not matter?
	*/
	return false;
}