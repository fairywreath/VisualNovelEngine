#ifndef BACKLOGSTATE_HPP
#define BACKLOGSTATE_HPP

#include "State.hpp"
#include "Engine.hpp"
#include "CommandManager.hpp"
#include "TextButton.hpp"
#include "BacklogPanel.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <deque>

class BacklogState : public State
{
public:
	using CommandPtr =  std::unique_ptr<Command>;
	using CommandItr = std::vector<Command*>::const_reverse_iterator;

public:
	BacklogState(StateStack& stack, Context context);
	~BacklogState() override;

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	void refresh() override;

private:
	void packComponent(GUI::Component* cmp);
	void setBacklogText(Command& command, GUI::BacklogPanel& backlog);

	void updateBacklogs();

private:
	static constexpr auto PanelX = 300.f;
	static constexpr auto PanelY = 300.f;
	static constexpr auto PanelDist = 100.f;
	static constexpr auto Count = 3;

	/*
		GUI
	*/
	std::vector<GUI::BacklogPanel> nBacklogs;
	std::vector<GUI::Component*> nComponents;
	
	CommandItr nIP;
	std::vector<Command*>& nDisplayCommands;
};

#endif

