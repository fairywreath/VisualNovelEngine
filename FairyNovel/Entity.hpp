#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <string>
#include <limits>

// entity class, identifier is their sprite name
// possibly create a character class with possible state changes in the future 

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(const std::string& identifier, const sf::Texture& texture);
	
	virtual void update(sf::Time dt);
	virtual sf::FloatRect getBoundingRect() const;

	std::string getIdentifier() const;

	void setTexture(const sf::Texture& texture);
	void setOpacityAlpha(int alpha);
	int getOpacityAlpha() const;

	virtual bool inAnimation() const;
	virtual void skipAnimation();		// skip to final position/opacity

	virtual void fade(float time, int targetAlpha, int startAlpha = INT_MAX);
	virtual void move(float time, const sf::Vector2f& dest, const sf::Vector2f& source = sf::Vector2f(FLT_MAX, FLT_MAX));

	void blur(float time, float endPerc, float startPerc = FLT_MAX);
	float getBlurPercentage() const;

	void setShaderUniform(const std::string& uniform, float args = FLT_MAX);

private:	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void initializeBlurShader();

private:
	std::string nIdentifier;		
	sf::Sprite nSprite;

	// fades
	int nOpacity;	
	int nTargetOpacity;
	float nFadeTime;	
	bool nInFade;

	// movement
	sf::Vector2f nStartingPosition;
	sf::Vector2f nTargetPosition;
	float nMoveTime;
	bool nInMovement;

	// blurring 
	sf::Shader nBlurShader;
	const float MaxBlurRadius;
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

