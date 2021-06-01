#include "Movable.hpp"

Movable::Movable(sf::Transformable* transformable) :
	nTransformable(transformable),
	nInMovement(false),
	nMoveTime(0),
	nMoveElapsed(sf::Time::Zero)
{
}

void Movable::update(sf::Time dt)
{
	if (nInMovement)
	{
		nMoveElapsed += dt;
		if (nMoveElapsed.asSeconds() >= nMoveTime)
		{
			nInMovement = false;
			nTransformable->setPosition(nTargetPosition);
			nMoveElapsed = sf::Time::Zero;
		}
		else
		{
			sf::Vector2f pos = nStartingPosition + (nTargetPosition - nStartingPosition)
				* nMoveElapsed.asSeconds() / nMoveTime;

			nTransformable->setPosition(pos);
		}
	}
}

void Movable::move(float time, const sf::Vector2f& dest, const sf::Vector2f& source)
{
	if (nTransformable->getPosition() != source) 
		nTransformable->setPosition(source);

	nStartingPosition = source;
	nTargetPosition = dest;
	nMoveTime = time;
	nInMovement = true;
}

bool Movable::inMovement() const
{
	return nInMovement;
}

void Movable::skipMovement()
{
	if (nInMovement)
	{
		nInMovement = false;
		nTransformable->setPosition(nTargetPosition);
		nMoveElapsed = sf::Time::Zero;
	}

}

void Movable::stopMovement()
{
	if (nInMovement)
	{
		nInMovement = false;
		nMoveElapsed = sf::Time::Zero;
	}
}
