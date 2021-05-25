#include "BacklogState.hpp"
#include "Utility.hpp"

#include <iostream>

BacklogState::BacklogState(StateStack& stack, Context context) :
	State(stack, context),
	nDisplayCommands(context.commandManager->getBacklogCommands()),
	nBacklogs(Count)
{
	nIP = nDisplayCommands.crbegin();
	
	for (auto& bl : nBacklogs)
	{
		bl.setFont(context.fonts->get("overlock"));
	}

	for (int i = 0; (i < Count) && nIP != nDisplayCommands.crend(); nIP++, i++)
	{
		setBacklogText(**nIP, nBacklogs[i]);
		nBacklogs[i].setPosition(PanelX, PanelY + ((float)Count - (float)(i * PanelDist)));
	}


	for (auto& bl : nBacklogs) packComponent(&bl);
}

BacklogState::~BacklogState()
{
}

void BacklogState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	for (const auto& cmp : nComponents) window.draw(*cmp);
}

bool BacklogState::update(sf::Time dt)
{
	for (const auto& cmp : nComponents) cmp->update(dt);


	return false;
}

bool BacklogState::handleEvent(const sf::Event& event)
{
	for (const auto& cmp : nComponents) cmp->handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	return false;
}

void BacklogState::refresh()
{
}

void BacklogState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}

/*
	@specifically for display text commands
*/
void BacklogState::setBacklogText(Command& command, GUI::BacklogPanel& backlog)
{
	backlog.setIdentifier(command.getIdentifier());
	backlog.setText(command.getArgumentString());
}

void BacklogState::updateBacklogs()
{

}
