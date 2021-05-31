#ifndef BLURABLE_HPP
#define BLURABLE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Time.hpp>

/*
	@need to always draw from this class
	@currently only implemented in entity
*/
class Blurable : public sf::Drawable
{
public:
	explicit Blurable(sf::Drawable* drawable);
	
	void update(sf::Time dt);

	void blur(float time, float endPerc, float startPerc);

	bool inAnimation() const;
	void skipAnimation();

	float getBlurPercentage() const;

	void setShaderUniform(float args);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Drawable* nDrawable;			// can possible be an array?
	sf::Shader nBlurShader;

	static constexpr float MaxBlurRadius = 0.25;

	bool nUseShader;
	bool nInBlurAnimation;
	float nBlurTime;
	float nBlurRadius;
	float nTargetBlurRadius;

	sf::Time nBlurElapsed;


};


#endif