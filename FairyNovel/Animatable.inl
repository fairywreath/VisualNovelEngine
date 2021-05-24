template<typename T>
Animatable<T>::Animatable() :
	nObject(nullptr),
	/*
		@fades
	*/
	nColorR(255),
	nColorG(255),
	nColorB(255),
	nInFade(false),
	nOpacity(255),		// start at 0 or 255?
	nFadeTime(0),
	nTargetOpacity(255),
	nFadeElapsed(sf::Time::Zero),
	/*
		@blurs
	*/
	nUseShader(false),
	nInBlurAnimation(false),
	nBlurElapsed(sf::Time::Zero),
	nBlurRadius(0),
	nTargetBlurRadius(0),
	nBlurTime(0)
{
	initializeBlurShader();
}

template<typename T>
Animatable<T>::Animatable(T& resource) :
	nObject(&resource),
	/*
		@fades
	*/
	nColorR(255),
	nColorG(255),
	nColorB(255),
	nInFade(false),
	nOpacity(255),		// start at 0 or 255?
	nFadeTime(0),
	nTargetOpacity(255),
	nFadeElapsed(sf::Time::Zero),
	/*
		@blurs
	*/
	nUseShader(false),
	nInBlurAnimation(false),
	nBlurElapsed(sf::Time::Zero),
	nBlurRadius(0),
	nTargetBlurRadius(0),
	nBlurTime(0)
{
	initializeBlurShader();
}

template<typename T>
void Animatable<T>::setObject(T& object)
{
	nObject = &object;
}

template<typename T>
void Animatable<T>::releaseObject()
{
	nObject = nullptr;
}

template<typename T>
void Animatable<T>::update(sf::Time dt)
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
			//std::cout << "radius: " << radius << std::endl;
			setShaderUniform(radius);
		}
	}
}

template<typename T>
void Animatable<T>::fade(float time, int targetAlpha, int startAlpha)
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
void Animatable<T>::blur(float time, float endPerc, float startPerc)
{
	if (nObject == nullptr) return;


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

template<typename T>
bool Animatable<T>::inAnimation() const
{
	return (nInFade || nInBlurAnimation);
}

template<typename T>
void Animatable<T>::skipAnimation()
{
	if (nInFade)
	{
		nInFade = false;
		nOpacity = nTargetOpacity;
		setOpacityAlpha((int)nTargetOpacity);
		nFadeElapsed = sf::Time::Zero;
	}

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

template<typename T>
void Animatable<T>::setOpacityAlpha(int alpha)
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
int Animatable<T>::getOpacityAlpha() const
{
	assert(!inAnimation());

	return nOpacity;
}

template<typename T>
float Animatable<T>::getBlurPercentage() const
{
	return 100 * (nBlurRadius / MaxBlurRadius);
}

template<typename T>
void Animatable<T>::setShaderUniform(float args)
{
	nBlurShader.setUniform("blur_radius", args);
}

template<typename T>
void Animatable<T>::setObjectColor(const sf::Color& color)
{
	nColorR = color.r;
	nColorG = color.g;
	nColorB = color.b;
}

template<typename T>
void Animatable<T>::setObjectAlpha(int alpha)
{
	assert(nObject);

	nObject->setFillColor(sf::Color(nColorR, nColorG, nColorB, alpha));
}

template<typename T>
void Animatable<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	assert(nObject);

	if (nUseShader)
	{
	//	std::cout << "shader used\n";
		states.shader = &nBlurShader;
	}
	target.draw(*nObject, states);
}

template<typename T>
void Animatable<T>::initializeBlurShader()
{
	if (!nBlurShader.loadFromFile("Media/Shaders/Blur.frag", sf::Shader::Fragment))
	{
		throw std::runtime_error("Cannot load blur shader\n");
	}

	nBlurShader.setUniform("texture", sf::Shader::CurrentTexture);
	nBlurShader.setUniform("blur_radius", 0.0f);
}