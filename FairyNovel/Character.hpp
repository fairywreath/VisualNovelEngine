#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include <map>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

class Character : public Entity
{
public:
	Character(const std::string& identifier, const sf::Texture& texture, const std::string& defState);
	~Character() override = default;

	void insertState(const std::string& id, const sf::Texture& texture);
	void setState(const std::string& id, float fadeTime = 0);

	bool inAnimation() const override;
	void skipAnimation() override;		// skip to final position/opacity

	virtual void update(sf::Time dt);

private:

private:
	// string is for states
	std::map<std::string, const sf::Texture&> nTextureMap;
};

#endif

