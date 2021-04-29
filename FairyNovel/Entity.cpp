#include "Entity.hpp"

#include <sfml/Graphics/RenderTarget.hpp>

Entity::Entity(const std::string& identifier, sf::Texture& texture) :
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
