#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Engine.hpp"
#include "CommandManager.hpp"

#include "TextButton.hpp"

#include <SFML/Graphics/Sprite.hpp>

class GameState : public State
{
public:
	using CommandPtr = std::unique_ptr<Command>;

public:
	GameState(StateStack& stack, Context context);
	~GameState() override;

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	void refresh() override;

private:
	void setButton(GUI::TextButton& btn);
	void packComponent(GUI::Component* cmp);

private:
	static constexpr auto ButtonsY = 710;
	static constexpr auto ButtonsDist = 40;
	static constexpr auto ButtonsStartY = 1100;
	/*
		GUI
	*/
	GUI::TextButton nConfigBtn;
	GUI::TextButton nBacklogBtn;
	GUI::TextButton nAutoModeBtn;
	GUI::TextButton nExitBtn;

	std::vector<GUI::Component*> nComponents;
	
	sf::Sprite nBackgroundSprite;

	Engine nEngine;
	CommandManager& nCommandManager;

};

#endif

