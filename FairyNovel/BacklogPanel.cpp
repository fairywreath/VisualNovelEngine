#include "BacklogPanel.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


GUI::BacklogPanel::BacklogPanel() 
{
	nTextLabel.setColor(sf::Color::Black);
	nIdLabel.setColor(sf::Color::Black);

	refreshOrigins();

	nIdLabel.setPosition(0.f, 0.f);
	nTextLabel.setPosition(0.f, DistY);
}

GUI::BacklogPanel::BacklogPanel(const std::string& text, const std::string& identifier, const sf::Font& font) :
	nTextLabel(text, font),
	nIdLabel(identifier, font),
	nFont(font)
{	
	nTextLabel.setColor(sf::Color::Black);
	nIdLabel.setColor(sf::Color::Black);

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
	sf::String wrapped = Util::wrapText(sf::String(text), MaxTextWidth, nFont, nTextLabel.getSize(), 0);

	nTextLabel.setText(wrapped);
	refreshOrigins();
}

void GUI::BacklogPanel::setFont(const sf::Font& font)
{
	nFont = font;
	nTextLabel.setFont(font);
	nIdLabel.setFont(font);
	refreshOrigins();
}

void GUI::BacklogPanel::setSize(int size)
{
	nTextLabel.setSize(size);
	nIdLabel.setSize(size);
	refreshOrigins();
}

bool GUI::BacklogPanel::isSelectable() const
{
	return false;
}

void GUI::BacklogPanel::handleEvent(const sf::Event& event)
{
}

void GUI::BacklogPanel::update(sf::Time dt)
{
	nTextLabel.update(dt);
	nIdLabel.update(dt);
}

void GUI::BacklogPanel::fade(float time, int target, int start)
{
	nTextLabel.fade(time, target, start);
	nIdLabel.fade(time, target, start);
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
