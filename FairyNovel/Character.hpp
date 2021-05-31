#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include "CharacterBlueprint.hpp"

#include <unordered_map>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

class Character : public sf::Drawable
{
public:
	explicit Character(const CharacterBlueprint& blueprint);
	~Character() = default;

	void update(sf::Time dt);

	/*
		@ only different with entity for movement
	*/
	void move(float time, const sf::Vector2f& target, const sf::Vector2f& source);
	
	void setPosition(const sf::Vector2f& pos);

	std::string getIdentifier() const;

	bool inAnimation() const;
	void skipAnimation();		

	// maybe change later for better implementation
	Entity* getEntity();

	bool setState(const std::string& id) noexcept;
	bool setState(const std::string& id, float transitionTime) noexcept;

	void stopTransition();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// change to reference later
	const CharacterBlueprint& nBlueprint;

	Entity nEntity;
	Entity nSecondaryEntity;

	std::string nCurrentState;
	sf::Time nTransitionElapsed;
	float nTransitionTime;
	bool nInTransition;

};

#endif

