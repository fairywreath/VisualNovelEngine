#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	// virtual functions for drawing, updating and handling events
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	// engine
	// characters and commands
};

#endif

