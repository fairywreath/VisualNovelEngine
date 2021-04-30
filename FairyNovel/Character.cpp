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
	nTargetOpacity(255)
//	nFadeDirection(0)
{
	insertState(defState, texture);
}

void Character::update(sf::Time dt)
{
	if (nInFade)
	{
		if (nFadeClock.getElapsedTime().asSeconds() >= nFadeTime)
		{
			nInFade = false;
			nOpacity = nTargetOpacity;
			std::cout << "fade done\n";
		}
		else
		{
			float alpha = (float)nOpacity + (float)(nTargetOpacity - nOpacity) 
				* nFadeClock.getElapsedTime().asSeconds() / nFadeTime;
			setOpacityAlpha((int)alpha);
			if (alpha == nTargetOpacity) 
			{
				nInFade = false;
				nOpacity = nTargetOpacity;
			}
		}
	}
	
	if (nInMovement)
	{

	}
}

void Character::fade(float time, int alpha)
{
	nTargetOpacity = alpha;
	nFadeTime = time;

	//if (alpha - nOpacity >= 0) nFadeDirection = 1;
	//else nFadeDirection = -1;

	nInFade = true;
	nFadeClock.restart();
}

void Character::fade(float time, int startAlpha, int targetAlpha)
{
	nOpacity = startAlpha;
	nTargetOpacity = targetAlpha;
	nFadeTime = time;
	setOpacityAlpha(startAlpha);

	nInFade = true;
	nFadeClock.restart();
}

void Character::move(float time, sf::Vector2f dest)
{

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
