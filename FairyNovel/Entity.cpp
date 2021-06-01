#include "Entity.hpp"
#include "Logger.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <stdexcept>
#include <cassert>
#include <iostream>

Entity::Entity(const std::string& identifier, const sf::Texture& texture) :
    nIdentifier(identifier),
    nSprite(),
	nAnimeSprite(nSprite),
	nMover(this)
{
	// if not default texture
	if (texture.getSize() != sf::Vector2u(0, 0))
	{
		nSprite.setTexture(texture);
	}

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(nAnimeSprite, states);
}


void Entity::update(sf::Time dt)
{
	nAnimeSprite.update(dt);
	nMover.update(dt);
}

void Entity::fade(float time, int targetAlpha)
{
	fade(time, targetAlpha, nAnimeSprite.getOpacityAlpha());
}

void Entity::fade(float time, int targetAlpha, int startAlpha)
{
	nAnimeSprite.fade(time, targetAlpha, startAlpha);
}

void Entity::move(float time, const sf::Vector2f& dest)
{
	move(time, dest, getPosition());
}

void Entity::move(float time, const sf::Vector2f& dest, const sf::Vector2f& source)
{
	nMover.move(time, dest, source);
}

void Entity::blur(float time, float endPerc)
{
	blur(time, endPerc, getBlurPercentage());
}

void Entity::blur(float time, float endPerc, float startPerc)
{
	nAnimeSprite.blur(time, endPerc, startPerc);
}

float Entity::getBlurPercentage() const
{
	return nAnimeSprite.getBlurPercentage();
}


sf::FloatRect Entity::getBoundingRect() const
{
    return getTransform().transformRect(nSprite.getLocalBounds());
}

std::string Entity::getIdentifier() const
{
    return nIdentifier;
}

void Entity::setTexture(const sf::Texture& texture)
{
    nSprite.setTexture(texture);	
}

void Entity::setOpacityAlpha(int alpha)
{
	nAnimeSprite.setOpacityAlpha(alpha);
}

int Entity::getOpacityAlpha() const
{
//	assert(!inAnimation());
	
	return nAnimeSprite.getOpacityAlpha();
}

bool Entity::inAnimation() const 
{
	return (nAnimeSprite.inAnimation() || nMover.inMovement());
}

void Entity::skipAnimation()
{
	nAnimeSprite.skipAnimation();
	nMover.skipMovement();
}

void Entity::stopAnimation()
{
	nAnimeSprite.stopAnimation();
	nMover.stopMovement();
}


