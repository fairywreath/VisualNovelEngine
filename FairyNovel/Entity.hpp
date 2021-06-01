#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <string>
#include <memory>

#include "Logger.hpp"
#include "Components.hpp"
#include "Animatable.hpp"
#include "Movable.hpp"


class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(const std::string& identifier, const sf::Texture& texture);
	virtual ~Entity() = default;

	virtual void update(sf::Time dt);
	
	std::string getIdentifier() const;

	void setTexture(const sf::Texture& texture);

	/*
		@fade values, on animatable
	*/
	void setOpacityAlpha(int alpha);
	int getOpacityAlpha() const;

	virtual bool inAnimation() const;
	virtual void skipAnimation();		// skip to final position/opacity
	virtual void stopAnimation();		// stop at current	

	void fade(float time, int targetAlpha);
	virtual void fade(float time, int targetAlpha, int startAlpha);
	
	void move(float time, const sf::Vector2f& dest);
	virtual void move(float time, const sf::Vector2f& dest, const sf::Vector2f& source);

	void blur(float time, float endPerc);
	virtual void blur(float time, float endPerc, float startPerc);

	float getBlurPercentage() const; 

	virtual sf::FloatRect getBoundingRect() const;


private:	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	AnimatableSprite nAnimeSprite;
	sf::Sprite nSprite;

	Movable nMover;

	std::string nIdentifier;	
};

#endif

