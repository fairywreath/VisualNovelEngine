#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Engine.hpp"

#include <SFML/Graphics/Sprite.hpp>

class GameState : public State
{
public:
	typedef std::unique_ptr<Command> CommandPtr;

public:
	GameState(StateStack& stack, Context context);

	// virtual functions for drawing, updating and handling events
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void refresh() override;

private:
	sf::Sprite nBackgroundSprite;

	std::vector<CommandPtr>& nCommands;
	std::vector<CommandPtr>::const_iterator nIP;		// instruction pointer
	std::unordered_map<std::string, std::vector<CommandPtr>::const_iterator>& nCommandLabels;

	// engine
	Engine nEngine;
	
	
	// characters and commands
};

#endif

