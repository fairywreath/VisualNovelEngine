#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include "CharacterBlueprint.hpp"

#include <unordered_map>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

class Character : public sf::Drawable, public sf::Transformable
{
public:
	explicit Character(CharacterBlueprint& blueprint);
	~Character() = default;

	void update(sf::Time dt);

	std::string getIdentifier() const;

	bool inAnimation() const;
	void skipAnimation();		

	// maybe change later for better implementation
	Entity* getEntity();

	bool setState(const std::string& id);
	bool setState(const std::string& id, float transitionTime);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// change to reference later
	CharacterBlueprint nBlueprint;


	Entity nEntity;
	Entity nSecondaryEntity;

	std::string nCurrentState;
	sf::Time nTransitionElapsed;
	float nTransitionTime;
	bool nInTransition;
};

#endif

