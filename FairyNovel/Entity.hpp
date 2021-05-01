#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <string>
#include <limits>

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
	Entity(const std::string& identifier, const sf::Texture& texture);
	
	virtual void update(sf::Time dt);

	virtual void fade(float time, int targetAlpha, int startAlpha = -1);
	virtual void move(float time, sf::Vector2f dest, sf::Vector2f source = sf::Vector2f(FLT_MAX, FLT_MAX ));

	virtual sf::FloatRect getBoundingRect() const;

	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

	std::string getIdentifier() const;

	void setTexture(const sf::Texture& texture);
	void setOpacityAlpha(int alpha);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::string nIdentifier;		// texture name for the texture manager
	sf::Vector2f nVelocity;
	sf::Sprite nSprite;


};

#endif

