#ifndef ACHIEVEMENT_HPP
#define ACHIEVEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Components.hpp"
#include "Animatable.hpp"

/*
	@possible baseclas?? who knows
*/
class Achievement : public sf::Drawable, public sf::Transformable
{
public:
	Achievement(const std::string& id, const sf::Texture& locked, const sf::Texture& unlocked);

	/*
		@not really needed? but oh well
	*/
	std::string getIdentifier() const;
	bool isLocked() const;
	
	void unlock();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const sf::Texture& nLockedTexture;
	const sf::Texture& nUnlockedTexture;

	bool nLocked;

	std::string nIdentifier;
	sf::Sprite nSprite;
	AnimatableSprite nAnimeSprite;
};


#endif