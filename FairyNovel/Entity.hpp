#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <string>
#include <limits>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(const std::string& identifier, const sf::Texture& texture);
	virtual ~Entity() = default;

	virtual void update(sf::Time dt);
	
	std::string getIdentifier() const;

	void setTexture(const sf::Texture& texture);
	void setOpacityAlpha(int alpha);
	int getOpacityAlpha() const;

	virtual bool inAnimation() const;
	virtual void skipAnimation();		// skip to final position/opacity

	void fade(float time, int targetAlpha);
	virtual void fade(float time, int targetAlpha, int startAlpha);
	
	void move(float time, const sf::Vector2f& dest);
	virtual void move(float time, const sf::Vector2f& dest, const sf::Vector2f& source);

	void blur(float time, float endPerc);
	virtual void blur(float time, float endPerc, float startPerc);

	float getBlurPercentage() const;
	void setShaderUniform(const std::string& uniform, float args);

	virtual sf::FloatRect getBoundingRect() const;

private:	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void initializeBlurShader();

private:
	std::string nIdentifier;		
	sf::Sprite nSprite;

	/*
		@fading
	*/
	int nOpacity;	
	int nTargetOpacity;
	float nFadeTime;	
	bool nInFade;

	/*
		@movement
	*/
	sf::Vector2f nStartingPosition;
	sf::Vector2f nTargetPosition;
	float nMoveTime;
	bool nInMovement;

	/*
		@blurring
	*/
	sf::Shader nBlurShader;
	
	static constexpr float MaxBlurRadius = 0.25;

	bool nUseShader;
	bool nInBlurAnimation;
	float nBlurTime;
	float nBlurRadius;
	float nTargetBlurRadius;			

	sf::Time nFadeElapsed;
	sf::Time nMoveElapsed;
	sf::Time nBlurElapsed;
};

#endif

