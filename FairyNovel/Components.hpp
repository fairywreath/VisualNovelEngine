#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

namespace sf
{
	class Sprite;
	class Text;
}

template<typename T>
class Animatable;

using AnimatableSprite = Animatable<sf::Sprite>;
using AnimatableText = Animatable<sf::Text>;



#endif