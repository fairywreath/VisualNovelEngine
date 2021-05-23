#include "ConfigButton.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GUI::ConfigButton::ConfigButton(State::Context context) :
	Button(context),
	nWindow(*context.window),
	FilledColor(146, 131, 164),
	HoverColor(232, 126, 146),
	NormalColor(252, 219, 226),
	nAmount(5),
	nRectangles(NumRects),
	ButtonBounds(0, 0, (NumRects * RectWidth) + ((NumRects - 1) * (RectDist - RectWidth)), RectHeight)
{
	initializeRectangles();
	updateColors();
}

void GUI::ConfigButton::handleEvent(const sf::Event& event)
{
	if (checkMouseLocation() && !isSelected())
	{
		select();
	}
	else if (isSelected())
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			updateAppearannceOnClick();
			activate();
		}

		else if (!checkMouseLocation())
		{
			deselect();
		}
	}
}

float GUI::ConfigButton::getAmount() const
{
	return (float)nAmount;
}

void GUI::ConfigButton::setAmount(int amount)
{
	nAmount = amount;
	updateColors();
}

void GUI::ConfigButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (const auto& rect : nRectangles) target.draw(rect, states);
}

void GUI::ConfigButton::updateApperance(ButtonState state)
{
	if (state == ButtonState::Normal)
	{
		updateColors();
	}
	else if (state == ButtonState::Hover)
	{
		updateColors(true);
	}
	else
	{
		/*
			@click is empty for now, maybe apply animation?
		*/
	}
}

bool GUI::ConfigButton::checkMouseLocation() const
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(nWindow);

	if (getTransform().transformRect(ButtonBounds).contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		return true;
	}

	return false;
}

void GUI::ConfigButton::initializeRectangles()
{
	float x{ 0.f };
	float y{ 0.f };

	for (auto& rect : nRectangles)
	{
		rect.setSize(sf::Vector2f(RectWidth, RectHeight));
		rect.setPosition(x, y);

		x += RectDist;
	}
}

void GUI::ConfigButton::updateColors(bool hover)
{
	for (int i = 0; i < NumRects; i++)
	{
		if (i < nAmount) {
			if (hover) nRectangles[i].setFillColor(HoverColor);
			else nRectangles[i].setFillColor(FilledColor);
		} else {
			nRectangles[i].setFillColor(NormalColor);
		}
	}
}

void GUI::ConfigButton::updateAppearannceOnClick()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(nWindow);
	float amount = ((float)mousePosition.x - (float)getPosition().x) / (RectWidth + (RectDist - RectWidth));
	nAmount = (int)std::ceil(amount);
	updateApperance(ButtonState::Hover);
}


