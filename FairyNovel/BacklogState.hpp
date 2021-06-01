#ifndef BACKLOGSTATE_HPP
#define BACKLOGSTATE_HPP

#include "State.hpp"
#include "Engine.hpp"
#include "CommandManager.hpp"
#include "TextButton.hpp"
#include "BacklogPanel.hpp"
#include "Components.hpp"

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

	void updateBacklog(int delta);		
	void setUpdateState(UpdateState state) override;

private:
	void packComponent(GUI::Component* cmp);
	void setBacklogText(Command& command, GUI::BacklogPanel& backlog);

private:
	static constexpr auto PanelX = 300.f;
	static constexpr auto PanelY = 500.f;
	static constexpr auto PanelDist = 150.f;
	static constexpr auto Count = 4;
	static constexpr auto FontSize = 25;
	static constexpr auto TitleLabelX = 1200.f;
	static constexpr auto TitleLabelY = 680.f;

	static constexpr auto FadeTime = 1.f;

	/*
		GUI
	*/
	GUI::Label nSectionLabel;
	GUI::TextButton nExitButton;

	std::vector<GUI::BacklogPanel> nBacklogs;
	std::vector<GUI::Component*> nComponents;

	sf::RectangleShape nBackground;
	FadableRectShape nFadableBg;
	sf::Sprite nSprite;
	FadableSprite nFadableSprite;
	
	CommandItr nIP;
	std::vector<Command*>& nDisplayCommands;
};

#endif

