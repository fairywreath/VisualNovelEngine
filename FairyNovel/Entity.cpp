#include "Entity.hpp"

#include <sfml/Graphics/RenderTarget.hpp>

Entity::Entity(const std::string& identifier, const sf::Texture& texture) :
    nIdentifier(identifier),
    nSprite(),
    nVelocity(sf::Vector2f(0.f, 0.f))
{
    nSprite.setTexture(texture);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();     // get transform from transformable class parent, when setPosition is doen from the oustide
    target.draw(nSprite, states);
}

void Entity::update(sf::Time dt)
{
    // posible animation updates
}

void Entity::fade(float time, int targetAlpha, int startAlpha)
{
    // maybe implement it in base class?
}

void Entity::move(float time, sf::Vector2f dest, sf::Vector2f source)
{
    // maybe implement it here in base class?
}


sf::FloatRect Entity::getBoundingRect() const
{
    return this->getTransform().transformRect(nSprite.getLocalBounds());
}

void Entity::setVelocity(const sf::Vector2f& velocity)
{
    nVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    nVelocity = sf::Vector2f(vx, vy);
}

sf::Vector2f Entity::getVelocity() const
{
    return nVelocity;
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
    nSprite.setColor(sf::Color(255, 255, 255, alpha));
}
