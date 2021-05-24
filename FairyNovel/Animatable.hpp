#ifndef ANIMATABLE_HPP
#define ANIMATABLE_HPP

#include <cassert>
#include <stdint.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logger.hpp"

/*
	@used on Entity, buttons etc. for fading, movement etc.
	@takes in a sf::Transoformable and sf::Drawable descendant
*/

template <typename T>
class Animatable : public sf::Drawable
{
public:		
	Animatable();
	explicit Animatable(T& resource);

	void setObject(T& object);
	void releaseObject();				// not needed really

	void update(sf::Time dt);

	void fade(float time, int targetAlpha, int startAlpha);;
	void blur(float time, float endPerc, float startPerc);

	bool inAnimation() const;
	void skipAnimation();

	void setOpacityAlpha(int alpha);
	int getOpacityAlpha() const;
	float getBlurPercentage() const;

	void setShaderUniform(float args);

	void setObjectColor(const sf::Color& color);

private:
	void setObjectAlpha(int alpha);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void initializeBlurShader();

private:
	T* nObject;
	/*
		@fading
	*/
	int nOpacity;
	int nTargetOpacity;
	float nFadeTime;
	bool nInFade;
	sf::Time nFadeElapsed;

	/*
		@blur colours, defaults are white
	*/
	uint8_t nColorR;
	uint8_t nColorG;
	uint8_t nColorB;

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

	sf::Time nBlurElapsed;

};

/*
	@full member specializations
*/
template<>
void Animatable<sf::Sprite>::setObjectAlpha(int alpha);

#include "Animatable.inl"
#endif

