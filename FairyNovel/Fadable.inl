template<typename T>
Fadable<T>::Fadable(T& resource) :
	nObject(&resource),
	/*
		@fades
	*/
	nColorR(255),
	nColorG(255),
	nColorB(255),
	nInFade(false),
	nOpacity(255),
	nFadeTime(0),
	nTargetOpacity(255),
	nFadeElapsed(sf::Time::Zero),
	nOutlineOnly(false)
{
}

template<typename T>
void Fadable<T>::update(sf::Time dt)
{
	if (nObject == nullptr) return;

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
			setObjectAlpha((int)alpha);
		}
	}
}

template<typename T>
void Fadable<T>::fade(float time, int targetAlpha, int startAlpha)
{
	if (nObject == nullptr) return;


	if (time < 0)
	{
		std::string msg = "Time is negative";
		LOGGER->Log("Error at blur entity", msg);
		return;
	}

	if (targetAlpha < 0 || targetAlpha > 255 || startAlpha < 0 || startAlpha > 255)
	{
		std::string msg = "Invalid arguments for fade alpha value: Target=" + std::to_string(targetAlpha)
			+ " Start= " + std::to_string(startAlpha);
		LOGGER->Log("Error at fade entity", msg);
		return;
	}

	nTargetOpacity = targetAlpha;
	nFadeTime = time;
	setOpacityAlpha(startAlpha);

	nInFade = true;
}


template<typename T>
bool Fadable<T>::inAnimation() const
{
	return nInFade;
}

template<typename T>
void Fadable<T>::skipAnimation()
{
	if (nInFade)
	{
		nInFade = false;
		nOpacity = nTargetOpacity;
		setOpacityAlpha((int)nTargetOpacity);
		nFadeElapsed = sf::Time::Zero;
	}
}

template<typename T>
void Fadable<T>::setOpacityAlpha(int alpha)
{
	if (nObject == nullptr) return;

	if (alpha < 0 || alpha > 255)
	{
		std::string ms = "Alpha opacity value should be in between 0 and 255";
		LOGGER->Log("Error in setting entity opacity", ms);
		return;
	}

	setObjectAlpha(alpha);
	nOpacity = alpha;
}

template<typename T>
int Fadable<T>::getOpacityAlpha() const
{
	assert(!inAnimation());

	return nOpacity;
}

template<typename T>
void Fadable<T>::setObjectColor(const sf::Color& color)
{
	nColorR = color.r;
	nColorG = color.g;
	nColorB = color.b;
}

template<typename T>
void Fadable<T>::setOutlineOnly(bool status)
{
	nOutlineOnly = true;
}

template<typename T>
void Fadable<T>::setObjectAlpha(int alpha)
{
	if (nObject == nullptr)
	{
		// maybe log?
		return;
	}

	if (nOutlineOnly)
	{
		nObject->setOutlineColor(sf::Color(nColorR, nColorG, nColorB, alpha));
	}
	else
	{
		nObject->setFillColor(sf::Color(nColorR, nColorG, nColorB, alpha));
	}
}

template<typename T>
void Fadable<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (nObject == nullptr)
	{
		// maybe log?
		return;
	}

	target.draw(*nObject, states);
}


