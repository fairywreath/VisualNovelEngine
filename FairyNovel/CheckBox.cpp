#include "CheckBox.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GUI::CheckBox::CheckBox(State::Context context) :
	Button(context),
	nWindow(*context.window),
	nChecked(false),
	nRect(),
	nSprite(context.textures->get("checkmark")),
	OutlineColor(249, 169, 178),
	HoverColor(252, 219, 226)
{
	nRect.setPosition(0, 0);
	nRect.setSize(sf::Vector2f(BoxHeight, BoxHeight));
	nRect.setFillColor(sf::Color::White);
	nRect.setOutlineColor(OutlineColor);
	nRect.setOutlineThickness(OutlineThickness);

	nSprite.setPosition(1.f, 1.f);

	setOrigin(0, nRect.getGlobalBounds().top + nRect.getGlobalBounds().height);
}

void GUI::CheckBox::handleEvent(const sf::Event& event)
{
	if (checkMouseLocation())
	{
		if (!isSelected() && !nChecked)
		{
			select();
		}
		else if (isSelected() || nChecked)
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				nChecked = !nChecked;
				activate();
				if (nChecked) deselect();
			}
		}
		else
		{
			/*
				@do nothing
			*/
		}
	}
	else
	{
		if (isSelected()) deselect();
	}
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

void GUI::CheckBox::updateApperance(ButtonState state)
{
	switch(state)
	{
	case ButtonState::Hover:
		nRect.setFillColor(HoverColor);
		break;
	case ButtonState::Normal:
		nRect.setFillColor(sf::Color::White);
		break;
	default:
		/*
			@do nothing, return
		*/
		break;
	}
}

