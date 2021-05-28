#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Engine.hpp"
#include "CommandManager.hpp"

#include "TextButton.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <unordered_map>

class GameState : public State
{
public:
	using CommandPtr = std::unique_ptr<Command>;

	using BtnItr = std::vector<GUI::Component*>::const_iterator;

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

	/*
		@decision making
	*/
public:
	void setDecisionState();
	void addDecisionButton(const std::string& text, const std::string& targetLabel);
	
private:
	static constexpr auto DecisionX = 300;
	static constexpr auto DecisionStartY = 200;
	static constexpr auto DecisionDist = 100;

	std::vector<std::unique_ptr<GUI::TextButton>> nDecisionBtns;
	void clearDecisions();
	bool nInDecision;
	

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

