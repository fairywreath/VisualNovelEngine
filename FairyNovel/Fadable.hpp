#ifndef FADABLE_HPP
#define FADABLE_HPP

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
class Fadable : public sf::Drawable
{
public:
	explicit Fadable(T& resource);

	void update(sf::Time dt);

	void fade(float time, int targetAlpha, int startAlpha);;

	bool inAnimation() const;
	void skipAnimation();

	void setOpacityAlpha(int alpha);
	int getOpacityAlpha() const;

	void setObjectColor(const sf::Color& color);
	void setOutlineOnly(bool status);					// for outline squares for example
	void setBothFillOutline(bool status);

private:
	void setObjectAlpha(int alpha);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


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
	bool nOutlineOnly;
	bool nBothFillOutline;

	/*
		@fade colours, defaults are white
	*/
	uint8_t nColorR;
	uint8_t nColorG;
	uint8_t nColorB;

	sf::Color nOutlineColor;
};

/*
	@full member specializations
*/
template<>
void Fadable<sf::Sprite>::setObjectAlpha(int alpha);

#include "Fadable.inl"
#endif