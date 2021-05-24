#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Engine.hpp"
#include "CommandManager.hpp"

#include <SFML/Graphics/Sprite.hpp>

class GameState : public State
{
public:
	typedef std::unique_ptr<Command> CommandPtr;

public:
	GameState(StateStack& stack, Context context);
	~GameState() override;

	// virtual functions for drawing, updating and handling events
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void refresh() override;

private:
	sf::Sprite nBackgroundSprite;

	Engine nEngine;
	CommandManager& nCommandManager;

};

#endif

