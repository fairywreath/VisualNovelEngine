#include "BacklogPanel.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


GUI::BacklogPanel::BacklogPanel() 
{
	nTextLabel.setSize(FontSize);
	nIdLabel.setSize(FontSize);

	nTextLabel.setColor(sf::Color::White);
	nIdLabel.setColor(sf::Color::White);
	refreshOrigins();

	nIdLabel.setPosition(0.f, 0.f);
	nTextLabel.setPosition(0.f, DistY);
}

GUI::BacklogPanel::BacklogPanel(const sf::Font& font) :
	nTextLabel("", font),
	nIdLabel("", font)
{
	nTextLabel.setSize(FontSize);
	nIdLabel.setSize(FontSize);

	nTextLabel.setColor(sf::Color::White);
	nIdLabel.setColor(sf::Color::White);
	refreshOrigins();

	nIdLabel.setPosition(0.f, 0.f);
	nTextLabel.setPosition(0.f, DistY);
}

GUI::BacklogPanel::BacklogPanel(const std::string& text, const std::string& identifier, const sf::Font& font) :
	nTextLabel(text, font),
	nIdLabel(identifier, font)
{
	nTextLabel.setSize(FontSize);
	nIdLabel.setSize(FontSize);
	
	nTextLabel.setColor(sf::Color::White);
	nIdLabel.setColor(sf::Color::White);

	refreshOrigins();

	nIdLabel.setPosition(0.f, 0.f);
	nTextLabel.setPosition(0.f, DistY);
}

void GUI::BacklogPanel::setIdentifier(const std::string& id)
{
	nIdLabel.setText(id);
	refreshOrigins();
}

void GUI::BacklogPanel::setText(const std::string& text)
{
	nTextLabel.setText(text);
	refreshOrigins();
}

void GUI::BacklogPanel::setFont(const sf::Font& font)
{
	nTextLabel.setFont(font);
	nIdLabel.setFont(font);
	refreshOrigins();
}

bool GUI::BacklogPanel::isSelectable() const
{
	return false;
}

void GUI::BacklogPanel::handleEvent(const sf::Event& event)
{
}

void GUI::BacklogPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(nTextLabel, states);
	target.draw(nIdLabel, states);
}

void GUI::BacklogPanel::refreshOrigins()
{
	nTextLabel.setOriginLeft();
	nTextLabel.setOriginTop();
	nIdLabel.setOriginRight();
	nIdLabel.setOriginBottom();
}
