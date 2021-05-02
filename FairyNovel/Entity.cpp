#include "Entity.hpp"
#include "Logger.hpp"

#include <sfml/Graphics/RenderTarget.hpp>

#include <stdexcept>
#include <cassert>
#include <iostream>

Entity::Entity(const std::string& identifier, const sf::Texture& texture) :
    nIdentifier(identifier),
    nSprite(),
    nInFade(false),
    nInMovement(false),
    nOpacity(255),		// start at 0 or 255?
    nFadeTime(0),
    nTargetOpacity(255),
    nMoveTime(0),
    nFadeElapsed(sf::Time::Zero),
    nMoveElapsed(sf::Time::Zero),
	nUseShader(false),
	nInBlurAnimation(false),
	nBlurElapsed(sf::Time::Zero),
	nBlurRadius(0),
	nTargetBlurRadius(0),
	MaxBlurRadius(0.025f),
	nBlurTime(0)
{
    nSprite.setTexture(texture);
	initializeBlurShader();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();     // get transform from transformable class parent, when setPosition is doen from the oustide
	if (nUseShader)
	{
		states.shader = &nBlurShader;
	}
	target.draw(nSprite, states);
}


void Entity::update(sf::Time dt)
{
	if (nInFade)
	{
		nFadeElapsed += dt;
		if (nFadeElapsed.asSeconds() >= nFadeTime)
		{
			nInFade = false;
			nOpacity = nTargetOpacity;
			setOpacityAlpha((int)nTargetOpacity);
			nFadeElapsed = sf::Time::Zero;
		}
		else
		{
			float alpha = (float)nOpacity + ((float)(nTargetOpacity - nOpacity)
				* nFadeElapsed.asSeconds() / nFadeTime);
			nSprite.setColor(sf::Color(255, 255, 255, (int)alpha));
		}
	}

	if (nInMovement)
	{
		nMoveElapsed += dt;
		if (nMoveElapsed.asSeconds() >= nMoveTime)
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

	if (nInBlurAnimation)
	{
		nBlurElapsed += dt;
		if (nBlurElapsed.asSeconds() >= nBlurTime)
		{
			nInBlurAnimation = false;

			if(nTargetBlurRadius == 0)
				nUseShader = false;
			else
				setShaderUniform("blur_radius", nTargetBlurRadius);

			nBlurRadius = nTargetBlurRadius;
			nMoveElapsed = sf::Time::Zero;
		}
		else
		{
			float radius = nBlurRadius + (nTargetBlurRadius - nBlurRadius)
				* nBlurElapsed.asSeconds() / nBlurTime;
			setShaderUniform("blur_radius", radius);
		}
	}
}

void Entity::fade(float time, int targetAlpha, int startAlpha)
{
	// std::cout << "fade\n";
	if (time < 0)
	{
		std::string msg = "Time is negative";
		LOGGER->Log("Error at blur entity", msg);
		return;
	}

	if (targetAlpha < 0 || targetAlpha > 255 || startAlpha < 0 || (startAlpha > 255 && startAlpha != INT_MAX))
	{
		std::string msg = "Invalid arguments for fade alpha value";
		LOGGER->Log("Error at fade entity", msg);
		return;
	}

	if (startAlpha != INT_MAX)		// given starting alpha, do not use current
		nOpacity = startAlpha;
	else
		startAlpha = nOpacity;
	
	nTargetOpacity = targetAlpha;
	nFadeTime = time;
	setOpacityAlpha(startAlpha);

	nInFade = true;
}

void Entity::move(float time, const sf::Vector2f& dest, const sf::Vector2f& source)
{
	sf::Vector2f start = source;
	if (start.x == FLT_MAX)		// flag to use current position
		start = getPosition();		// from current position
	else
		setPosition(source);

	nStartingPosition = start;
	nTargetPosition = dest;
	nMoveTime = time;
	nInMovement = true;
}

void Entity::blur(float time, float endPerc, float startPerc)
{
	if (time < 0)
	{
		std::string msg = "Time is negative";
		LOGGER->Log("Error at blur entity", msg);
		return;
	}

	if ((startPerc > 100 && startPerc != FLT_MAX) || startPerc < 0 || endPerc > 100 || endPerc < 0)
	{
		std::string msg = "Invalid arguments for blur percentage";
		LOGGER->Log("Error at blur entity", msg);
		return;
	}

	float startRadius = nBlurRadius;
	if (startPerc != FLT_MAX) startRadius = (startPerc / 100.f) * MaxBlurRadius;

	nBlurRadius = startRadius;
	nTargetBlurRadius = (endPerc / 100.f) * MaxBlurRadius;
	setShaderUniform("blur_radius", startRadius);
	nInBlurAnimation = true;
	nUseShader = true;
	nBlurTime = time;
}

float Entity::getBlurPercentage() const
{
	return 100 * (nBlurRadius / MaxBlurRadius);
}


void Entity::setShaderUniform(const std::string& uniform, float args)
{
	if (args == FLT_MAX) return;
	nBlurShader.setUniform(uniform, args);
}


sf::FloatRect Entity::getBoundingRect() const
{
    return this->getTransform().transformRect(nSprite.getLocalBounds());
}

std::string Entity::getIdentifier() const
{
    return nIdentifier;
}

void Entity::setTexture(const sf::Texture& texture)
{
    nSprite.setTexture(texture);
}

void Entity::setOpacityAlpha(int alpha)
{
	if (alpha < 0 || alpha > 255)
	{
		std::string ms = "Alpha opacity value should be in between 0 and 255";
		LOGGER->Log("Error in setting entity opacity", ms);
		return;
	}

    nSprite.setColor(sf::Color(255, 255, 255, alpha));
	nOpacity = alpha;
}

int Entity::getOpacityAlpha() const
{
	// value when in animation may be off
	assert(!inAnimation());
	
	return nOpacity;
}

bool Entity::inAnimation() const 
{
	return (nInFade || nInMovement || nInBlurAnimation);
}

void Entity::skipAnimation()
{
	if (nInFade)
	{
		nInFade = false;
		nOpacity = nTargetOpacity;
		setOpacityAlpha((int)nTargetOpacity);
		nFadeElapsed = sf::Time::Zero;
	}

	if (nInMovement)
	{
		nInMovement = false;
		setPosition(nTargetPosition);
		nMoveElapsed = sf::Time::Zero;
	}

	if (nInBlurAnimation)
	{
		nInBlurAnimation = false;

		if (nTargetBlurRadius == 0)
			nUseShader = false;
		else
			setShaderUniform("blur_radius", nTargetBlurRadius);

		nBlurRadius = nTargetBlurRadius;
		nMoveElapsed = sf::Time::Zero;
	}
}


void Entity::initializeBlurShader()
{
	if (!nBlurShader.loadFromFile("Media/Shaders/Blur.frag", sf::Shader::Fragment))
	{
		throw std::runtime_error("Cannot load blur shader\n");
	}

	nBlurShader.setUniform("texture", sf::Shader::CurrentTexture);
	nBlurShader.setUniform("blur_radius", 0.0f);
}