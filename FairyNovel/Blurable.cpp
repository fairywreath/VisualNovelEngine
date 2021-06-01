#include "Blurable.hpp"
#include "Logger.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <stdexcept>
#include <cassert>

Blurable::Blurable(sf::Drawable* drawable) :
	nDrawable(drawable),
	nUseShader(false),
	nInBlurAnimation(false),
	nBlurElapsed(sf::Time::Zero),
	nBlurRadius(0),
	nTargetBlurRadius(0),
	nBlurTime(0)
{
	if (!nBlurShader.loadFromFile("Media/Shaders/Blur.frag", sf::Shader::Fragment))
	{
		throw std::runtime_error("Cannot load blur shader\n");
	}

	nBlurShader.setUniform("texture", sf::Shader::CurrentTexture);
	nBlurShader.setUniform("blur_radius", 0.0f);
}

void Blurable::update(sf::Time dt)
{
	if (nInBlurAnimation)
	{
		nBlurElapsed += dt;
		if (nBlurElapsed.asSeconds() >= nBlurTime)
		{
			nInBlurAnimation = false;

			if (nTargetBlurRadius == 0)
				nUseShader = false;
			else
				setShaderUniform(nTargetBlurRadius);

			nBlurRadius = nTargetBlurRadius;
			nBlurElapsed = sf::Time::Zero;
		}
		else
		{
			float radius = nBlurRadius + (nTargetBlurRadius - nBlurRadius)
				* nBlurElapsed.asSeconds() / nBlurTime;
			setShaderUniform(radius);
		}
	}
}

void Blurable::blur(float time, float endPerc, float startPerc)
{
	if (time < 0)
	{
		std::string msg = "Time is negative";
		LOGGER->Log("Error at blur entity", msg);
		return;
	}

	if (startPerc > 100 || startPerc < 0 || endPerc > 100 || endPerc < 0)
	{
		std::string msg = "Invalid arguments for blur percentage";
		LOGGER->Log("Error at blur entity", msg);
		return;
	}

	float startRadius = nBlurRadius;
	if (startPerc != getBlurPercentage()) startRadius = (startPerc / 100.f) * MaxBlurRadius;

	nBlurRadius = startRadius;
	nTargetBlurRadius = (endPerc / 100.f) * MaxBlurRadius;
	setShaderUniform(startRadius);
	nInBlurAnimation = true;
	nUseShader = true;
	nBlurTime = time;
}

bool Blurable::inAnimation() const
{
	return nInBlurAnimation;
}

void Blurable::skipAnimation()
{
	if (nInBlurAnimation)
	{
		nInBlurAnimation = false;

		if (nTargetBlurRadius == 0)
			nUseShader = false;
		else
			setShaderUniform(nTargetBlurRadius);

		nBlurRadius = nTargetBlurRadius;
	}
}

void Blurable::stopAnimation()
{
	if (nInBlurAnimation)
	{
		nInBlurAnimation = false;
		nUseShader = true;			// always assumed to be true, thats why it is unsafe
	}
}

float Blurable::getBlurPercentage() const
{
	return 100 * (nBlurRadius / MaxBlurRadius);
}

void Blurable::setShaderUniform(float args)
{
	nBlurShader.setUniform("blur_radius", args);
}

void Blurable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (nUseShader)
	{
		//	std::cout << "shader used\n";
		states.shader = &nBlurShader;
	}
	target.draw(*nDrawable, states);
}
