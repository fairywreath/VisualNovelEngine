#include "Character.hpp"

#include <stdexcept>
#include <iostream>

Character::Character(const std::string& identifier, const sf::Texture& texture,
	const std::string& defState) :
	Entity(identifier, texture),
	nTextureMap(),
	nInFade(false),
	nInMovement(false),
	nOpacity(255),		// start at 0 or 255?
	nFadeTime(0),
	nTargetOpacity(255),
	nMoveTime(0),
	nFadeElapsed(sf::Time::Zero),
	nMoveElapsed(sf::Time::Zero)
{
	insertState(defState, texture);
}

void Character::update(sf::Time dt)
{
	if (nInFade)
	{
		nFadeElapsed += dt;
		//if (nFadeClock.getElapsedTime().asSeconds() >= nFadeTime)
		if (nFadeElapsed.asSeconds() >= nFadeTime)
		{
			nInFade = false;
			nOpacity = nTargetOpacity;
			setOpacityAlpha((int)nTargetOpacity);
			nFadeElapsed = sf::Time::Zero;
		}
		else
		{
			float alpha = (float)nOpacity + (float)(nTargetOpacity - nOpacity) 
				* nFadeElapsed.asSeconds() / nFadeTime;
			setOpacityAlpha((int)alpha);
		}
	}
	
	if (nInMovement)
	{
		nMoveElapsed += dt;
		if (nMoveElapsed.asSeconds() > nMoveTime)
		{
			nInMovement = false;
			setPosition(nTargetPosition);
			nMoveElapsed = sf::Time::Zero;
		}
		else
		{
			sf::Vector2f pos = nStartingPosition + (nTargetPosition - nStartingPosition)
				* nMoveElapsed.asSeconds() / nMoveTime;
			
			setPosition(pos);
		}
	}
}

void Character::fade(float time, int targetAlpha,  int startAlpha)
{
	if (targetAlpha < 0 || targetAlpha > 255 || startAlpha < 0 || (startAlpha > 255 && startAlpha != INT_MAX))
		throw std::runtime_error("Invalid Alpha amount for fade\n");

	if (startAlpha != INT_MAX)		// given starting alpha, do not use current
		nOpacity = startAlpha;
	else
		startAlpha = nOpacity;

	nTargetOpacity = targetAlpha;
	nFadeTime = time;
	setOpacityAlpha(startAlpha);

	nInFade = true;
//	nFadeElapsed = sf::Time::Zero;  // sanity check
}

void Character::move(float time, sf::Vector2f dest, sf::Vector2f source)
{
	if (source.x == FLT_MAX)		// flag to use current position
		source = getPosition();		// from current position
	else
		setPosition(source);

	nStartingPosition = source;
	nTargetPosition = dest;
	nMoveTime = time;
	nInMovement = true;
//	nMoveElapsed = sf::Time::Zero;
}


void Character::insertState(const std::string& id, const sf::Texture& texture)
{
	nTextureMap.insert(std::make_pair(id, &texture));
}

void Character::setState(const std::string& id)
{
	if (nTextureMap.find(id) == nTextureMap.end())
		throw std::runtime_error("Character State Texture ID is not in map");
	setTexture(*nTextureMap.at(id));		// change sprite texture
}

bool Character::inAnimation()
{
	return (nInFade || nInMovement);
}


//void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//}
