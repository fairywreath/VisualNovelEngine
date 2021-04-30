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

	virtual void fade(float time, int alpha = 255) override;		// 0 = transparent, 255 = full opacity
	
	void fade(float time, int startAlpha, int targetAlpha);
	
	virtual void move(float time, sf::Vector2f) override;

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
//	int nFadeDirection;		// -1 or +!

	sf::Clock nFadeClock;
	
	sf::Vector2f nTargetPosition;
	sf::Clock nMovementClock;

	bool nInFade;
	bool nInMovement;		// blur, move in, fade etc.
};

#endif

