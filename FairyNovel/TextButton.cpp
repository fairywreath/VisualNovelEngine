#include "TextButton.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

GUI::TextButton::TextButton(State::Context context, const std::string& text) :
	Button(context),
	nWindow(*context.window),
	nText(text, context.fonts->get("aria")),
	nAnimeText(nText),
	nMover(this),
	NormalColor(sf::Color(249, 169, 178)),
	HoverColor(232, 126, 146),
	FilledColor(252, 219, 226),
	OutlineHoverColor(237, 228, 128, 125)
{
	nText.setCharacterSize(30);
	nText.setFillColor(NormalColor);
	nText.setOutlineColor(OutlineHoverColor);

	nAnimeText.setObjectColor(NormalColor);
}

void GUI::TextButton::handleEvent(const sf::Event& event)
{
	if (checkMouseLocation() && !isSelected())
	{
		select();
	}
	else if (isSelected())
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			activate();		// deactivates instantly if toggle is default(which is the default status)
		}
		else if (!checkMouseLocation())
		{
			deselect();
		}
		else
		{
			// empty
		}
	}
}

void GUI::TextButton::setText(const std::string& text)
{
	nText.setString(text);
	refreshOrigin();
}

void GUI::TextButton::setFont(const sf::Font& font)
{
	nText.setFont(font);
	refreshOrigin();
}

void GUI::TextButton::setSize(int size)
{
	nText.setCharacterSize(size);
	refreshOrigin();
}

void GUI::TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(nText, states);
}

void GUI::TextButton::updateApperance(ButtonState state)
{
	switch (state)
	{
	case ButtonState::Hover:
		nText.setFillColor(HoverColor);
		nText.setOutlineThickness(4.f);
		break;
	case ButtonState::Normal:
		nText.setFillColor(NormalColor);
		nText.setOutlineThickness(0);
		break;
	case ButtonState::Pressed:
		nText.setFillColor(FilledColor);
		break;
	default:
		break;
	}
}

bool GUI::TextButton::checkMouseLocation() const
{
	return getTransform().transformRect(nText.getGlobalBounds()).
		contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(nWindow)));
}


void GUI::TextButton::refreshOrigin()
{
	/*
		@refresh without underlying below line strokes
	*/
	std::string curr = nText.getString();
	nText.setString("SHINOBU");			// all caps
	setOrigin(0, nText.getGlobalBounds().top + nText.getGlobalBounds().height);
	nText.setString(curr);
}

void GUI::TextButton::update(sf::Time dt)
{
	if (nAnimeText.inAnimation()) nAnimeText.update(dt);
	if (nMover.inMovement()) nMover.update(dt);
}

void GUI::TextButton::fade(float time, int targetAlpha, int startAlpha)
{
	nAnimeText.fade(time, targetAlpha, startAlpha);
}

void GUI::TextButton::move(float time, const sf::Vector2f& dest, const sf::Vector2f& source)
{
	nMover.move(time, dest, source);
}
