#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "Animatable.hpp"

namespace sf
{
	class Sprite;
	class Text;
}


using AnimatableSprite = Animatable<sf::Sprite>;
using AnimatableText = Animatable<sf::Text>;
using AnimatableRectShape = Animatable<sf::RectangleShape>;



#endif