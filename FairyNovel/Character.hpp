#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include <map>

#include <SFML/System/Clock.hpp>

class Character : public Entity
{
public:
	Character(const std::string& identifier, const sf::Texture& texture, const std::string& defState);
	
	void insertState(const std::string& id, const sf::Texture& texture);
	void setState(const std::string& id);

	
	bool inAnimation();

	virtual void fade(float time, int targetAlpha, int startAlpha = INT_MAX) override;
	virtual void move(float time, sf::Vector2f dest, sf::Vector2f source = sf::Vector2f(FLT_MAX, FLT_MAX));

	virtual void update(sf::Time dt);

private:
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// string is for states
	std::map<std::string, const sf::Texture*> nTextureMap;

	// use linear interpolation
	int nOpacity;	// starting opacity
	int nTargetOpacity;	// end opacity
	float nFadeTime;	// in seconds
	bool nInFade;

	sf::Vector2f nStartingPosition;
	sf::Vector2f nTargetPosition;
	float nMoveTime;
	bool nInMovement;	

	sf::Time nFadeElapsed;
	sf::Time nMoveElapsed;
};

#endif

