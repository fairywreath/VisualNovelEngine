template<typename T>
Animatable<T>::Animatable(T& resource) :
	nObject(&resource),
	nFadable(resource),
	nBlurable(&resource)
{
	
}


template<typename T>
void Animatable<T>::update(sf::Time dt)
{
	nFadable.update(dt);
	nBlurable.update(dt);
}

template<typename T>
void Animatable<T>::fade(float time, int targetAlpha, int startAlpha)
{
	nFadable.fade(time, targetAlpha, startAlpha);
}

template<typename T>
void Animatable<T>::blur(float time, float endPerc, float startPerc)
{
	nBlurable.blur(time, endPerc, startPerc);
}

template<typename T>
bool Animatable<T>::inAnimation() const
{
	return (nFadable.inAnimation() || nBlurable.inAnimation());
}

template<typename T>
void Animatable<T>::skipAnimation()
{
	nFadable.skipAnimation();
	nBlurable.skipAnimation();
}

template<typename T>
void Animatable<T>::setOpacityAlpha(int alpha)
{
	if (nObject == nullptr) return;

	nFadable.setOpacityAlpha(alpha);
}

template<typename T>
int Animatable<T>::getOpacityAlpha() const
{
	assert(!inAnimation());

	return nFadable.getOpacityAlpha();
}

template<typename T>
float Animatable<T>::getBlurPercentage() const
{
	return nBlurable.getBlurPercentage();
}

template<typename T>
void Animatable<T>::setShaderUniform(float args)
{
	nBlurable.setShaderUniform(args);
}

template<typename T>
void Animatable<T>::setObjectColor(const sf::Color& color)
{
	nFadable.setObjectColor(color);
}

template<typename T>
void Animatable<T>::setOutlineOnly(bool status)
{
	nFadable.setOutlineOnly(status);
}


template<typename T>
void Animatable<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (nObject == nullptr) return;

	target.draw(nBlurable, states);
}

