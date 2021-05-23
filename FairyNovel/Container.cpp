#include "Container.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

GUI::Container::Container()
{
}

void GUI::Container::pack(Component::Ptr component)
{
	nComponents.push_back(std::move(component));
}

bool GUI::Container::isSelectable() const
{
	return false;
}

void GUI::Container::handleEvent(const sf::Event& event)
{
	for (const auto& cmp : nComponents) cmp->handleEvent(event);
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/*
		@no need to get transform maybe?
	*/
	states.transform *= getTransform();
	for (const auto& cmp : nComponents) target.draw(*cmp, states);
}
