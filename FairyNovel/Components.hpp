#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "Fadable.hpp"
#include "Blurable.hpp"
#include "Animatable.hpp"

namespace sf
{
	class Sprite;
	class Text;
}

using FadableSprite = Fadable<sf::Sprite>;
using FadableText = Fadable<sf::Text>;
using FadableRectShape = Fadable<sf::RectangleShape>;

using AnimatableSprite = Animatable<sf::Sprite>;
using AnimatableText = Animatable<sf::Text>;
using AnimatableRectShape = Animatable<sf::RectangleShape>;



#endif