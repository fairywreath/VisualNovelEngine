#ifndef ANIMATABLE_HPP
#define ANIMATABLE_HPP

#include <cassert>
#include <stdint.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Fadable.hpp"
#include "Blurable.hpp"
#include "Logger.hpp"

/*
	@used on Entity, buttons etc. for fading, movement etc.
	@takes in a sf::Transoformable and sf::Drawable descendant
*/

template <typename T>
class Animatable : public sf::Drawable
{
public:		
	explicit Animatable(T& resource);

	void update(sf::Time dt);

	void fade(float time, int targetAlpha, int startAlpha);;
	void blur(float time, float endPerc, float startPerc);

	bool inAnimation() const;
	void skipAnimation();
	void stopAnimation();

	void setOpacityAlpha(int alpha);
	int getOpacityAlpha() const;
	float getBlurPercentage() const;

	void setShaderUniform(float args);

	void setObjectColor(const sf::Color& color);

	void setOutlineOnly(bool status);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	T* nObject;

	Fadable<T> nFadable;
	Blurable nBlurable;
};

#include "Animatable.inl"
#endif

