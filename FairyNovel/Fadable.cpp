#include "Fadable.hpp"

template<>
void Fadable<sf::Sprite>::setObjectAlpha(int alpha)
{
	if (nObject == nullptr) return;

	nObject->setColor(sf::Color(nColorR, nColorG, nColorB, alpha));
}