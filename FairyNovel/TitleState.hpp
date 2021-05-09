#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "SpriteButton.hpp"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	// virtual functions for drawing, updating and handling events
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Sprite nBackgroundSprite;		
	sf::Text nText;
	bool nShowText;					
	sf::Time nTextEffectTime;

	GUI::SpriteButton button1;
	GUI::SpriteButton button2;
};

#endif

