#include "SpriteButton.hpp"
#include "Utility.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GUI::SpriteButton::SpriteButton(State::Context context) :
	Button(context),
	nWindow(*context.window),
	nNormalTexture(context.textures->get("ButtonNormal")),
	nHoverTexture(context.textures->get("ButtonHover")),
	nPressedTexture(context.textures->get("ButtonClick")),
	nSprite(),
	nText()
{
	nSprite.setTexture(nNormalTexture);

	nText.setFont(context.fonts->get("overlock"));
	nText.setCharacterSize(30);
	sf::FloatRect bounds = nSprite.getLocalBounds();	
	nText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	Util::centerOrigin<sf::Text>(nText);
}

void GUI::SpriteButton::handleEvent(const sf::Event& event)
{
	if (checkMouseLocation() && !isSelected())
	{
		select();
	}
	else if (isSelected())
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			activate();
		}

		else if (!checkMouseLocation())
		{
			deselect();
		}
	}
}

void GUI::SpriteButton::setText(const std::string& text)
{
	nText.setString(text);
	Util::centerOrigin<sf::Text>(nText);

}

void GUI::SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(nSprite, states);
	target.draw(nText, states);
}

void GUI::SpriteButton::updateApperance(ButtonState state)
{
	if (state == ButtonState::Normal)
		nSprite.setTexture(nNormalTexture);
	else if (state == ButtonState::Hover)
		nSprite.setTexture(nHoverTexture);
	else
		nSprite.setTexture(nPressedTexture);
}

bool GUI::SpriteButton::checkMouseLocation() const
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(nWindow);

	sf::FloatRect buttonBounds = getTransform().transformRect(nSprite.getGlobalBounds());
	
	if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition)))
		return true;
	
	return false;
}
