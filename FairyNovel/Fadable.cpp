#include "Fadable.hpp"

template<>
void Fadable<sf::Sprite>::setObjectAlpha(int alpha)
{
	if (nObject == nullptr) return;

	nObject->setColor(sf::Color(nFillColor.r, nFillColor.g, nFillColor.b, alpha));
}