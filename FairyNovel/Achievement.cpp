#include "Achievement.hpp"

Achievement::Achievement(const std::string& id, const sf::Texture& locked, 
	const sf::Texture& unlocked) :
	nIdentifier(id),
	nLockedTexture(locked),
	nUnlockedTexture(unlocked),
	nSprite(locked),
	nAnimeSprite(nSprite),
	nLocked(false)
{
}

std::string Achievement::getIdentifier() const
{
	return nIdentifier;
}

bool Achievement::isLocked() const
{
	return nLocked;
}

void Achievement::unlock()
{
	nLocked = true;
	nSprite.setTexture(nUnlockedTexture);
}

void Achievement::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(nSprite, states);
}
