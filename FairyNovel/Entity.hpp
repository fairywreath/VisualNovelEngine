#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <string>

// entity class, identifier is their sprite name
// possibly create a character class with possible state changes in the future 

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	// possible states later?
	enum class EntityState
	{
		Animation
	};

public:
	Entity(const std::string& identifier, sf::Texture& texture);
	void update(sf::Time dt);

	virtual sf::FloatRect getBoundingRect() const;

	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

	std::string getIdentifier() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::string nIdentifier;		// texture name for the texture manager
	sf::Vector2f nVelocity;
	sf::Sprite nSprite;

};

#endif

