#include "Character.hpp"

#include <stdexcept>
#include <iostream>

Character::Character(CharacterBlueprint& blueprint) :
	nEntity(blueprint.getIdentifier(), blueprint.getTexture(blueprint.getDefaultState())),
	nSecondaryEntity(blueprint.getIdentifier(), blueprint.getTexture(blueprint.getDefaultState())),
	nBlueprint(blueprint),
	nTransitionTime(0.0),
	nTransitionElapsed(sf::Time::Zero),
	nInTransition(false),
	nCurrentState(blueprint.getDefaultState())
{
}

void Character::update(sf::Time dt)
{
	if (nInTransition)
	{
		nTransitionElapsed += dt;

		if (nTransitionElapsed.asSeconds() > nTransitionTime)
		{
			nInTransition = false;
			// guards
			nEntity.skipAnimation();
			nSecondaryEntity.skipAnimation();
			nTransitionElapsed = sf::Time::Zero;
		}
	}

	if (nInTransition)
	{
		nSecondaryEntity.update(dt);
	}
	nEntity.update(dt);
}

std::string Character::getIdentifier() const
{
	// get from blueprint
	return nBlueprint.getIdentifier();
}

// instant set no fade
bool Character::setState(const std::string& id) noexcept
{
	if (!nBlueprint.stateExists(id))
	{
		return false;		// also log later
	}

	nCurrentState = id;
	nEntity.setTexture(nBlueprint.getTexture(id));
	return true;
}

bool Character::setState(const std::string& id, float transitionTime) noexcept
{
	if (!nBlueprint.stateExists(id))
	{
		return false;		
	}


	if (transitionTime < 0)
	{
		return false;
	}

	if (transitionTime > 0)
	{
		nInTransition = true;
		nTransitionTime = transitionTime;

		nSecondaryEntity.setTexture(nBlueprint.getTexture(nCurrentState));
		nSecondaryEntity.setOpacityAlpha(255);		// max, just in case 
		
		nEntity.setTexture(nBlueprint.getTexture(id));
		
		nSecondaryEntity.fade(transitionTime, 0);
		nEntity.fade(transitionTime, 255, 0);

		nCurrentState = id;			// future current state
		return true;
	}
	
	return setState(id);		// instant
}

bool Character::inAnimation() const
{
	// use all 3 just to be safe
	return (nEntity.inAnimation() || nSecondaryEntity.inAnimation() || nInTransition);
}

void Character::skipAnimation()
{
	// skip transition
	if (nInTransition)
	{
		nInTransition = false;
		nEntity.skipAnimation();
		nSecondaryEntity.skipAnimation();
		nTransitionElapsed = sf::Time::Zero;
	}
}

Entity* Character::getEntity() 
{
	return &nEntity;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// states.transform *= getTransform();   

	if (nInTransition)
	{
		target.draw(nSecondaryEntity, states);
	}
	target.draw(nEntity, states);
}

