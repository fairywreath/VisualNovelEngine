#include "Character.hpp"

#include <stdexcept>
#include <iostream>

Character::Character(const std::string& identifier, const sf::Texture& texture,
	const std::string& defState) :
	Entity(identifier, texture),
	nTextureMap()
{
	insertState(defState, texture);
}

void Character::update(sf::Time dt)
{
}

void Character::fade(float time, int targetAlpha,  int startAlpha)
{
}

//void Character::move(float time, sf::Vector2f dest, sf::Vector2f source)
//{
//
//}


void Character::insertState(const std::string& id, const sf::Texture& texture)
{
	nTextureMap.insert(std::make_pair(id, &texture));
}

void Character::setState(const std::string& id, float fadeTime)
{
	if (fadeTime < 0)
		throw std::runtime_error("Time value for fade cannot be negative\n");
	else if (fadeTime > 0)
	{
		fade(fadeTime, 255, 0);
	}

	if (nTextureMap.find(id) == nTextureMap.end())
		throw std::runtime_error("Character State Texture ID is not in map");
	setTexture(*nTextureMap.at(id));		// change sprite texture
}

bool Character::inAnimation()
{
	return false;
}

void Character::skipAnimation()
{

}


//void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//}
